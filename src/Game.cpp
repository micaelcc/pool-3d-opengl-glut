#include "../include/game.h"
#define WIDTH 1000
#define HEIGHT 800

Game::Game()
{
    this->init();
}

Point *cameraPosition = NULL;
Point *cameraCenter = NULL;

void Game::init()
{
    this->applying_force = WAITING;
    this->forceApplied = 0;

    Ball *cue_ball = new Ball(0, CLOTH_HEIGHT, 0.2, WHITE_CUE_BALL, "../assets/textures/W_Ball.png", false);
    Ball *ball_8 = new Ball(-1, -1, 1, BALL_8, "../assets/textures/Ball_8.png", true);

    // colored balls
    Ball *colored_ball1 = new Ball(-1, -1, -1, COLORED_BALL, "../assets/textures/Ball_1.png", false);
    Ball *colored_ball2 = new Ball(-1, -1, -1, COLORED_BALL, "../assets/textures/Ball_2.png", false);
    Ball *colored_ball3 = new Ball(-1, -1, -1, COLORED_BALL, "../assets/textures/Ball_3.png", false);
    Ball *colored_ball4 = new Ball(-1, -1, -1, COLORED_BALL, "../assets/textures/Ball_4.png", false);
    Ball *colored_ball5 = new Ball(-1, -1, -1, COLORED_BALL, "../assets/textures/Ball_5.png", false);
    Ball *colored_ball6 = new Ball(-1, -1, -1, COLORED_BALL, "../assets/textures/Ball_6.png", false);
    Ball *colored_ball7 = new Ball(-1, -1, -1, COLORED_BALL, "../assets/textures/Ball_7.png", false);
    Ball *colored_ball8 = new Ball(-1, -1, -1, COLORED_BALL, "../assets/textures/Ball_9.png", true);
    Ball *colored_ball9 = new Ball(-1, -1, -1, COLORED_BALL, "../assets/textures/Ball_10.png", true);
    Ball *colored_ball10 = new Ball(-1, -1, -1, COLORED_BALL, "../assets/textures/Ball_11.png", true);
    Ball *colored_ball11 = new Ball(-1, -1, -1, COLORED_BALL, "../assets/textures/Ball_12.png", true);
    Ball *colored_ball12 = new Ball(-1, -1, -1, COLORED_BALL, "../assets/textures/Ball_13.png", true);
    Ball *colored_ball13 = new Ball(-1, -1, -1, COLORED_BALL, "../assets/textures/Ball_14.png", true);
    Ball *colored_ball14 = new Ball(-1, -1, -1, COLORED_BALL, "../assets/textures/Ball_15.png", true);

    this->balls = {
        cue_ball,
        ball_8,
        colored_ball1,
        colored_ball2,
        colored_ball3,
        colored_ball4,
        colored_ball5,
        colored_ball6,
        colored_ball7,
        colored_ball8,
        colored_ball9,
        colored_ball10,
        colored_ball11,
        colored_ball12,
        colored_ball13,
        colored_ball14,
    };

    Point *pocket1 = new Point(2.16, 2.515, CLOTH_HEIGHT);
    Point *pocket2 = new Point(4.10, 2.515, CLOTH_HEIGHT);
    Point *pocket3 = new Point(2.16, 3.509, CLOTH_HEIGHT);
    Point *pocket4 = new Point(4.10, 3.509, CLOTH_HEIGHT);
    Point *pocket5 = new Point(3.125, 3.523, CLOTH_HEIGHT);
    Point *pocket6 = new Point(3.125, 2.49, CLOTH_HEIGHT);

    this->pockets = {
        pocket1,
        pocket2,
        pocket3,
        pocket4,
        pocket5,
        pocket6};

    this->initBallPositions();

    this->cue = new Cue("../assets/models/Cue.obj", "../assets/textures/Cue.png");
    this->table = new Model();
    this->table->load(
        "../assets/models/POOTABLE.obj",
        "../assets/textures/pooltable.png",
        glm::vec3(0.8, 0.8, 0.8),
        glm::vec3(0.8, 0.8, 0.8),
        glm::vec3(0.7, 0.7, 0.8),
        1000);

    this->floor = new Floor("../assets/textures/WoodFloor.png");

    this->wall = new Wall("../assets/textures/BrickWall.png", "../assets/textures/CeramicWall.png");

    this->collisionAudios = {new Audio(), new Audio(), new Audio(), new Audio()};

    this->collisionAudios[0]->load("../assets/audios/Collision1.mp3");
    this->collisionAudios[1]->load("../assets/audios/Collision2.mp3");
    this->collisionAudios[2]->load("../assets/audios/Collision3.mp3");
    this->collisionAudios[3]->load("../assets/audios/Collision4.mp3");

    this->cueHitAudios = {new Audio(), new Audio()};

    this->cueHitAudios[0]->load("../assets/audios/CueHit.mp3");
    this->cueHitAudios[1]->load("../assets/audios/CueHit2.mp3");

    this->pocketAudio = new Audio();

    this->pocketAudio->load("../assets/audios/Pocket.mp3");

    cameraPosition = new Point(-1, -1, -1);
    cameraCenter = new Point(-1, -1, -1);

    this->cameraMode = 2;

    this->updateCameraMode(2);
}

void Game::updateCuePosition(int mouseX)
{
    Point *newPoint = new Point(0, 0, 0);

    Geometry::scale(newPoint, 0.02, 0.02, 0.02);
    Geometry::translate(newPoint, -1.4, 0.0f, 0.0f);
    Geometry::rotate(newPoint, 3, 0.0, 1.0, 0.0);
    Geometry::rotate(newPoint, mouseX, 0.0, 0.0f, 1.0f);
    Geometry::translate(
        newPoint,
        this->balls[WHITE_CUE_BALL]->getPosition()->x,
        this->balls[WHITE_CUE_BALL]->getPosition()->y,
        this->balls[WHITE_CUE_BALL]->getPosition()->z);

    this->cue->attPosition(newPoint);
}

void Game::updateCameraMode(int cameraMode = 1)
{
    if (cameraMode < 1 || cameraMode > 5)
        cameraMode = 1;

    this->cameraMode = cameraMode;

    if (this->cameraMode == CAMERA_MODES::CUE_STICK)
    {
        cameraPosition->x = this->cue->getPosition()->x;
        cameraPosition->y = this->cue->getPosition()->y;
        cameraPosition->z = this->cue->getPosition()->z + 0.5;

        cameraCenter->x = this->cue->getDirection()->x;
        cameraCenter->y = this->cue->getDirection()->y;
        cameraCenter->z = this->cue->getDirection()->z;
    }

    if (this->cameraMode == CAMERA_MODES::HORIZONTAL)
    {
        cameraPosition->x = 3.1;
        cameraPosition->y = 1.3;
        cameraPosition->z = 2.5;

        cameraCenter->x = 3.1;
        cameraCenter->y = 2.9;
        cameraCenter->z = CLOTH_HEIGHT;
    }

    if (this->cameraMode == CAMERA_MODES::VERTICAL)
    {
        cameraPosition->x = 5.2;
        cameraPosition->y = 2.9;
        cameraPosition->z = 2.2;

        cameraCenter->x = 3.1;
        cameraCenter->y = 2.9;
        cameraCenter->z = CLOTH_HEIGHT;
    }

    if (this->cameraMode == CAMERA_MODES::RANDOM_BALL)
    {
        int ball = 0;
        do
        {
            ball = Random::generateRandom(15, 0);
        } while (!this->balls[ball]->isEnabled());

        cameraPosition->x = 1.6;
        cameraPosition->y = 1.5;
        cameraPosition->z = 2.2;

        cameraCenter->x = this->balls[ball]->getPosition()->x;
        cameraCenter->y = this->balls[ball]->getPosition()->y;
        cameraCenter->z = this->balls[ball]->getPosition()->z;
    }

    if (this->cameraMode == CAMERA_MODES::TOP_VIEW)
    {
        cameraPosition->x = 3.1;
        cameraPosition->y = 3.1;
        cameraPosition->z = 3.1;

        cameraCenter->x = 3.1;
        cameraCenter->y = 2.9;
        cameraCenter->z = CLOTH_HEIGHT;
    }
}

void Game::update()
{
    checkCollisions();
    checkPockets();

    if (this->cameraMode == 1)
        this->updateCameraMode();

    if (this->forceApplied >= 1 || this->applying_force == HIT_BALL && !this->balls[WHITE_CUE_BALL]->isMoving())
    {
        this->cueHitAudios[Random::generateRandom(1, 0)]->play();
        this->balls[WHITE_CUE_BALL]->setDirection(
            this->cue->getDirection()->x,
            this->cue->getDirection()->y,
            this->cue->getDirection()->z,
            this->forceApplied);

        this->updateCameraMode(Random::generateRandom(4, 2));
        this->forceApplied = 0;
        this->applying_force = WAITING;
    }

    if (this->applying_force == APPLYING_FORCE && this->forceApplied < 1 && !this->balls[WHITE_CUE_BALL]->isMoving())
    {
        this->forceApplied = this->forceApplied + 0.01;

        this->cue->onAppliedForce(this->forceApplied);
    }

    bool ballsMoving = false;

    for (Ball *ball : this->balls)
    {
        ball->updateRotationAngle();

        if (ball->isEnabled() && ball->isMoving())
        {
            ball->moveBall();
            ballsMoving = true;
        }
    }

    this->cue->setIsVisible(!ballsMoving);
}

void Game::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_SMOOTH);
    glLoadIdentity();

    gluLookAt(
        cameraPosition->x, cameraPosition->y, cameraPosition->z,
        cameraCenter->x, cameraCenter->y, cameraCenter->z,
        0.0f, 0.0f, 1.0f);

    /* Aplica transformaçoes e desenha chao*/
    glPushMatrix();
    glTranslatef(3, 3, 0);
    glRotatef(-90, 1, 0, 0);
    glScalef(1.2, 1.2, 1.2);
    this->floor->draw();
    glPopMatrix();

    /* Aplica transformaçoes e desenha mesa*/
    glPushMatrix();
    glTranslatef(3, 3, 0);
    glRotatef(90, 1, 0, 0);
    this->table->render();
    glPopMatrix();

    /* Desenha 4 paredes */
    this->wall->draw();

    /* Desenha taco de acordo com a posiçao da bola branca */
    this->cue->draw(this->balls[0]->getPosition());

    /* Desenha esferas se habilitadas */
    for (Ball *ball : this->balls)
        if (ball->isEnabled())
            ball->draw();

    glFlush();
    glutSwapBuffers();
}

void Game::checkCollisions()
{
    for (int i = 0; i < this->balls.size(); ++i)
        for (int j = i + 1; j < this->balls.size(); ++j)
            if (balls[i]->isEnabled() && balls[j]->isEnabled() &&
                Collision::checkCollision(this->balls[i], this->balls[j]))
            {
                int random = Random::generateRandom(3, 0);
                this->collisionAudios[random]->play();
                Collision::updateSpeeds(this->balls[i], this->balls[j]);
            }
}

bool Game::checkCollisionWithOutTable(Ball ball)
{
    return (ball.getPosition()->x + BALL_RADIUS > TABLE_OUT_MAX_X || ball.getPosition()->x - BALL_RADIUS < TABLE_OUT_MIN_X) ||
           (ball.getPosition()->y + BALL_RADIUS > TABLE_OUT_MAX_Y || ball.getPosition()->y - BALL_RADIUS < TABLE_OUT_MIN_Y);
}

void Game::checkPockets()
{
    for (Ball *ball : this->balls)
        for (Point *pocket : this->pockets)
            if (ball->isEnabled() && (this->checkCollisionWithOutTable(*ball) || Collision::getDistance(pocket, ball->getPosition()) < BALL_RADIUS))
            {
                this->pocketAudio->play();

                if (ball->getType() != WHITE_CUE_BALL)
                    ball->disable();
                else
                    this->reposWhiteBall();
            }
}

void Game::reposWhiteBall()
{
    float x, y;

    for (int count = 0;;)
    {
        if (!count)
        {
            float xMax = 4060, xMin = 2198;
            float yMax = 3470, yMin = 2555;

            x = (float)Random::generateRandom(xMax, xMin) / 1000.0;
            y = (float)Random::generateRandom(yMax, yMin) / 1000.0;
        }

        if (count == this->balls.size() - 1)
        {
            break;
        }

        for (Ball *balls : this->balls)
        {
            if (balls->getType() != WHITE_CUE_BALL)
            {
                float distance = Collision::getDistance(new Point(x, y, CLOTH_HEIGHT), new Point(balls->getPosition()->x, balls->getPosition()->y, balls->getPosition()->z));
                if (distance >= BALL_RADIUS * 2)
                {
                    count++;
                }
            }
        }
    }

    this->balls[0]->setPosition(x, y, CLOTH_HEIGHT);

    this->balls[0]->setSpeed(0, 0);
}

void Game::handleMouseClick(int button, int status, int x, int y)
{
    if (button == GLUT_RIGHT_BUTTON)
    {
        if (status == GLUT_DOWN)
            this->applying_force = APPLYING_FORCE;

        if (status == GLUT_UP)
            this->applying_force = HIT_BALL;
    }
}

void Game::handleMouseMove(int x, int y)
{
    this->updateCuePosition(x);

    this->cue->attDirection(this->balls[WHITE_CUE_BALL]->getPosition());

    this->cue->onMouseMove(x);

    glutPostRedisplay();
}

void Game::initBallPositions()
{
    float xInc = 0.3;
    float tempX = 2.65, pointY = 3, pointZ = CLOTH_HEIGHT;
    float spaceBetweenZ = BALL_RADIUS + 0.001;

    balls[0]->setPosition(3.66, 3, CLOTH_HEIGHT);

    balls[2]->setPosition(tempX, pointY, pointZ);

    tempX -= 2 * spaceBetweenZ;
    balls[9]->setPosition(tempX, pointY - spaceBetweenZ, pointZ);
    balls[3]->setPosition(tempX, pointY + spaceBetweenZ, pointZ);

    tempX -= 2 * spaceBetweenZ;
    balls[10]->setPosition(tempX, pointY - spaceBetweenZ * 2, pointZ);
    balls[4]->setPosition(tempX, pointY + spaceBetweenZ * 2, pointZ);
    balls[1]->setPosition(tempX, pointY, pointZ);

    tempX -= 2 * spaceBetweenZ;
    balls[11]->setPosition(tempX, pointY - spaceBetweenZ, pointZ);
    balls[5]->setPosition(tempX, pointY - spaceBetweenZ * 3, pointZ);
    balls[12]->setPosition(tempX, pointY + spaceBetweenZ * 3, pointZ);
    balls[6]->setPosition(tempX, pointY + spaceBetweenZ, pointZ);

    tempX -= 2 * spaceBetweenZ;
    balls[13]->setPosition(tempX, pointY - spaceBetweenZ * 2, pointZ);
    balls[7]->setPosition(tempX, pointY - spaceBetweenZ * 4, pointZ);
    balls[14]->setPosition(tempX, pointY + spaceBetweenZ * 4, pointZ);
    balls[8]->setPosition(tempX, pointY + spaceBetweenZ * 2, pointZ);
    balls[15]->setPosition(tempX, pointY, pointZ);
}

void Game::handleKeyboard(unsigned char key)
{
    switch (key)
    {
    case 'C':
    case 'c':
        this->updateCameraMode(this->cameraMode + 1);
        break;
    case ' ':
        this->cameraMode = 1;
        break;
    case 'q':
    case 'Q':
    case 27:
        this->exitGame();
        break;
    default:
        break;
    }
}

void Game::exitGame()
{
    for (Ball *ball : this->balls)
    {
        free(ball);
    };

    for (Point *pocket : this->pockets)
    {
        free(pocket);
    }

    free(table);

    free(floor);
    free(wall);

    // Finalizar SDL e SDL_mixer
    Mix_CloseAudio();

    SDL_Quit();

    free(this->cue);

    exit(1);
}