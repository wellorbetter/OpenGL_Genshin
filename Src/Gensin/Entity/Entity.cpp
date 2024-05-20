#include "../../../Including/Gensin/Entity/Entity.h"

glm::vec3 Entity::getVelocity()
{
	return this->velocity;
}

void Entity::setVelocity(glm::vec3& _velocity)
{
	this->velocity = _velocity;
}

void Entity::zeroVelocity()
{
	this->velocity = glm::vec3(0.0f);
}

glm::vec3 Entity::getDirection()
{
	return this->direction;
}

void Entity::setDirection(glm::vec3& _direction)
{
	this->direction = _direction;
}

void Entity::setAnimation(string _stateName, bool _isActive)
{
	string modelPth = "Animation/babala/" + _stateName;
	this->model = new Model(modelPth);
	this->animation = new Animation(modelPth, model);
	this->animator = new Animator(this->animation);
}

void Entity::setPosition(glm::vec3& _position)
{
	this->position = _position;
}

glm::vec3 Entity::getPosition()
{
	return this->position;
}

void Entity::Update() 
{
	
}

void Entity::Start()
{

}

void Entity::Destroy()
{
	// 看看顺序有没有问题
	delete this->model;
	delete this->animation;
	delete this->animator;
}