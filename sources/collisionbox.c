#include "../headers/collisionbox.h"

int collided(CollisionBox a, CollisionBox b)
{
    if (a.min.x > b.max.x || a.max.x < b.min.x || a.min.y > b.max.y || a.max.y < b.min.y)
    {
        return 0;
    }

    return 1;
}