//
// Created by sziraqui on 16/6/19.
//
#include <string>
#include <iostream>
#include "OutputUtils.h"
#include "../cvtypes/Mat.h"

Napi::Object Nodoface::Init(Napi::Env env, Napi::Object exports) {
    exports.Set("showImage", Napi::Function::New(env, Nodoface::showImage));
    exports.Set("readImage", Napi::Function::New(env, Nodoface::readImage));
    return exports;
}

// js-args: Nodoface.Image instance
Napi::Value Nodoface::showImage(const Napi::CallbackInfo& info) {
    std::cout<<"showImage info.Length "<<info.Length()<<std::endl;
    Napi::Env env = info.Env();
    // Unwrap Image and get mat
    Napi::Object parent = info[0].As<Napi::Object>();
    Nodoface::Image *image = Napi::ObjectWrap<Nodoface::Image>::Unwrap(parent);
    std::cout<<"showImage image unrwappped\n";
    cv::Mat mat = image->GetMat();
    std::cout<<"showImage: mat rows :"<<mat.rows <<" cols:"<<mat.cols << " type :" <<mat.type()<<std::endl;
    // Get optional arguments
    std::string title = info.Length() >= 2? info[1].As<Napi::String>().Utf8Value() : "output";
    int ms = info.Length() >=3 ? info[2].As<Napi::Number>().Int32Value() : 0;
    std::cout<<"showImage: mat.isContinuous:"<<mat.isContinuous()<<std::endl;
    // Display mat
    cv::namedWindow(title, cv::WINDOW_AUTOSIZE);
    std::cout<<"showImage imshow\n";
    cv::imshow(title, mat);
    std::cout<<"showImage imshow done\n";
    cv::waitKey(ms);
    return env.Undefined();
}

Napi::Value Nodoface::readImage(const Napi::CallbackInfo &info) {
    Napi::EscapableHandleScope scope(info.Env());
    std::string path = info[0].As<Napi::String>().Utf8Value();
    std::cout<<"image path:" << path << std::endl;
    cv::Mat mat = cv::imread(path, cv::IMREAD_UNCHANGED);
    std::cout<<"readImage: mat rows :"<<mat.rows <<" cols:"<<mat.cols << " type :" <<mat.type()<<std::endl;
    cv::namedWindow("readImageOg", cv::WINDOW_AUTOSIZE);
    cv::imshow("readImageOg", mat);
    cv::waitKey(0);
    auto imgObj = Nodoface::Image::NewObject(info.Env(), mat).As<Napi::Object>();
    std::cout<<"readImage imgObj type " << typeid(imgObj).name()<<std::endl;
    Nodoface::Image* image = Napi::ObjectWrap<Nodoface::Image>::Unwrap(imgObj);
    cv::namedWindow("readImageUnwrap", cv::WINDOW_AUTOSIZE);
    cv::imshow("readImageUnwrap", image->GetMat());
    cv::waitKey(0);
    return scope.Escape(imgObj);
}