#pragma once

#include "value.h"

class CCore
{
private:
	LEVELUPINFO m_tLevelUpInfo[JOB_END - 1];

public:
	LEVELUPINFO GetLevelUpInfo(JOB eJob);
	
public:
	bool Init();
	void Run();

private:
	int OutputMenu();
	void SetLevelUPInfo();
	LEVELUPINFO CreateLevelUpInfo(int chaAttackMin, int chaAttackMax, int chaArmorMin, int chaArmorMax, int ChaHP, int ChaMP);
	DECLARE_SINGLE(CCore)
	
};

