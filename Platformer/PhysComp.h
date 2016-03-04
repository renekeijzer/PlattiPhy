#include "TheGrid\Component.hpp"
#include "Forces.h"
#include "Manifold.h"
#include <algorithm>

struct AABB {
	sf::Vector2f min;
	sf::Vector2f max;

public:
	sf::Vector2f getCenter() {
		auto returnVector = max - min;
		returnVector.x /= 2;
		returnVector.y /= 2;
		returnVector += min;

		return returnVector;
	}
};




struct PhysComp : Component<PhysComp>{
public:
	PhysComp(sf::Vector2f maxVelocity, float transitionSpeed, sf::Vector2f size, sf::Vector2f position, float imass) :
		velocity(sf::Vector2f(0, 0)),
		size(size),
		maxVelocity(maxVelocity),
		transitionSpeed(transitionSpeed),
		position(position),
		resitution(0.2)
	{
		if (imass == 0){
			mass = 0;
		}
		else{ mass = 1 / imass; }
		updateAABB();
	}

	


	sf::Vector2f calculateSpeed(double dt, sf::Vector2f heading) {

		velocity.x = velocity.x * (1 - dt * transitionSpeed) + (heading.x * maxVelocity.x) * (dt * transitionSpeed);
		velocity.y = velocity.y * (1 - dt * transitionSpeed) + (heading.y * maxVelocity.y) * (dt * transitionSpeed);

		return velocity;
	
	}

	sf::Vector2f getVelocity() {
		return velocity;
	}


	static bool AABBCollisionCheck(AABB a, AABB b) {
		if (a.max.x < b.min.x || a.min.x > b.max.x) 
			return false;
		if (a.max.y < b.min.y || a.min.y > b.max.y) 
			return false;
		return true;
	}

	void setPosition(sf::Vector2f pos) {
		position = pos;
		updateAABB();
	}

	sf::Vector2f getPosition() {
		return position;
	}

	void setSize(sf::Vector2f newSize){
		size = newSize;
		updateAABB();
	}

	sf::Vector2f getSize() {
		return size;
	}

	void setTransitionSpeed(float speed) {
		transitionSpeed = speed;
	}

	float getTransitionSpeed() {
		return transitionSpeed;
	}

	AABB getAABB() {
		return collision;
	}

	void updateAABB() {
		sf::Vector2f min, max;
		min.x = position.x;
		min.y = position.y;

		max.x = position.x + size.x;
		max.y = position.y + size.y;

		collision.min = min;
		collision.max = max;
	}

	static void resolveCollison(ComponentHandle<PhysComp> & lhs, ComponentHandle<PhysComp> & rhs) {
		
		if (rhs->getAABB().min.x < lhs->getAABB().min.x && rhs->getAABB().max.x < lhs->getAABB().max.x) {
			auto temp = lhs;
			lhs = rhs;
			rhs = temp;
		}

		if (rhs->mass == 0){ //division by 0 fix
			auto temp = lhs;
			lhs = rhs;
			rhs = temp;
		}


		sf::Vector2f rv = rhs->velocity - lhs->velocity;
		float velAlongNormal = dotProduct(rv, normalize(lhs->getAABB().getCenter(), rhs->getAABB().getCenter()));
		if (velAlongNormal > 0) {
			return;
		}
		///should fix this someday
		float minRes = 1;

		float j = -(1 + minRes) * velAlongNormal;
		j /= lhs->mass + 1 / rhs->mass;

		
		sf::Vector2f impulseVector = normalize(lhs->getAABB().getCenter(), rhs->getAABB().getCenter()) * j;

		float massSum = lhs->mass + rhs->mass;
		float ratio = lhs->mass / rhs->mass;
		lhs->velocity -= ratio * impulseVector;

		ratio = rhs->mass / massSum;

		rhs->velocity += ratio * impulseVector;

		Manifold man(lhs, rhs);	
		AABBvsAABB(man);
		posistionalCorrection(man);


	}
	
	static bool AABBvsAABB(Manifold & man) {
		auto A = man.lhs;
		auto B = man.rhs;
			// Vector from A to B
		sf::Vector2f n = B->getPosition() - A->getPosition();

		AABB abox = A->getAABB();
		AABB bbox = B->getAABB();

			// Calculate half extents along x axis for each object
		float a_extent = (abox.max.x - abox.min.x) / 2;
		float b_extent = (bbox.max.x - bbox.min.x) / 2;

			// Calculate overlap on x axis
		float x_overlap = a_extent + b_extent - abs(n.x);
		
			// SAT test on x axis
			if (x_overlap > 0)
			{
				// Calculate half extents along x axis for each object
				float a_extent = (abox.max.y - abox.min.y) / 2;
				float b_extent = (bbox.max.y - bbox.min.y) / 2;

					// Calculate overlap on y axis
				float y_overlap = a_extent + b_extent - abs(n.y);

					// SAT test on y axis
					if (y_overlap > 0)
					{
						// Find out which axis is axis of least penetration
						if (x_overlap > y_overlap)
						{
							// Point towards B knowing that n points from A to B
							if (n.x < 0) {
								man.normal = sf::Vector2f(-1, 0);
							}
							else {
								man.normal = sf::Vector2f(1, 0);
								man.penetration = x_overlap;
								return true;
							}
						}
						else
						{
							// Point toward B knowing that n points from A to B
							if (n.y < 0) {
								man.normal = sf::Vector2f(0, -1);
							}
							else {
								man.normal = sf::Vector2f(0, 1);
								man.penetration = y_overlap;
								return true;
							}
						}
					}
			}
	}

	static sf::Vector2f normalize(sf::Vector2f lhs, sf::Vector2f rhs) {
		sf::Vector2f vec = rhs - lhs;
		sf::Vector2f normal;

		normal.x = vec.x / length(vec);
		normal.y = vec.y / length(vec);
		
		return normal;
	}

	static void posistionalCorrection(Manifold & man){
		const float percent = 0.2;
		float slop = 0.1;

		sf::Vector2f n = man.normal;

		sf::Vector2f correction(0,0);
		
		correction.x = (std::max)(man.penetration - slop, 0.0f) / (man.lhs->mass + man.rhs->mass) * percent;
		correction.x = correction.x * n.x;

		correction.y = (std::max)(man.penetration - slop, 0.0f) / (man.lhs->mass + man.rhs->mass) * percent;
		correction.y = correction.y * n.y;
		std::cout << "correction : " << correction.x << " - " << correction.y << std::endl;

		man.lhs->setPosition(man.lhs->getPosition() - man.lhs->mass * correction);
		man.rhs->setPosition(man.rhs->getPosition() + man.rhs->mass * correction);

	}

	static AABB getCollisionRectangle(AABB & lhs, AABB & rhs){
		sf::Vector2f minV(0, 0);
		sf::Vector2f maxV(0, 0);
		AABB intersect;
		
		if (!AABBCollisionCheck(lhs, rhs)){
			intersect.min = minV;
			intersect.max = maxV;

			return intersect;
		}

		intersect.min = rhs.min;
		intersect.max = lhs.max;

		return intersect;

	}

	static float dotProduct(sf::Vector2f rhs, sf::Vector2f lhs) {
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}

	static float length(sf::Vector2f vec) {
		return sqrt(vec.x * vec.x + vec.y * vec.y);
	}


	bool colidesWith(AABB & other) {
		return AABBCollisionCheck(collision, other);
	}
private:

	sf::Vector2f velocity;
	sf::Vector2f maxVelocity;
	sf::Vector2f position;
	sf::Vector2f size;

	float mass;
	float resitution;
	float transitionSpeed;
	AABB collision;

};
