var b = {};
try {
    b = require('bonescript');
} catch(ex) {
    b.pinMode = function() {};
    b.analogWrite = function() {};
}
var xSERVO = 'P9_14';
var ySERVO = 'P9_22';
var leftEyebrow = 'P8_45'

//Servo info
var increment = 0.01;
var xposition = 0.55;
var yposition = 0.6;
var leftEyePos = 0;
var duty_min = 0.03;
var inx = 0;

var xmin = 0.3;
var ymin = 0.5;
var xmax = 0.9;
var ymax = 0.8;
var leftMax = 0.43;
var leftMin = 0;

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
    
    if (stdin[0] != 0 && stdin[1] != 0 ){
        leftEyePos = leftMax;
    } 
    else{
        leftEyePos = leftMin;
    }
    
    var duty_cycle = (xposition * 0.115) + duty_min;
    b.analogWrite(xSERVO, duty_cycle, 60);
    console.log("duty_cycle: " + duty_cycle);
    
    var leftDuty_cycle = (leftEyePos * 0.115) + duty_min;
    b.analogWrite(leftEyebrow, leftDuty_cycle, 60);
    console.log("duty_cycle: " + leftDuty_cycle);
    
    var Yduty_cycle = (yposition * 0.115) + duty_min;
    b.analogWrite(ySERVO, Yduty_cycle, 60);
    console.log("Yduty_cycle: " + Yduty_cycle);
}

function onLine(line) {
    console.log(line);
    stdin = line.split(" ");
    
    
        
    if (stdin[0] > 20) {
        if (stdin[0] > 60)  { xposition = (xposition - (2*increment));}
        else {
        xposition = (xposition - increment);
        }
    }
    if (stdin[0] < -20) {
        if (stdin[0] < -60){ xposition = (xposition + (2*increment)); }
        else {
        xposition = (xposition + increment);
        }
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

function subtract_calculate(inx){
    var subtracted = (inx - 20);
    out = (((subtracted*0.1)/100)/3);
    return out;
}

function add_calculate(inx){
    var add = ((inx + 20)*-1);
    out = (((add*0.1)/100)/3);
    return out;
}
