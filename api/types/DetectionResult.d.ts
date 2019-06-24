import {Rect} from "./Rect";

export interface DetectionResult {
    detections: Rect[];
    confidences: number[];
}