import {Image} from "./Image";
import {Rect} from "./Rect";

export function drawRect(image: Image, rect: Rect, color: number[]): undefined;
export function drawRect(image: Image, rect: Rect, color: number[], thickness: number): undefined;
export function drawRect(image: Image, rect: Rect, color: number[], thickness: number, lineType: number): undefined;