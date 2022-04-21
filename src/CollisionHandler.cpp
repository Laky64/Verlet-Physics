#include "../include/CollisionHandler.h"
#include "math.h"

CollisionHandler::CollisionHandler()
{
}

CollisionHandler::~CollisionHandler()
{
}

bool CollisionHandler::getIntersection(line first, line second)
{

    float slope = (first.start.y - first.end.y) / (first.end.x - first.start.x);
    float xPos1 = second.start.x - first.start.x;
    float xPos2 = second.end.x - first.start.x;
    bool firstY = (first.start.y - (xPos1 * slope) > second.start.y);
    bool secondY = (first.start.y - (xPos2 * slope) > second.end.y);
    if (firstY != secondY)
    {
        slope = (second.start.y - second.end.y) / (second.end.x - second.start.x);
        xPos1 = first.start.x - second.start.x;
        xPos2 = first.end.x - second.start.x;
        firstY = (second.start.y - (xPos1 * slope) > first.start.y);
        secondY = (second.start.y - (xPos2 * slope) > first.end.y);
        if (firstY != secondY)
        {
            return true;
        }
    }
    return false;
}

void CollisionHandler::solveCollisions(std::list<VerletObject *> *Objects)
{

    for (VerletObject *it : *Objects)
    {
        for (VerletObject *it2 : *Objects)
        {
            if (it->index != it2->index && it->index > it2->index)
            {
                for (VerletString &it3 : it->Strings)
                {
                    for (VerletString &it4 : it2->Strings)
                    {

                        const line first(it3.start, it3.end);
                        const line second(it4.start, it4.end);

                        if (getIntersection(first, second))
                        {
                            sf::Vector2f collision = it->getPosition() - it2->getPosition();
                            sf::Vector2f collisionForce = collision / sqrtf((collision.x) * (collision.x) + (collision.y) * (collision.y));
                            it->addPostion(0.5f * collisionForce);
                            it2->addPostion(-0.5f * collisionForce);
                        }
                    }
                }
            }
        }
    }
}
