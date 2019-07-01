import {Image} from "./Image";
import {Rect} from "./Rect";

export function drawRect(image: Image, rect: Rect, color: number[]);
export function drawRect(image: Image, rect: Rect, color: number[], thickness: number);
export function drawRect(image: Image, rect: Rect, color: number[], thickness: number, lineType: number);
