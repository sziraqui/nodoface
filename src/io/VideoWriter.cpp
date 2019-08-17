//
// Created by sziraqui on 16/8/19.
//

#include "VideoWriter.h"

Napi::FunctionReference Nodoface::VideoWriter::constructor;

Napi::Object Nodoface::VideoWriter::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function ctr = DefineClass(env, "VideoWriter", {
            InstanceMethod("write", &VideoWriter::Write),
    });
    constructor = Napi::Persistent(ctr);
    constructor.SuppressDestruct();
    exports.Set("VideoWriter", ctr);
    return exports;
}

Nodoface::VideoWriter::VideoWriter(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    uint argLen = info.Length();
    Napi::Env env = info.Env();
    uint i = 0;
    std::string file = info[i].As<Napi::String>().Utf8Value(); i++;
    int width = info[i].As<Napi::Number>().Int32Value(); i++;
    int height = info[i].As<Napi::Number>().Int32Value(); i++;
    double fps = argLen > i && info[i].IsNumber()? info[i].As<Napi::Number>().DoubleValue(): 30; i++;
    std::string cc = argLen > i && info[i].IsString()? info[i].As<Napi::String>().Utf8Value(): "MJPG"; i++;
    this->instance = new cv::VideoWriter(file, cv::VideoWriter::fourcc(cc[0], cc[1], cc[2], cc[3]), fps, cv::Size(width, height));
}

Napi::Value Nodoface::VideoWriter::Write(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Nodoface::Image * img = Nodoface::Image::Unwrap(info[0].As<Napi::Object>());
    cv::Mat* frame = new cv::Mat(img->GetMat());
    cv::cvtColor(*frame, *frame, cv::COLOR_RGB2BGR);
    this->instance->write(*frame);
    return env.Undefined();
}

Napi::Value Nodoface::VideoWriter::NewObject(Napi::Env env, std::string file, int width, int height, double fps, std::string fourcc) {
    
    return Nodoface::VideoWriter::constructor.New({
       Napi::String::New(env, file),
       NapiExtra::toNapi(env, width),
       NapiExtra::toNapi(env, height),
       NapiExtra::toNapi(env, fps),
       Napi::String::New(env, fourcc)
    });
}

Nodoface::VideoWriter::~VideoWriter() {
    this->instance->release();
    delete this->instance;
}