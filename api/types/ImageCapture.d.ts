import {Image} from "./Image";
import {Rect} from "./Rect";

export class ImageCapture {
    constructor();

    open(arguments: string[]): boolean;

    openVideoFile(imageDir: string): boolean;

    openDirectory(imageDir: string, bboxDir: string): boolean;

    openDirectory(imageDir: string, bboxDir: string, fx: number, fy: number, cx: number, cy: number): boolean;

    openImageFiles(files: string[]): boolean;

    openImageFiles(files: string[], fx: number, fy: number, cx: number, cy: number): boolean;

    getNextImage(): Image;

    getGrayFrame(): Image;

    getBoundingBoxes(): Rect[];

    getProgress(): number;

    width: number;

    height: number;

    fx: number;

    fy: number;

    cx: number;

    cy: number;
}