//
// Created by sziraqui on 22/6/19.
//

#ifndef NODOFACE_MATINT_H
#define NODOFACE_MATINT_H

#include <vector>

#include <opencv2/core/mat.hpp>
#ifdef DEBUG_MATWRAPPER
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#endif

#include <napi.h>

#include "../extras/napiextra.h"
#include "../jserrors/JSErrors.h"

namespace Nodoface {
    // Wraps OpenCV Mat_<int> partially for sending and receiving Mat_<int> objects to/from node
    class IntImage : public Napi::ObjectWrap<IntImage> {

    public:
        static Napi::Object Init(Napi::Env env, Napi::Object exports);

        static Napi::Value NewObject(Napi::Env env, cv::Mat_<int>& mat);

        static cv::Mat_<int>* NewMat(Napi::TypedArrayOf<int>& arr, Napi::Number& rows, Napi::Number& cols, Napi::Number& type);

        IntImage(const Napi::CallbackInfo& info);

        cv::Mat_<int> GetMat();

        ~IntImage();
    private:

        cv::Mat_<int>* mat;

        static Napi::FunctionReference constructor;

        Napi::Value Type(const Napi::CallbackInfo& info);

        Napi::Value Rows(const Napi::CallbackInfo& info);

        Napi::Value Columns(const Napi::CallbackInfo& info);

        Napi::Value Channels(const Napi::CallbackInfo& info);
    };
}



#endif //NODOFACE_MATINT_H
