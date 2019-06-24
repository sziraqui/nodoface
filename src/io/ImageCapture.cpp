//
// Created by sziraqui on 3/6/19.
//
#include "ImageCapture.h"

Napi::FunctionReference Nodoface::ImageCapture::constructor;

Napi::Object Nodoface::ImageCapture::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "ImageCapture", {
        InstanceMethod("open", &Nodoface::ImageCapture::Open),
        InstanceMethod("openDirectory", &Nodoface::ImageCapture::OpenDirectory),
        InstanceMethod("openImageFiles", &Nodoface::ImageCapture::OpenImageFiles),
        InstanceMethod("getNextImage", &Nodoface::ImageCapture::GetNextImage),
        InstanceMethod("getGrayFrame", &Nodoface::ImageCapture::GetGrayFrame),
        InstanceMethod("getProgress", &Nodoface::ImageCapture::GetProgress),
        InstanceMethod("getBoundingBoxes", &Nodoface::ImageCapture::GetBoundingBoxes),
        InstanceMethod("getImageHeight", &Nodoface::ImageCapture::GetImageHeight),
        InstanceMethod("setImageHeight", &Nodoface::ImageCapture::SetImageHeight),
        InstanceMethod("getImageWidth", &Nodoface::ImageCapture::GetImageWidth),
        InstanceMethod("setImageWidth", &Nodoface::ImageCapture::SetImageWidth),
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

Napi::Value Nodoface::ImageCapture::Open(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    size_t argLen = info.Length();
    if (argLen == 0) {
        JSErrors::InsufficientArguments(env, 1, argLen);
    } else if (argLen >= 1 && !info[0].IsArray()) {
        JSErrors::IncorrectDatatype(env, JSErrors::ARRAY, 0);
    }

    const Napi::Array arguments = info[0].As<Napi::Array>();
    std::vector<std::string> vecList(arguments.Length());
    for(uint i = 0; i < arguments.Length(); ++i) {

        std::string s = arguments[i].As<Napi::String>().Utf8Value();
        vecList[i] = s;
    }
    bool result = this->imageCapture->Open(vecList);
    return NapiExtra::toNapi(env, result);
}

Napi::Value Nodoface::ImageCapture::OpenDirectory(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    size_t argLen = info.Length();

    std::string imgDir;
    std::string bboxDir = "";
    if (argLen < 1u) {
        JSErrors::InsufficientArguments(env, 2u, argLen);
    } else if(!info[0].IsString()) {
        JSErrors::IncorrectDatatype(env, JSErrors::STRING, 0);
    } else if(argLen < 2u || !info[1].IsString()) {
        JSErrors::IncorrectDatatype(env, JSErrors::STRING, 1);
    } else {
        bboxDir = info[1].As<Napi::String>().Utf8Value();
    }
    imgDir = info[0].As<Napi::String>().Utf8Value();
    uint8_t i = 2;
    float fx = argLen > i && info[i].IsNumber()? info[i].As<Napi::Number>().FloatValue() : -1; i++;
    float fy = argLen > i && info[i].IsNumber()? info[i].As<Napi::Number>().FloatValue() : -1; i++;
    float cx = argLen > i && info[i].IsNumber()? info[i].As<Napi::Number>().FloatValue() : -1; i++;
    float cy = argLen > i && info[i].IsNumber()? info[i].As<Napi::Number>().FloatValue() : -1;

    bool result = this->imageCapture->OpenDirectory(imgDir, bboxDir, fx, fy, cx, cy);
    return NapiExtra::toNapi(env, result);
}

// js-args: String[] imageFileList, number fx?, number fy?, number cx?, number cy? // ensure defaults exist
Napi::Value Nodoface::ImageCapture::OpenImageFiles(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    size_t argLen = info.Length();
    if (argLen == 0) {
        JSErrors::InsufficientArguments(env, 1, argLen);
    } else if (argLen >= 1 && !info[0].IsArray()) {
        JSErrors::IncorrectDatatype(env, JSErrors::ARRAY, 0);
    }
    // Converting js values to c++ types
    float fx, fy, cx, cy;
    fx = info[1].As<Napi::Number>().FloatValue();
    fy = info[2].As<Napi::Number>().FloatValue();
    cx = info[3].As<Napi::Number>().FloatValue();
    cy = info[4].As<Napi::Number>().FloatValue();

    const Napi::Array arguments = info[0].As<Napi::Array>();
    std::vector<std::string> vecList(arguments.Length());
    for(uint i = 0; i < arguments.Length(); ++i) {

        std::string s = arguments[i].As<Napi::String>().Utf8Value();
        vecList[i] = s;
    }
    // call native method
    bool result = this->imageCapture->OpenImageFiles(vecList, fx, fy, cx, cy);
    return NapiExtra::toNapi(env, result);
}

Napi::Value Nodoface::ImageCapture::GetNextImage(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::EscapableHandleScope scope(env);
    cv::Mat mat = this->imageCapture->GetNextImage();
    Napi::Object imgObj = Nodoface::Image::NewObject(env, mat).As<Napi::Object>();
    return scope.Escape(imgObj);
}

Napi::Value Nodoface::ImageCapture::GetGrayFrame(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::EscapableHandleScope scope(env);
    cv::Mat frame = this->imageCapture->GetGrayFrame();
    Napi::Object imgObj = Nodoface::Image::NewObject(env, frame).As<Napi::Object>();
    return scope.Escape(imgObj);
}

Napi::Value Nodoface::ImageCapture::GetBoundingBoxes(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    std::vector<cv::Rect_<float>> bboxes = this->imageCapture->GetBoundingBoxes();
    Napi::Array array = NapiExtra::cv2NapiArray<cv::Rect_<float>>(env, bboxes);
    return array;
}

Napi::Value Nodoface::ImageCapture::GetProgress(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    double progress = this->imageCapture->GetProgress();
    return NapiExtra::toNapi(env, progress);
}

// GetSet for public variables
// int image_width;
Napi::Value Nodoface::ImageCapture::GetImageWidth(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    return NapiExtra::toNapi(env, this->imageCapture->image_width);
}

Napi::Value Nodoface::ImageCapture::SetImageWidth(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() != 1 || !info[0].IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = info[0].As<Napi::Number>();
    this->imageCapture->image_width = num.DoubleValue();
    return NapiExtra::toNapi(env, true);
}

// int image_height
Napi::Value Nodoface::ImageCapture::GetImageHeight(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    return NapiExtra::toNapi(env, this->imageCapture->image_height);
}

Napi::Value Nodoface::ImageCapture::SetImageHeight(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() != 1 || !info[0].IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = info[0].As<Napi::Number>();
    this->imageCapture->image_height = num.DoubleValue();
    return NapiExtra::toNapi(env, true);
}

// float fx, fy, cx, cy;
Napi::Value Nodoface::ImageCapture::GetFx(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    return NapiExtra::toNapi(env, this->imageCapture->fx);
}

Napi::Value Nodoface::ImageCapture::GetFy(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    return NapiExtra::toNapi(env, this->imageCapture->fy);
}

Napi::Value Nodoface::ImageCapture::GetCx(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    return NapiExtra::toNapi(env, this->imageCapture->cx);
}

Napi::Value Nodoface::ImageCapture::GetCy(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    return NapiExtra::toNapi(env, this->imageCapture->cy);
}

Napi::Value Nodoface::ImageCapture::SetFx(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() != 1 || !info[0].IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = info[0].As<Napi::Number>();
    this->imageCapture->fx = num.DoubleValue();
    return NapiExtra::toNapi(env, true);
}

Napi::Value Nodoface::ImageCapture::SetFy(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() != 1 || !info[0].IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = info[0].As<Napi::Number>();
    this->imageCapture->fy = num.DoubleValue();
    return NapiExtra::toNapi(env, true);
}

Napi::Value Nodoface::ImageCapture::SetCx(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() != 1 || !info[0].IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = info[0].As<Napi::Number>();
    this->imageCapture->cx = num.DoubleValue();
    return NapiExtra::toNapi(env, true);
}

Napi::Value Nodoface::ImageCapture::SetCy(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    if(info.Length() != 1 || !info[0].IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = info[0].As<Napi::Number>();
    this->imageCapture->cy = num.DoubleValue();
    return NapiExtra::toNapi(env, true);
}
