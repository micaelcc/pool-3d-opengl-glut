import subprocess
import os
import time
import signal
import datetime 

GCC_COMPILE_C_FILES = "g++ -c ../src/*.cpp && g++ *.o -o main -lGL -lglut -lassimp -lGLU -lSOIL -lSDL2 -lSDL2_mixer"
CLOSE_GAME_COMMAND = f'xdotool search --name "Side Pocket" windowactivate --sync sleep 0.1 key --window %@ "q"'

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

def closeGame():
    os.killpg(os.getpgid(process.pid), signal.SIGINT)
    subprocess.run(CLOSE_GAME_COMMAND, shell=True)

def recompile():    
    subprocess.call(GCC_COMPILE_C_FILES,shell = True)

recompile()

process = subprocess.Popen(["./main"], preexec_fn=os.setsid)

while True:
    if hasFileChanged():
        closeGame()
        recompile()
        process = subprocess.Popen(["./main"], preexec_fn=os.setsid)

        time.sleep(1)