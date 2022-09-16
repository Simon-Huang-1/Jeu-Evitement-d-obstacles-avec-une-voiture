#include "Ground.h"
#include "DataTypes.h"
#include <QGLWidget>
#include <math.h>

Ground::Ground(float* speed){
    speed_=speed;
    qim_TextureGrass_=QGLWidget::convertToGLFormat(QImage("://Textures/grass.jpg"));
    qim_TextureRoad_=QGLWidget::convertToGLFormat(QImage("://Textures/road.jpg"));
    qim_TextureSky_=QGLWidget::convertToGLFormat(QImage("://Textures/sky1.jpg"));
    qim_TextureBarrel_=QGLWidget::convertToGLFormat(QImage("://Textures/barel.png"));
    m_TextureID_=new GLuint[4];
    glGenTextures(3,m_TextureID_);


    glBindTexture(GL_TEXTURE_2D,m_TextureID_[0]);

    glTexImage2D(GL_TEXTURE_2D,0,4,qim_TextureGrass_.width(),qim_TextureGrass_.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,qim_TextureGrass_.bits());

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,m_TextureID_[1]);

    glTexImage2D(GL_TEXTURE_2D,0,4,qim_TextureRoad_.width(),qim_TextureRoad_.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,qim_TextureRoad_.bits());

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


    glBindTexture(GL_TEXTURE_2D,m_TextureID_[2]);
    glTexImage2D(GL_TEXTURE_2D,0,4,qim_TextureSky_.width(),qim_TextureSky_.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,qim_TextureSky_.bits());

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D,m_TextureID_[3]);
    glTexImage2D(GL_TEXTURE_2D,0,4,qim_TextureBarrel_.width(),qim_TextureBarrel_.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,qim_TextureBarrel_.bits());

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}
Ground::~Ground(){
    delete m_TextureID_;
}

void Ground::draw(){

    shift_=shift_+*speed_;
    *speed_=*speed_-100.f*floor(*speed_/100.f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,m_TextureID_[0]);


    glBegin(GL_QUADS);

    // Grass
    glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialProperty(0.3f,.4f,0.3f).get());
    glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialProperty(.2,.5,.2).get());
    glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialProperty(0.0225f,0.0225f,0.0225f).get());
    glMaterialfv(GL_FRONT,GL_EMISSION,MaterialProperty().get());
    glMaterialfv(GL_FRONT,GL_SHININESS,MaterialProperty(12.8f).getFirst());
    glColor3f(1.f,1.f,1.f);

    glNormal3f(0.f,1.f,0.f);
    glTexCoord2f(0.f,100.f+shift_/10.f); glVertex3f(-1000.f,-0.01f,-1000.f);
    glTexCoord2f(0.f,.0f+shift_/10.f); glVertex3f(-1000.f,-0.01f,10.f);
    glTexCoord2f(200.f,0.f+shift_/10.f); glVertex3f(1000.f,-0.01f,10.f);
    glTexCoord2f(200.f,100.f+shift_/10.f); glVertex3f(1000.f,-0.01f,-1000.f);


    glEnd();


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,m_TextureID_[1]);
    //

    glBegin(GL_QUADS);
    // Road
    glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialProperty(0.5f,.5f,0.5f).get());
    glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialProperty(.1,.1,.1).get());
    glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialProperty(0.0225f,0.0225f,0.0225f).get());
    glMaterialfv(GL_FRONT,GL_EMISSION,MaterialProperty().get());
    glMaterialfv(GL_FRONT,GL_SHININESS,MaterialProperty(1.f).getFirst());
    glColor3f(1.f,1.f,1.f);

    glNormal3f(0.f,1.f,0.f);
    glTexCoord2f(0.f,256.f+shift_*2.698f); glVertex3f(-5.f,0.f,-1000.f);
    glTexCoord2f(0.f,0.f+shift_*2.698f); glVertex3f(-5.f,0.f,-50.f);
    glTexCoord2f(1.f,0.f+shift_*2.698f); glVertex3f(5.f,0.f,-50.f);
    glTexCoord2f(1.f,256.f+shift_*2.698f); glVertex3f(5.f,0.f,-1000.f);

    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.f,1.f,0.f);

    for (int i=0;i<20;i++){
        for (int j=0;j<120;j++){
            glTexCoord2f((float)i/20.f,(1.f-((float)(j+1))/120.f)*2.698f-shift_/20.f); glVertex3f(i/2.f-5.f,0.f,9.5f-j/2.f);
            glTexCoord2f((float)i/20.f,(1.f-(float)j/120.f)*2.698f-shift_/20.f); glVertex3f(i/2.f-5.f,0.f,10.f-j/2.f);
            glTexCoord2f(((float)(i+1))/20.f,(1.f-(float)j/120.f)*2.698f-shift_/20.f); glVertex3f(i/2.f-4.5f,0.f,10.f-j/2.f);
            glTexCoord2f(((float)(i+1))/20.f,(1.f-((float)(j+1))/120.f)*2.698f-shift_/20.f); glVertex3f(i/2.f-4.5f,0.f,9.5f-j/2.f);
        }
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Sky
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    glBindTexture(GL_TEXTURE_2D,m_TextureID_[2]);

    glBegin(GL_QUADS);
    glTexCoord2f(0.f,0.f); glVertex3f(-1500.f,-10.f,-1001.f);
    glTexCoord2f(1.f,0.f); glVertex3f(1500.f,-10.f,-1001.f);
    glTexCoord2f(1.f,1.f); glVertex3f(1500.f,180.f,-1001.f);
    glTexCoord2f(0.f,1.f); glVertex3f(-1500.f,180.f,-1001.f);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    //Barrel

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    /*glMaterialfv(GL_FRONT,GL_AMBIENT,MaterialProperty().get());
    glMaterialfv(GL_FRONT,GL_DIFFUSE,MaterialProperty().get());
    glMaterialfv(GL_FRONT,GL_SPECULAR,MaterialProperty(.9f,.9f,.9f).get());
    glMaterialfv(GL_FRONT,GL_SHININESS,MaterialProperty(30.f).getFirst());
    glMaterialfv(GL_FRONT,GL_EMISSION,MaterialProperty(.9f,.3f,.3f).get());*/
    glRotatef(90,1,0,0);
    glTranslatef(-2,0,-2);

    GLUquadric* bidonQuadric = gluNewQuadric();
    glBindTexture(GL_TEXTURE_2D,m_TextureID_[3]);
    gluQuadricDrawStyle(bidonQuadric,GLU_FILL);
    gluQuadricTexture(bidonQuadric,GL_TRUE);
    gluCylinder(bidonQuadric,.1,.1,.25,12,1);
    gluDisk(bidonQuadric,0.,.1,12,1);


    glTranslatef(2,0,2);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glColor3f(.9f,.7f,.2f);

    glTranslatef(-150.f,30.f,-1000.f);
    glRotatef(180.f,0.f,1.f,0.f);


    glEnable(GL_LIGHTING);
    light();
    glPopMatrix();

}

void Ground::light()
{
    glPushMatrix();
    glRotatef(10.f,1.f,0.f,0.f);
    glRotatef(15.f,0.f,1.f,0.f);
    float factor=1.f;
    glLightfv(GL_LIGHT0,GL_AMBIENT,MaterialProperty(.9f/factor,.8f/factor,.2f/factor,1.f).get());
    glLightfv(GL_LIGHT0,GL_DIFFUSE,MaterialProperty(.9f/factor,.8f/factor,.2f/factor,1.f).get());
    glLightfv(GL_LIGHT0,GL_SPECULAR,MaterialProperty(.9f/factor,.8f/factor,.2f/factor,.1f).get());
    glLightfv(GL_LIGHT0,GL_POSITION,MaterialProperty(0.f,0.f,-1.f,0.f).get());
    glPopMatrix();
}
