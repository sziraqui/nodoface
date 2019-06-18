const nodoface = require('../api/nodoface');
console.log('INFO: Uncomment DEBUG_MATWRAPPER in binding.gyp "defines" and rebuild to run this example');
let argv = process.argv.slice(2);
console.log(argv);
let img = nodoface.readImage(argv[0]);
nodoface.showImage(img, "Show Image", 1000);
