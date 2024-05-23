#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Utils/animator.h"
#include "../GameObject/GameObject.h"
// 实体类
// 首先应该具有速度，位置，动画等属性
class Entity:public GameObject, public Collider {
public:
	Animator* animator;
	Model* model;
	std::string modelPath;
	glm::vec3 position;
	float HP; bool isAlive = true;
	Entity();

	void setSpeed(glm::vec3& _speed);
	glm::vec3 getSpeed();

	// getter setter
	glm::vec3 getVelocity();
	void setVelocity(glm::vec3& _velocity, std::string type);
	void setVelocity(glm::vec3& _velocity);
	void setVelocity(glm::vec2& _velocity);
	void zeroVelocity();

	glm::vec3 getDirection();
	void setDirection(glm::vec3& _direction);


	glm::vec3 getPosition();
	void setPosition(glm::vec3& _position);
	void setPosition(glm::vec2& _position);
	void setColliderPosition(glm::vec3& _position);
	// 需要给Animator设置update
	void UpdateAnimation(float deltaTime);

	// 移动
	void move(glm::vec2 _direction, float deltaTime);

	// 给出模型dae的地址，直接设置对应的模型和动画
	// 算了直接给出状态名更加贴切
	// 这里我实际上不是很懂，它们两个是一起设置的
	// 骨骼模型的材质和动画绑定在一起
	void setAnimation(string _stateName, bool _isActive);
	void Update(GLFWwindow* window) override;
	void Awake() override;
	void Start() override;
	void Destroy() override;
	virtual void Damage();
private:
	// 模型 给出模型地址然后加载
	
	
	// 当前播放的动画
	Animation* animation;

	// 应当具有的各方向速度
	glm::vec3 speed;

	// 实际速度
	glm::vec3 velocity;
	
	// 方向
	glm::vec3 direction;

	// 位置 这里本该是Transform的，但是这个游戏比较简单，就只用得到position
	

	// 当前的移动速度

	// 动画  这里实际上在最开始的时候
	// Animator 就应该初始化所有的动画
	// 然后通过static来直接访问
	// 通过设置布尔值来决定当前状态
	
};