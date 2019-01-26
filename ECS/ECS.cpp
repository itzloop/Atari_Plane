#pragma once
#include "ECS.h"

void Entity::AddGroup(Group mGroup)
{

    groupBitset[mGroup] = true;
    manager.AddGroup(this , mGroup);

}
