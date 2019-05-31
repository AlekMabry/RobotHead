/*
* SERVO: uses rc_send_servo_pulse_normalized() to set one or all servo positions
* to a value from -1.5 to 1.5 corresponding to their extended range. 
* -1 to 1 is considered the "safe" normal range as some servos will not go 
* beyond this. Test your servos incrementally to find their safe range.
* 
* SERVO POWER RAIL: The robotics cape has a software-controlled 6V power
* regulator allowing controlled steady power to drive servos. This can be
* enabled at the command line with the -v option. It will not allow you to
* enable the power rail when using the ESC mode as sending 6V into an ESC
* may damage it. It is best to physically cut the center wire on ESC connections
* as the BEC function is not needed when using the Robotics Cape.
*******************************************************************************/

#include "servos.h"

// printed if some invalid argument was given
void print_usage(){
	printf("\n");
	printf(" Options\n");
	printf(" -c {channel}   Specify one channel from 1-8.\n");
	printf("                Otherwise all channels will be driven equally\n");
	printf(" -f {hz}        Specify pulse frequency, otherwise 50hz is used\n");
	printf(" -v             Enable 6V servo power rail\n");
	printf("                DO NOT use power option with ESCs\n");
	printf(" -p {position}  Drive servos to a position between -1.5 & 1.5\n");
	printf(" -e {throttle}  Drive ESCs at normalized throttle from 0-1\n");
	printf(" -u {width_us}  Send pulse width in microseconds (us)\n");
	printf(" -s {limit}     Sweep servo back/forth between +- limit\n");
	printf("                Limit can be between 0 & 1.5\n");
	printf(" -r             Use DSM radio input to set ESC speed\n");
	printf(" -h             Print this help messege \n\n");
	printf("sample use to center servo channel 1:\n");
	printf("   rc_test_servos -v -c 1 -p 0.0\n\n");
}


	double servo_pos = 0;
	double sweep_limit = 0;

	int width_us = 0;
	int ch = 0;

	int c;
	int all = 1;	// set to 0 if a channel -c  argument is given 
	test_mode_t mode = DISABLED; //start mode disabled
	int power_en = 0; // change to 1 if user wishes to enable power rail
	int frequency_hz = 50; // default 50hz frequency to send pulses
	int toggle = 0;
	int i;

	// parse arguments
	opterr = 0;
	while ((c = getopt(argc, argv, "c:f:vrp:e:u:s:h")) != -1){
		switch (c){
		case 'c': // servo/esc channel option
			ch = atoi(optarg);
			if(ch<=8 && ch>=1){
				all = 0;
			}
			else{
				printf("channel option must be from 1-4\n");
				return -1;
			}
			break;
		
		case 'f': // pulse frequency option
			frequency_hz = atoi(optarg);
			if(frequency_hz<1){
				printf("Frequency option must be >=1\n");
				return -1;
			}
			break;
		
		case 'v':
			power_en=1; //enable power rail later
			break;
			
		case 'p': // servo position option
			if(mode!=DISABLED) print_usage();
			servo_pos = atof(optarg);
			if(servo_pos<=1.5 && servo_pos >=-1.5){
				mode = SERVO;
			}
			else{
				printf("Servo position must be from -1.5 to 1.5\n");
				return -1;
			}
			break;
			
		case 'e': // esc throttle option
			if(mode!=DISABLED) print_usage();
			esc_throttle = atof(optarg);
			if(esc_throttle<=1 && esc_throttle>=0){
				mode = ESC;
			}
			else{
				printf("ESC throttle must be from 0 to 1\n");
				return -1;
			}
			break;
			
		case 'u': // width in microsecons option
			if(mode!=DISABLED) print_usage();
			width_us = atof(optarg);
			if(width_us >= 10){
				mode = MICROSECONDS;
			}
			else{
				printf("Width in microseconds must be >10\n");
				return -1;
			}
			break;
			
		case 's':
			if(mode!=DISABLED) print_usage();
			sweep_limit = atof(optarg);
			if(sweep_limit<=1.5 && sweep_limit>=-1.5){
				mode = SWEEP;
				servo_pos = 0;
			}
			else{
				printf("Sweep limit must be from -1.5 to 1.5\n");
				return -1;
			}
			break;
			
	}


	

		printf("Using rc_send_servo_pulse_normalized\n");
		printf("Normalized Signal: %f  Pulse Frequency: %d\n", \
												servo_pos, frequency_hz);


	// Main loop runs at frequency_hz
	while(rc_get_state()!=EXITING){

			if(all) rc_send_servo_pulse_normalized_all(servo_pos);
			else rc_send_servo_pulse_normalized(ch, servo_pos);
			break;
			

		
		// sleep roughly enough to maintain frequency_hz
		rc_usleep(1000000/frequency_hz);
	}
	
	rc_cleanup();
	return 0;
}

