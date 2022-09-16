#include <qopengl.h>
#include <GL/glu.h>

#include <QImage>
/*
 * Classe qui permet de générer et animer le décor
 *
*/
class Ground
{
public:
    Ground(float* speed);
    ~Ground();
    void draw();// Dessine le ciel l'herbe ,la route et le baril

private:
    void light();// gestion de la lumière
    float* speed_=nullptr;// vitesse
    QImage qim_TextureGrass_;// Texture de l'herbe
    QImage qim_TextureRoad_;// Texture de la route
    QImage qim_TextureSky_;// Texture du ciel
    QImage qim_TextureBarrel_;// Texture du baril
    GLuint* m_TextureID_=nullptr;// les ids des textures
    float shift_=0;
};
