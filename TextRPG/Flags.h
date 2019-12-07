
#pragma once

//Player Job Type
enum JOB
{
	JOB_NONE,
	JOB_WARRIOR,
	JOB_ARCHER,
	JOB_MAGICIAN,
	JOB_END

};

//Object Type
enum OBJECT_TYPE 
{
	OT_PLAYER,
	OT_MONSTER,
	OT_ITEM_WEAPON,
	OT_ITEM_ARMOR

};

//Item Type
enum ITEM_TYPE 
{
	ITEM_WEAPON,
	ITEM_ARMOR,
	ITEM_MAX

};

//Stage Type
enum STAGE_TYPE
{
	ST_NONE,
	ST_EASY,
	ST_NORMAL,
	ST_HARD,
	ST_BACK

};