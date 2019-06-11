const nodoface = require("../api/nodoface");
let imageCapture = new nodoface.ImageCapture();
console.log(imageCapture);
const argv = process.argv.slice(1);
console.log(argv);
imageCapture.open(argv);
console.log('Actual properties',
    '\nprogress', imageCapture.getProgress(),
    '\nImage Ht', imageCapture.getImageHeight(),
    '\nImage Wd', imageCapture.getImageWidth(),
    '\nFx', imageCapture.getFx(),
    '\nFy', imageCapture.getFy(),
    '\nCx', imageCapture.getCx(),
    '\nCy', imageCapture.getCy(),
    '\nNext Image', imageCapture.getNextImage(),
    '\nGray frame', imageCapture.getGrayFrame()
);
imageCapture.setImageWidth(imageCapture.getImageWidth() - 1);
imageCapture.setImageHeight(imageCapture.getImageHeight() - 1);
imageCapture.setFx(imageCapture.getFx() + 1);
imageCapture.setFy(imageCapture.getFy() + 1);
imageCapture.setCx(imageCapture.getCx() + 1);
imageCapture.setCy(imageCapture.getCy() + 1);
console.log('New properties',
    '\nprogress', imageCapture.getProgress(),
    '\nImage Ht', imageCapture.getImageHeight(),
    '\nImage Wd', imageCapture.getImageWidth(),
    '\nFx', imageCapture.getFx(),
    '\nFy', imageCapture.getFy(),
    '\nCx', imageCapture.getCx(),
    '\nCy', imageCapture.getCy(),
    '\nNext Image', imageCapture.getNextImage(),
    '\nGray frame', imageCapture.getGrayFrame()
);