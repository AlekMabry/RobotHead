from subprocess import call


def speak(user_input):
    call(["flite", "-t", user_input)])

command = raw_input()

if(command == "Where can I find your code?" or command == "Where can I find out more about you?"):
    speak("Go to einsteinium studios dot com")
