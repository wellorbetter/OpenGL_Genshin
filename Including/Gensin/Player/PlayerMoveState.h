#pragma once
#include "PlayerState.h"

class PlayerFrontMoveState;
class PlayerBackMoveState;
class PlayerLeftMoveState;
class PlayerRightMoveState;

class PlayerMoveState : public PlayerState
{
public:
	void Update(GLFWwindow* window) override;
	void Update(GLFWwindow* window, float deltaTime) override;
	void Enter() override;
	PlayerFrontMoveState* frontState;
	PlayerBackMoveState* backState;
	PlayerLeftMoveState* leftState;
	PlayerRightMoveState* rightState;
	PlayerMoveState(Player* _player, PlayerStateMachine* _stateMachine, std::string _stateName);
};

void moveUpdate(PlayerState* nowState, PlayerMoveState* state, GLFWwindow* window, float deltaTime);

void changeDir(Player* player, MoveDirection moveDirection);

class PlayerFrontMoveState :public PlayerState {
public:
	PlayerMoveState* moveState;
	PlayerFrontMoveState(Player* _player, PlayerStateMachine* _stateMachine, PlayerMoveState* _moveState, std::string _stateName)
		:PlayerState(_player, _stateMachine, _stateName)
	{
		moveState = _moveState;
	}
	void Update(GLFWwindow* window) override {
		
	}
	void Update(GLFWwindow* window, float deltaTime) override
	{
		this->Update(window);
		moveUpdate(this, moveState, window, deltaTime);
	}
};

class PlayerBackMoveState :public PlayerState {
public:
	PlayerMoveState* moveState;
	PlayerBackMoveState(Player* _player, PlayerStateMachine* _stateMachine, PlayerMoveState* _moveState, std::string _stateName)
		:PlayerState(_player, _stateMachine, _stateName)
	{
		moveState = _moveState;
	}
	void Update(GLFWwindow* window) override {

	}
	void Update(GLFWwindow* window, float deltaTime) override
	{
		this->Update(window);
		moveUpdate(this, moveState, window, deltaTime);
	}
};

class PlayerLeftMoveState :public PlayerState {
public:
	PlayerMoveState* moveState;
	PlayerLeftMoveState(Player* _player, PlayerStateMachine* _stateMachine, PlayerMoveState* _moveState, std::string _stateName)
		:PlayerState(_player, _stateMachine, _stateName)
	{
		moveState = _moveState;
	}
	void Update(GLFWwindow* window) override {

	}
	void Update(GLFWwindow* window, float deltaTime) override
	{
		this->Update(window);
		moveUpdate(this, moveState, window, deltaTime);
	}
};

class PlayerRightMoveState :public PlayerState {
public:
	PlayerMoveState* moveState;
	PlayerRightMoveState(Player* _player, PlayerStateMachine* _stateMachine, PlayerMoveState* _moveState, std::string _stateName)
		:PlayerState(_player, _stateMachine, _stateName)
	{
		moveState = _moveState;
	}
	void Update(GLFWwindow* window) override {

	}
	void Update(GLFWwindow* window, float deltaTime) override
	{
		this->Update(window);
		moveUpdate(this, moveState, window, deltaTime);
	}
};