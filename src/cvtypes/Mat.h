//
// Created by sziraqui on 17/6/19.
//

#ifndef NODOFACE_MAT_H
#define NODOFACE_MAT_H

#include <vector>

#include <napi.h>
#include <opencv2/core/mat.hpp>
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
namespace Nodoface {
    // Wraps OpenCV Mat partially for sending and receiving Mat objects to/from node
    class Image : public Napi::ObjectWrap<Image> {

        public:
            static Napi::Object Init(Napi::Env env, Napi::Object exports);

            static Napi::Object NewObject(Napi::Env env, cv::Mat& mat);

            static cv::Mat NewMat(Napi::TypedArrayOf<uchar>& arr, Napi::Int32Array& size, Napi::Number& type);

            Image(const Napi::CallbackInfo& info);

            static Napi::FunctionReference constructor;

            cv::Mat GetMat();
    private:

            cv::Mat mat;

            // Return Uint32Array [rows, columns, channels]
            Napi::Value Shape(const Napi::CallbackInfo& info);

            Napi::Value Type(const Napi::CallbackInfo& info);


    };
}


#endif //NODOFACE_MAT_H
