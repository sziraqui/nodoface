//
// Created by sziraqui on 22/6/19.
//

#ifndef NODOFACE_MATFLOAT_H
#define NODOFACE_MATFLOAT_H

#include <vector>

#include <opencv2/core/mat.hpp>

#include <napi.h>

#include "../extras/napiextra.h"
#include "../jserrors/JSErrors.h"

namespace Nodoface {
    // Wraps OpenCV Mat_<float> partially for sending and receiving Mat_<float> objects to/from node
    class FloatImage : public Napi::ObjectWrap<FloatImage> {

    public:
        static Napi::Object Init(Napi::Env env, Napi::Object exports);

        static Napi::Value NewObject(Napi::Env env, cv::Mat_<float>& mat);

        static cv::Mat_<float>* NewMat(Napi::TypedArrayOf<float>& arr, Napi::Number& rows, Napi::Number& cols, Napi::Number& type);

        FloatImage(const Napi::CallbackInfo& info);

        cv::Mat_<float> GetMat();

        ~FloatImage();
    private:

        cv::Mat_<float>* mat;

        static Napi::FunctionReference constructor;

        Napi::Value Type(const Napi::CallbackInfo& info);

        Napi::Value Rows(const Napi::CallbackInfo& info);

        Napi::Value Columns(const Napi::CallbackInfo& info);

        Napi::Value Channels(const Napi::CallbackInfo& info);
    };
}

#endif //NODOFACE_MATFLOAT_H
