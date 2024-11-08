const addon = require('./electron_printer.node');
module.exports.sayMyName = addon.SayMyName
module.exports.getPrinters = addon.getPrinters
module.exports.printDirect = addon.printDirect
module.exports.getDefaultPrinterName = addon.getDefaultPrinterName
