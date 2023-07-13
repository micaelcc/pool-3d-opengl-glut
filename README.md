## Instruções

Tenha glutgl, assimp e sdl instalado no seu sistema

Instalação para debian-based

```bash
sudo apt install freeglut3-dev libassimp-dev libsdl2-dev libsdl2-mixer-dev libsoil-dev libglm-dev
```

#### Executando direto

Execute dentro da pasta src

```bash
g++ -c *.cpp
```

```bash
g++ *.o -o main -lGL -lglut -lassimp -lGLU -lSOIL -lSDL2 -lSDL2_mixer
```

```bash
./main
```

#### Executando via python (testado apenas no Linux)

Tenha python3 instalado no seu sistema

Va ate o diretorio python/

```bash
python3 main.py
```
