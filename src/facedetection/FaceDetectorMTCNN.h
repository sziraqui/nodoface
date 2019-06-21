//
// Created by sziraqui on 20/6/19.
//

#ifndef NODOFACE_FACEDETECTORMTCNN_H
#define NODOFACE_FACEDETECTORMTCNN_H

#include <vector>
#include <string>
#include <map>
#include <OpenFace/FaceDetectorMTCNN.h>
#include <opencv2/opencv.hpp>
#include <napi.h>

#include "../jserrors/JSErrors.h"
#include "../cvtypes/Mat.h"
#include "../extras/napiextra.h"

namespace Nodoface {
class FaceDetectorMTCNN : public Napi::ObjectWrap<Nodoface::FaceDetectorMTCNN> {
        public:

            static Napi::Object Init(Napi::Env env, Napi::Object exports);

            static Napi::Object NewObject(Napi::Env env, std::string txtPath);

//    Constructors
//          FaceDetectorMTCNN() {  }
//          FaceDetectorMTCNN(const string& location);
//          FaceDetectorMTCNN(const FaceDetectorMTCNN& other);
            FaceDetectorMTCNN(const Napi::CallbackInfo& info);

            LandmarkDetector::FaceDetectorMTCNN GetInternalInstance();
        private:
            static Napi::FunctionReference constructor;

            // Given an image, orientation and detected landmarks output the result of the appropriate regressor
      //    bool DetectFaces(vector<cv::Rect_<float> >& o_regions, const cv::Mat& input_img, std::vector<float>& o_confidences, int min_face = 60, float t1 = 0.6, float t2 = 0.7, float t3 = 0.7);
            Napi::Value DetectFaces(const Napi::CallbackInfo& info);
            // Reading in the model
      //    void Read(const string& location);
            Napi::Value Read(const Napi::CallbackInfo& info);
            // Indicate if the model has been read in
      //    bool empty() { return PNet.NumberOfLayers() == 0 || RNet.NumberOfLayers() == 0 || ONet.NumberOfLayers() == 0; };
            Napi::Value Empty(const Napi::CallbackInfo& info);
            // Internal instance
            LandmarkDetector::FaceDetectorMTCNN* model;
    };
}



#endif //NODOFACE_FACEDETECTORMTCNN_H
