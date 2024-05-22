#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Utils/animator.h"
#include "../GameObject/GameObject.h"
// ʵ����
// ����Ӧ�þ����ٶȣ�λ�ã�����������
class Entity:public GameObject, public Collider {
public:
	Animator* animator;
	Model* model;
	std::string modelPath;
	glm::vec3 position;
	float HP;
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
	// ��Ҫ��Animator����update
	void UpdateAnimation(float deltaTime);

	// �ƶ�
	void move(glm::vec2 _direction, float deltaTime);

	// ����ģ��dae�ĵ�ַ��ֱ�����ö�Ӧ��ģ�ͺͶ���
	// ����ֱ�Ӹ���״̬����������
	// ������ʵ���ϲ��Ǻܶ�������������һ�����õ�
	// ����ģ�͵Ĳ��ʺͶ�������һ��
	void setAnimation(string _stateName, bool _isActive);
	void Update(GLFWwindow* window) override;
	void Awake() override;
	void Start() override;
	void Destroy() override;
	virtual void Damage();
private:
	// ģ�� ����ģ�͵�ַȻ�����
	
	
	// ��ǰ���ŵĶ���
	Animation* animation;

	// Ӧ�����еĸ������ٶ�
	glm::vec3 speed;

	// ʵ���ٶ�
	glm::vec3 velocity;
	
	// ����
	glm::vec3 direction;

	// λ�� ���ﱾ����Transform�ģ����������Ϸ�Ƚϼ򵥣���ֻ�õõ�position
	

	// ��ǰ���ƶ��ٶ�

	// ����  ����ʵ�������ʼ��ʱ��
	// Animator ��Ӧ�ó�ʼ�����еĶ���
	// Ȼ��ͨ��static��ֱ�ӷ���
	// ͨ�����ò���ֵ��������ǰ״̬
	
};