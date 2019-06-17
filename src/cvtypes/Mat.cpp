//
// Created by sziraqui on 17/6/19.
//

#include "Mat.h"
#include "../extras/napiextra.h"

Napi::FunctionReference Nodoface::Image::constructor;

Napi::Object Nodoface::Image::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "Image", {
        InstanceMethod("shape", &Nodoface::Image::Shape),
        InstanceMethod("type", &Nodoface::Image::Type)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("Image", func);
    return exports;
}

Nodoface::Image::Image(const Napi::CallbackInfo& info) : ObjectWrap<Nodoface::Image>(info) {
    std::cout<<"inside Mat constructor\n";
    if(info.Length() == 2) {
        std::cout<<"Mat Unwrap start\n";
        Image * img = Napi::ObjectWrap<Image>::Unwrap(info[1].As<Napi::Object>());
        std::cout<<"Mat Unwrap end\n";
        this->mat = img->mat;
    }
    std::cout<<"Mat constructor finish\n";
}

Nodoface::Image Nodoface::Image::New(const Napi::CallbackInfo& info, cv::Mat& mat) {
    auto env = info.Env();
    std::cout<<"inside Mat New\n";
    Nodoface::Image img(info);
    img.mat = &mat;
    return img;
}


Napi::Value Nodoface::Image::Shape(const Napi::CallbackInfo &info) {
    std::vector<int32_t > vec(this->mat->size.p, this->mat->size.p + this->mat->size.dims());
    vec.push_back(this->mat->channels());
    auto ab = Napi::ArrayBuffer::New(info.Env(), vec.data(), sizeof(int32_t)/ sizeof(uint8_t));
    auto arr = Napi::Int32Array::New(info.Env(), vec.size(), ab, 0);
    return arr;
}

Napi::Value Nodoface::Image::Type(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->mat->type());
}

cv::Mat Nodoface::Image::GetMat() {
    return *this->mat;
}