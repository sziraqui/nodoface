//
// Created by sziraqui on 22/6/19.
//

#include "FaceModelParameters.h"

Napi::FunctionReference Nodoface::LandmarkModelConfig::constructor;

Napi::Object Nodoface::LandmarkModelConfig::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function ctor = DefineClass(env, "FaceModelParameters", {
            InstanceMethod("getModelLocation", &Nodoface::LandmarkModelConfig::GetModelLocation),
            InstanceMethod("getMtcnnLocation", &Nodoface::LandmarkModelConfig::GetMtcnnLocation),
            InstanceMethod("getHaarLocation", &Nodoface::LandmarkModelConfig::GetHaarLocation),
            InstanceMethod("getCurrentFdId", &Nodoface::LandmarkModelConfig::GetCurrentFdId),
            InstanceMethod("getCurrentLdId", &Nodoface::LandmarkModelConfig::GetCurrentLdId)
    });

    constructor = Napi::Persistent(ctor);
    constructor.SuppressDestruct();
    exports.Set("FaceModelParameters", ctor);
    return exports;
}

Napi::Value Nodoface::LandmarkModelConfig::NewObject(Napi::Env env, std::vector<std::string> &arguments) {
    Napi::Array args = NapiExtra::toNapiArray<std::string>(env, arguments);
    return constructor.New({args});
}

Nodoface::LandmarkModelConfig::LandmarkModelConfig(const Napi::CallbackInfo &info)
        : ObjectWrap<Nodoface::LandmarkModelConfig>(info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() != 1) {
        JSErrors::InsufficientArguments(env, 1, info.Length());
    }

    const Napi::Array args = info[0].As<Napi::Array>();
    std::vector<std::string> vecArgs = NapiExtra::Napi2StringVector(args);

    this->instance = new ::LandmarkDetector::FaceModelParameters(vecArgs);
}

Napi::Value Nodoface::LandmarkModelConfig::GetModelLocation(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return NapiExtra::toNapi(env, this->instance->model_location);
}

Napi::Value Nodoface::LandmarkModelConfig::GetMtcnnLocation(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return NapiExtra::toNapi(env, this->instance->mtcnn_face_detector_location);
}

Napi::Value Nodoface::LandmarkModelConfig::GetHaarLocation(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return NapiExtra::toNapi(env, this->instance->haar_face_detector_location);
}

Napi::Value Nodoface::LandmarkModelConfig::GetCurrentFdId(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return NapiExtra::toNapi(env, GetInternalInstance().curr_face_detector);
}

Napi::Value Nodoface::LandmarkModelConfig::GetCurrentLdId(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return NapiExtra::toNapi(env, GetInternalInstance().curr_landmark_detector);
}

LandmarkDetector::FaceModelParameters Nodoface::LandmarkModelConfig::GetInternalInstance() {
    return *this->instance;
}

Nodoface::LandmarkModelConfig::~LandmarkModelConfig() {
    delete this->instance;
}
