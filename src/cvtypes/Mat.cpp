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
    if(info.Length() == 1) {
        std::cout<<"Mat Unwrap start\n";
        Image * img = Napi::ObjectWrap<Image>::Unwrap(info[0].As<Napi::Object>());
        std::cout<<"Mat Unwrap end\n";
        this->mat = img->mat;
        this->shape = GetShape(info.Env(), this->mat);
    }
    std::cout<<"Mat constructor finish\n";
}

Nodoface::Image Nodoface::Image::New(const Napi::CallbackInfo& info, cv::Mat& mat) {
    auto env = info.Env();
    std::cout<<"inside Mat New\n";
    Nodoface::Image img(info);
    img.mat = mat;
    img.shape = GetShape(env, mat);
    return img;
}

Napi::Int32Array Nodoface::Image::GetShape(Napi::Env env, cv::Mat &mat) {
    std::vector<int32_t > vec(mat.size.p, mat.size.p + mat.size.dims());
    vec.push_back(mat.channels());
    auto ab = Napi::ArrayBuffer::New(env, vec.data(), sizeof(int32_t)/ sizeof(uint8_t));
    auto arr = Napi::Int32Array::New(env, vec.size(), ab, 0);
    return arr;
}

Napi::Value Nodoface::Image::Shape(const Napi::CallbackInfo &info) {
    return this->shape;
}

Napi::Value Nodoface::Image::Type(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), this->mat.type());
}

cv::Mat Nodoface::Image::GetMat() {
    return this->mat;
}