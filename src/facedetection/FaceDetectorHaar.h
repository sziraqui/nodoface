//
// Created by sziraqui on 26/6/19.
//

#ifndef NODOFACE_FACEDETECTORHAAR_H
#define NODOFACE_FACEDETECTORHAAR_H

#include <opencv2/opencv.hpp>

#include <OpenFace/LandmarkDetectorUtils.h>

#include <napi.h>

namespace Nodoface {
class FaceDetectorHaar : public Napi::ObjectWrap<Nodoface::FaceDetectorHaar> {
    public:

        static Napi::Object Init(Napi::Env env, Napi::Object exports);

        static Napi::Object NewObject(Napi::Env env, std::string txtPath);

//    Constructors
//          FaceDetectorHaar() {  }
//          FaceDetectorHaar(const string& location);
        FaceDetectorHaar(const Napi::CallbackInfo &info);


    private:
        static Napi::FunctionReference constructor;

        // Given an image, orientation and detected landmarks output the result of the appropriate regressor
        // void DetectFaces(vector<cv::Rect_<float> >& o_regions, const cv::Mat_<uchar>& intensity, cv::CascadeClassifier& classifier, float min_width, cv::Rect_<float> roi)
        Napi::Value DetectFaces(const Napi::CallbackInfo &info);

        // Reading in the model
        //    void Read(const string& location);
        Napi::Value Read(const Napi::CallbackInfo &info);

        cv::CascadeClassifier* model;

        // Internal instance
    };
}


#endif //NODOFACE_FACEDETECTORHAAR_H
