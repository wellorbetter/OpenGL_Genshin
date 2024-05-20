#pragma once
#include "../Entity/Entity.h"
#include "PlayerIdleState.h"
#include "Player.h"

// �����
// �����Ӧ�����ж�Ӧ��״̬����
class Player :public Entity {
public:
	PlayerIdelState* idleState;
	PlayerStateMachine* stateMachine;

	void Awake() override;
	void Start() override;
	void Update() override;
};