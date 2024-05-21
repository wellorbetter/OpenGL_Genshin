#pragma once
#include "../Entity/Entity.h"
#include "PlayerStateMachine.h"
#include "PlayerIdleState.h"
// �����
// �����Ӧ�����ж�Ӧ��״̬����
class Player :public Entity {
public:
	PlayerIdleState* idleState;
	PlayerStateMachine* stateMachine;

	void Awake() override;
	void Start() override;
	void Update(GLFWwindow* window) override;
};