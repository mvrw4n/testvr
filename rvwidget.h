#ifndef RVWIDGET_H
#define RVWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QPixmap>
#include <QOpenGLFramebufferObject>
#include "rvbody.h"
#include "rvcamera.h"
#include "rvcube.h"
#include "rvplane.h"
#include "rvsphere.h"
#include "rvplanet.h"
#include "rvtorus.h"
#include "rvtexcube.h"
#include "rvdice.h"
#include "rvscene.h"
#include "rvsphericalcamera.h"
#include "rvskybox.h"
#include "rvlight.h"
#include "rvspecularcube.h"
#include "rvspeculartorus.h"
#include "rvspecularsphere.h"

class RVWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT


public:
    RVWidget(QWidget *parent = nullptr);
    ~RVWidget();

    // Attributs pour le rendu

    RVScene *getScene() const;
    RVLight *getLight() const;

private:
    RVBody* body;
    RVBody* plane;
    RVBody* world;
    RVBody* torus;
    RVBody* dice;
    RVBody* specCube;
    RVSphericalCamera* camera;
    RVScene* scene;
    RVSkyBox* skybox;
    RVLight* light;
    RVBody* cube;
    RVBody* sun;
    QTimer* timer;
    float angleY;
    bool animationOn = false;
    bool animationOnLight = false;
    float angleX;
    QPointF oldPos;
    bool showSun = false;

protected slots:
    void update();

public slots:
    void startAnimation();
    void startAnimationLight();
    void changeFov(int);
    void changeOpacity(int);
    void changeSize(int value);
    void changeSaturation(int value);
    void changeCulling();
    void changeWireframe();
    void addBody(QVector3D pos, QQuaternion orientation, QString corps);
    void setSkyboxImage(QString img);
    void changeXLight(double newX);
    void changeYLight(double newY);
    void changeZLight(double newZ);
    void changeSpecCoeff(int newCoeff);
    void rotateLight(float angle) ;
    QPixmap getImage();


    // QOpenGLWidget interface
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void wheelEvent(QWheelEvent * event) override;

};
#endif // RVWIDGET_H
