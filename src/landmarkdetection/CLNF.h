//
// Created by sziraqui on 22/6/19.
//

#ifndef NODOFACE_CLNF_H
#define NODOFACE_CLNF_H

#include <vector>
#include <string>

#include <opencv2/core/mat.hpp>

#include <OpenFace/LandmarkDetectorModel.h>

#include <napi.h>

#include "../extras/napiextra.h"
#include "../jserrors/JSErrors.h"
#include "../cvtypes/Mat.h"

namespace Nodoface {

    // Wrapper for OpenFace CLNF face model that computes face landmarks and bounding box
class CLNF : public Napi::ObjectWrap<CLNF> {
    public:
        static Napi::Object Init(Napi::Env, Napi::Object);

        static Napi::Object NewObject(Napi::Env, std::string&);

        CLNF(const Napi::CallbackInfo&);

        CLNF GetInternalInstance();

        ~CLNF();

    private:
        static Napi::FunctionReference constructor;

        // internal instance
        LandmarkDetector::CLNF* instance;

    // Does the actual work - landmark detection
//    bool DetectLandmarks(const cv::Mat_<uchar> &image, FaceModelParameters& params);
        Napi::Value DetectLandmarks(const Napi::CallbackInfo&);

    // Gets the shape of the current detected landmarks in camera space (given camera calibration)
    // Can only be called after a call to DetectLandmarksInVideo or DetectLandmarksInImage
//    cv::Mat_<float> GetShape(float fx, float fy, float cx, float cy) const;
        Napi::Value GetShape(const Napi::CallbackInfo&);

    // A utility bounding box function
//    cv::Rect_<float> GetBoundingBox() const;
        Napi::Value GetBoundingBox(const Napi::CallbackInfo&);

    // Get the currently non-self occluded landmarks
//    cv::Mat_<int> GetVisibilities() const;
        Napi::Value GetVisibilities(const Napi::CallbackInfo&);

    // Reset the model (useful if we want to completelly reinitialise, or we want to track another video)
//    void Reset();
    // Reset the model, choosing the face nearest (x,y) where x and y are between 0 and 1.
//    void Reset(double x, double y);
        Napi::Value Reset(const Napi::CallbackInfo&);

    // Reading the model in
//    void Read(string name);
        Napi::Value Read(const Napi::CallbackInfo&);
    };
}


#endif //NODOFACE_CLNF_H
