#include "../../../Including/Gensin/Entity/Entity.h"

void Entity::setSpeed(glm::vec3& _speed)
{
	this->speed = _speed;
}

glm::vec3 Entity::getSpeed()
{
	return this->speed;
}

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


void Entity::Update(GLFWwindow* window)
{
	// 实体这里是不能设置速度这些的，因为这些东西只有在具体的状态下面才会有
	// 实体可能会拥有这些状态，但是并不一定处于这些状态
	
}

void Entity::Awake()
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