from subprocess import call
import datetime
a = 1
voice = "rms"

def speak(user_input):
    call(["flite", "-voice", voice, "-t", user_input])

while(a==1):

    command = raw_input()

    if(command == "Hello!" or command == "hello!" or command == "Hello" or command == "hello" or command == "hi"):
        speak("Hello! Ask a question or say a command to begin!")
    if(command == "Where can I find your code?" or command == "Where can I find out more about you?"):
        speak("Go to einsteinium studios dot com")
    
    if(command == "What is the time?"):
        now = datetime.datetime.now()
        speak("Include date?")
        command = raw_input()
        if(command == "No" or command == "no"):
            speak(now.strftime("%H:%M"))
        if(command == "Yes" or command == "yes"):
            speak(now.strftime("%Y-%m-%d %H:%M"))
    
    if(command == "What is your name?"):
        speak("I am the Smart Alek Robot Head")
    
    if(command == "Quit" or command == "Exit"):
        speak("Are you sure you want to quit?")
        command = raw_input()
        if(command == "yes" or command == "Yes"):
            speak("Quitting Program")
            a = 0
    if(command == "Change Voice" or command == "Change Voice" or command == "Change voice"):
        speak("Enter voice name to change too.")
        print("options include: ")
        command = raw_input()
        if(command != ""):
            voice = command
            speak("Changed to "+command+" Voice")
        
