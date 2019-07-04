//
// Created by sziraqui on 7/6/19.
//

#include "SequenceCapture.h"

Napi::FunctionReference Nodoface::SequenceCapture::constructor;

Napi::Object Nodoface::SequenceCapture::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "SequenceCapture", {
            InstanceMethod("open", &Nodoface::SequenceCapture::Open),
            InstanceMethod("openWebcam", &Nodoface::SequenceCapture::OpenWebcam),
            InstanceMethod("openVideoFile", &Nodoface::SequenceCapture::OpenVideoFile),
            InstanceMethod("isWebcam", &Nodoface::SequenceCapture::IsWebcam),
            InstanceMethod("isOpened", &Nodoface::SequenceCapture::IsOpened),
            InstanceMethod("getFrameNumber", &Nodoface::SequenceCapture::GetFrameNumber),
            InstanceMethod("getNextFrame", &Nodoface::SequenceCapture::GetNextFrame),
            InstanceMethod("getGrayFrame", &Nodoface::SequenceCapture::GetGrayFrame),
            InstanceMethod("getProgress", &Nodoface::SequenceCapture::GetProgress),
            InstanceAccessor("name", &Nodoface::SequenceCapture::GetName, &Nodoface::SequenceCapture::SetName),
            InstanceAccessor("noInputSpecified", &Nodoface::SequenceCapture::GetNoInputSpecified, &Nodoface::SequenceCapture::SetNoInputSpecified),
            InstanceAccessor("width", &Nodoface::SequenceCapture::GetFrameWidth, &Nodoface::SequenceCapture::SetFrameWidth),
            InstanceAccessor("height", &Nodoface::SequenceCapture::GetFrameHeight, &Nodoface::SequenceCapture::SetFrameHeight),
            InstanceAccessor("fps", &Nodoface::SequenceCapture::GetFPS, &Nodoface::SequenceCapture::SetFPS),
            InstanceAccessor("timeStamp", &Nodoface::SequenceCapture::GetTimeStamp, &Nodoface::SequenceCapture::SetTimeStamp),
            InstanceAccessor("fx", &Nodoface::SequenceCapture::GetFx, &Nodoface::SequenceCapture::SetFx),
            InstanceAccessor("fy", &Nodoface::SequenceCapture::GetFy, &Nodoface::SequenceCapture::SetFy),
            InstanceAccessor("cx", &Nodoface::SequenceCapture::GetCx, &Nodoface::SequenceCapture::SetCx),
            InstanceAccessor("cy", &Nodoface::SequenceCapture::GetCy, &Nodoface::SequenceCapture::SetCy),
            StaticMethod("getCaptureCapacity", &Nodoface::SequenceCapture::GetCaptureCapacity),
            InstanceMethod("close", &Nodoface::SequenceCapture::Close)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("SequenceCapture", func);
    return exports;
}

Nodoface::SequenceCapture::SequenceCapture(const Napi::CallbackInfo &info)
        : Napi::ObjectWrap<Nodoface::SequenceCapture>(info) {
    if (info.Length() != 0) {
        JSErrors::TooManyArguments(info.Env(), 0, info.Length());
    }
    this->sequenceCapture = new Utilities::SequenceCapture();
}

Napi::Value Nodoface::SequenceCapture::Open(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    size_t argLen = info.Length();
    if (argLen == 0) {
        JSErrors::InsufficientArguments(env, 1, argLen);
    } else if (argLen >= 1 && !info[0].IsArray()) {
        JSErrors::IncorrectDatatype(env, JSErrors::ARRAY, 0);
    }

    const Napi::Array arguments = info[0].As<Napi::Array>();
    std::vector<std::string> vecList(arguments.Length());
    for (uint i = 0; i < arguments.Length(); ++i) {

        std::string s = arguments[i].As<Napi::String>().Utf8Value();
        vecList[i] = s;
    }
    bool result = this->sequenceCapture->Open(vecList);
    return NapiExtra::toNapi(env, result);
}

// bool OpenWebcam(int device_id, int image_width = 640, int image_height = 480, float fx = -1, float fy = -1, float cx = -1, float cy = -1);
Napi::Value Nodoface::SequenceCapture::OpenWebcam(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    size_t argLen = info.Length();
    if (argLen == 0) {
        JSErrors::InsufficientArguments(env, 1, argLen);
    } else if (argLen >= 1 && !info[0].IsNumber()) {
        JSErrors::IncorrectDatatype(env, JSErrors::NUMBER, 0);
    } else if (argLen > 7) {
        JSErrors::TooManyArguments(env, 7, argLen);
    }

    uint8_t i = 0;
    int device_id = info[i].As<Napi::Number>().Int32Value();
    i++;
    int image_wd = argLen > i && info[i].IsNumber() ? info[i].As<Napi::Number>().Int32Value() : 640;
    i++;
    int image_ht = argLen > i && info[i].IsNumber() ? info[i].As<Napi::Number>().Int32Value() : 480;
    i++;
    float fx = argLen > i && info[i].IsNumber() ? info[i].As<Napi::Number>().FloatValue() : -1;
    i++;
    float fy = argLen > i && info[i].IsNumber() ? info[i].As<Napi::Number>().FloatValue() : -1;
    i++;
    float cx = argLen > i && info[i].IsNumber() ? info[i].As<Napi::Number>().FloatValue() : -1;
    i++;
    float cy = argLen > i && info[i].IsNumber() ? info[i].As<Napi::Number>().FloatValue() : -1;

    bool result = this->sequenceCapture->OpenWebcam(device_id, image_wd, image_ht, fx, fy, cx, cy);
    return NapiExtra::toNapi(env, result);
}

// bool OpenVideoFile(std::string video_file, float fx = -1, float fy = -1, float cx = -1, float cy = -1);
Napi::Value Nodoface::SequenceCapture::OpenVideoFile(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    size_t argLen = info.Length();
    if (argLen == 0) {
        JSErrors::InsufficientArguments(env, 1, argLen);
    } else if (argLen >= 1 && !info[0].IsString()) {
        JSErrors::IncorrectDatatype(env, JSErrors::NUMBER, 0);
    } else if (argLen > 5) {
        JSErrors::TooManyArguments(env, 5, argLen);
    }

    uint8_t i = 0;
    std::string videoFile = info[i].As<Napi::String>().Utf8Value();
    i++;
    float fx = argLen > i && info[i].IsNumber() ? info[i].As<Napi::Number>().FloatValue() : -1;
    i++;
    float fy = argLen > i && info[i].IsNumber() ? info[i].As<Napi::Number>().FloatValue() : -1;
    i++;
    float cx = argLen > i && info[i].IsNumber() ? info[i].As<Napi::Number>().FloatValue() : -1;
    i++;
    float cy = argLen > i && info[i].IsNumber() ? info[i].As<Napi::Number>().FloatValue() : -1;

    bool result = this->sequenceCapture->OpenVideoFile(videoFile, fx, fy, cx, cy);
    return NapiExtra::toNapi(env, result);
}

Napi::Value Nodoface::SequenceCapture::IsWebcam(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return NapiExtra::toNapi(env, this->sequenceCapture->IsWebcam());
}

Napi::Value Nodoface::SequenceCapture::IsOpened(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return NapiExtra::toNapi(env, this->sequenceCapture->IsOpened());
}

Napi::Value Nodoface::SequenceCapture::GetNextFrame(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::EscapableHandleScope scope(env);
    cv::Mat img = this->sequenceCapture->GetNextFrame();
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
    Napi::Object imgObj = Nodoface::Image::NewObject(env, img).As<Napi::Object>();
    return scope.Escape(imgObj);
}

Napi::Value Nodoface::SequenceCapture::GetGrayFrame(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::EscapableHandleScope scope(env);
    cv::Mat img = this->sequenceCapture->GetGrayFrame();
    Napi::Object imgObj = Nodoface::Image::NewObject(env, img).As<Napi::Object>();
    return scope.Escape(imgObj);
}


Napi::Value Nodoface::SequenceCapture::GetProgress(const Napi::CallbackInfo &info) {
    double progress = this->sequenceCapture->GetProgress();
    return NapiExtra::toNapi(info.Env(), progress);
}

Napi::Value Nodoface::SequenceCapture::GetFrameNumber(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return NapiExtra::toNapi(env, (int) (this->sequenceCapture->GetFrameNumber()));
}

// GetSet for public variables
// int image_width;
Napi::Value Nodoface::SequenceCapture::GetFrameWidth(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return NapiExtra::toNapi(env, this->sequenceCapture->frame_width);
}

void Nodoface::SequenceCapture::SetFrameWidth(const Napi::CallbackInfo &info, const Napi::Value &value) {
    Napi::Env env = info.Env();
    if (!value.IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = value.As<Napi::Number>();
    this->sequenceCapture->frame_width = num.Int32Value();
}

// int image_height
Napi::Value Nodoface::SequenceCapture::GetFrameHeight(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return NapiExtra::toNapi(env, this->sequenceCapture->frame_height);
}

void Nodoface::SequenceCapture::SetFrameHeight(const Napi::CallbackInfo &info, const Napi::Value &value) {
    Napi::Env env = info.Env();
    if (!value.IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = value.As<Napi::Number>();
    this->sequenceCapture->frame_height = num.Int32Value();
}

// float fx, fy, cx, cy;
Napi::Value Nodoface::SequenceCapture::GetFx(const Napi::CallbackInfo &info) {
    return NapiExtra::toNapi(info.Env(), this->sequenceCapture->fx);
}

Napi::Value Nodoface::SequenceCapture::GetFy(const Napi::CallbackInfo &info) {
    return NapiExtra::toNapi(info.Env(), this->sequenceCapture->fy);
}

Napi::Value Nodoface::SequenceCapture::GetCx(const Napi::CallbackInfo &info) {
    return NapiExtra::toNapi(info.Env(), this->sequenceCapture->cx);
}

Napi::Value Nodoface::SequenceCapture::GetCy(const Napi::CallbackInfo &info) {
    return NapiExtra::toNapi(info.Env(), this->sequenceCapture->cy);
}

void Nodoface::SequenceCapture::SetFx(const Napi::CallbackInfo &info, const Napi::Value &value) {
    Napi::Env env = info.Env();
    if (!value.IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = value.As<Napi::Number>();
    this->sequenceCapture->fx = num.DoubleValue();
}

void Nodoface::SequenceCapture::SetFy(const Napi::CallbackInfo &info, const Napi::Value &value) {
    Napi::Env env = info.Env();
    if (!value.IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = value.As<Napi::Number>();
    this->sequenceCapture->fy = num.DoubleValue();
}

void Nodoface::SequenceCapture::SetCx(const Napi::CallbackInfo &info, const Napi::Value &value) {
    Napi::Env env = info.Env();
    if (!value.IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = value.As<Napi::Number>();
    this->sequenceCapture->cx = num.DoubleValue();
}

void Nodoface::SequenceCapture::SetCy(const Napi::CallbackInfo &info, const Napi::Value &value) {
    Napi::Env env = info.Env();
    if (!value.IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = value.As<Napi::Number>();
    this->sequenceCapture->cy = num.DoubleValue();
}

// double fps;
Napi::Value Nodoface::SequenceCapture::GetFPS(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return NapiExtra::toNapi(env, this->sequenceCapture->fps);
}

void Nodoface::SequenceCapture::SetFPS(const Napi::CallbackInfo &info, const Napi::Value &value) {
    Napi::Env env = info.Env();
    if (!value.IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = value.As<Napi::Number>();
    this->sequenceCapture->fps = num.DoubleValue();
}

// double time_stamp;
Napi::Value Nodoface::SequenceCapture::GetTimeStamp(const Napi::CallbackInfo &info) {
    return NapiExtra::toNapi(info.Env(), this->sequenceCapture->time_stamp);
}

void Nodoface::SequenceCapture::SetTimeStamp(const Napi::CallbackInfo &info, const Napi::Value &value) {
    Napi::Env env = info.Env();
    if (!value.IsNumber()) {
        JSErrors::SetterError(env, JSErrors::NUMBER);
    }
    Napi::Number num = value.As<Napi::Number>();
    this->sequenceCapture->time_stamp = num.DoubleValue();
}

// Name of the video file, image directory, or the webcam
// std::string name;
Napi::Value Nodoface::SequenceCapture::GetName(const Napi::CallbackInfo &info) {
    return NapiExtra::toNapi(info.Env(), this->sequenceCapture->name);
}

void Nodoface::SequenceCapture::SetName(const Napi::CallbackInfo &info, const Napi::Value &value) {
    Napi::Env env = info.Env();
    if (!value.IsNumber()) {
        JSErrors::SetterError(env, JSErrors::STRING);
    }
    Napi::String str = value.As<Napi::String>();
    this->sequenceCapture->name = str.Utf8Value();
}

// Allows to differentiate if failed because no input specified or if failed to open a specified input
// bool no_input_specified;
Napi::Value Nodoface::SequenceCapture::GetNoInputSpecified(const Napi::CallbackInfo &info) {
    return NapiExtra::toNapi(info.Env(), this - sequenceCapture->no_input_specified);
}

void Nodoface::SequenceCapture::SetNoInputSpecified(const Napi::CallbackInfo &info, const Napi::Value &value) {
    Napi::Env env = info.Env();
    if (!value.IsNumber()) {
        JSErrors::SetterError(env, JSErrors::BOOLEAN);
    }
    Napi::Boolean val = value.As<Napi::Boolean>();
    this->sequenceCapture->no_input_specified = val.Value();
}

// Storing the captured data queue
// static const int CAPTURE_CAPACITY = 200; // 200 MB
Napi::Value Nodoface::SequenceCapture::GetCaptureCapacity(const Napi::CallbackInfo &info) {
    return NapiExtra::toNapi(info.Env(), Utilities::SequenceCapture::CAPTURE_CAPACITY);
}

Nodoface::SequenceCapture::~SequenceCapture() {
    if(this->sequenceCapture->IsOpened()) {
        this->sequenceCapture->Close();
    }
    delete this->sequenceCapture;
}
