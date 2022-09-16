#include "Car.h"
#include <QOpenGLDebugLogger>

Car::Car() : Entity(){
    color_=new Color(1.f,1.f,1.f);

    wheelQuadric_=gluNewQuadric();
    gluQuadricDrawStyle(wheelQuadric_, GLU_FILL);
}

Car::Car(float colorR, float colorG, float colorB){
    color_= new Color(colorR,colorG,colorB);

    wheelQuadric_=gluNewQuadric();
    gluQuadricDrawStyle(wheelQuadric_, GLU_FILL);
}

Car::~Car(){
    gluDeleteQuadric(wheelQuadric_);
    delete color_;
}

void Car::drawCar(){

    glBegin(GL_QUADS);

    glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialProperty(color_->red()/4.+0.05,color_->green()/4.+0.05,color_->blue()/4.+0.05).get());
    glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialProperty(color_->red()/2.5,color_->green()/2.5,color_->blue()/2.5).get());
    glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialProperty(color_->red()/1.291,color_->green()/1.291,color_->blue()/1.291,1.).get());
    glMaterialfv(GL_FRONT,GL_SHININESS,MaterialProperty(76.8f).getFirst());
    glMaterialfv(GL_FRONT,GL_EMISSION,MaterialProperty().get());

    glColor3f(color_->red(),color_->green(),color_->blue());

    // Front face
    glNormal3f(0.f,0.f,-1.f);
    glVertex3f(-0.5f,0.2f,-1.f);
    glVertex3f(-0.5f,.6f,-1.f);
    glVertex3f(0.5f,.6f,-1.f);
    glVertex3f(0.5f,0.2f,-1.f);

    // Top face
    glNormal3f(0.f,0.89f,-0.45f);
    glVertex3f(-0.5f,.85f,0.5f);
    glVertex3f(0.5f,.85f,0.5f);
    glVertex3f(0.5f,.85f,-.25f);
    glVertex3f(-0.5f,.85f,-.25f);

    glNormal3f(0.f,0.89f,-0.45f);
    glVertex3f(-0.5f,.85f,-0.25f);
    glVertex3f(0.5f,.85f,-0.25f);
    glVertex3f(0.5f,.6f,-1.f);
    glVertex3f(-0.5f,.6f,-1.f);

    // Right face
    glNormal3f(-1.f,0.f,0.f);
    glVertex3f(0.5f,.85f,0.5f);
    glVertex3f(0.5f,0.2f,0.5f);
    glVertex3f(0.5f,0.2f,-.25f);
    glVertex3f(0.5f,.85f,-.25f);

    glNormal3f(-1.f,0.f,0.f);
    glVertex3f(0.5f,.85f,-.25f);
    glVertex3f(0.5f,0.2f,-.25f);
    glVertex3f(0.5f,0.2f,-1.f);
    glVertex3f(0.5f,.6f,-1.f);


    // Back face
    glNormal3f(0.f,0.f,1.f);
    glVertex3f(-0.5f,0.2f,0.5f);
    glVertex3f(0.5f,0.2f,0.5f);
    glVertex3f(0.5f,0.85f,0.5f);
    glVertex3f(-0.5f,0.85f,0.5f);

    // Bottom face
    glNormal3f(0.f,-1.f,0.f);
    glVertex3f(-0.5f,0.2f,0.5f);
    glVertex3f(-0.5f,0.2f,-1.f);
    glVertex3f(0.5f,0.2f,-1.f);
    glVertex3f(0.5f,0.2f,0.5f);

    // Left face
    glNormal3f(1.f,0.f,0.f);
    glVertex3f(-0.5f,0.2f,0.5f);
    glVertex3f(-0.5f,.85f,0.5f);
    glVertex3f(-0.5f,.85f,-.25f);
    glVertex3f(-0.5f,0.2f,-.25f);

    glNormal3f(1.f,0.f,0.f);
    glVertex3f(-0.5f,0.2f,-.25f);
    glVertex3f(-0.5f,.85f,-.25f);
    glVertex3f(-0.5f,.6f,-1.f);
    glVertex3f(-0.5f,0.2f,-1.f);

    glEnd();



    // Phares

    glBegin(GL_QUADS);

    glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialProperty().get());
    glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialProperty().get());
    glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialProperty(.9f,.9f,.9f).get());
    glMaterialfv(GL_FRONT,GL_SHININESS,MaterialProperty(30.f).getFirst());
    glMaterialfv(GL_FRONT,GL_EMISSION,MaterialProperty(1.f,0.f,0.f).get());

    glNormal3f(0.f,0.f,1.f);

    glVertex3f(-0.45f,0.6f,0.55f);
    glVertex3f(-0.1f,0.6f,0.55f);
    glVertex3f(-0.1f,0.7f,0.55f);
    glVertex3f(-0.45f,0.7f,0.55f);

    glVertex3f(0.1f,0.6f,0.55f);
    glVertex3f(0.45f,0.6f,0.55f);
    glVertex3f(0.45f,0.7f,0.55f);
    glVertex3f(0.1f,0.7f,0.55f);


    glEnd();

    // Wheels

    glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialProperty(.02f,.02f,.02f).get());
    glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialProperty(.01f,.01f,.01f).get());
    glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialProperty(.5f,.5f,.5f).get());
    glMaterialfv(GL_FRONT,GL_SHININESS,MaterialProperty(10.f).getFirst());
    glMaterialfv(GL_FRONT,GL_EMISSION,MaterialProperty().get());

    //Front right wheel
    glPushMatrix();
    glTranslatef(.5f,.25f,-0.75);
    drawWheel();
    glPopMatrix();

    //Back right wheel
    glPushMatrix();
    glTranslatef(.5f,.25f,0.2);
    drawWheel();
    glPopMatrix();

    //Front left wheel
    glPushMatrix();
    glTranslatef(-0.75f,.25f,-0.75);
    drawWheel();
    glPopMatrix();

    //Back left wheel
    glPushMatrix();
    glTranslatef(-0.75f,.25f,0.2);
    drawWheel();
    glPopMatrix();


}


void Car::drawWheel(){

    glPushMatrix();
    glRotatef(90,0,1,0);

    glColor3f(.5f,.5f,.5f);
    gluCylinder(wheelQuadric_,.25,.25,.25,12,1);

    glColor3f(.25f,.25f,.25f);
    gluDisk(wheelQuadric_,0.,.25,12,1);

    glColor3f(.5f,.5f,.5f);
    glTranslatef(0.f,0.f,0.25f);
    gluDisk(wheelQuadric_,0.,.25,12,1);

    glPopMatrix();
}
void Car::drawBarrel(bool wasHit){


    glPushMatrix();
    glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialProperty().get());
    glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialProperty().get());
    glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialProperty(.9f,.9f,.9f).get());
    glMaterialfv(GL_FRONT,GL_SHININESS,MaterialProperty(30.f).getFirst());
    glMaterialfv(GL_FRONT,GL_EMISSION,MaterialProperty(.9f,.3f,.3f).get());
        glRotatef(90,1,0,0);

        glTranslatef(-2,0,-2);
        glColor3f(.9f,.3f,.3f);

        GLUquadric* bidonQuadric = gluNewQuadric();
        if(wasHit){
           glMaterialfv(GL_FRONT,GL_EMISSION,MaterialProperty(1.f,0.f,0.f).get());
        }
        gluCylinder(bidonQuadric,.1,.1,.25,12,1);

        glColor3f(.9f,.3f,.3f);
        gluDisk(bidonQuadric,0.,.1,12,1);
        glTranslatef(2,0,2);
        glPopMatrix();
}

Position Car::getPosition()
{
    return(*pos_);
}

BoxHitBox Car::hitbox(){

    Position minPos=Position(pos_->x()-0.5f,pos_->y(),pos_->z()-1.f);
    Position maxPos=Position(pos_->x()+0.5f,1.1f+pos_->y(),pos_->z()+1.f);
    return(BoxHitBox(minPos, maxPos));
}


Player::Player() : Car()
{
    beaconTimer_=10;
}

Player::~Player()
{
}



void Player::draw(){

    glPushMatrix();

    //glTranslatef(pos_->x(),pos_->y(),pos_->z());

    drawCar();
    beacon();

    glPopMatrix();
}
void Player::resetX(){
    pos_->setX(0);
}
void Player::beacon(){


    glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialProperty(0.05f,.05f,.05f).get());
    glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialProperty(0.05f,0.05f,0.05f).get());
    glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialProperty(.5f,.5f,.5f,1.).get());
    glMaterialfv(GL_FRONT,GL_SHININESS,MaterialProperty(30.f).getFirst());
    glMaterialfv(GL_FRONT,GL_EMISSION,MaterialProperty().get());

    glBegin(GL_QUADS);

    if(beaconTimer_<5){
        glMaterialfv(GL_FRONT,GL_EMISSION,MaterialProperty(0.f,0.f,1.f,0.f).get());
    }
    else{
        glMaterialfv(GL_FRONT,GL_EMISSION,MaterialProperty(1.f,0.f,0.f,0.f).get());
    }
    // Top
    glNormal3f(0.f,1.,0.f);
    glVertex3f(-0.2f,1.f,0.05f);
    glVertex3f(0.2f,1.f,0.05f);
    glVertex3f(0.2f,1.f,-0.05f);
    glVertex3f(-0.2f,1.f,-0.05f);

    // Back
    glNormal3f(0.f,0.,1.f);
    glVertex3f(-0.2f,0.6,0.05f);
    glVertex3f(0.2f,0.6f,0.05f);
    glVertex3f(0.2f,1.f,0.05f);
    glVertex3f(-0.2f,1.f,0.05f);

    // Front
    glNormal3f(0.f,0.,1.f);
    glVertex3f(-0.2f,0.6,-0.05f);
    glVertex3f(0.2f,0.6f,-0.05f);
    glVertex3f(0.2f,1.f,-0.05f);
    glVertex3f(-0.2f,1.f,-0.05f);

    // Right
    glNormal3f(0.f,0.,1.f);
    glVertex3f(0.2f,1.f,-0.05f);
    glVertex3f(0.2f,0.6f,-0.05f);
    glVertex3f(0.2f,0.6f,0.05f);
    glVertex3f(0.2f,1.f,0.05f);

    // Left
    glNormal3f(0.f,0.,1.f);
    glVertex3f(-0.2f,1.f,-0.05f);
    glVertex3f(-0.2f,0.6f,-0.05f);
    glVertex3f(-0.2f,0.6f,0.05f);
    glVertex3f(-0.2f,1.f,0.05f);

    glEnd();



    glDepthMask(GL_TRUE);

    if(beaconTimer_>5){
        glLightfv(GL_LIGHT2,GL_AMBIENT,MaterialProperty(0.f,0.f,0.f).get());
        glLightfv(GL_LIGHT2,GL_DIFFUSE,MaterialProperty(1.f,0.f,0.f).get());
        glLightfv(GL_LIGHT2,GL_SPECULAR,MaterialProperty(1.f,0.f,0.).get());
        glLightfv(GL_LIGHT2,GL_POSITION,MaterialProperty(-0.3f,1.f,0.f).get());
    }
    else{
        glLightfv(GL_LIGHT2,GL_AMBIENT,MaterialProperty(.0f,.0f,0.f).get());
        glLightfv(GL_LIGHT2,GL_DIFFUSE,MaterialProperty(.0f,.0f,1.f).get());
        glLightfv(GL_LIGHT2,GL_SPECULAR,MaterialProperty(.0f,.0f,1.f).get());
        glLightfv(GL_LIGHT2,GL_POSITION,MaterialProperty(0.3f,1.f,0.f).get());

    }

    if(beaconTimer_<=0){
        beaconTimer_=10;
    }
    else {
        beaconTimer_=beaconTimer_-1;
    };
}
void Player::left(){
     pos_->setX(pos_->x()-0.1);
}
void Player::right(){
    pos_->setX(pos_->x()+0.1);

}
EnnemyCar::EnnemyCar(float* speed)  : Car(rand()/(float)RAND_MAX,rand()/(float)RAND_MAX,rand()/(float)RAND_MAX)
{
    speed_=speed;
    pos_->setZ(-170);
    pos_->setX((rand()%6)-3);
    pos_->setY(0);
}
EnnemyCar::~EnnemyCar(){
    gluDeleteQuadric(wheelQuadric_);
}

void EnnemyCar::draw(){
    if(canDraw){
        updatePos();

        glPushMatrix();
        if(pos_->z()>10){
            pos_->setX((rand()%6)-3);
            pos_->setZ(-170);
        }
        glTranslatef(pos_->x(),0,*speed_+pos_->z());
        glRotatef (180,0,1,0);
        drawCar();

        glPopMatrix();
    }


}
void EnnemyCar::updatePos(){

    pos_->setZ(pos_->z()+*speed_);
}


