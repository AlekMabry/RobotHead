from subprocess import call
import datetime

def speak(user_input):
    call(["flite", "-t", user_input])

while(1==1):

    command = raw_input()

    if(command == "Where can I find your code?" or command == "Where can I find out more about you?"):
        speak("Go to einsteinium studios dot com")
    
    if(command == "What is the time?"):
        now = datetime.datetime.now()
        speak(now.hour+" "+now.minute)
    
    if(command == "What is your name?"):
        speak("I am the Smart Alek Robot Head")
