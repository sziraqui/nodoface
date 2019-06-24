//
// Created by sziraqui on 14/6/19.
//

#ifndef NODOFACE_NAPIEXTRA_H
#define NODOFACE_NAPIEXTRA_H
// system includes
#include <vector>
#include <string>
// opencv includes
#include <opencv2/core/types.hpp>

// napi
#include <napi.h>

// local includes
#include "ndarray.h"

namespace NapiExtra {


    static Napi::Boolean toNapi(Napi::Env env, bool val) {
        return Napi::Boolean::New(env, val);
    }

    static Napi::Number toNapi(Napi::Env env, int val) {
        return Napi::Number::New(env, val);
    }

    static Napi::Number toNapi(Napi::Env env, double val) {
        return Napi::Number::New(env, val);
    }

    static Napi::String toNapi(Napi::Env env, std::string &val) {
        return Napi::String::New(env, val);
    }

    template<typename anyType>
    static Napi::Array toNapiArray(Napi::Env env, std::vector<anyType> &vec) {
        Napi::Array array = Napi::Array::New(env, vec.size());
        for (uint i = 0; i < vec.size(); ++i) {
            array[i] = toNapi(env, vec[i]);
        }
        return array;
    }

    template<class numericType = int>
    static Napi::Object cv2Napi(Napi::Env env, cv::Point_<numericType> &point) {
        auto obj = Napi::Object::New(env);
        obj["x"] = Napi::Number::New(env, point.x);
        obj["y"] = Napi::Number::New(env, point.y);
        return obj;
    }

    template<class numericType = int>
    static Napi::Object cv2Napi(Napi::Env env, cv::Point3_<numericType> point) {
        auto obj = Napi::Object::New(env);
        obj["x"] = Napi::Number::New(env, point.x);
        obj["y"] = Napi::Number::New(env, point.y);
        obj["y"] = Napi::Number::New(env, point.z);
        return obj;
    }

    template<class numericType = int>
    static Napi::Object cv2Napi(Napi::Env env, cv::Rect_<numericType> &rect) {
        auto obj = Napi::Object::New(env);
        obj["x"] = Napi::Number::New(env, rect.x);
        obj["y"] = Napi::Number::New(env, rect.y);
        obj["width"] = Napi::Number::New(env, rect.width);
        obj["height"] = Napi::Number::New(env, rect.height);
        return obj;
    }

    template<typename anyType>
    static Napi::Array cv2NapiArray(Napi::Env env, std::vector<anyType> &vec) {
        Napi::Array array = Napi::Array::New(env, vec.size());
        for (uint i = 0; i < vec.size(); ++i) {
            array[i] = cv2Napi(env, vec[i]);
        }
        return array;
    }

    static cv::Rect Napi2Rect(Napi::Object rectObj) {
        int x = rectObj.Get("x").As<Napi::Number>().Int32Value();
        int y = rectObj.Get("y").As<Napi::Number>().Int32Value();
        int w = rectObj.Get("width").As<Napi::Number>().Int32Value();
        int h = rectObj.Get("height").As<Napi::Number>().Int32Value();
        return cv::Rect(x, y, w, h);
    }

    static std::vector<cv::Rect> Napi2RectVector(Napi::Array arr) {
        std::vector<cv::Rect> vec(arr.Length());
        for (uint i = 0; i < vec.size(); ++i) {
            vec[i] = Napi2Rect(arr.Get(i).As<Napi::Object>());
        }
        return vec;
    }

    static cv::Scalar Napi2ScalarBgr(Napi::Object rgbColor) {
        uchar r = rgbColor.Has(0u) ? rgbColor.Get(0u).As<Napi::Number>().Uint32Value() : 0;
        uchar g = rgbColor.Has(1u) ? rgbColor.Get(1u).As<Napi::Number>().Uint32Value() : 0;
        uchar b = rgbColor.Has(2u) ? rgbColor.Get(2u).As<Napi::Number>().Uint32Value() : 0;
        const cv::Scalar bgrColor(b, g, r);
        return bgrColor;
    }

    static std::vector<std::string> Napi2StringVector(const Napi::Array arr) {
        std::vector<std::string> vec(arr.Length());
        for (uint i = 0; i < vec.size(); ++i) {
            vec[i] = arr[i].As<Napi::String>().Utf8Value();
        }
        return vec;
    }

    template<class numericType>
    static cv::Point_<numericType> Napi2Point(Napi::Object obj) {
        numericType x = (numericType) obj.Get("x").As<Napi::Number>().DoubleValue();
        numericType y = (numericType) obj.Get("y").As<Napi::Number>().DoubleValue();
        return cv::Point_<numericType>(x, y);
    }

    template<class numericType>
    static cv::Point3_<numericType> Napi2Point3(Napi::Object obj) {
        numericType x = (numericType) obj.Get("x").As<Napi::Number>().DoubleValue();
        numericType y = (numericType) obj.Get("y").As<Napi::Number>().DoubleValue();
        numericType z = (numericType) obj.Get("z").As<Napi::Number>().DoubleValue();
        return cv::Point3_<numericType>(x, y, z);
    }

}

#endif //NODOFACE_NAPIEXTRA_H
