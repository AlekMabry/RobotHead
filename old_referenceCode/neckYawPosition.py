import Adafruit_BBIO.PWM as PWM

servo_pin = "P9_14"
duty_min = 6
duty_max = 12
duty_span = duty_max - duty_min

def startNeckYawServo():
    PWM.start(servo_pin, (100-duty_min), 60.0)
    duty = ((duty_span * 45)/90)+duty_min
    PWM.set_duty_cycle(servo_pin, duty)

def setNeckYawPos(degrees):
    duty = ((duty_span * degrees)/90)+duty_min
    PWM.set_duty_cycle(servo_pin, duty)

def stopNeckYawServo():
    PWM.stop(servo_pin)
    PWM.cleanup()
