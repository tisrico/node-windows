const events = require('events');
const bindings = require('bindings');

exports.load = function(module) {
  var addon = bindings(module);
  for(var ix in addon) {
    var a = addon[ix];
    if(a.prototype == undefined) 
      continue;
     exports.inherits(a, events);
     exports.inherits(a, messaging);
  }
  return addon;
}

exports.inherits = function(target, source) {
  for (var k in source.prototype)
    target.prototype[k] = source.prototype[k];
}

function messaging() {
}

messaging.prototype = {
  post: function(evt) {
   var args = arguments;
   setImmediate(()=> {
     this.emit.apply(this, args);
  });
 },

 send:function(evt) {
   this.emit.apply(this, arguments);
 }
}
