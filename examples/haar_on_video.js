const nodoface = require("../api/nodoface");
let sequenceCapture = new nodoface.SequenceCapture();
let haar = new nodoface.FaceDetectorHaar();

const argv = process.argv.slice(2);

sequenceCapture.openVideoFile(argv[0]);
haar.load(argv[1]);

img = sequenceCapture.getNextFrame();
console.log(`Frame: rows:${img.height()}, cols:${img.width()}, channels:${img.channels()}`);
let res = haar.detectFaces(sequenceCapture.getGrayFrame());

for (let i = 0; sequenceCapture.isOpened() && sequenceCapture.getProgress() < 1; i++) {
    console.log(`Frame ${i} detections [Progress ${(100 * sequenceCapture.getProgress()).toFixed(2)}%]:`);
    let bboxes = res.detections;
    let conf = res.confidences;
    for (let j = 0; j < bboxes.length; j++) {
        let rect = bboxes[j];
        console.log(`\tDetection ${j}: 
            x:${rect.x.toFixed(0)}, y:${rect.y.toFixed(0)}, 
            width:${rect.width.toFixed(0)}, height:${rect.height.toFixed(0)} | 
            Confidence:${conf[j].toFixed(2)}`
        );
        nodoface.drawRect(img, bboxes[j], [0, 255, 0]);
    }
    nodoface.showImage(img, 'output');
    nodoface.waitKey(1000 / sequenceCapture.fps);
    img = sequenceCapture.getNextFrame();
    res = haar.detectFaces(sequenceCapture.getGrayFrame());
}
nodoface.destroyAllWindows();
