//
// Created by sziraqui on 3/6/19.
//
#include <opencv/cv.h>
#include <vector>
#include <string>

#include "ImageCapture.h"
#include "../jserrors/JSErrors.h"

Napi::FunctionReference Nodoface::ImageCapture::constructor;

Napi::Object Nodoface::ImageCapture::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "ImageCapture", {
        InstanceMethod("getProgress", &Nodoface::ImageCapture::GetProgress),
        InstanceMethod("getImageWidth", &Nodoface::ImageCapture::GetImageHeight),
        InstanceMethod("setImageHeight", &Nodoface::ImageCapture::SetImageHeight),
        InstanceMethod("getImageWidth", &Nodoface::ImageCapture::GetImageWidth),
        InstanceMethod("setImageHeight", &Nodoface::ImageCapture::SetImageHeight),
        InstanceMethod("getFx", &Nodoface::ImageCapture::GetFx),
        InstanceMethod("setFx", &Nodoface::ImageCapture::SetFx),
        InstanceMethod("getFy", &Nodoface::ImageCapture::GetFy),
        InstanceMethod("setFy", &Nodoface::ImageCapture::SetFy),
        InstanceMethod("getCx", &Nodoface::ImageCapture::GetCx),
        InstanceMethod("setCx", &Nodoface::ImageCapture::SetCx),
        InstanceMethod("getCy", &Nodoface::ImageCapture::GetCy),
        InstanceMethod("setCy", &Nodoface::ImageCapture::SetCy)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("ImageCapture", func);
    return exports;
}

Nodoface::ImageCapture::ImageCapture(const Napi::CallbackInfo &info) : Napi::ObjectWrap<Nodoface::ImageCapture>(info) {
    if(info.Length() != 0) {
        JSErrors::TooManyArguments(info.Env(), 0, info.Length());
    }
    this->imageCapture = new Utilities::ImageCapture();
}

// js-args: String[] imageFileList, number fx?, number fy?, number cx?, number cy?
Napi::Value Nodoface::ImageCapture::OpenImageFiles(const Napi::CallbackInfo &info) {
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

Napi::Value Nodoface::ImageCapture::GetNextImage(const Napi::CallbackInfo &info) {
    cv::Mat img = this->imageCapture->GetNextImage();
    // TODO: handle cv Mat of multi channels
}

Napi::Value Nodoface::ImageCapture::GetGrayFrame(const Napi::CallbackInfo &info) {
    cv::Mat_<uchar> frame = this->imageCapture->GetGrayFrame();
    // TODO: handle cv Mat of single channel
}

Napi::Value Nodoface::ImageCapture::GetBoundingBoxes(const Napi::CallbackInfo &info) {
    std::vector<cv::Rect_<float> > bboxes = this->imageCapture->GetBoundingBoxes();
    // TODO: handle cv Rect
}

Napi::Value Nodoface::ImageCapture::GetProgress(const Napi::CallbackInfo &info) {
    double progress = this->imageCapture->GetProgress();
    return Napi::Number::New(info.Env(), progress);
}

// GetSet for public variables
// int image_width;
Napi::Value Nodoface::ImageCapture::GetImageWidth(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->imageCapture->image_width);
}

Napi::Value Nodoface::ImageCapture::SetImageWidth(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() != 1 || !info[0].IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = info[0].As<Napi::Number>();
    this->imageCapture->image_width = num.DoubleValue();
    return Napi::Boolean::New(env, true);
}

// int image_height
Napi::Value Nodoface::ImageCapture::GetImageHeight(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->imageCapture->image_height);
}

Napi::Value Nodoface::ImageCapture::SetImageHeight(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() != 1 || !info[0].IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = info[0].As<Napi::Number>();
    this->imageCapture->image_height = num.DoubleValue();
    return Napi::Boolean::New(env, true);
}

// float fx, fy, cx, cy;
Napi::Value Nodoface::ImageCapture::GetFx(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->imageCapture->fx);
}

Napi::Value Nodoface::ImageCapture::GetFy(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->imageCapture->fy);
}

Napi::Value Nodoface::ImageCapture::GetCx(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->imageCapture->cx);
}

Napi::Value Nodoface::ImageCapture::GetCy(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->imageCapture->cy);
}

Napi::Value Nodoface::ImageCapture::SetFx(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() != 1 || !info[0].IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = info[0].As<Napi::Number>();
    this->imageCapture->fx = num.DoubleValue();
    return Napi::Boolean::New(env, true);
}

Napi::Value Nodoface::ImageCapture::SetFy(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() != 1 || !info[0].IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = info[0].As<Napi::Number>();
    this->imageCapture->fy = num.DoubleValue();
    return Napi::Boolean::New(env, true);
}

Napi::Value Nodoface::ImageCapture::SetCx(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() != 1 || !info[0].IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = info[0].As<Napi::Number>();
    this->imageCapture->cx = num.DoubleValue();
    return Napi::Boolean::New(env, true);
}

Napi::Value Nodoface::ImageCapture::SetCy(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() != 1 || !info[0].IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = info[0].As<Napi::Number>();
    this->imageCapture->cy = num.DoubleValue();
    return Napi::Boolean::New(env, true);
}
