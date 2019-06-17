const nodoface = require('../api/nodoface');
let argv = process.argv.slice(2);
let img = nodoface.readImage(argv[0]);
console.log('image', img);
nodoface.showImage(img);
