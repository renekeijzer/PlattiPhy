#include "TheGrid\Component.hpp"
#include "Forces.h"

struct AABB {
	sf::Vector2f min;
	sf::Vector2f max;
};

struct PhysComp : Component<PhysComp>{
public:
	PhysComp(sf::Vector2f maxVelocity, float transitionSpeed, sf::Vector2f size, sf::Vector2f position, float mass) :
		velocity(sf::Vector2f(0, 0)),
		size(size),
		maxVelocity(maxVelocity),
		transitionSpeed(transitionSpeed),
		position(position),
		resitution(0.2),
		mass(1/mass)
	{
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


		auto rhsMiddleVector = rhs->getAABB().max - rhs->getAABB().min;
		rhsMiddleVector.x /= 2;
		rhsMiddleVector.y /= 2;
		rhsMiddleVector += rhs->getAABB().min;

		auto lhsMiddleVector = lhs->getAABB().max - lhs->getAABB().min;
		lhsMiddleVector.x /= 2;
		lhsMiddleVector.y /= 2;
		lhsMiddleVector += lhs->getAABB().min;		
		
		sf::Vector2f rv = rhs->velocity - lhs->velocity;
		float velAlongNormal = dotProduct(rv, normalize(rhsMiddleVector, lhsMiddleVector));
		if (velAlongNormal > 0) {
			return;
		}
		///should fix this someday
		float minRes = 0.2;

		float j = -(1 + minRes) * velAlongNormal;
		j /= lhs->mass + 1 / rhs->mass;

		
		sf::Vector2f impulseVector = normalize(rhsMiddleVector, lhsMiddleVector) * j;

		//lhs->velocity -= 1 / lhs->mass * impulseVector;
		//rhs->velocity += 1 / rhs->mass * impulseVector;

		float massSum = lhs->mass + rhs->mass;
		float ratio = lhs->mass / rhs->mass;
		lhs->velocity -= ratio * impulseVector;

		ratio = rhs->mass / massSum;
		rhs->velocity += ratio * impulseVector;



	}

	static sf::Vector2f normalize(sf::Vector2f rhs, sf::Vector2f lhs) {
		sf::Vector2f vec = rhs - lhs;
		sf::Vector2f normal;

		normal.x = vec.x / length(vec);
		normal.y = vec.y / length(vec);
		
		return normal;
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
	float resitution;
	sf::Vector2f velocity;
	sf::Vector2f maxVelocity;
	sf::Vector2f position;
	sf::Vector2f size;
	float mass;
	float transitionSpeed;
	AABB collision;

};
