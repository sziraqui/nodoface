//
// Created by sziraqui on 16/6/19.
//
#include <string>

#include "OutputUtils.h"
#include "../cvtypes/Mat.h"

Napi::Object Nodoface::Init(Napi::Env env, Napi::Object exports) {
    exports.Set("showImage", Napi::Function::New(env, Nodoface::showImage));
    return exports;
}

// js-args: Nodoface.Image instance
Napi::Value Nodoface::showImage(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Nodoface::Image image(info);
    cv::Mat mat = image.GetMat();
    std::string title = info.Length() >= 2? info[1].As<Napi::String>().Utf8Value() : "output";
    double ms = info.Length() >=3 ? info[2].As<Napi::Number>().DoubleValue() : 0;
    cv::namedWindow(title, cv::WINDOW_AUTOSIZE);
    cv::imshow("Output", mat);
    cv::waitKey(ms);
    return env.Null();
}