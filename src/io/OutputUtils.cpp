//
// Created by sziraqui on 16/6/19.
//
#include <string>

#include "OutputUtils.h"
#include "../cvtypes/Mat.h"

Napi::Object Nodoface::Init(Napi::Env env, Napi::Object exports) {
    exports.Set("showImage", Napi::Function::New(env, Nodoface::showImage));
    exports.Set("readImage", Napi::Function::New(env, Nodoface::readImage));
    return exports;
}

// js-args: Nodoface.Image instance
Napi::Value Nodoface::showImage(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Nodoface::Image image(info);
    cv::Mat mat = image.GetMat();
    std::string title = info.Length() >= 2? info[1].As<Napi::String>().Utf8Value() : "output";
    int ms = info.Length() >=3 ? info[2].As<Napi::Number>().Int32Value() : 0;
    cv::namedWindow(title, cv::WINDOW_AUTOSIZE);
    cv::imshow(title, mat);
    cv::waitKey(ms);
    return env.Null();
}

Napi::Value Nodoface::readImage(const Napi::CallbackInfo &info) {
    std::string path = info[0].As<Napi::String>().Utf8Value();
    cv::Mat mat = cv::imread(path, cv::IMREAD_UNCHANGED);
    auto img = Nodoface::Image::New(info, mat);
    Napi::Value val = img.Value(); // returns the whole addon!!*
    return val;
}