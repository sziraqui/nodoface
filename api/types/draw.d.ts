import { Image } from "./Image";
import { Rect } from "./Rect";
import { Point } from "./Point";

export function drawRect(image: Image, rect: Rect, color: number[]);
export function drawRect(image: Image, rect: Rect, color: number[], thickness: number);
export function drawRect(image: Image, rect: Rect, color: number[], thickness: number, lineType: number);
export function drawText(image: Image, text: string, point: Point, color: [number, number, number]);
export function drawText(image: Image, text: string, point: Point, color: [number, number, number], fontScale: number, thickness: number);
