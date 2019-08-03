//
// Created by sziraqui on 21/6/19.
//
#include "cvdraw.h"

using namespace Nodoface;

Napi::Object Draw::Init(Napi::Env env, Napi::Object exports) {
    exports.Set("drawRect", Napi::Function::New(env, Nodoface::Draw::rectangle));
    exports.Set("drawText", Napi::Function::New(env, Nodoface::Draw::putText));
    return exports;
}

// args: Image, Rect, color Array/Uint8Array, thickness Number, lineType Number
Napi::Value Draw::rectangle(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int argLen = info.Length();
    if(argLen < 3) {
        JSErrors::InsufficientArguments(env, 3, argLen);
    } else if (argLen > 5) {
        JSErrors::TooManyArguments(env, 5, argLen);
    }
    Napi::Object imgObj = info[0].As<Napi::Object>();
    Nodoface::Image* img = Napi::ObjectWrap<Nodoface::Image>::Unwrap(imgObj);
    cv::Mat mat = img->GetMat();

    cv::Rect rect = NapiExtra::Napi2Rect(info[1].As<Napi::Object>());

    cv::Scalar bgrColor = NapiExtra::Napi2ScalarBgr(info[2].As<Napi::Object>());

    int i = 3;
    int thickness = argLen > i? info[i].As<Napi::Number>().Int32Value(): 1; i++;
    int lineType = argLen > i? info[i].As<Napi::Number>().Int32Value(): cv::LINE_8;

    cv::rectangle(mat, rect, bgrColor, thickness, lineType);

    return env.Undefined();
}

Napi::Value Draw::putText(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int argLen = info.Length();
    if(argLen < 4) {
        JSErrors::InsufficientArguments(env, 4, argLen);
    } else if (argLen > 6) {
        JSErrors::TooManyArguments(env, 6, argLen);
    }
    uint i = 0;
    Napi::Object imgObj = info[i].As<Napi::Object>(); i++;
    Nodoface::Image* img = Napi::ObjectWrap<Nodoface::Image>::Unwrap(imgObj);
    cv::Mat mat = img->GetMat();

    std::string text = info[i].As<Napi::String>().Utf8Value(); i++;

    cv::Point pt = NapiExtra::Napi2Point<int>(info[i].As<Napi::Object>());

    cv::Scalar bgrColor = NapiExtra::Napi2ScalarBgr(info[i].As<Napi::Object>()); i++;

    int scale = argLen > i? info[i].As<Napi::Number>().Int32Value(): 1; i++;
    int thickness = argLen > i? info[i].As<Napi::Number>().Int32Value(): 1; i++;

    cv::putText(mat, text, pt, cv::FONT_HERSHEY_SIMPLEX, scale, bgrColor, thickness);

    env.Undefined();
}
