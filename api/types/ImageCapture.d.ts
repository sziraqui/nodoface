import {Image} from "./Image";
import {Rect} from "./Rect";

export interface ImageCapture {
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

    getImageWidth(): number;

    getImageHeight(): number;

    setImageWidth(): number;

    setImageHeight(): number;

    getFx(): number;

    getFy(): number;

    getCx(): number;

    getCy(): number;

    setFx(fx: number);

    setFy(fy: number);

    setCx(cx: number);

    setCy(cy: number);
}