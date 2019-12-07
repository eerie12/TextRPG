#pragma once

#include "value.h"

enum STORE_TYPE 
{
	STORE_NONE,
	STORE_WEAPON,
	STORE_ARMOR,
	STORE_BACK,

};


class CStoreManager
{
private:
	vector<class CStore*> m_vecstore;


public:
	bool Init();
	void Run();

private:
	CStore* CreateStore(STORE_TYPE eType);
	int OutputMenu();

	DECLARE_SINGLE(CStoreManager)

};

