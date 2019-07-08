//
// Created by sziraqui on 14/6/19.
//

#ifndef NODOFACE_NAPIEXTRA_H
#define NODOFACE_NAPIEXTRA_H

// system includes
#include <vector>
#include <string>

// opencv includes
#include <opencv2/opencv.hpp>

// napi
#include <napi.h>


namespace NapiExtra {


    Napi::Boolean toNapi(Napi::Env env, bool val);

    Napi::Number toNapi(Napi::Env env, int val);

    Napi::Number toNapi(Napi::Env env, double val);

    Napi::String toNapi(Napi::Env env, std::string &val);

    template<typename anyType>
    Napi::Array toNapiArray(Napi::Env env, std::vector<anyType> &vec);

    template<class numericType = int>
    Napi::Object cv2Napi(Napi::Env env, cv::Point_<numericType> &point);

    template<class numericType = int>
    Napi::Object cv2Napi(Napi::Env env, cv::Point3_<numericType> point);

    template<class numericType = int>
    Napi::Object cv2Napi(Napi::Env env, cv::Rect_<numericType> &rect);

    template<typename anyType>
    Napi::Array cv2NapiArray(Napi::Env env, std::vector<anyType> &vec);

    template <class numericType = int>
    cv::Rect_<numericType> Napi2Rect(Napi::Object rectObj);

    std::vector<cv::Rect> Napi2RectVector(Napi::Array arr);

    cv::Scalar Napi2ScalarBgr(Napi::Object rgbColor);

    std::vector<std::string> Napi2StringVector(const Napi::Array arr);

    template<class numericType>
    cv::Point_<numericType> Napi2Point(Napi::Object obj);

    template<class numericType>
    cv::Point3_<numericType> Napi2Point3(Napi::Object obj);

    Napi::Object detectionResult2Napi(Napi::Env env, std::vector<cv::Rect_<float>> & out_bboxes, std::vector<float> &out_confidences);

    template <class numericType>
    Napi::TypedArrayOf<numericType> cvMat2TypedArray(Napi::Env env, cv::Mat_<numericType>& mat);

    template <class numericType>
    Napi::TypedArrayOf<numericType> cvMat2TypedArray(Napi::Env env, cv::Mat& mat);

}

#endif //NODOFACE_NAPIEXTRA_H
