//
// Created by sziraqui on 26/6/19.
//

#include "FaceDetectorHaar.h"

Napi::FunctionReference Nodoface::FaceDetectorHaar::constructor;

Napi::Object Nodoface::FaceDetectorHaar::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    auto func = DefineClass(env, "FaceDetectorHaar", {
        InstanceMethod("load", &Nodoface::FaceDetectorHaar::Read),
        InstanceMethod("detectFaces", &Nodoface::FaceDetectorHaar::DetectFaces),

    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("FaceDetectorHaar", func);
    return exports;
}

Napi::Object Nodoface::FaceDetectorHaar::NewObject(Napi::Env env, std::string txtPath) {
    Napi::String txtFilePath = Napi::String::New(env, txtPath);
    Napi::Object modelObj = constructor.New({txtFilePath});
    return modelObj;
}

Nodoface::FaceDetectorHaar::FaceDetectorHaar(const Napi::CallbackInfo &info) : Napi::ObjectWrap<Nodoface::FaceDetectorHaar>(info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    auto argLen = info.Length();
    if (argLen > 1) {
        JSErrors::TooManyArguments(env, 1, argLen);
    }
    if (argLen == 0) {
        // do nothing
    } else if (argLen == 1) {
        if (info[0].IsString()) {
            std::string txtFilePath = info[0].As<Napi::String>();
            this->model = new cv::CascadeClassifier(txtFilePath);
        } else if (info[0].IsObject()) { // copy constructor called
            Napi::Object parent = info[0].As<Napi::Object>();
            FaceDetectorHaar *modelWrap = ObjectWrap<FaceDetectorHaar>::Unwrap(parent);
            this->model = modelWrap->model;
        }
    } else {
        JSErrors::IncorrectDatatype(env, JSErrors::STRING + "|" + JSErrors::OBJECT, 0);
    }

}
// tweaked implementation is in OpenFace/LandmarkDetectorUtils
Napi::Value Nodoface::FaceDetectorHaar::DetectFaces(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    auto argLen = info.Length();
    if (argLen < 1) {
        JSErrors::InsufficientArguments(env, 1, 0);
    } else if (argLen >= 1 && !info[0].IsObject()) {
        JSErrors::IncorrectDatatype(env, JSErrors::OBJECT + "(Image)", 0);
    } else if (argLen > 3) {
        JSErrors::TooManyArguments(env, 3, argLen);
    }
    // Convert js args to c++
    Napi::Object imgObj = info[0].As<Napi::Object>();
    Nodoface::Image *img = Napi::ObjectWrap<Nodoface::Image>::Unwrap(imgObj);
    const cv::Mat mat = img->GetMat();
    if(mat.channels() > 1) {
        JSErrors::IncorrectImageType(env, "GRAYSCALE");
    }
    float minWid = argLen > 1? info[1].As<Napi::Number>().FloatValue(): mat.cols*0.1; // default minWid to 10% of image width
    cv::Rect_<float> roi = argLen > 2? NapiExtra::Napi2Rect<float>(info[2].As<Napi::Object>()): cv::Rect_<float>(0.0, 0.0, 1.0, 1.0); // default roi in OpenFace
    // pre-allocated vectors
    std::vector<cv::Rect_<float>> out_bboxes;

    LandmarkDetector::DetectFaces(out_bboxes, mat, *this->model, minWid, roi);
    std::vector<float> out_confidences(out_bboxes.size(), -1);
    Napi::Object detectionResult = NapiExtra::detectionResult2Napi(env, out_bboxes, out_confidences);
    return detectionResult;
}

Napi::Value Nodoface::FaceDetectorHaar::Read(const Napi::CallbackInfo &info) {
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
    this->model = new cv::CascadeClassifier(location);
    return env.Undefined();
}
