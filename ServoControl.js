var b = require('bonescript');
var SERVO = 'P9_14';
var duty_min = 0.03;
var position = 0;
var increment = 0.01;
var xposition = 0.55;
var yposition = 0.6;
var xmin = 0.3;
var ymin = 0.5;
var xmax = 0.9;
var ymax = 0.8;
var stdin = [0, 0];
//Variables end

rl.on('line', onLine);
var readline = require('readline');
var rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
  terminal: false
});

b.pinMode(SERVO, b.ANALOG_OUTPUT);
updateDuty();

function onLine('line') {
    updateDuty();
    console.log(line);
    stdin = line.split(" ");
    if (stdin[0] > 20) {
        xposition = (xposition - increment);
    }
    if (stdin[0] < -20) {
        xposition = (xposition + increment);
    }
    if (stdin[1] < -20) {
        yposition = (yposition + increment);
    }
    if (stdin[1] > 20) {
        yposition = (yposition - increment);
    }
    if (xposition < xmin) xposition = xmin;
    if (xposition > xmax) xposition = xmax;
    if (yposition < ymin) yposition = ymin;
    if (yposition > ymax) yposition = ymax;
    updateDuty();
}

function updateDuty() {
    // compute and adjust duty_cycle based on
    // desired position in range 0..1
    var duty_cycle = (position*0.115) + duty_min;
    b.analogWrite(SERVO, duty_cycle, 60);
    console.log("Duty Cycle: " + 
        parseFloat(duty_cycle*100).toFixed(1) + " %");   
}


