#ifndef ENTITY_H
#define ENTITY_H

#include "DataTypes.h"
/*
 * Classe qui permet de créer un objet avec une position
 *
*/
class Entity
{
public:
    Entity();
    ~Entity();

protected:
    Position* pos_=nullptr;
};

#endif // ENTITY_H
