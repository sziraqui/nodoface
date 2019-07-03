//
// Created by sziraqui on 17/6/19.
//

#include "Mat.h"

// static methods
template <>
Napi::Object Nodoface::Image::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "Image", {
        InstanceMethod("type", &Nodoface::Image::Type),
        InstanceMethod("height", &Nodoface::Image::Rows),
        InstanceMethod("width", &Nodoface::Image::Columns),
        InstanceMethod("channels", &Nodoface::Image::Channels)
    });

    Image::constructor = Napi::Persistent(func);
    Image::constructor.SuppressDestruct();
    exports.Set("Image", func);
    return exports;
}

