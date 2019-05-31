#include "libraries/rc_usefulincludes.h"
#include "libraries/roboticscape.h"

#define SERVO_NECK_YAW 1
#define SERVO_NECK_PITCH 2
#define SERVO_JAW 3
#define SERVO_LEFTEYE 7
#define SERVO_RIGHTEYE 8

class servos
{
    private:
            // 0
        int frequency_hz = 50; // default 50hz frequency to send pulses
    public:
        // const servo_limits[5][2]
        // double servo_degrees[5];
        double servo_pos[5];
        const int servo_mapping[5] = { SERVO_NECK_YAW, SERVO_NECK_PITCH, SERVO_JAW,
            SERVO_LEFTEYE, SERVO_RIGHTEYE };
        
        int init();   // Returns -1 if failed, causing the robot to run without servos
        void update();
};