const nodoface = require("../api/nodoface");
let sequenceCapture = new nodoface.SequenceCapture();

const argv = process.argv.slice(1);

sequenceCapture.openWebCam(0);

console.log('Actual properties',
    '\nprogress', sequenceCapture.getProgress(),
    '\nframe Ht', sequenceCapture.getFrameHeight(),
    '\nframe Wd', sequenceCapture.getFrameWidth(),
    '\nFx', sequenceCapture.getFx(),
    '\nFy', sequenceCapture.getFy(),
    '\nCx', sequenceCapture.getCx(),
    '\nCy', sequenceCapture.getCy(),
);
// let img = sequenceCapture.getNextFrame();
// console.log(`nextSequence is Uint8Array: ${img instanceof Uint8Array} | size: ${img.length}`);
//
// let grayImg = sequenceCapture.getGrayFrame();
// console.log(`grayFrame is Uint8Array: ${grayImg instanceof Uint8Array}| size: ${grayImg.length}`);
//
// console.log('New properties',
//     '\nprogress', sequenceCapture.getProgress(),
//     '\nSequence Ht', sequenceCapture.getFrameHeight(),
//     '\nSequence Wd', sequenceCapture.getFrameWidth(),
//     '\nFx', sequenceCapture.getFx(),
//     '\nFy', sequenceCapture.getFy(),
//     '\nCx', sequenceCapture.getCx(),
//     '\nCy', sequenceCapture.getCy(),
// );
// sequenceCapture.getNextFrame();
//
// let bboxes = sequenceCapture.getBoundingBoxes();
// console.log(`bboxes is Array: ${Array.isArray(bboxes)}| size: ${bboxes.length}`);
// for(let rect of bboxes) {
//     console.log(`x:${rect.x}, y:${rect.y}, w:${rect.width}, h:${rect.height}`);
// }