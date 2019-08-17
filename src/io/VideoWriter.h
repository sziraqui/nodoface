//
// Created by sziraqui on 16/8/19.
//

#ifndef NODOFACE_VIDEOWRITER_H
#define NODOFACE_VIDEOWRITER_H

#include <string>

#include <opencv2/opencv.hpp>
#include <napi.h>

#include "../jserrors/JSErrors.h"
#include "../extras/napiextra.h"
#include "../cvtypes/Mat.h"

namespace Nodoface {
class VideoWriter : public Napi::ObjectWrap<VideoWriter>{
public:
        VideoWriter(const Napi::CallbackInfo& info);

        Napi::Value Write(const Napi::CallbackInfo& info);

        Napi::Value NewObject(Napi::Env env, std::string file, int width, int height, double fps, std::string fourcc);

        static Napi::Object Init(Napi::Env env, Napi::Object exports);

        ~VideoWriter();
private:
    static Napi::FunctionReference constructor;
    cv::VideoWriter * instance;
    };
}

#endif //NODOFACE_VIDEOWRITER_H
