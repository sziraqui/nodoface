import {Image} from "./Image";

export class FaceDetectorMTCNN {
    constructor();
    constructor(modelFile: string);
    constructor(instance: FaceDetectorMTCNN);

    detectFaces(image: Image);
    detectFaces(image: Image, minFace: number);
    detectFaces(image: Image, minFace: number, t1: number);
    detectFaces(image: Image, minFace: number, t1: number, t2: number);
    detectFaces(image: Image, minFace: number, t1: number, t2: number, t3: number);

    load(modelFile: string): undefined;

    empty(): boolean;
}