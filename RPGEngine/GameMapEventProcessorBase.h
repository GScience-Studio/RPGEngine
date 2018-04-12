#pragma once

class GameMap;

class GameMapEventProcessorBase
{
public:
	//!������ƶ�ʱ����
	virtual void onPlayerMove(GameMap* gameMap, int toX, int toY) = 0;
	//����Һ͵�ͼ����ʱ���ã����Ի�ȡ����ҵ�λ�úͽ�����λ��
	virtual void onPlayerInteractTile(GameMap* gameMap, int playerX, int playerY, int x, int y) = 0;
	
	//����Һ�actor����ʱ���ã����Ի�ȡ����ҵ�λ�úͽ���actor��λ��
	virtual void onPlayerInteractActor(GameMap* gameMap, int playerX, int playerY, int x, int y) = 0;
	//����ҽ���Actor��Ұʱ���ã����Ի�ȡ����ҵ�λ�úͽ���actor��λ��
	virtual void onPlayerMoveInActorSight(GameMap* gameMap, int playerX, int playerY, int x, int y) = 0;

	virtual ~GameMapEventProcessorBase() = default;
};