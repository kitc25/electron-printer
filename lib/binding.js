const addon = require('./electron_printer.node');
module.exports.sayMyName = addon.SayMyName
module.exports.getPrinters = addon.getPrinters
module.exports.printDirect = function (e){
    return ""; // @todo will be implemented soon
}

module.exports.getDefaultPrinterName = function (){
    return ""  // @todo will be implemented soon
} 
