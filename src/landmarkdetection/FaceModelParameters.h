//
// Created by sziraqui on 22/6/19.
//

#ifndef NODOFACE_FACEMODELPARAMETERS_H
#define NODOFACE_FACEMODELPARAMETERS_H

#include <vector>
#include <string>

#include <napi.h>

#include <OpenFace/LandmarkDetectorParameters.h>

#include "../jserrors/JSErrors.h"
#include "../extras/napiextra.h"

namespace Nodoface {

    class LandmarkModelConfig : public Napi::ObjectWrap<Nodoface::LandmarkModelConfig>{

        public:

            static Napi::Object Init(Napi::Env env, Napi::Object exports);

            static Napi::Value NewObject(Napi::Env env, std::vector<std::string> &arguments);

        //    LandmarkModelConfig();
        //    LandmarkModelConfig(vector<string> &arguments);
            LandmarkModelConfig(const Napi::CallbackInfo& info);

            LandmarkDetector::FaceModelParameters GetInternalInstance();

           ~LandmarkModelConfig();
        private:

            static Napi::FunctionReference constructor;

            LandmarkDetector::FaceModelParameters* instance;

            // Where to load the model from
    //    string model_location;
            Napi::Value GetModelLocation(const Napi::CallbackInfo& info);

            // Based on model location, this affects the parameter settings
//            enum LandmarkDetector { CLM_DETECTOR, CLNF_DETECTOR, CECLM_DETECTOR};
    //    LandmarkDetector curr_landmark_detector;
            Napi::Value GetCurrentLdId(const Napi::CallbackInfo& info);

            // Determining which face detector to use for (re)initialisation, HAAR is quicker but provides more false positives and is not goot for in-the-wild conditions
            // Also HAAR detector can detect smaller faces while HOG SVM is only capable of detecting faces at least 70px across
            // MTCNN detector is much more accurate that the other two, and is even suitable for profile faces, but it is somewhat slower
//            enum FaceDetector{HAAR_DETECTOR, HOG_SVM_DETECTOR, MTCNN_DETECTOR};
    //    FaceDetector curr_face_detector;
            Napi::Value GetCurrentFdId(const Napi::CallbackInfo& info);
    //    string haar_face_detector_location;
            Napi::Value GetHaarLocation(const Napi::CallbackInfo& info);
    //    string mtcnn_face_detector_location;
            Napi::Value GetMtcnnLocation(const Napi::CallbackInfo& info);

    };
}
#endif //NODOFACE_FACEMODELPARAMETERS_H

