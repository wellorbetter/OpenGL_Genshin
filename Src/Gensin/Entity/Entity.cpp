#include "../../../Including/Gensin/Entity/Entity.h"

Entity::Entity()
	:GameObject()
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
	// modelPath + _stateName ����Ƿ���ȷ
	string _path = modelPath + _stateName + "/" + _stateName + ".dae";
	this->model = Animator::models[_path];
	this->animation = Animator::animations[_path];
	this->animator = new Animator(this->animation);
}

void Entity::setPosition(glm::vec3& _position)
{
	this->position = _position;
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
	// ʵ�������ǲ��������ٶ���Щ�ģ���Ϊ��Щ����ֻ���ھ����״̬����Ż���
	// ʵ����ܻ�ӵ����Щ״̬�����ǲ���һ��������Щ״̬
	
}

void Entity::Awake()
{
	
}


void Entity::Start()
{

}


void Entity::Damage()
{
	// �˺�
	this->HP -= 1;
}