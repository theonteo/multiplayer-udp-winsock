#include "Physics.h"

bool Physics::CircleToCircle
(const glm::vec3 pos1, float r1, const glm::vec3 pos2, float r2)
{
	return (glm::length(pos1 - pos2) < (r1 + r2));
}
