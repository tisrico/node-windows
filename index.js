const vm = require('vm');
const message = require('./messaging.js');
const EventEmitter = require('events');
const addon = message.load('addon');

var obj = new addon.MyObject(10);
var sb = new addon.SandBox();
var wind = new addon.Window();
var out = 0;

obj.on('plused', (a)=> { console.log('plused:', a, out++);});
sb.on('added', (a)=> { console.log('added', a, out++);});

sb.add("obj1", obj);
sb.add("obj2", obj);
sb.add("console", console);

console.log(obj.value()); 

var script = new vm.Script("obj1.plusOne(); obj2.plusOne();");

for (var i = 0; i < 3; ++i) {
  const context = new vm.createContext(sb);
  script.runInContext(context);
}

console.log(obj.value());
wind.start();
wind.on('window', (a)=> { console.log('window', a);});

setInterval(function () {
  var wind = new addon.Window();
  var x = wind;
  x.start();
  x.on('window', (a)=> { console.log('window', a);});

  console.log("5 sconds")
}, 5000);