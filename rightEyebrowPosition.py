import Adafruit_BBIO.PWM as PWM

servo_pin = "P9_22"
duty_min = 3
duty_max = 7
duty_span = duty_max - duty_min

def startNeckPitchServo():
    PWM.start(servo_pin, (100-duty_min), 60.0)
    duty = ((duty_span * 45)/90)+duty_min
    PWM.set_duty_cycle(servo_pin, duty)

def setNeckPitchPos(degrees):
    duty = ((duty_span * degrees)/90)+duty_min
    PWM.set_duty_cycle(servo_pin, duty)

def stopNeckPitchServo():
    PWM.stop(servo_pin)
    PWM.cleanup()
