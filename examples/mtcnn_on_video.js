const nodoface = require("../api/nodoface");
let sequenceCapture = new nodoface.SequenceCapture();
let mtcnn = new nodoface.FaceDetectorMTCNN();

const argv = process.argv.slice(2);

sequenceCapture.openVideoFile(argv[0])
mtcnn.read(argv[1]);

img = sequenceCapture.getNextFrame();
console.log(`Frame: rows:${img.height()}, cols:${img.width()}, channels:${img.channels()}`);
let res = mtcnn.detectFaces(img);

for(let i = 2; i < 60; i++) {
    console.log(`res frame[${i}]- bboxes: ${res.detections[0].x},${res.detections[0].y},${res.detections[0].width},${res.detections[0].height} | conf: ${res.confidences[0]}`);
    nodoface.showImage(img, 'output');
    nodoface.waitKey(1000/25);
    img = sequenceCapture.getNextFrame();
    res = mtcnn.detectFaces(img);
}
nodoface.destroyAllWindows();
