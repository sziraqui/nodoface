//
// Created by sziraqui on 23/6/19.
//

#include "GazeAnalyser.h"

Napi::FunctionReference Nodoface::GazeAnalyser::constructor;

Napi::Object Nodoface::GazeAnalyser::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    auto func = DefineClass(env, "GazeAnalyser", {
            InstanceMethod("estimateGaze", &Nodoface::GazeAnalyser::EstimateGaze),
            InstanceMethod("getGazeAngle", &Nodoface::GazeAnalyser::GetGazeAngle),
            InstanceMethod("getPupilPosition", &Nodoface::GazeAnalyser::GetPupilPosition)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("GazeAnalyser", func);
    return exports;
}

Napi::Object Nodoface::GazeAnalyser::NewObject() {
    Napi::Object modelObj = constructor.New({});
    return modelObj;
}

Nodoface::GazeAnalyser::GazeAnalyser(const Napi::CallbackInfo &info) : Napi::ObjectWrap<Nodoface::GazeAnalyser>(info) {
    if (info.Length() != 0) {
        JSErrors::TooManyArguments(info.Env(), 0, info.Length());
    }
}

Napi::Value Nodoface::GazeAnalyser::EstimateGaze(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    uint argLen = info.Length();

    if (argLen < 6) {
        JSErrors::InsufficientArguments(env, 6, argLen);
    } else if (argLen > 6) {
        JSErrors::TooManyArguments(env, 6, argLen);
    }

    LandmarkDetector::CLNF clnfModel;
    float fx = 0, fy = 0, cx = 0, cy = 0;
    bool leftEye = false;
    int i = 0;
    if (info[i].IsObject()) {
        Nodoface::CLNF *clnf = Nodoface::CLNF::Unwrap(info[i].As<Napi::Object>());
        clnfModel = clnf->GetInternalInstance();
    } else {
        JSErrors::IncorrectDatatype(env, JSErrors::OBJECT, i);
    }
    i++;
    if (info[i].IsNumber()) {
        fx = info[i].As<Napi::Number>().FloatValue();
    } else {
        JSErrors::IncorrectDatatype(env, JSErrors::NUMBER, i);
    }
    i++;
    if (info[i].IsNumber()) {
        fy = info[i].As<Napi::Number>().FloatValue();
    } else {
        JSErrors::IncorrectDatatype(env, JSErrors::NUMBER, i);
    }
    i++;
    if (info[i].IsNumber()) {
        cx = info[i].As<Napi::Number>().FloatValue();
    } else {
        JSErrors::IncorrectDatatype(env, JSErrors::NUMBER, i);
    }
    i++;
    if (info[i].IsNumber()) {
        cy = info[i].As<Napi::Number>().FloatValue();
    } else {
        JSErrors::IncorrectDatatype(env, JSErrors::NUMBER, i);
    }
    i++;
    if (info[i].IsBoolean()) {
        leftEye = info[i].As<Napi::Number>().FloatValue();
    } else {
        JSErrors::IncorrectDatatype(env, JSErrors::NUMBER, i);
    }
    cv::Point3f gazeAbsolute;
    GazeAnalysis::EstimateGaze(clnfModel, gazeAbsolute, fx, fy, cx, cy, leftEye);
    return NapiExtra::cv2Napi(env, gazeAbsolute);
}

Napi::Value Nodoface::GazeAnalyser::GetGazeAngle(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    uint argLen = info.Length();

    if (argLen < 2) {
        JSErrors::InsufficientArguments(env, 2, argLen);
    } else if (argLen > 2) {
        JSErrors::TooManyArguments(env, 2, argLen);
    }
    for (uint i = 0; i < argLen; i++) {
        if (!info[i].IsObject()) {
            JSErrors::IncorrectDatatype(env, JSErrors::OBJECT, i);
        }
    }
    cv::Point3_<float> gazeVec1 = NapiExtra::Napi2Point3<float>(info[0].As<Napi::Object>());
    cv::Point3_<float> gazeVec2 = NapiExtra::Napi2Point3<float>(info[1].As<Napi::Object>());

    cv::Vec2f result = GazeAnalysis::GetGazeAngle(gazeVec1, gazeVec2);
    Napi::Array arr = Napi::Array::New(env, 2);
    arr.Set(0u, NapiExtra::toNapi(env, result[0]));
    arr.Set(1u, NapiExtra::toNapi(env, result[1]));
    return arr;
}

Napi::Value Nodoface::GazeAnalyser::GetPupilPosition(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    uint argLen = info.Length();

    if (argLen < 1) {
        JSErrors::InsufficientArguments(env, 1, argLen);
    } else if (!info[0].IsObject()) {
        JSErrors::IncorrectDatatype(env, JSErrors::OBJECT, 0);
    }
    Nodoface::FloatImage *floatImage = Nodoface::FloatImage::Unwrap(info[0].As<Napi::Object>());
    cv::Mat_<float> eyeLandmarks = floatImage->GetMat();

    cv::Point3_<float> result = GazeAnalysis::GetPupilPosition(eyeLandmarks);
    return NapiExtra::cv2Napi<float>(env, result);
}