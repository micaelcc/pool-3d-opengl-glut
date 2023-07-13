#include "GL/gl.h"
#include "GL/glut.h"
#include "vector"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "model.h"
#include "light.h"
#include "floor.h"
#include "audio.h"
#include "geometry.h"
#include "wall.h"
#include "point.h"
#include "ball.h"
#include "cue.h"
#include "collision.h"
#include "random.h"
#define POCKET_RADIUS 0.0405

#define TABLE_OUT_MAX_X 4.11
#define TABLE_OUT_MIN_X 2.15
#define TABLE_OUT_MAX_Y 3.52
#define TABLE_OUT_MIN_Y 2.508

enum MOUSE_BUTTON_STATUS
{
    APPLYING_FORCE = 1,
    HIT_BALL = 2,
    WAITING = 3
};

enum CAMERA_MODES
{
    CUE_STICK = 1,
    VERTICAL = 2,
    HORIZONTAL = 3,
    RANDOM_BALL = 4,
    TOP_VIEW = 5
};

class Game
{
private:
    std::vector<Point *> pockets;
    std::vector<Ball *> balls;
    Cue *cue;
    float applying_force;
    float forceApplied;
    Model *table;
    Floor *floor;
    Wall *wall;
    int cameraMode;
    std::vector<Audio *> collisionAudios;
    std::vector<Audio *> cueHitAudios;
    Audio *pocketAudio;

public:
    Game();
    void init();
    void update();
    void checkCollisions();
    void checkPockets();
    void initBallPositions();
    void draw();
    void handleMouseClick(int, int, int, int);
    void handleMouseMove(int, int);
    void reposWhiteBall();
    void handleKeyboard(unsigned char);
    bool checkCollisionWithOutTable(Ball);
    void exitGame();
    void updateCuePosition(int);
    void updateCameraMode(int);
};