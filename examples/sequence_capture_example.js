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
let img = sequenceCapture.getNextFrame();
console.log(`Image: rows:${img.height()}, cols:${img.width()}, channels:${img.channels()}`);

let grayImg = sequenceCapture.getGrayFrame();
console.log(`Image: rows:${grayImg.height()}, cols:${img.width()}, channels:${grayImg.channels()}`);

console.log('New properties',
    '\nprogress', sequenceCapture.getProgress(),
    '\nSequence Ht', sequenceCapture.getFrameHeight(),
    '\nSequence Wd', sequenceCapture.getFrameWidth(),
    '\nFrame number', sequenceCapture.getFrameNumber(),
    '\nFx', sequenceCapture.getFx(),
    '\nFy', sequenceCapture.getFy(),
    '\nCx', sequenceCapture.getCx(),
    '\nCy', sequenceCapture.getCy(),
);
img = sequenceCapture.getNextFrame();
for(let i = 2; i < 30; i++) {
    nodoface.showImage(img);
    img = sequenceCapture.getNextFrame();
    console.log(`Frame[${i}]: rows:${img.height()}, cols:${img.width()}, channels:${img.channels()}`);
}
