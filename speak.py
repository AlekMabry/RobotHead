#imports and stuff
from subprocess import call
import datetime

#by changing a to a value other than one ends the loop and closes the program
a = 1

#define the default voice. This will be changed by the program later on
voice = "rms"

#define all the ways to ask one type of question.

qHello = ["hello", "hello!", "hi", "hi!"]
qTime = ["what is the time?", "what is the time", "current time"]
qName = ["what is your name?", "what is your name", "who are you?", "what are you?"]
cQuit = ["quit","exit","end"]
cVoice = ["change voice", "voice change"]
qAbout = ["where can i find your code?", "where can i find out more about you?"]
cYes = ["yes", "y"]
cNo = ["no", "n"]

#Create a function to speak with flite.
def speak(user_input):
    call(["flite", "-voice", voice, "-t", user_input])

#main loop
while(a==1):

    #Getting input
    command = raw_input()

    #Comparing the input to possible questions.

    if(command.lower() in qHello):
        speak("Hello! Ask a question or say a command to begin!")

    if(command.lower() in qAbout):
        speak("Go to einsteinium studios dot com")

    if(command.lower() in qTime):
        now = datetime.datetime.now()
        speak("Include date?")
        command = raw_input()
        if(command.lower() in cNo):
            speak(now.strftime("%H:%M"))
        if(command.lower() in cYes):
            speak(now.strftime("%Y-%m-%d %H:%M"))

    if(command.lower() in qName):
        speak("I am the Smart Alek Robot Head")

    if(command.lower() in cQuit):
        speak("Are you sure you want to quit?")
        command = raw_input()
        if(command.lower() in cYes):
            speak("Quitting Program")
            a = 0
        else:
            speak("please ask another question!")

    if(command.lower() in cVoice):
        speak("Enter voice name to change too.")
        print("options include: ")
        command = raw_input()
        if(command != ""):
            voice = command
            speak("Changed to "+command+" Voice")
