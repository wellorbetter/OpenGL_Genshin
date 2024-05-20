#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Utils/animator.h"
#include "../GameObject/GameObject.h"
// ʵ����
// ����Ӧ�þ����ٶȣ�λ�ã�����������
class Entity:public GameObject {
public:
	Entity();

	// getter setter
	glm::vec3 getVelocity();
	void setVelocity(glm::vec3& _velocity);
	void zeroVelocity();

	glm::vec3 getDirection();
	void setDirection(glm::vec3& _direction);


	glm::vec3 getPosition();
	void setPosition(glm::vec3& _position);



	// ����ģ��dae�ĵ�ַ��ֱ�����ö�Ӧ��ģ�ͺͶ���
	// ����ֱ�Ӹ���״̬����������
	// ������ʵ���ϲ��Ǻܶ�������������һ�����õ�
	// ����ģ�͵Ĳ��ʺͶ�������һ��
	void setAnimation(string _stateName, bool _isActive);
	void Update() override;
	void Awake() override;
	void Start() override;

	void Destroy() override;
private:
	// ģ�� ����ģ�͵�ַȻ�����
	Model* model;
	
	// ��ǰ���ŵĶ���
	Animation* animation;

	// �ٶ�
	glm::vec3 velocity;
	
	// ����
	glm::vec3 direction;

	// λ�� ���ﱾ����Transform�ģ����������Ϸ�Ƚϼ򵥣���ֻ�õõ�position
	glm::vec3 position;

	// ��ǰ���ƶ��ٶ�

	// ����  ����ʵ�������ʼ��ʱ��
	// Animator ��Ӧ�ó�ʼ�����еĶ���
	// Ȼ��ͨ��static��ֱ�ӷ���
	// ͨ�����ò���ֵ��������ǰ״̬
	Animator* animator;
};