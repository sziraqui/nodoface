//
// Created by sziraqui on 27/6/19.
//

#include "FaceDetectorHOG.h"

Napi::FunctionReference Nodoface::FaceDetectorHOG::constructor;

Napi::Object Nodoface::FaceDetectorHOG::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    auto func = DefineClass(env, "FaceDetectorHOG", {
            InstanceMethod("load", &Nodoface::FaceDetectorHOG::Read),
            InstanceMethod("detectFaces", &Nodoface::FaceDetectorHOG::DetectFaces),

    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("FaceDetectorHOG", func);
    return exports;
}

Napi::Object Nodoface::FaceDetectorHOG::NewObject(Napi::Env env, std::string txtPath) {
    Napi::String txtFilePath = Napi::String::New(env, txtPath);
    Napi::Object modelObj = constructor.New({txtFilePath});
    return modelObj;
}

Nodoface::FaceDetectorHOG::FaceDetectorHOG(const Napi::CallbackInfo &info) : Napi::ObjectWrap<Nodoface::FaceDetectorHOG>(info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    auto argLen = info.Length();
    if (argLen > 1) {
        JSErrors::TooManyArguments(env, 1, argLen);
    }
    if (argLen == 0) {
        this->model = new dlib::frontal_face_detector();
    } else if (argLen == 1) {
        if (info[0].IsObject()) { // copy constructor called
            Napi::Object parent = info[0].As<Napi::Object>();
            FaceDetectorHOG *modelWrap = ObjectWrap<FaceDetectorHOG>::Unwrap(parent);
            this->model = modelWrap->model;
        }
    } else {
        JSErrors::IncorrectDatatype(env, JSErrors::OBJECT, 0);
    }

}
// tweaked implementation is in OpenFace/LandmarkDetectorUtils
Napi::Value Nodoface::FaceDetectorHOG::DetectFaces(const Napi::CallbackInfo &info) {
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
    std::vector<float> out_confidences;
    LandmarkDetector::DetectFacesHOG(out_bboxes, mat, out_confidences, minWid, roi);

    Napi::Object detectionResult = NapiExtra::detectionResult2Napi(env, out_bboxes, out_confidences);
    return detectionResult;
}

Napi::Value Nodoface::FaceDetectorHOG::Read(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    auto argLen = info.Length();
    if (argLen > 0) {
        JSErrors::TooManyArguments(env, 0, argLen);
    }
    this->model = new dlib::frontal_face_detector();
    return env.Undefined();
}