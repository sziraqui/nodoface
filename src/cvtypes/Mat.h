//
// Created by sziraqui on 17/6/19.
//

#ifndef NODOFACE_MAT_H
#define NODOFACE_MAT_H

#include <vector>

#include <napi.h>
#include <opencv2/core/mat.hpp>
#ifdef DEBUG_MATWRAPPER
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#endif

namespace Nodoface {
    // Wraps OpenCV Mat partially for sending and receiving Mat objects to/from node
    class Image : public Napi::ObjectWrap<Image> {

        public:
            static Napi::Object Init(Napi::Env env, Napi::Object exports);

            static Napi::Value NewObject(Napi::Env env, cv::Mat& mat);

            static cv::Mat NewMat(Napi::TypedArrayOf<uchar>& arr, Napi::Number& rows, Napi::Number& cols, Napi::Number& type);

            Image(const Napi::CallbackInfo& info);

            cv::Mat GetMat();
    private:

            cv::Mat mat;

            size_t rows, cols, channels, type;

            static Napi::FunctionReference constructor;

            Napi::Value Type(const Napi::CallbackInfo& info);

            Napi::Value Rows(const Napi::CallbackInfo& info);

            Napi::Value Columns(const Napi::CallbackInfo& info);

            Napi::Value Channels(const Napi::CallbackInfo& info);
    };
}


#endif //NODOFACE_MAT_H
