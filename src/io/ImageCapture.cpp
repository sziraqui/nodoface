//
// Created by sziraqui on 3/6/19.
//
#include <opencv/cv.h>
#include <vector>
#include <string>

#include "ImageCapture.h"
#include "../jserrors/JSErrors.h"
#include "../extratypes/napiextratypes.h";

// js-args: String[] imageFileList, number fx?, number fy?, number cx?, number cy?
Napi::Boolean Nodoface::ImageCapture::OpenImageFiles(const Napi::CallbackInfo &info) {
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
    NapiExtra::StringArray imageFileList = info[0].As<NapiExtra::StringArray>();
    // TODO: Convert to vector and call native method

}

Napi::Uint8Array Nodoface::ImageCapture::GetNextImage(const Napi::CallbackInfo &info) {
    cv::Mat img = this->imageCapture->GetNextImage();
    // TODO: handle cv Mat of multi channels
}

Napi::Uint8Array Nodoface::ImageCapture::GetGrayFrame(const Napi::CallbackInfo &info) {
    cv::Mat_<uchar> frame = this->imageCapture->GetGrayFrame();
    // TODO: handle cv Mat of single channel
}

Napi::TypedArray Nodoface::ImageCapture::GetBoundingBoxes(const Napi::CallbackInfo &info) {
    std::vector<cv::Rect_<float> > bboxes = this->imageCapture->GetBoundingBoxes();
    // TODO: handle cv Rect
}

Napi::Number Nodoface::ImageCapture::GetProgress(const Napi::CallbackInfo &info) {
    double progress = this->imageCapture->GetProgress();
    return Napi::Number::New(info.Env(), progress);
}

// GetSet for public variables
// int image_width;
Napi::Number Nodoface::ImageCapture::GetImageWidth(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->imageCapture->image_width);
}

Napi::Boolean Nodoface::ImageCapture::SetImageWidth(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() != 1 || !info[0].IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = info[0].As<Napi::Number>();
    this->imageCapture->image_width = num.DoubleValue();
    return Napi::Boolean::New(env, true);
}

// int image_height
Napi::Number Nodoface::ImageCapture::GetImageHeight(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->imageCapture->image_height);
}

Napi::Boolean Nodoface::ImageCapture::SetImageHeight(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() != 1 || !info[0].IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = info[0].As<Napi::Number>();
    this->imageCapture->image_height = num.DoubleValue();
    return Napi::Boolean::New(env, true);
}

// float fx, fy, cx, cy;
Napi::Number Nodoface::ImageCapture::GetFx(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->imageCapture->fx);
}

Napi::Number Nodoface::ImageCapture::GetFy(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->imageCapture->fy);
}

Napi::Number Nodoface::ImageCapture::GetCx(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->imageCapture->cx);
}

Napi::Number Nodoface::ImageCapture::GetCy(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->imageCapture->cy);
}

Napi::Boolean Nodoface::ImageCapture::SetFx(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() != 1 || !info[0].IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = info[0].As<Napi::Number>();
    this->imageCapture->fx = num.DoubleValue();
    return Napi::Boolean::New(env, true);
}

Napi::Boolean Nodoface::ImageCapture::SetFy(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() != 1 || !info[0].IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = info[0].As<Napi::Number>();
    this->imageCapture->fy = num.DoubleValue();
    return Napi::Boolean::New(env, true);
}

Napi::Boolean Nodoface::ImageCapture::SetCx(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() != 1 || !info[0].IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = info[0].As<Napi::Number>();
    this->imageCapture->cx = num.DoubleValue();
    return Napi::Boolean::New(env, true);
}

Napi::Boolean Nodoface::ImageCapture::SetCy(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() != 1 || !info[0].IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = info[0].As<Napi::Number>();
    this->imageCapture->cy = num.DoubleValue();
    return Napi::Boolean::New(env, true);
}