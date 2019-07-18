//
// Created by sziraqui on 22/6/19.
//

#include "MatInt.h"

// static methods
template <>
Napi::Object Nodoface::IntImage::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "IntImage", {
            InstanceMethod("type", &Nodoface::IntImage::Type),
            InstanceMethod("height", &Nodoface::IntImage::Rows),
            InstanceMethod("width", &Nodoface::IntImage::Columns),
            InstanceMethod("channels", &Nodoface::IntImage::Channels),
            InstanceMethod("toInt32Array", &Nodoface::IntImage::ToTypedArray),
            InstanceMethod("extract", &Nodoface::IntImage::Extract)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("IntImage", func);
    return exports;
}
