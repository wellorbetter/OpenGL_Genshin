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
	this->model = Animator::models[_stateName];
	this->animation = Animator::animations[_stateName];
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

void Entity::UpdateAnimation(float deltaTime)
{
	this->animator->UpdateAnimation(deltaTime);
}


void Entity::Update() 
{
	
}

void Entity::Awake()
{
	
}


void Entity::Start()
{

}

void Entity::Destroy()
{
	// ����˳����û������
	delete this->model;
	delete this->animation;
	delete this->animator;
}