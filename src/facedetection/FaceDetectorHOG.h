//
// Created by sziraqui on 27/6/19.
//

#ifndef NODOFACE_FACEDETECTORHOG_H
#define NODOFACE_FACEDETECTORHOG_H

#include <OpenFace/LandmarkDetectorUtils.h>

#include "../jserrors/JSErrors.h"
#include "../cvtypes/Mat.h"
#include "../extras/napiextra.h"

namespace Nodoface {
class FaceDetectorHOG : public Napi::ObjectWrap<Nodoface::FaceDetectorHOG>{
    public:

        static Napi::Object Init(Napi::Env env, Napi::Object exports);

        static Napi::Object NewObject(Napi::Env env, std::string txtPath);

//    Constructors
//          FaceDetectorHOG() {  }
//          FaceDetectorHOG(const string& location);
        FaceDetectorHOG(const Napi::CallbackInfo &info);


    private:
        static Napi::FunctionReference constructor;

        // Given an image, orientation and detected landmarks output the result of the appropriate regressor
        // void DetectFaces(vector<cv::Rect_<float> >& o_regions, const cv::Mat_<uchar>& intensity, dlib::frontal_face_detector &detector, std::vector<float> &confidences, float min_width, cv::Rect_<float> roi)
        Napi::Value DetectFaces(const Napi::CallbackInfo &info);

        // Reading in the model
        //    void Read(const string& location);
        Napi::Value Read(const Napi::CallbackInfo &info);

        dlib::frontal_face_detector* model;
    };
}



#endif //NODOFACE_FACEDETECTORHOG_H
