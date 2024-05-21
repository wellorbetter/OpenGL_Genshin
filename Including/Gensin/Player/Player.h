#pragma once
#include "../Entity/Entity.h"
#include "PlayerStateMachine.h"
#include "PlayerMoveState.h"
#include "PlayerIdleState.h"
#include "../../Utils/Cinemachine.h"
// �����
// �����Ӧ�����ж�Ӧ��״̬����
class Player :public Entity {
public:
	PlayerIdleState* idleState;
	PlayerStateMachine* stateMachine;
	PlayerMoveState* moveState;
	Player(Cinemachine* _cinemachine);

	bool isMoving = false;

	void Awake() override;
	void Start() override;
	void Update(GLFWwindow* window) override;
	void Update(GLFWwindow* window, float deltaTime);
	// ��Ҫ��һ����һ�˳��ӽǵķ���λ��
private:
	Cinemachine* cinemachine;
};