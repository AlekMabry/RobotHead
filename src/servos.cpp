#include "servos.h"

int servos::init()
{
    if(rc_initialize()){
		fprintf(stderr,"ERROR: failed to run rc_initialize(), are you root?\n");
		return -1;
	}
	
	rc_enable_servo_power_rail();
	
	return 1;
}

void servos::update()
{
    for (int i = 0; i < 5; i++)
    {
        if (servo_pos[i] > 1.5)
        {
            servo_pos[i] = 1.5;
        }
        if (servo_pos[i] < -1.5)
        {
            servo_pos[i] = -1.5;
        }
        rc_send_servo_pulse_normalized(servo_mapping[i], servo_pos[i]);
    }
}

/*
~servos::servos()
{
    rc_cleanup();
}
*/