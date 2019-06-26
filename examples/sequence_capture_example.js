const nodoface = require("../api/nodoface");
let sequenceCapture = new nodoface.SequenceCapture();

const argv = process.argv.slice(2);

sequenceCapture.openVideoFile(argv[0])

console.log('Actual properties',
    '\nprogress', sequenceCapture.getProgress(),
    '\nframe Ht', sequenceCapture.height,
    '\nframe Wd', sequenceCapture.width,
    '\nFx', sequenceCapture.fx,
    '\nFy', sequenceCapture.fy,
    '\nCx', sequenceCapture.cx,
    '\nCy', sequenceCapture.cy,
);
let img = sequenceCapture.getNextFrame();
console.log(`Image: rows:${img.height()}, cols:${img.width()}, channels:${img.channels()}`);

let grayImg = sequenceCapture.getGrayFrame();
console.log(`Image: rows:${grayImg.height()}, cols:${img.width()}, channels:${grayImg.channels()}`);

console.log('New properties',
    '\nprogress', sequenceCapture.getProgress(),
    '\nSequence Ht', sequenceCapture.height,
    '\nSequence Wd', sequenceCapture.width,
    '\nFrame number', sequenceCapture.getFrameNumber(),
    '\nFx', sequenceCapture.fx,
    '\nFy', sequenceCapture.fy,
    '\nCx', sequenceCapture.cx,
    '\nCy', sequenceCapture.cy,
);
for (let i = 2; sequenceCapture.getProgress() < 1; i++) {
    img = sequenceCapture.getNextFrame();
    nodoface.showImage(img, 'output');
    nodoface.waitKey(1000 / sequenceCapture.fps);
    console.log(`Frame[${i}]: rows:${img.height()}, cols:${img.width()}, channels:${img.channels()}`);
}
nodoface.destroyAllWindows();
