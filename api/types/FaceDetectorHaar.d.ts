import {Image} from "./Image";

export class FaceDetectorHaar {
    constructor();
    constructor(modelFile: string);
    constructor(instance: FaceDetectorHaar);

    detectFaces(image: Image);
    detectFaces(image: Image, minWidth: number);
    detectFaces(image: Image, minWidth: number, roi: number);

    load(modelFile: string): undefined;

    empty(): boolean;
}