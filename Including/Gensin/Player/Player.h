#pragma once
#include "../Entity/Entity.h"
#include "PlayerStateMachine.h"
#include "PlayerSlideState.h"
// 玩家类
// 玩家类应当具有对应的状态管理
class Player :public Entity {
public:
	PlayerIdelState* idleState;
	PlayerStateMachine* stateMachine;

	void Awake() override;
	void Start() override;
	void Update() override;
};