//
// Created by sziraqui on 14/7/19.
//

#ifndef NODOFACE_VIDEOCAPTURE_H
#define NODOFACE_VIDEOCAPTURE_H

#include <string>

#include <opencv2/opencv.hpp>
#include <napi.h>

#include "../jserrors/JSErrors.h"
#include "../extras/napiextra.h"
#include "../cvtypes/Mat.h"

namespace Nodoface {
class VideoCapture : public Napi::ObjectWrap<VideoCapture>{
public:
        VideoCapture(const Napi::CallbackInfo& info);

        Napi::Value Read(const Napi::CallbackInfo& info);

        Napi::Value Open(const Napi::CallbackInfo& info);

        Napi::Value IsOpened(const Napi::CallbackInfo& info);

        Napi::Value NewObject(Napi::Env env);

        static Napi::Object Init(Napi::Env env, Napi::Object exports);

        ~VideoCapture() {
            if(this->instance->isOpened()) {
                this->instance->release();
            }
        }
private:
    static Napi::FunctionReference constructor;
    cv::VideoCapture * instance;
    };
}



#endif //NODOFACE_VIDEOCAPTURE_H
