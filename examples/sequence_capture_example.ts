#!/usr/bin/env ts-node
import * as nodoface from '../';
import { SequenceCapture } from '../';

let sequenceCapture = new SequenceCapture();

const argv = process.argv.slice(1);

sequenceCapture.open(argv);

console.log('Actual properties',
    '\nprogress', sequenceCapture.getProgress(),
    '\nImage Ht', sequenceCapture.height,
    '\nImage Wd', sequenceCapture.width,
    '\nFx', sequenceCapture.fx,
    '\nFy', sequenceCapture.fy,
    '\nCx', sequenceCapture.cx,
    '\nCy', sequenceCapture.cy,
);
let img = sequenceCapture.getNextFrame();
console.log(`Image: rows:${img.height()}, cols:${img.width()}, channels:${img.channels()}`);
nodoface.showImage(img, 'color');
nodoface.waitKey(0);
nodoface.destroyWindow('color');

let grayImg = sequenceCapture.getGrayFrame();
console.log(`Image: rows:${grayImg.height()}, cols:${grayImg.width()}, channels:${grayImg.channels()}`);
nodoface.showImage(grayImg, 'gray', true);
nodoface.waitKey(0);
nodoface.destroyWindow('gray');

console.log('New properties',
    '\nprogress', sequenceCapture.getProgress(),
    '\nImage Ht', sequenceCapture.height,
    '\nImage Wd', sequenceCapture.width,
    '\nFx', sequenceCapture.fx,
    '\nFy', sequenceCapture.fy,
    '\nCx', sequenceCapture.cx,
    '\nCy', sequenceCapture.cy,
);
img = sequenceCapture.getNextFrame();
console.log(`Image: rows:${img.height()}, cols:${img.width()}, channels:${img.channels()}`);
nodoface.showImage(img);
nodoface.waitKey(0);
nodoface.destroyAllWindows();
sequenceCapture.close();
