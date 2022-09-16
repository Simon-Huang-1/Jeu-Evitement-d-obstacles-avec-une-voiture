#include "myglwidget.h"
#include <QApplication>
#include <QDesktopWidget>
#include <GL/glu.h>
#include <QTimer>
#include <QDebug>
#include <DataTypes.h>
#include <QProgressBar>

#include "opencv2/opencv.hpp"
#include "ui_widget.h"
#include <QString>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

std::vector<Rect> fists;
/*
 * Affiche les différentes fonctions
 *
 *
 *
 *
 *
*/
// Declarations des constantes
const unsigned int WIN = 900;

// Constructeur
MyGLWidget::MyGLWidget(QWidget * parent) : QOpenGLWidget(parent), ui(new Ui::Widget)
{

    ui->setupUi(this);

    webCam_=new VideoCapture(0);
    int width=webCam_->get(CAP_PROP_FRAME_WIDTH);
    int height=webCam_->get(CAP_PROP_FRAME_HEIGHT);

    timer_ = new QTimer(this);
    timer_->setInterval(17);
    connect(timer_, SIGNAL(timeout()),this, SLOT(refresh()));
    timer_->start();
    timer2_ = new QTimer(this);
    timer2_->setInterval(1000);
    connect(timer2_, SIGNAL(timeout()),this, SLOT(updateFuel()));
    timer2_->start();

    timer3_ = new QTimer(this);
    timer_->setInterval(17);
    connect(timer3_, SIGNAL(timeout()),this, SLOT(refreshCamera()));
    timer3_->start();


    // Reglage de la taille/position de la fenêtre principale
    setMinimumSize(WIN, WIN);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());
}

//Destructeur
MyGLWidget::~MyGLWidget(){
    clearGL();

    delete timer_;
    delete timer2_;
}

void MyGLWidget::clearGL(){
    delete player_;
    delete ennemyCars_;
    delete ennemyCars2_;
    delete ennemyCars3_;
    delete ground_;
    delete speed_;
}

void MyGLWidget::restart(){
    *speed_=2.8f;
    carx=0;
    player_->resetX();
    ennemyCars_=new EnnemyCar(speed_);
    ennemyCars2_=new EnnemyCar(speed_);
    ennemyCars3_=new EnnemyCar(speed_);
    ennemyCars_-> setCanDraw(true);
    if(time_.elapsed()/1000>highestTime_){
        highestTime_=time_.elapsed()/1000;
     }
    time_.start();
    fillFuel();

}

void MyGLWidget::updateFuel(){
    if(fuel_>0){
        fuel_-=1;
    }
}

void MyGLWidget::fillFuel(){
    fuel_=50;
}

// Fonction d'initialisation
void MyGLWidget::initializeGL()
{
    speed_=new float(2.8);
    highestTime_=0;
    player_ = new Player();
    ground_ = new Ground(speed_);
    ennemyCars_=new EnnemyCar(speed_);
    ennemyCars_-> setCanDraw(true);
    ennemyCars2_=new EnnemyCar(speed_);
    ennemyCars3_=new EnnemyCar(speed_);
    time_.start();


    glClearColor(.3f,.7f,.9f,1.f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.,1.,2,2000.);
}

void MyGLWidget::resizeGL(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.,width/(float)height,2,2000.);
    glViewport(0, 0, width, height);
}


// fonction de rafraichissement
void MyGLWidget::refresh(){
    BoxHitBox playerHitbox=player_->hitbox();
    if (playerHitbox.collision(ennemyCars_->hitbox())||playerHitbox.collision(ennemyCars2_->hitbox())||playerHitbox.collision(ennemyCars3_->hitbox())||fuel_<1) {
            restart();
    }
    update();

}

// fonction de rafraichissement de la caméra
void MyGLWidget::refreshCamera(){
    if (webCam_->isOpened()) {
            Mat image;
            std::vector<Rect> fists;
            CascadeClassifier Fist;

            Fist.load("../TestWebCamQt/fist_v3.xml"); //Specifieur

            if (webCam_->read(image)) {   // Capture a frame

                // Flip to get a mirror effect
                flip(image,image,1);

                Fist.detectMultiScale(image,fists,1.1,3,0,Size(30, 30));
                qDebug()<<player_->getPosition().x();

                for(int	i=0 ; i< fists.size() ;i++)
                {
                    //-------------Conditions----------------
                    //Position neutre: Mains écartés - Augmentation de la vitesse
                    //Bleu (Système BGR)
                    if (fists[0].x<fists[0].y && abs(fists[0].x+ fists[0].width-fists[1].x- fists[1].width)>260){
                        circle(image, Point(fists[i].x+ fists[i].width/2 , fists[i].y+ fists[i].height/2), fists[i].width/2, Scalar(255,0,0), 2, 8 );
                        //Limite de vitesse possible
                        if(*speed_<4){
                            *speed_+=0.05f;
                        }
                        repaint();
                    }
                    //Arrêt
                    //Rouge (Système BGR)
                    //Conditions de la boucle if: Il ne faut pas qu'une main ne soit trop au dessus de l'autre main, distances entre les deux mains

                    if (abs(fists[0].y-fists[1].y)<100 && fists[0].x<fists[1].x && abs(fists[0].x+ fists[0].width-fists[1].x- fists[1].width)>=120 && abs(fists[0].x+ fists[0].width-fists[1].x- fists[1].width)<=260 ){
                        circle(image, Point(fists[i].x+ fists[i].width/2 , fists[i].y+ fists[i].height/2), fists[i].width/2, Scalar(0,0,255), 2, 8 );
                        *speed_=0.0f;
                    }

                    //Si on n'est pas à l'arrêt, on peut tourner à droite ou à gauche
                    if (*speed_!=0)
                    {
                        //Tourner à droite: On lève la main gauche
                        if (carx<3 && abs(fists[0].y-fists[1].y)>=100&& fists[0].y<fists[1].y && fists[0].x<fists[1].x){ //La condition fists[0].x<fists[1].x c'est pour vérifier que le fists[0] a bien la main gauche
                            circle(image, Point(fists[i].x+ fists[i].width/2 , fists[i].y+ fists[i].height/2), fists[i].width/2, Scalar(0,255,255), 2, 8 ); //Couleur Jaune
                            carx+=0.1;
                            player_->right();
                            repaint();
                        }

                        //Tourner à gauche: On lève la main droite
                        if (carx >-3 && abs(fists[1].y-fists[0].y)>=100&& fists[1].y<fists[0].y && fists[0].x<fists[1].x){ //La condition fists[0].x<fists[1].x c'est pour vérifier que le fists[0] a bien la main gauche
                            circle(image, Point(fists[i].x+ fists[i].width/2 , fists[i].y+ fists[i].height/2), fists[i].width/2, Scalar(255,0,255), 2, 8 ); //Couleur Magenta
                            carx-=0.1;
                            player_->left();
                            repaint();
                        }
                    }

                }
                // Invert Blue and Red color channels
                cvtColor(image,image,COLOR_BGR2RGB);
                // Convert to Qt image
                QImage img= QImage((const unsigned char*)(image.data),image.cols,image.rows,QImage::Format_RGB888);
                // Display on label
                ui->imageLabel_->setPixmap(QPixmap::fromImage(img));

                //Position en haut à droite pour l'image
                ui->imageLabel_->move(1269,11);

                // Resize the label to fit the image
                ui->imageLabel_->resize(ui->imageLabel_->pixmap()->size());
            }
            else {
                qDebug()<<"Failed to open the camera";
            }
    }
    update();

}

void MyGLWidget::mousePressEvent(QMouseEvent * event)
{
    if(event->button()==Qt::LeftButton)
    {
            GLint hits;
            GLuint selectBuf[512];
            glSelectBuffer(512,selectBuf);

            glRenderMode(GL_SELECT);
            glInitNames();
            glPushName(0);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            GLint viewport[4];
            glGetIntegerv(GL_VIEWPORT,viewport);
            gluPickMatrix(event->x(),(viewport[3]-event->y()),2.0,2.0,viewport);

            glOrtho(-10,10,-10,10,-10,10);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(0,0,0,0,0,-10,0,1,0);
            glLoadName(1);

            glBegin(GL_QUADS);

            glVertex3f(-3.9f,2.2f,0);
            glVertex3f(-3.3f,2.2f,0);
            glVertex3f(-3.3f,3.3f,0);
            glVertex3f(-3.9f,3.3f,0);

            glEnd();
            glFlush();

            hits = glRenderMode(GL_RENDER);
            qDebug()<<hits;
            if(hits==1){
                player_->wasHit=!player_->wasHit;
                fillFuel();
            }
    }

}

//Possibilité de se déplacer avec le clavier
void MyGLWidget::keyPressEvent(QKeyEvent * event)
{
    switch(event->key())
    {
        case Qt::Key_Right:
        if(carx<3){
            carx+=0.1;
            player_->right();
        }
            break;
        case Qt::Key_Left:
        if(carx>(-3)){
            carx-=0.1;
            player_->left();
        }
            break;
        case Qt::Key_Up:
        if(*speed_<1){
            *speed_+=0.05f;
        }
            break;
        case Qt::Key_Down:
        if(*speed_>=0){
            *speed_-=0.05f;
        }
            break;
        case Qt::Key_P:
            if(timer_->isActive()){timer_->stop();}
            else {timer_->start();}
            break;
        case Qt::Key_R:
            restart();
            return;
            break;

            default:
        {
            // Ignorer l'evenement
            event->ignore();
            return;
        }
    }

    // Acceptation de l'evenement et mise a jour de la scene
    event->accept();
}

void MyGLWidget::paintEvent(QPaintEvent *){

    QPainter painter(this);
    painter.beginNativePainting();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0,3,4,0,1.,0,0,1,0);

    ennemyCars_->draw();
    if(ennemyCars_->getPosition().z()>-60){
         ennemyCars2_->setCanDraw(true);
    }
    if(ennemyCars2_->getPosition().z()>-60){
         ennemyCars3_->setCanDraw(true);
    }
    if(ennemyCars2_->getCanDraw()){
        ennemyCars2_->draw();
    }
    if(ennemyCars3_->getCanDraw()){
        ennemyCars3_->draw();
    }
    glTranslatef(player_->getPosition().x(),0,player_->getPosition().z());
    player_->draw();
    glTranslatef(-player_->getPosition().x(),0,-player_->getPosition().z());
    ground_->draw();

    //painter.drawText(5*width()/9,height()-height()/8, QString("Record : ")+QString::number((int)(record_*120))+QString("kph"));

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    painter.endNativePainting();
    glDisable(GL_DEPTH_TEST);


    painter.setRenderHint(QPainter::Antialiasing);

    QRect hud=rect();
    QProgressBar progressBar;
    progressBar.setMinimum(0);
    progressBar.setMaximum(100);

    for( int i = 0; i <100; ++i ) {
       progressBar.setValue(i);
    }

    hud.moveTop(3*hud.bottom()/4);
    painter.setPen(Qt::white);
    QFont font("times", width()/50);
    painter.setFont(font);
    painter.drawText(width()/20,height()-height()/6, QString("Speed : ")+QString::number((int)(*speed_*30))+QString("kph"));
    painter.drawText(width()/9,height()-height()/10, QString("Fuel : ")+QString::number(fuel_));
    painter.drawText(6*width()/9,height()-height()/6, QString("Time : ")+QString::number(time_.elapsed()/1000)+QString("s"));
    painter.drawText(5.5*width()/9,height()-height()/10, QString("Highest Time : ")+QString::number(highestTime_)+QString("s"));
    painter.fillRect(hud,QColor(0,0,0,95));
    glColor3f(0,0,1);

    painter.end();


};
