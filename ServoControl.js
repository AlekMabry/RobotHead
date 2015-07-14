
//Beginning code for reading from stding 
//url:http://stackoverflow.com/questions/20086849/how-to-read-from-stdin-line-by-line-in-node
var readline = require('readline');
var rl = readline.createInterface({
        input: process.stdin,
        output: process.stdout,
        terminal: false
});

var b = require('bonescript');
//Define servo pinouts for neck
var xServo = 'P9_14';
var yServo = 'P9_22';
var duty_min = 0.03;
var xposition = 0.5;
var yposition = 0.7;
var increment = 0.1;
//The line being read is outputed in this format: +1000 +3089 Where "+1000" is the x value and "+3089" is the y value.
//The x and y values are split and placed into the variables below.
var stdinx = 0;
var stdiny = 0;

b.pinMode(xServo, b.OUTPUT);
b.pinMode(yServo, b.OUTPUT);
updateDuty();


function updateDuty() {

    //this section is the same as the beagleboard.org servo code but duplicated for both servos. The top
    //analogWrite() function doesn't include "scheduleNextUpdate" so it doesn't check x/y values twice during the servo update.
    var duty_cycle = (xposition*0.115) + duty_min;
    b.analogWrite(xServo, duty_cycle, 60);
    
    var Yduty_cycle = (yposition*0.115) + duty_min;
    b.analogWrite(yServo, Yduty_cycle, 60, scheduleNextUpdate);

}

function scheduleNextUpdate() {
        
        //create variable line that holds the values from the current incoming string
        rl.on('line', function(line){
        
        //The tracker program used to output *'s to show that the ball was not detected. Originally I had code here to convert
        //the *'s into 0's, but I recently changed the tracker.cpp to output 0's when the ball is not detected, so the code
        //is no longer needed.
        
            
        //split the incoming string into it's x and y values.
        stdinx = line.substring(0,5);
        stdiny = line.substring(6,11);
        
                //the code below checks that if the ball is more than 20 units from the center of the screen, then
                //add an increment to the current servo position until it centers.
                if (stdinx > 20){
                        xposition = (xposition-increment);
                }
                if (stdinx < -20){
                        xposition = (xposition+increment);
                }
                if (stdiny < -20){
                        yposition = (yposition+increment);
                }
                if (stdiny > 20){
                        yposition= (yposition-increment);
                }
 })
    setTimeout(updateDuty, 10);
}
