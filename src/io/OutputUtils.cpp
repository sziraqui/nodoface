//
// Created by sziraqui on 16/6/19.
//
#include "OutputUtils.h"

Napi::Object Nodoface::Init(Napi::Env env, Napi::Object exports) {
    exports.Set("showImage", Napi::Function::New(env, Nodoface::showImage));
    exports.Set("readImage", Napi::Function::New(env, Nodoface::readImage));
    exports.Set("destroyWindow", Napi::Function::New(env, Nodoface::destroyWindow));
    exports.Set("destroyAllWindows", Napi::Function::New(env, Nodoface::destroyAllWindows));
    exports.Set("waitKey", Napi::Function::New(env, Nodoface::waitKey));
    exports.Set("saveImage", Napi::Function::New(env, Nodoface::saveImage));
    return exports;
}

// js-args: Nodoface.Image instance
Napi::Value Nodoface::showImage(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    // TODO: input validation
    // Unwrap Image and get mat
    Napi::Object parent = info[0].As<Napi::Object>();
    Nodoface::Image *image = Napi::ObjectWrap<Nodoface::Image>::Unwrap(parent);
    cv::Mat mat = image->GetMat();
    // Get optional arguments
    std::string title = info.Length() >= 2? info[1].As<Napi::String>().Utf8Value() : "output";
    cv::namedWindow(title, cv::WINDOW_AUTOSIZE);
    cv::imshow(title, mat);
    return env.Undefined();
}

Napi::Value Nodoface::readImage(const Napi::CallbackInfo &info) {
    Napi::EscapableHandleScope scope(info.Env());
    // TODO: input validation
    std::string path = info[0].As<Napi::String>().Utf8Value();
    cv::Mat mat = cv::imread(path, cv::IMREAD_UNCHANGED);
#ifdef DEBUG_MATWRAPPER
    cv::namedWindow("readImageOg", cv::WINDOW_AUTOSIZE);
    cv::imshow("readImageOg", mat);
    cv::waitKey(100);
#endif
    auto imgObj = Nodoface::Image::NewObject(info.Env(), &mat).As<Napi::Object>();
#ifdef DEBUG_MATWRAPPER
    Nodoface::Image* image = Napi::ObjectWrap<Nodoface::Image>::Unwrap(imgObj);
    cv::namedWindow("readImageUnwrap", cv::WINDOW_AUTOSIZE);
    cv::imshow("readImageUnwrap", image->GetMat());
    cv::waitKey(0);
#endif
    return scope.Escape(imgObj);
}

Napi::Value Nodoface::destroyWindow(const Napi::CallbackInfo &info) {
    // TODO: input validation
    auto windowName = info[0].As<Napi::String>().Utf8Value();
    cv::destroyWindow(windowName);
    info.Env().Undefined();
}

Napi::Value Nodoface::destroyAllWindows(const Napi::CallbackInfo &info) {
    cv::destroyAllWindows();
    return info.Env().Undefined();
}

Napi::Value Nodoface::waitKey(const Napi::CallbackInfo &info) {
    // TODO: input validation
    auto delay = info[0].As<Napi::Number>().Int32Value();
    int key = cv::waitKey(delay);
    return Napi::Number::New(info.Env(), key);
}

Napi::Value Nodoface::saveImage(const Napi::CallbackInfo& info) {
    // TODO: input validation
    auto absPath = info[0].As<Napi::String>().Utf8Value();
    auto imageObj = info[1].As<Napi::Object>();
    Nodoface::Image* img = Napi::ObjectWrap<Nodoface::Image>::Unwrap(imageObj);
    cv::imwrite(absPath, img->GetMat());
    return info.Env().Undefined();
}
