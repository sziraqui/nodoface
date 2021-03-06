#!/usr/bin/env ts-node
import * as nodoface from '../';
import { ImageCapture } from '../';

let imageCapture = new ImageCapture();

const argv = process.argv.slice(1);

imageCapture.open(argv);

console.log('Actual properties',
    '\nprogress', imageCapture.getProgress(),
    '\nImage Ht', imageCapture.height,
    '\nImage Wd', imageCapture.width,
    '\nFx', imageCapture.fx,
    '\nFy', imageCapture.fy,
    '\nCx', imageCapture.cx,
    '\nCy', imageCapture.cy,
);
let img = imageCapture.getNextImage();
console.log(`Image: rows:${img.height()}, cols:${img.width()}, channels:${img.channels()}`);
nodoface.showImage(img, 'color');
nodoface.waitKey(0);
nodoface.destroyWindow('color');

let grayImg = imageCapture.getGrayFrame();
console.log(`Image: rows:${grayImg.height()}, cols:${grayImg.width()}, channels:${grayImg.channels()}`);
nodoface.showImage(grayImg, 'gray', true);
nodoface.waitKey(0);
nodoface.destroyWindow('gray');

console.log('New properties',
    '\nprogress', imageCapture.getProgress(),
    '\nImage Ht', imageCapture.height,
    '\nImage Wd', imageCapture.width,
    '\nFx', imageCapture.fx,
    '\nFy', imageCapture.fy,
    '\nCx', imageCapture.cx,
    '\nCy', imageCapture.cy,
);
img = imageCapture.getNextImage();
console.log(`Image: rows:${img.height()}, cols:${img.width()}, channels:${img.channels()}`);
nodoface.showImage(img);
nodoface.waitKey(0);
nodoface.destroyAllWindows();

let bboxes = imageCapture.getBoundingBoxes();
console.log(`bboxes is Array: ${Array.isArray(bboxes)}| size: ${bboxes.length}`);
for (let rect of bboxes) {
    console.log(`x:${rect.x}, y:${rect.y}, w:${rect.width}, h:${rect.height}`);
}
