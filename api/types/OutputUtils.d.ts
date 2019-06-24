import {Image} from "./Image";

export function readImage(filePath: string): Image;

export function showImage(image: Image): undefined;
export function showImage(image: Image, windowName: string): undefined;

export function destroyWindow(windowName: string): undefined;

export function destroyAllWindows(): undefined;

export function waitKey(milliseconds: number): number;