#imports and stuff
from subprocess import call
import datetime
import os
from os import listdir

#Setup color text
class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

#setup accounts
current_people = []
current_person = "default_user"

#by changing a to a value other than one ends the loop and closes the program
a = 1

#define the default voice. This will be changed by the program later on
voice = "rms"
options = "Currently Unavailable"

#define all the ways to ask one type of question.

qHello = ["hello", "hello!", "hi", "hi!"]
qTime = ["what is the time?", "what is the time", "current time"]
qName = ["what is your name?", "what is your name", "who are you?", "what are you?"]
cQuit = ["quit","exit","end"]
cVoice = ["change voice", "voice change"]
qAbout = ["where can i find your code?", "where can i find out more about you?"]
cYes = ["yes", "y"]
cNo = ["no", "n"]
qStatus = ["current status", "current status?", "how are you doing?", "how are you doing", "status"]
qInfo = ["login","new session"]
qPossible = [qHello, qTime, qName, cQuit, cVoice, qAbout, cYes, cNo, qStatus, qInfo]

#Create a function to speak with flite.
def speak(user_input):
    print(bcolors.OKGREEN+bcolors.BOLD+"Smart Alek Robot Head: "+bcolors.ENDC+bcolors.OKBLUE+bcolors.BOLD+user_input+bcolors.ENDC)
    call(["flite", "-voice", voice, "-t", user_input])
def speak2(user_input):
    print(bcolors.OKGREEN+bcolors.BOLD+"Smart Alek Robot Head: "+bcolors.ENDC+bcolors.FAIL+bcolors.BOLD+user_input+bcolors.ENDC)
    call(["flite", "-voice", voice, "-t", user_input])
speak("Hello! Ask a question or say a command to begin!")

#main loop
while(a==1):

    #Getting input
    command = raw_input()

    #Comparing the input to possible questions.

    if(command.lower() in qInfo):
        speak("What is your name?")
        command = raw_input()
        current_people = os.listdir("people/")
        if(command in current_people):
            current_person = command
            speak("Welcome Back! "+current_person)
            if("color.txt" not in os.listdir("people/"+current_person)):
                speak("It appears that your favorite color is not in my database!")
                speak("What is your favorite color?")
                command = raw_input()
                speak("Your favorite color is "+command.lower()+ "? That is mine too!")
                # Open a file
                fo = open("people/"+current_person+"/color.txt", "wb")
                fo.write(command.lower());

                # Close opend file
                fo.close()
        else:
            call(["mkdir","people/"+command])
            current_person = command
            speak("Hello! " + current_person)
            speak("Please answer a few questions about yourself!")
            speak("What is your favorite color?")
            command = raw_input()
            speak("Your favorite color is "+command.lower()+ "? That is mine too!")
            # Open a file
            fo = open("people/"+current_person+"/color.txt", "wb")
            fo.write(command.lower());

            # Close opend file
            fo.close()



    if(command.lower() in qStatus):
        speak("I am doing fine")

    if(command.lower() in qHello):
        speak("Hello! What is your name?")

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
        speak2("Are you sure you want to quit?")
        command = raw_input()
        if(command.lower() in cYes):
            speak2("Quitting Program")
            a = 0
        else:
            speak("please ask another question!")

    if(command.lower() in cVoice):
        speak("Enter voice name to change to.")
        options = call(["flite", "-lv"])
        print(options)
        command = raw_input()
        if(command != ""):
            voice = command
            speak("Changed to "+command+" Voice")
