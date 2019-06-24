//
// Created by sziraqui on 23/6/19.
//

#ifndef NODOFACE_GAZEANALYSER_H
#define NODOFACE_GAZEANALYSER_H

#include <opencv2/core/types.hpp>

#include <OpenFace/GazeEstimation.h>

#include <napi.h>

#include "../jserrors/JSErrors.h"
#include "../landmarkdetection/CLNF.h"
#include "../extras/napiextra.h"
#include "../cvtypes/MatFloat.h"

namespace Nodoface {
    class GazeAnalyser : public Napi::ObjectWrap<Nodoface::GazeAnalyser> {
    public:
        static Napi::Object Init(Napi::Env env, Napi::Object exports);

        static Napi::Object NewObject();

        GazeAnalyser(const Napi::CallbackInfo &info);

    private:
        static Napi::FunctionReference constructor;

//        void EstimateGaze(const LandmarkDetector::CLNF& clnf_model, cv::Point3f& gaze_absolute, float fx, float fy, float cx, float cy, bool left_eye);
        Napi::Value EstimateGaze(const Napi::CallbackInfo &info);

        // Getting the gaze angle in radians with respect to the world coordinates (camera plane), when looking ahead straight at camera plane the gaze angle will be (0,0)
//        cv::Vec2f GetGazeAngle(cv::Point3f& gaze_vector_1, cv::Point3f& gaze_vector_2);
        Napi::Value GetGazeAngle(const Napi::CallbackInfo &info);

        // Some utilities
//        cv::Point3f GetPupilPosition(cv::Mat_<float> eyeLdmks3d);
        Napi::Value GetPupilPosition(const Napi::CallbackInfo &info);
    };
}

#endif //NODOFACE_GAZEANALYSER_H
