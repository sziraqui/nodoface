//
// Created by sziraqui on 7/6/19.
//

#include "SequenceCapture.h"
#include <opencv/cv.h>
#include <vector>
#include <string>

#include "SequenceCapture.h"
#include "../jserrors/JSErrors.h"

Napi::FunctionReference Nodoface::SequenceCapture::constructor;

Napi::Object Nodoface::SequenceCapture::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "SequenceCapture", {
            InstanceMethod("getProgress", &Nodoface::SequenceCapture::GetProgress),
            InstanceMethod("getImageWidth", &Nodoface::SequenceCapture::GetFrameHeight),
            InstanceMethod("setImageHeight", &Nodoface::SequenceCapture::SetFrameHeight),
            InstanceMethod("getImageWidth", &Nodoface::SequenceCapture::GetFrameWidth),
            InstanceMethod("setImageHeight", &Nodoface::SequenceCapture::SetFrameHeight),
            InstanceMethod("getFx", &Nodoface::SequenceCapture::GetFx),
            InstanceMethod("setFx", &Nodoface::SequenceCapture::SetFx),
            InstanceMethod("getFy", &Nodoface::SequenceCapture::GetFy),
            InstanceMethod("setFy", &Nodoface::SequenceCapture::SetFy),
            InstanceMethod("getCx", &Nodoface::SequenceCapture::GetCx),
            InstanceMethod("setCx", &Nodoface::SequenceCapture::SetCx),
            InstanceMethod("getCy", &Nodoface::SequenceCapture::GetCy),
            InstanceMethod("setCy", &Nodoface::SequenceCapture::SetCy)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("SequenceCapture", func);
    return exports;
}

Nodoface::SequenceCapture::SequenceCapture(const Napi::CallbackInfo &info) : Napi::ObjectWrap<Nodoface::SequenceCapture>(info) {
    if(info.Length() != 0) {
        JSErrors::TooManyArguments(info.Env(), 0, info.Length());
    }
    this->sequenceCapture = new Utilities::SequenceCapture();
}

// js-args: String[] imageFileList, number fx?, number fy?, number cx?, number cy?
Napi::Value Nodoface::SequenceCapture::OpenImageSequence(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    size_t argLen = info.Length();
    if (argLen == 0) {
        // throw insufficient arguments error
    } else if (argLen >= 1 && !info[0].IsArray()) {
        // throw String array expected at argument 0
    } else if(argLen) {
        for (int i = 1; i < argLen; ++i) {
            if (!info[i].IsNumber()) {
                // throw Number Expected at argument i
            }
        }
    }
    const Napi::Array imageFileList = info[0].As<Napi::Array>();
    // TODO: Convert to vector and call native method

}

Napi::Value Nodoface::SequenceCapture::GetNextFrame(const Napi::CallbackInfo &info) {
    cv::Mat img = this->sequenceCapture->GetNextFrame();
    // TODO: handle cv Mat of multi channels
}

Napi::Value Nodoface::SequenceCapture::GetGrayFrame(const Napi::CallbackInfo &info) {
    cv::Mat_<uchar> frame = this->sequenceCapture->GetGrayFrame();
    // TODO: handle cv Mat of single channel
}


Napi::Value Nodoface::SequenceCapture::GetProgress(const Napi::CallbackInfo &info) {
    double progress = this->sequenceCapture->GetProgress();
    return Napi::Number::New(info.Env(), progress);
}

// GetSet for public variables
// int image_width;
Napi::Value Nodoface::SequenceCapture::GetFrameWidth(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->sequenceCapture->frame_width);
}

Napi::Value Nodoface::SequenceCapture::SetFrameWidth(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() != 1 || !info[0].IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = info[0].As<Napi::Number>();
    this->sequenceCapture->frame_width = num.DoubleValue();
    return Napi::Boolean::New(env, true);
}

// int image_height
Napi::Value Nodoface::SequenceCapture::GetFrameHeight(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->sequenceCapture->frame_height);
}

Napi::Value Nodoface::SequenceCapture::SetFrameHeight(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() != 1 || !info[0].IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = info[0].As<Napi::Number>();
    this->sequenceCapture->frame_height = num.DoubleValue();
    return Napi::Boolean::New(env, true);
}

// float fx, fy, cx, cy;
Napi::Value Nodoface::SequenceCapture::GetFx(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->sequenceCapture->fx);
}

Napi::Value Nodoface::SequenceCapture::GetFy(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->sequenceCapture->fy);
}

Napi::Value Nodoface::SequenceCapture::GetCx(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->sequenceCapture->cx);
}

Napi::Value Nodoface::SequenceCapture::GetCy(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->sequenceCapture->cy);
}

Napi::Value Nodoface::SequenceCapture::SetFx(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() != 1 || !info[0].IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = info[0].As<Napi::Number>();
    this->sequenceCapture->fx = num.DoubleValue();
    return Napi::Boolean::New(env, true);
}

Napi::Value Nodoface::SequenceCapture::SetFy(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() != 1 || !info[0].IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = info[0].As<Napi::Number>();
    this->sequenceCapture->fy = num.DoubleValue();
    return Napi::Boolean::New(env, true);
}

Napi::Value Nodoface::SequenceCapture::SetCx(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() != 1 || !info[0].IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = info[0].As<Napi::Number>();
    this->sequenceCapture->cx = num.DoubleValue();
    return Napi::Boolean::New(env, true);
}

Napi::Value Nodoface::SequenceCapture::SetCy(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() != 1 || !info[0].IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = info[0].As<Napi::Number>();
    this->sequenceCapture->cy = num.DoubleValue();
    return Napi::Boolean::New(env, true);
}