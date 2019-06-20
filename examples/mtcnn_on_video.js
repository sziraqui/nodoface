const nodoface = require("../api/nodoface");
let sequenceCapture = new nodoface.SequenceCapture();
let mtcnn = new nodoface.FaceDetectorMTCNN();

const argv = process.argv.slice(2);

sequenceCapture.openVideoFile(argv[0])
mtcnn.read(argv[1]);

img = sequenceCapture.getNextFrame();
let res = mtcnn.detectFaces(img);

for(let i = 2; i < 60; i++) {
    console.log(`res frame[${i}]: ${res}`);
    nodoface.showImage(img, 'output');
    nodoface.waitKey(0);
    img = sequenceCapture.getNextFrame();
    console.log(`Frame[${i}]: rows:${img.height()}, cols:${img.width()}, channels:${img.channels()}`);
}
nodoface.destroyAllWindows();
