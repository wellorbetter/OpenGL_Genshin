#include "../../../Including/Gensin/Entity/Entity.h"

Entity::Entity()
	:GameObject(), Collider()
{
	this->position = glm::vec3(0.0f);
	this->speed = glm::vec3(0.0f);
	this->velocity = glm::vec3(0.0f);
	this->direction = glm::vec3(0.0f);
	this->model = nullptr;
	this->animation = nullptr;
	this->animator = nullptr;
	this->HP = 3;
}

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

void Entity::setVelocity(glm::vec3& _velocity, std::string type)
{
	glm::vec2 newVelocity;
	if (type == "2D")
	{
		newVelocity = glm::vec2(_velocity.x, _velocity.z);
		this->setVelocity(newVelocity);
	}
	else
	{
		this->setVelocity(_velocity);
	}
}

void Entity::setVelocity(glm::vec3& _velocity)
{
	this->velocity = _velocity;
}

void Entity::setVelocity(glm::vec2& _velocity)
{
	this->velocity = glm::vec3(_velocity.x, 0, _velocity.y);
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
	// modelPath + _stateName 检测是否正确
	string _path = modelPath + _stateName + "/" + _stateName + ".dae";
	this->model = Animator::models[_path];
	this->animation = Animator::animations[_path];
	this->animator = new Animator(this->animation);
}

void Entity::setPosition(glm::vec3& _position)
{
	this->position = _position;
	// 更新位置的时候也要更新碰撞体的位置
	this->setColliderPosition(_position);
}

void Entity::setColliderPosition(glm::vec3& _position)
{
	// 当前中心点就是position的位置，以它为中心长为boxLength的盒子即可
	this->colliderCenter = _position;
	this->leftDown = glm::vec3(_position.x - this->boxLength / 2, _position.y - this->boxLength / 2, _position.z - this->boxLength / 2);
	this->rightUp = glm::vec3(_position.x + this->boxLength / 2, _position.y + this->boxLength / 2, _position.z + this->boxLength / 2);
}


void Entity::setPosition(glm::vec2& _position)
{
	glm::vec3 newPosition = glm::vec3(_position.x, 0, _position.y);
	this->position = newPosition;
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

void Entity::Damage()
{
	// 伤害
	this->HP -= 1;
}