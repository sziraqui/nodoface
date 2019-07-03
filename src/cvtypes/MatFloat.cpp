//
// Created by sziraqui on 22/6/19.
//

#include "MatFloat.h"

// static methods
template <>
Napi::Object Nodoface::FloatImage::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "FloatImage", {
            InstanceMethod("type", &Nodoface::FloatImage::Type),
            InstanceMethod("height", &Nodoface::FloatImage::Rows),
            InstanceMethod("width", &Nodoface::FloatImage::Columns),
            InstanceMethod("channels", &Nodoface::FloatImage::Channels)
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("FloatImage", func);
    return exports;
}