import {Image} from "./Image";
import {Rect} from "./Rect";

export function rectangle(image: Image, rect: Rect, color: number[]): undefined;
export function rectangle(image: Image, rect: Rect, color: number[], thickness: number): undefined;
export function rectangle(image: Image, rect: Rect, color: number[], thickness: number, lineType: number): undefined;