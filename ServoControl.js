//var b = require('bonescript');
var xSERVO = 'P9_14';
var ySERVO = 'P9_22';

//Servo info
var increment = 0.01;
var xposition = 0.55;
var yposition = 0.6;
var duty_min = 0.03;

var xmin = 0.3;
var ymin = 0.5;
var xmax = 0.9;
var ymax = 0.8;

var stdin = [0, 0];
//Variables end

//b.pinMode(xSERVO, b.ANALOG_OUTPUT);
//b.pinMode(ySERVO, b.ANALOG_OUTPUT);
updateDuty();

var readline = require('readline');
var rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});
rl.on('line', onLine);

function updateDuty() {
    // compute and adjust duty_cycle based on
    // desired position in range 0..1
    var duty_cycle = (xposition * 0.115) + duty_min;
    //b.analogWrite(xSERVO, duty_cycle, 60);
    var Yduty_cycle = (yposition * 0.115) + duty_min;
    //b.analogWrite(ySERVO, Yduty_cycle, 60);
}

function onLine(line) {
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
