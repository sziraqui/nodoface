//
// Created by sziraqui on 20/6/19.
//

#include "FaceDetectorMTCNN.h"

Napi::FunctionReference Nodoface::FaceDetectorMTCNN::constructor;

Napi::Object Nodoface::FaceDetectorMTCNN::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    auto func = DefineClass(env, "FaceDetectorMTCNN", {
            InstanceMethod("load", &Nodoface::FaceDetectorMTCNN::Read),
            InstanceMethod("detectFaces", &Nodoface::FaceDetectorMTCNN::DetectFaces),
            InstanceMethod("empty", &Nodoface::FaceDetectorMTCNN::Empty)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("FaceDetectorMTCNN", func);
    return exports;
}

Napi::Object Nodoface::FaceDetectorMTCNN::NewObject(Napi::Env env, std::string txtPath) {
    Napi::String txtFilePath = Napi::String::New(env, txtPath);
    Napi::Object modelObj = constructor.New({txtFilePath});
    return modelObj;
}

Nodoface::FaceDetectorMTCNN::FaceDetectorMTCNN(const Napi::CallbackInfo &info)
        : ObjectWrap<Nodoface::FaceDetectorMTCNN>(info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    auto argLen = info.Length();
    if (argLen > 1) {
        JSErrors::TooManyArguments(env, 1, argLen);
    }
    if (argLen == 0) {
        this->model = new LandmarkDetector::FaceDetectorMTCNN();
    } else if (argLen == 1) {
        if (info[0].IsString()) {
            std::string txtFilePath = info[0].As<Napi::String>();
            this->model = new LandmarkDetector::FaceDetectorMTCNN(txtFilePath);
        } else if (info[0].IsObject()) { // copy constructor called
            Napi::Object parent = info[0].As<Napi::Object>();
            FaceDetectorMTCNN *modelWrap = ObjectWrap<FaceDetectorMTCNN>::Unwrap(parent);
            this->model = modelWrap->model;
        }
    } else {
        JSErrors::IncorrectDatatype(env, JSErrors::STRING + "|" + JSErrors::OBJECT, 0);
    }
}

Napi::Value Nodoface::FaceDetectorMTCNN::Read(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    auto argLen = info.Length();
    if (argLen == 0) {
        JSErrors::InsufficientArguments(env, 1, 0);
    } else if (argLen > 1) {
        JSErrors::TooManyArguments(env, 1, argLen);
    } else if (!info[0].IsString()) {
        JSErrors::IncorrectDatatype(env, JSErrors::STRING, 0);
    }
    std::string location = info[0].As<Napi::String>().Utf8Value();
    this->model->Read(location);
    return env.Undefined();
}

// args: Image/Mat rgbImage, Number/int min_face, Number/float t1, Number/float t2, Number/float t3
// returns: Bounding boxes and confidence scores as Object of Arrays
Napi::Value Nodoface::FaceDetectorMTCNN::DetectFaces(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    auto argLen = info.Length();
    if (argLen < 1) {
        JSErrors::InsufficientArguments(env, 1, 0);
    } else if (argLen >= 1 && !info[0].IsObject()) {
        JSErrors::IncorrectDatatype(env, JSErrors::OBJECT + "(Image)", 0);
    } else if (argLen <= 5) {
        for (uint i = 1; i < argLen; ++i) {
            if (!info[i].IsNumber()) {
                JSErrors::IncorrectDatatype(env, JSErrors::NUMBER, i);
            }
        }
    } else if (argLen > 5) {
        JSErrors::TooManyArguments(env, 5, argLen);
    }
    // pre-allocated vectors
    std::vector<cv::Rect_<float>> out_bboxes;
    std::vector<float> out_confidences;
    // Convert js args to c++
    Napi::Object imgObj = info[0].As<Napi::Object>();
    Nodoface::Image *img = Napi::ObjectWrap<Nodoface::Image>::Unwrap(imgObj);
    const cv::Mat mat = img->GetMat();

    uint i = 1;
    int min_face = argLen > i ? info[i].As<Napi::Number>().Int32Value() : 60;
    i++;
    float t1 = argLen > i ? info[i].As<Napi::Number>().FloatValue() : 0.6;
    i++;
    float t2 = argLen > i ? info[i].As<Napi::Number>().FloatValue() : 0.7;
    i++;
    float t3 = argLen > i ? info[i].As<Napi::Number>().FloatValue() : 0.7;
//     actual detection
    this->model->DetectFaces(out_bboxes, mat, out_confidences, min_face, t1, t2, t3);
//     Convert c++ to js
    Napi::Object output = NapiExtra::detectionResult2Napi(env, out_bboxes, out_confidences);
    return output;
}

Napi::Value Nodoface::FaceDetectorMTCNN::Empty(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    auto argLen = info.Length();
    if (argLen != 0) {
        JSErrors::TooManyArguments(env, 0, argLen);
    }
    bool result = this->model->empty();
    return NapiExtra::toNapi(env, result);
}
