#pragma once
#include "../Entity/Entity.h"
#include "PlayerStateMachine.h"
#include "PlayerMoveState.h"
#include "PlayerIdleState.h"
#include "PlayerJumpState.h"
#include "PlayerAttackState.h"
#include "../../Utils/Cinemachine.h"
// �����
// �����Ӧ�����ж�Ӧ��״̬����
class Player :public Entity {
public:
	PlayerIdleState* idleState;
	PlayerStateMachine* stateMachine;
	PlayerMoveState* moveState;
	PlayerJumpState* jumpState;
	PlayerAttackState* attackState;

	Player(Cinemachine* _cinemachine);

	bool isMoving = false;

	void Awake() override;
	void Start() override;
	void Update(GLFWwindow* window) override;
	void Update(GLFWwindow* window, float deltaTime);
	void Damage() override;
	// ��Ҫ��һ����һ�˳��ӽǵķ���λ��
	void fireBullet(float len);
	Cinemachine* cinemachine;
};

class Bullet : public Collider {
	// ��ǰλ�� ���� �ٶ�
public:
	glm::vec3 position;
	glm::vec3 direction;
	float speed;
	Bullet(glm::vec3 _position, glm::vec3 _direction, float _speed)
	{
		position = _position;
		direction = _direction;
		speed = _speed;
	}
	void Update(float deltaTime);
	void Draw();
};