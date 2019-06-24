import {CLNF} from "./CLNF";
import {Point3} from "./Point3";
import {FloatImage} from "./FloatImage";

export class GazeAnalyser {
    constructor();
    estimateGaze(landmarkModel: CLNF, fx: number, fy: number, cx: number, cy: number, leftEye: boolean): Point3;
    getGazeAngle(gazeVector1: Point3, gazeVector2: Point3): number[];
    getPupilPosition(eyeLandmarks: FloatImage): Point3;
}