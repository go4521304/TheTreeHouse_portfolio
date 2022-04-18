#pragma once
#include <unordered_map>

class cUser;

class cUserManager
{
public:
	cUserManager();
	~cUserManager();

	void Init();
	void InitUsers();
	unsigned int GetNewID();

public: 
	static unordered_map <unsigned int, cUser*> m_users;

private:
	unsigned int     m_last_id;
	CRITICAL_SECTION m_last_id_cs;
};