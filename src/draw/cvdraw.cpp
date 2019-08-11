//
// Created by sziraqui on 21/6/19.
//
#include "cvdraw.h"

using namespace Nodoface;

Napi::Object Draw::Init(Napi::Env env, Napi::Object exports) {
    exports.Set("drawRect", Napi::Function::New(env, Nodoface::Draw::rectangle));
    exports.Set("drawText", Napi::Function::New(env, Nodoface::Draw::putText));
    exports.Set("drawDetections", Napi::Function::New(env, Nodoface::Draw::drawDetections));
    return exports;
}

// args: Image, Rect, color Array/Uint8Array, thickness Number, lineType Number
Napi::Value Draw::rectangle(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int argLen = info.Length();
    if(argLen < 3) {
        JSErrors::InsufficientArguments(env, 3, argLen);
    } else if (argLen > 5) {
        JSErrors::TooManyArguments(env, 5, argLen);
    }
    Napi::Object imgObj = info[0].As<Napi::Object>();
    Nodoface::Image* img = Napi::ObjectWrap<Nodoface::Image>::Unwrap(imgObj);
    cv::Mat mat = img->GetMat();

    cv::Rect rect = NapiExtra::Napi2Rect(info[1].As<Napi::Object>());

    cv::Scalar bgrColor = NapiExtra::Napi2ScalarBgr(info[2].As<Napi::Object>());

    int i = 3;
    int thickness = argLen > i? info[i].As<Napi::Number>().Int32Value(): 1; i++;
    int lineType = argLen > i? info[i].As<Napi::Number>().Int32Value(): cv::LINE_8;

    cv::rectangle(mat, rect, bgrColor, thickness, lineType);

    return env.Undefined();
}

Napi::Value Draw::putText(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int argLen = info.Length();
    if(argLen < 4) {
        JSErrors::InsufficientArguments(env, 4, argLen);
    } else if (argLen > 6) {
        JSErrors::TooManyArguments(env, 6, argLen);
    }
    uint i = 0;
    Napi::Object imgObj = info[i].As<Napi::Object>(); i++;
    Nodoface::Image* img = Napi::ObjectWrap<Nodoface::Image>::Unwrap(imgObj);
    cv::Mat mat = img->GetMat();

    std::string text = info[i].As<Napi::String>().Utf8Value(); i++;

    cv::Point pt = NapiExtra::Napi2Point<int>(info[i].As<Napi::Object>());

    cv::Scalar bgrColor = NapiExtra::Napi2ScalarBgr(info[i].As<Napi::Object>()); i++;

    int scale = argLen > i? info[i].As<Napi::Number>().DoubleValue(): 1; i++;
    int thickness = argLen > i? info[i].As<Napi::Number>().Int32Value(): 1; i++;

    cv::putText(mat, text, pt, cv::FONT_HERSHEY_SIMPLEX, scale, bgrColor, thickness);

    env.Undefined();
}

Napi::Value Draw::drawDetections(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    uint argLen = info.Length();
    // TODO: error handling
    uint i = 0;
    // arg1 image
    Napi::Object imgObj = info[i].As<Napi::Object>(); i++;
    Nodoface::Image* img = Napi::ObjectWrap<Nodoface::Image>::Unwrap(imgObj);
    cv::Mat mat = img->GetMat();
    // arg 2 bounding boxes
    std::vector<cv::Rect> bboxes = NapiExtra::Napi2RectVector(info[i].As<Napi::Array>()); i++;
    // arg 3 text
    std::vector<std::string> texts = NapiExtra::Napi2StringVector(info[i].As<Napi::Array>()); i++;
    // arg 4 colors
    const Napi::Array colorArr = info[i].As<Napi::Array>(); i++;
    std::vector<cv::Scalar> colors(colorArr.Length());
    for(uint c = 0; c < colorArr.Length(); c++) {
        colors[c] = NapiExtra::Napi2ScalarBgr(colorArr[c].As<Napi::Object>());
    }
    // arg 5 fontScale (optional)
    double fontScale = argLen > i? info[i].As<Napi::Number>().DoubleValue(): 1; i++;
    // arg 6 thickness (optional)
    int thickness = argLen > i? info[i].As<Napi::Number>().Int32Value(): 1; i++;

    int fontFace = cv::FONT_HERSHEY_PLAIN;
    for(uint j = 0; j < bboxes.size(); j++) {
        cv::rectangle(mat, bboxes[j], colors[j]);
        int baseline;
        cv::Size textSize = cv::getTextSize(texts[j], fontFace, fontScale, thickness, &baseline);
        baseline += thickness;
        // draw the box
        cv::Rect textBox(bboxes[j].x, bboxes[j].y, textSize.width, textSize.height + baseline);
        cv::Point textOrg(bboxes[j].x, bboxes[j].y + textBox.height/2 + baseline/2);
        cv::rectangle(mat, textOrg + cv::Point(0, baseline), textOrg + cv::Point(textSize.width, -textSize.height), colors[j], cv::FILLED);
        // draw text
        cv::putText(mat, texts[j], textOrg, fontFace, fontScale, cv::Scalar(255, 255, 255) - colors[j], thickness);
    }
    return Nodoface::Image::NewObject(env, mat);
}
