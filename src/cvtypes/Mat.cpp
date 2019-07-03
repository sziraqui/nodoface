//
// Created by sziraqui on 17/6/19.
//

#include "Mat.h"

Napi::FunctionReference Nodoface::Image::constructor;

// static methods
Napi::Object Nodoface::Image::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "Image", {
        InstanceMethod("type", &Nodoface::Image::Type),
        InstanceMethod("height", &Nodoface::Image::Rows),
        InstanceMethod("width", &Nodoface::Image::Columns),
        InstanceMethod("channels", &Nodoface::Image::Channels)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("Image", func);
    return exports;
}

