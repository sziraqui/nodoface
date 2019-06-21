//
// Created by sziraqui on 21/6/19.
//
#include "cvdraw.h"

using namespace Nodoface;

Napi::Object Draw::Init(Napi::Env env, Napi::Object exports) {
    exports.Set("drawRect", Napi::Function::New(env, Nodoface::Draw::rectangle));
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
