import {Image} from "./Image";
import {Rect} from "./Rect";

export function rectangle(image: Image, rect: Rect, color: number[]);
export function rectangle(image: Image, rect: Rect, color: number[], thickness: number);
export function rectangle(image: Image, rect: Rect, color: number[], thickness: number, lineType: number);