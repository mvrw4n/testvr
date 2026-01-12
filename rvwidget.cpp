#include "rvwidget.h"

RVWidget::RVWidget(QWidget *parent)
    : QOpenGLWidget(parent), QOpenGLFunctions()
{
    timer = new QTimer();
    angleY = 5;

    grabKeyboard();
}

RVWidget::~RVWidget()
{
}

RVLight *RVWidget::getLight() const
{
    return light;
}

RVScene *RVWidget::getScene() const
{
    return scene;
}

void RVWidget::update()
{
    if (animationOn) {
        scene->rotate(angleY, QVector3D(0, 1, 0));
        QOpenGLWidget::update();
    }
    if (animationOnLight) {
        this->rotateLight(0.1);
        QOpenGLWidget::update();
    }
}

void RVWidget::changeFov(int fov)
{
    camera->setFov(fov);
    QOpenGLWidget::update();
}

void RVWidget::startAnimation()
{
    animationOn = !animationOn;
}

void RVWidget::startAnimationLight()
{
    animationOnLight = !animationOnLight;
}

void RVWidget::changeOpacity(int val)
{
    //body->setOpacity(val * 0.01f);
    plane->setOpacity(val * 0.01f);
    QOpenGLWidget::update();
}

void RVWidget::changeSize(int value)
{
    body->setScale(value*0.1f);
    QOpenGLWidget::update();
}

void RVWidget::changeSaturation(int value)
{
    int gris = (int)(2.55f * value);
    body->setGlobalColor(QColor(gris, gris, gris));
    QOpenGLWidget::update();
}

void RVWidget::changeCulling()
{
    bool culling = !body->getCulling();
    body->setCulling(culling);
    QOpenGLWidget::update();
}

void RVWidget::changeWireframe()
{
    bool wireframe = !world->getWireframe();
    world->setWireframe(wireframe);
    QOpenGLWidget::update();
}

void RVWidget::addBody(QVector3D pos, QQuaternion orientation, QString corps)
{
    this->makeCurrent();

    RVBody* newBody = new RVCube();

    if (corps == "Dé"){
        newBody = new RVDice();
        newBody->setTexture(":/textures/dice_texture.jpg");
    }
    else if (corps == "Cube texturé"){
        newBody = new RVTexCube();
        newBody->setTexture(":/textures/polytech_logo.jpg");
    }
    else if (corps == "Cube Speculaire"){
        newBody = new RVSpecularCube();
        dynamic_cast<RVSpecularCube*>(newBody)->setCubeTexture(":/textures/Ciel/left.jpg",
                                                                   ":/textures/Ciel/right.jpg",
                                                                   ":/textures/Ciel/front.jpg",
                                                                   ":/textures/Ciel/back.jpg",
                                                                   ":/textures/Ciel/top.jpg",
                                                                   ":/textures/Ciel/bottom.jpg");
    }
    else if (corps == "Tore"){
        newBody = new RVTorus();
        newBody->setFSFileName(":/shaders/FS_lit_checker.fsh");
    }
    else if (corps == "Tore Speculaire"){
        newBody = new RVSpecularTorus();
        dynamic_cast<RVSpecularTorus*>(newBody)->setCubeTexture(":/textures/Ciel/left.jpg",
                                                                   ":/textures/Ciel/right.jpg",
                                                                   ":/textures/Ciel/front.jpg",
                                                                   ":/textures/Ciel/back.jpg",
                                                                   ":/textures/Ciel/top.jpg",
                                                                   ":/textures/Ciel/bottom.jpg");
    }
    else if (corps == "Planete"){
        newBody = new RVPlanet();
        newBody->setTexture(":/textures/2k_earth_daymap.jpg");
        //dynamic_cast<RVPlanet*>(newBody)->setNightTexture(":/textures/2k_earth_nightmap.jpg", true, true);
    }
    else if (corps == "Sphere"){
        newBody = new RVSphere();
    }
    else if (corps == "Sphere Speculaire"){
        newBody = new RVSpecularSphere();
        dynamic_cast<RVSpecularSphere*>(newBody)->setCubeTexture(":/textures/Ciel/left.jpg",
                                                                   ":/textures/Ciel/right.jpg",
                                                                   ":/textures/Ciel/front.jpg",
                                                                   ":/textures/Ciel/back.jpg",
                                                                   ":/textures/Ciel/top.jpg",
                                                                   ":/textures/Ciel/bottom.jpg");
    }
    else if (corps == "Plan"){
        newBody = new RVPlane();
        newBody->setLight(light);
        newBody->setTexture(":/textures/wood.png");
    }

    newBody->setLight(light);
    newBody->setPosition(pos);
    newBody->setOrientation(orientation);
    newBody->initialize();
    newBody->setCamera(camera);
    scene->append(newBody);

}

void RVWidget::setSkyboxImage(QString img)
{
    this->makeCurrent();
    skybox->setCubeTexture(":/textures/"+img+"/left.jpg",
                           ":/textures/"+img+"/right.jpg",
                           ":/textures/"+img+"/front.jpg",
                           ":/textures/"+img+"/back.jpg",
                           ":/textures/"+img+"/top.jpg",
                           ":/textures/"+img+"/bottom.jpg");
    QOpenGLWidget::update();

}

void RVWidget::changeXLight(double newX)
{
    QVector3D pos = light->getPositionLight();
    light->setPositionLight(QVector3D(newX, pos.y(), pos.z()));
    sun->setPosition(QVector3D(newX, pos.y(), pos.z()));
    QOpenGLWidget::update();
}

void RVWidget::changeYLight(double newY)
{
    QVector3D pos = light->getPositionLight();
    light->setPositionLight(QVector3D(pos.x(), newY, pos.z()));
    sun->setPosition(QVector3D(pos.x(), newY, pos.z()));
    QOpenGLWidget::update();
}

void RVWidget::changeZLight(double newZ)
{
    QVector3D pos = light->getPositionLight();
    light->setPositionLight(QVector3D(pos.x(), pos.y(), newZ));
    sun->setPosition(QVector3D(pos.x(), pos.y(), newZ));
    QOpenGLWidget::update();
}

void RVWidget::changeSpecCoeff(int newCoeff)
{
    scene->setSpecStrength(newCoeff);
    QOpenGLWidget::update();
}

void RVWidget::rotateLight(float angle)
{
    QVector3D center = scene->getPosition();
    QVector3D pos = light->getPositionLight();
    float x_new = (pos.x()-center.x())*cos(angle)+(pos.z()-center.z())*sin(angle);
    float z_new = -(pos.x()-center.x())*sin(angle)+(pos.z()-center.z())*cos(angle);
    light->setPositionLight(QVector3D(x_new,pos.y(),z_new));
    sun->setPosition(QVector3D(x_new,pos.y(),z_new));

}

void RVWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.0f, 0.566f, 0.867f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    camera = new RVSphericalCamera();
    camera->setFov(90.0f);
    camera->setZMin(1);
    camera->setZMax(800);

    light = new RVLight();
    sun = new RVSphere();
    sun->setPosition(light->getPositionLight());
    sun->setTexture(":/textures/sun_texture.jpg",true,true);
    sun->initialize();

    body = new RVTexCube();
    body->setPosition(QVector3D(4, 4, 8));
    body->setScale(3);
    body->setTexture(":/textures/polytech_logo.jpg");
    body->initialize();

    cube = new RVCube();
    cube->setPosition(QVector3D(8, 4, 8));
    cube->setScale(3);
    cube->initialize();

    dice = new RVDice();
    dice->setPosition(QVector3D(0, 4, 8));
    dice->setScale(3);
    dice->setTexture(":/textures/dice_texture.jpg");
    dice->initialize();


    plane = new RVPlane(40, 40);
    plane->setPosition(QVector3D(0, -4, -4));
    plane->setTexture(":/textures/wood.png");
    plane->initialize();

    /*
    world = new RVPlanet(2.5);
    world->setPosition(QVector3D(0, 3, -3));
    world->setTexture(":/textures/2k_earth_daymap.jpg", true, true);
    //dynamic_cast<RVPlanet*>(world)->setNightTexture(":/textures/2k_earth_nightmap.jpg", true, true);
    world->initialize(); 
*/

    world = new RVSpecularSphere();
    world->setPosition(QVector3D(0, 3, -3));
    dynamic_cast<RVSpecularSphere*>(world)->setCubeTexture(":/textures/Ciel/left.jpg",
                           ":/textures/Ciel/right.jpg",
                           ":/textures/Ciel/front.jpg",
                           ":/textures/Ciel/back.jpg",
                           ":/textures/Ciel/top.jpg",
                           ":/textures/Ciel/bottom.jpg");
    world->initialize();

    /*torus = new RVTorus();
    torus->setPosition(QVector3D(0, 3, -3));
    //torus->setFSFileName(":/shaders/FS_lit_checker.fsh");
    torus->initialize();*/

    torus = new RVSpecularTorus();
    torus->setPosition(QVector3D(0, 3, -3));
    dynamic_cast<RVSpecularTorus*>(torus)->setCubeTexture(":/textures/Ciel/left.jpg",
                           ":/textures/Ciel/right.jpg",
                           ":/textures/Ciel/front.jpg",
                           ":/textures/Ciel/back.jpg",
                           ":/textures/Ciel/top.jpg",
                           ":/textures/Ciel/bottom.jpg");
    torus->initialize();

    skybox = new RVSkyBox();
    skybox->setPosition(QVector3D(0,0,0));
    skybox->setScale(300);
    skybox->setCubeTexture(":/textures/Ciel/left.jpg",
                           ":/textures/Ciel/right.jpg",
                           ":/textures/Ciel/front.jpg",
                           ":/textures/Ciel/back.jpg",
                           ":/textures/Ciel/top.jpg",
                           ":/textures/Ciel/bottom.jpg");
    skybox->initialize();

    specCube = new RVSpecularCube();
    specCube->setPosition(QVector3D(0,0,4));
    dynamic_cast<RVSpecularCube*>(specCube)->setCubeTexture(":/textures/Ciel/left.jpg",
                           ":/textures/Ciel/right.jpg",
                           ":/textures/Ciel/front.jpg",
                           ":/textures/Ciel/back.jpg",
                           ":/textures/Ciel/top.jpg",
                           ":/textures/Ciel/bottom.jpg");
    specCube->setScale(5);
    specCube->initialize();

    scene = new RVScene();
    scene->setPosition(QVector3D(0,0,0));
    scene->append(skybox);
    scene->append(body);
    scene->append(dice);
    scene->append(plane);
    scene->append(world);
    scene->append(torus);
    scene->append(cube);
    scene->append(sun);
    scene->append(specCube);
    scene->setCamera(camera);
    scene->setLight(light);


    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);
}

void RVWidget::resizeGL(int w, int h)
{
    float aspect = ((float)w)/h;
    camera->setAspect(aspect);
    glViewport(0, 0, w, h);
}

void RVWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scene->draw();
}

void RVWidget::mousePressEvent(QMouseEvent *event)
{
    oldPos = event->position();
}

void RVWidget::mouseMoveEvent(QMouseEvent *event)
{
    float dx = (event->position().x() - oldPos.x()) / width();
    float dy = (event->position().y() - oldPos.y()) / height();

    float xAngle = 180 * dy;
    float yAngle = 180 * dx;


    camera->setPhi(camera->getPhi() + qDegreesToRadians(xAngle));
    camera->setTheta(camera->getTheta() + qDegreesToRadians(yAngle));

    //body->rotate(yAngle, QVector3D(0, 1, 0));
    //body->rotate(xAngle, QVector3D(1, 0, 0));
    QOpenGLWidget::update();

    oldPos = event->pos();
}

void RVWidget::keyPressEvent(QKeyEvent *event)
{
    QVector3D camPos = camera->getPosition();
    float delta = 0.2f;
    switch (event->key())
    {
    case Qt::Key_Left:
        camPos.setX(camPos.x() - delta);
        break;
    case Qt::Key_Right:
        camPos.setX(camPos.x() + delta);
        break;
    case Qt::Key_Up:
        camPos.setY(camPos.y() + delta);
        break;
    case Qt::Key_Down:
        camPos.setY(camPos.y() - delta);
        break;
    }
    camera->setPosition(camPos);
    QOpenGLWidget::update();
}

void RVWidget::wheelEvent(QWheelEvent *event)
{
    int newRho = event->angleDelta().y();
    if (camera->getRho()+newRho>0 && camera->getRho()+newRho<200)
        camera->setRho(camera->getRho()+newRho);
    QOpenGLWidget::update();
}

QPixmap RVWidget::getImage()
{
    makeCurrent();

    QOpenGLFramebufferObject* fbo = new QOpenGLFramebufferObject(this->width(), this->height());
    fbo->setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    fbo->bind();
    glViewport(0, 0, this->width(), this->height());
    paintGL();
    QImage img(fbo->toImage(true));
    fbo->release();
    return QPixmap::fromImage(img);
}

