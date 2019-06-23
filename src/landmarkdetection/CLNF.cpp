//
// Created by sziraqui on 22/6/19.
//

#include "CLNF.h"
#include "FaceModelParameters.h"
#include "../cvtypes/MatFloat.h"
#include "../cvtypes/MatInt.h"


Napi::FunctionReference Nodoface::CLNF::constructor;

Napi::Object Nodoface::CLNF::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function ctor = DefineClass(env, "CLNF", {
        InstanceMethod("detectLandmarks", &Nodoface::CLNF::DetectLandmarks),
        InstanceMethod("getShape", &Nodoface::CLNF::GetShape),
        InstanceMethod("getVisibilities", &Nodoface::CLNF::GetVisibilities),
        InstanceMethod("getBoundingBox", &Nodoface::CLNF::GetBoundingBox),
        InstanceMethod("reset", &Nodoface::CLNF::Reset),
        InstanceMethod("read", &Nodoface::CLNF::Read)
    });
    constructor = Napi::Persistent(ctor);
    constructor.SuppressDestruct();
    exports.Set("CLNF", ctor);
    return exports;
}

Napi::Object Nodoface::CLNF::NewObject(Napi::Env env, std::string& modelLocation) {
    Napi::String location = NapiExtra::toNapi(env, modelLocation);
    return constructor.New({ location });
}

Nodoface::CLNF::CLNF(const Napi::CallbackInfo & info) : Napi::ObjectWrap<CLNF>(info) {
    Napi::Env env = info.Env();
    if(info.Length() > 1) {
        JSErrors::TooManyArguments(env, 1, info.Length());
    }
    if(info.Length() == 1) {
        std::string location = info[0].As<Napi::String>().Utf8Value();
        this->instance = new LandmarkDetector::CLNF(location);
    }  else {
        this->instance = new LandmarkDetector::CLNF();
    }
}

Napi::Value Nodoface::CLNF::DetectLandmarks(const Napi::CallbackInfo & info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    if(info.Length() < 2) {
        JSErrors::InsufficientArguments(env, 2, info.Length());
    } else if(info.Length() > 2) {
        JSErrors::TooManyArguments(env, 2, info.Length());
    } else if (!info[0].IsObject() || !info[1].IsObject()) {
        JSErrors::IncorrectDatatype(env, JSErrors::OBJECT + "(Image, FaceModelParameters)");
    }
    Nodoface::Image* image = Nodoface::Image::Unwrap(info[0].As<Napi::Object>());
    cv::Mat_<uchar> mat = image->GetMat();

    Nodoface::LandmarkModelConfig* params = Nodoface::LandmarkModelConfig::Unwrap(info[1].As<Napi::Object>());
    LandmarkDetector::FaceModelParameters modelParameters = params->GetInternalInstance();

    bool result = this->instance->DetectLandmarks(mat, modelParameters);

    return NapiExtra::toNapi(env, result);
}

Napi::Value Nodoface::CLNF::GetShape(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() < 4) {
        JSErrors::InsufficientArguments(env, 4, info.Length());
    } else if(info.Length() > 4) {
        JSErrors::TooManyArguments(env, 4, info.Length());
    } else {
        for (uint i = 0; i < info.Length(); i++) {
            if (!info[i].IsNumber()) {
                JSErrors::IncorrectDatatype(env, JSErrors::NUMBER, i);
            }
        }
    }
    float fx = info[0].As<Napi::Number>().FloatValue();
    float fy = info[1].As<Napi::Number>().FloatValue();
    float cx = info[2].As<Napi::Number>().FloatValue();
    float cy = info[3].As<Napi::Number>().FloatValue();

    cv::Mat_<float> mat = this->instance->GetShape(fx, fy, cx, cy);
    return Nodoface::FloatImage::NewObject(env, mat);
}

Napi::Value Nodoface::CLNF::GetBoundingBox(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() !=0 ) {
        JSErrors::TooManyArguments(env, 0, info.Length());
    }
    cv::Rect_<float> rect = this->instance->GetBoundingBox();
    return NapiExtra::cv2Napi(env, rect);
}

Napi::Value Nodoface::CLNF::GetVisibilities(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() !=0 ) {
        JSErrors::TooManyArguments(env, 0, info.Length());
    }
    cv::Mat_<int> mat = this->instance->GetVisibilities();
    return Nodoface::IntImage::NewObject(env, mat);
}

Napi::Value Nodoface::CLNF::Reset(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    uint argLen = info.Length();

    if(argLen == 0) {
        this->instance->Reset();
        return env.Undefined();
    } else if(argLen == 1) {
        JSErrors::InsufficientArguments(env, 2, 1);
    } else if (argLen == 2) {
        for (uint i = 0; i < argLen; i++) {
            if (!info[i].IsNumber()) {
                JSErrors::IncorrectDatatype(env, JSErrors::NUMBER, i);
            }
        }
        double x = info[0].As<Napi::Number>().DoubleValue();
        double y = info[1].As<Napi::Number>().DoubleValue();
        this->instance->Reset(x, y);
        return env.Undefined();
    } else {
        JSErrors::TooManyArguments(env, 2, argLen);
    }
}

Napi::Value Nodoface::CLNF::Read(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() == 0) {
        JSErrors::InsufficientArguments(env, 1, 0);
    } else if(info.Length() > 1) {
        JSErrors::TooManyArguments(env, 1, info.Length());
    }
    if(info.Length() == 1) {
        std::string location = info[0].As<Napi::String>().Utf8Value();
        this->instance->Read(location);
    }
    return env.Undefined();
}