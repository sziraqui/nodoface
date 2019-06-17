//
// Created by sziraqui on 16/6/19.
//

#include "OutputUtils.h"

Napi::Object Nodoface::Init(Napi::Env env, Napi::Object exports) {
    exports.Set("showImage", Napi::Function::New(env, Nodoface::showImage));
    return exports;
}

// js-args: Uint8Array, shape, type
Napi::Value Nodoface::showImage(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    Napi::Uint8Array flat = info[0].As<Napi::Uint8Array>();
    Napi::Int32Array shape = info[1].As<Napi::Int32Array>();
    int type =  CV_8UC3;//info[2].As<Napi::Number>().Int32Value();

    NapiExtra::NdArray<uchar> ndArray = NapiExtra::NdArray<>::From(flat, shape);
    cv::Mat mat = ndArray.ToMat(type);
    cv::namedWindow("Output", cv::WINDOW_AUTOSIZE);
    cv::imshow("Output", mat);
    cv::waitKey(1000/30);
    return env.Null();
}