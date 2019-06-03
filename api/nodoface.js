let nodoface = null;
if(process.env.NODOFACE_BUILD_TYPE_DEBUG) {
    nodoface = require('../build/Debug/nodoface.node');
} else {
    nodoface = require('../build/Release/nodoface.node');
}
console.log(`nodoface: ${nodoface}`);

module.exports = nodoface;