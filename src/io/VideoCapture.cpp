//
// Created by sziraqui on 14/7/19.
//

#include "VideoCapture.h"

Napi::FunctionReference Nodoface::VideoCapture::constructor;

Napi::Object Nodoface::VideoCapture::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function ctr = DefineClass(env, "VideoCapture", {
            InstanceMethod("open", &VideoCapture::Open),
            InstanceMethod("read", &VideoCapture::Read),
            InstanceMethod("isOpened", &VideoCapture::IsOpened)
    });
    constructor = Napi::Persistent(ctr);
    constructor.SuppressDestruct();
    exports.Set("VideoCapture", ctr);
    return exports;
}

Nodoface::VideoCapture::VideoCapture(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    uint argLen = info.Length();
    Napi::Env env = info.Env();
    if(argLen != 0) {
        JSErrors::TooManyArguments(env, 0, argLen);
    }
    this->instance = new cv::VideoCapture();
}

Napi::Value Nodoface::VideoCapture::Read(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::EscapableHandleScope scope(env);
    cv::Mat frame;
    bool hasFrame = this->instance->read(frame);
    if(!hasFrame) {
        return env.Undefined();
    }
    cv::Mat* rgbFrame = new cv::Mat(frame);
    cv::cvtColor(*rgbFrame, *rgbFrame, cv::COLOR_BGR2RGB);
    Napi::Object image = Nodoface::Image::NewObject(env, *rgbFrame);
    return scope.Escape(image).As<Napi::Object>();
}

Napi::Value Nodoface::VideoCapture::Open(const Napi::CallbackInfo &info) {
    uint argLen = info.Length();
    Napi::Env env = info.Env();

    if(argLen == 0) {
        JSErrors::InsufficientArguments(env, 1, argLen);
    }
    else if(argLen > 1) {
        JSErrors::TooManyArguments(env, 1, argLen);
    }
    if(info[0].IsNumber()) {
        uint device = info[0].As<Napi::Number>().Uint32Value();
        this->instance->open(device);
    } else if (info[0].IsString()) {
        std::string file = info[0].As<Napi::String>().Utf8Value();
        this->instance->open(file);
    } else {
        JSErrors::IncorrectDatatype(env, JSErrors::NUMBER+"|"+JSErrors::STRING, 0);
    }
    return env.Undefined();
}

Napi::Value Nodoface::VideoCapture::IsOpened(const Napi::CallbackInfo &info) {
    auto env = info.Env();
    return NapiExtra::toNapi(env, this->instance->isOpened());
}

Napi::Value Nodoface::VideoCapture::NewObject(Napi::Env env) {
    return constructor.New({});
}

Nodoface::VideoCapture::~VideoCapture() {
    // std::cout<<"VideoCapture: Destructor called"<<std::endl;
    if(this->instance->isOpened()) {
        this->instance->release();
    }
    delete this->instance;
}