#pragma once
#include <unordered_map>
#include <mutex>
#include "ObjectPool.h"
#include "GameObject.h"
#include "Character.h"

class cRoom;

class cRoomManager
{
public:
	cRoomManager();
	~cRoomManager();

	void Init();
	void InitRooms();
	unsigned int CreateRoom(const unsigned int _user_id);
	bool JoinRoom(const unsigned int _user_id, const unsigned int _room_id);

public:
	static unordered_map<unsigned int, cRoom*> m_rooms;

protected:
	static cObjectPool<cGameObject>       m_object_pool;
	static cObjectPool<cCharacter>        m_character_pool;

private:
	std::atomic<unsigned int>             m_last_id;

	friend cRoom;

};