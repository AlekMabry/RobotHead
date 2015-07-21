var b = {};
try {
    b = require('bonescript');
} catch(ex) {
    b.pinMode = function() {};
    b.analogWrite = function() {};
}
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
var lingeringLine = "";
//Variables end

b.pinMode(xSERVO, b.ANALOG_OUTPUT);
b.pinMode(ySERVO, b.ANALOG_OUTPUT);
updateDuty();

process.stdin.resume();
process.stdin.setEncoding('utf8');
process.stdin.on('data', onData);
process.stdin.on('end', onEnd);

function onData(chunk) {
    lines = chunk.split("\n");

    lines[0] = lingeringLine + lines[0];
    lingeringLine = lines.pop();

    lines.forEach(onLine);
}

function onEnd() {
    onLine(lingeringLine);
}

function updateDuty() {
    // compute and adjust duty_cycle based on
    // desired position in range 0..1
    var duty_cycle = (xposition * 0.115) + duty_min;
    b.analogWrite(xSERVO, duty_cycle, 60);
    console.log("duty_cycle: " + duty_cycle);
    var Yduty_cycle = (yposition * 0.115) + duty_min;
    b.analogWrite(ySERVO, Yduty_cycle, 60);
    console.log("Yduty_cycle: " + Yduty_cycle);
}

function onLine(line) {
    console.log(line);
    stdin = line.split(" ");
    if (stdin[0] > 20) {
        xposition = (xposition - subtract_calculate(stdin[0]) );
    }
    if (stdin[0] < -20) {
        xposition = (xposition + add_calculate(stdin[0]) );
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

function subtract_calculate(in){
    var subtracted = (in - 20);
    out = (((subtracted*0.3)/100)/3)
    return out;
}

function add_calculate(in){
    var add = ((in + 20)*-1);
    out = (((subtracted*0.3)/100)/3)
    return out;
}

}
