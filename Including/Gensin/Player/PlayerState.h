#pragma once

#include <string>
#include "Player.h"
#include "PlayerStateMachine.h"

class PlayerState {
public:
	virtual void Enter() = 0;
	virtual void Exit() = 0;
protected:
	// ״̬�� 
	// ������Animation\babala\stateName
	// �����ҵ���Ӧ��ģ���ļ�
	std::string stateName;

	// ״̬���ֵ�player
	Player* player;

	// ��Ӧ��״̬�� ������Ȼ������player���ʣ�����Ϊ�˼���ǰ׺�����Ǽ���
	PlayerStateMachine* stateMachine;

	// ��ʼ�����캯��
	PlayerState(Player* _player, PlayerStateMachine* _stateMachine, string _stateName);
};