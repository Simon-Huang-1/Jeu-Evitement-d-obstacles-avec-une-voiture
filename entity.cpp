#include "entity.h"

Entity::Entity()
{
    pos_=new Position();
}

Entity::~Entity()
{
    delete pos_;
}
