//
// Created by sziraqui on 17/6/19.
//

#ifndef NODOFACE_MAT_H
#define NODOFACE_MAT_H

#include <vector>

#include <napi.h>
#include <opencv2/core/mat.hpp>

namespace Nodoface {
    // Wraps OpenCV Mat partially for sending and receiving Mat objects to/from node
    class Image : public Napi::ObjectWrap<Image> {

        public:
            static Napi::Object Init(Napi::Env env, Napi::Object exports);

            static Image New(const Napi::CallbackInfo& info, cv::Mat& mat);

            Image(const Napi::CallbackInfo& info);

            cv::Mat GetMat();

            static Napi::FunctionReference constructor;

            cv::Mat mat;
            Napi::Int32Array shape;

            static Napi::Int32Array GetShape(Napi::Env env, cv::Mat& mat);
            // To create a local instance for sending to nodejs
            Image(const Napi::CallbackInfo& info, cv::Mat& mat);
            // Return Uint32Array [rows, columns, channels]
            Napi::Value Shape(const Napi::CallbackInfo& info);

            Napi::Value Type(const Napi::CallbackInfo& info);


    };
}


#endif //NODOFACE_MAT_H
