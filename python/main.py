import subprocess
import os
import time
import signal
import datetime 

GCC_COMPILE_C_FILES = "g++ -c Ball.cpp  Cue.cpp main.cpp  Audio.cpp Game.cpp Collision.cpp Point.cpp Wall.cpp Random.cpp Light.cpp Geometry.cpp Floor.cpp  Texture.cpp Model.cpp"
GCC_COMPILE_MAIN = "g++ Ball.o  Cue.o main.o Point.o Audio.o Game.o Light.o Wall.o Texture.o Model.o Random.o Geometry.o Floor.o Collision.o -o main -lGL -lglut -lassimp -lGLU -lSOIL -lSDL2 -lSDL2_mixer"

path = os.path.dirname(os.path.abspath(__file__))
os.chdir(path + '/../src')

 
def hasFileChanged():
    for filename in os.listdir('../src'):
        if filename.endswith(".cpp") or filename.endswith(".h"):
            filepath = os.path.join('../src', filename)
            modify_time = os.path.getmtime(filepath)
            current_time = datetime.datetime.now().timestamp()
            time_diff = current_time - modify_time
            if time_diff <= 0.20:
                return True
    
    for filename in os.listdir('./../include'):
        if filename.endswith(".cpp") or filename.endswith(".h"):
            filepath = os.path.join('./../include', filename)
            modify_time = os.path.getmtime(filepath)
            current_time = datetime.datetime.now().timestamp()
            time_diff = current_time - modify_time
            if time_diff <= 0.20:
                return True
    return False


def recompile():
    command = GCC_COMPILE_C_FILES.split()
    command2 = GCC_COMPILE_MAIN.split()

    subprocess.call(command)
    subprocess.call(command2)


recompile()

process = subprocess.Popen(["./main"])

while True:
    if hasFileChanged():
        os.kill(process.pid, signal.SIGINT)

        recompile()
        process = subprocess.Popen(["./main"])

        time.sleep(1)
