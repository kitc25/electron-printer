const addon = require("../lib/binding.js");
const sayMyName = addon.sayMyName;

console.log("Say my name:", sayMyName());