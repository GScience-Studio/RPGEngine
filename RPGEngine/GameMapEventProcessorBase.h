#pragma once

class GameMap;

/*!�������ͼ�¼�
 * ����Ϊÿ����ͼ����һ������GameMapEventProcessorBase���ಢ�ڴ�����ͼʱ����
 */
class GameMapEventProcessorBase
{
public:
	//!������ƶ�ʱ����
	virtual void onPlayerMove(int toX, int toY) {};
	//!����Һ͵�ͼ����ʱ���ã����Ի�ȡ����ҵ�λ�úͽ�����λ��
	virtual void onPlayerInteractTile(int playerX, int playerY, int x, int y) {};
	
	//!����Һ�actor����ʱ���ã����Ի�ȡ����ҵ�λ�úͽ���actor��λ��
	virtual void onPlayerInteractActor(const char* actorName, int playerX, int playerY, int x, int y) {};
	//!����ҽ���Actor��Ұʱ���ã����Ի�ȡ����ҵ�λ�úͽ���actor��λ��
	virtual void onPlayerMoveInActorSight(const char* actorName, int playerX, int playerY, int x, int y) {};

	//!����ͼ��ʼ����ʱ�򣬼�����������ʱ��
	virtual void onInitMap(GameMap* gameMap) {};

	virtual ~GameMapEventProcessorBase() = default;
};