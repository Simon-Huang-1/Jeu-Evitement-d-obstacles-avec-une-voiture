#include "Car.h"
#include "Ground.h"
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QElapsedTimer>
#include <vector>
#include <qpainter.h>

#include "opencv2/opencv.hpp"
#include <QWidget>
#include <QPainter>
#include <QPainterPath>

using namespace cv;

namespace Ui {
class Widget;
}

/*
 * Widget permettant d'afficher le jeu avec les fonctions draw.
 *
*/
class MyGLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:

    MyGLWidget(QWidget * parent = nullptr);
    ~MyGLWidget();
    float carx=0.0f;
    float carz=0.0f;


protected:
    void initializeGL(); //initialisation de l'affichage
    void resizeGL(int width, int height); //Redimensionnement
    void mousePressEvent(QMouseEvent * event);// detection d'une pression de la souris
    void keyPressEvent(QKeyEvent* event);// detection d'une pression d'une touche
    void paintEvent(QPaintEvent *event);// fonction d'affichage
    void restart();// nouvelle partie
    void fillFuel();// remplit le fuel

private:
    float* speed_;// vitesse
    float highestTime_;// record de temps
    int fuel_=50;// essence
    Player * player_=nullptr;// voiture du joueur
    Ground * ground_=nullptr;// environement
    QTimer * timer_=nullptr;// timer pour le refresh
    QTimer * timer2_=nullptr;// timer pour le fuel
    QTimer * timer3_=nullptr;// timer pour le refresh camera
    QElapsedTimer time_;// chrono
    EnnemyCar * ennemyCars_=nullptr;// Une voiture adverse
    EnnemyCar * ennemyCars2_=nullptr; //2ème type voiture adverse
    EnnemyCar * ennemyCars3_=nullptr; //3ème type de voiture adverse

    Ui::Widget *ui; //Accès à l'ui pour afficher la caméra
    VideoCapture * webCam_;// webcam

private slots:
    void refresh();// fonction de rafraichissement qui controle une fin de partie ou update l'affichage
    void refreshCamera();//fonction de rafraichissement de la caméra
    void clearGL(); //Supprimer les champs relatifs aux voitures ennemies, au sol, à la vitesse
    void updateFuel();// diminue le fuel de 1 par seconde
};
