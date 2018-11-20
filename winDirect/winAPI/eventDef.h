#pragma once

// ----- type : 0x000f ----- //
// 이벤트로 전달되는 인자의 형태
// 각 sour, destParam의 0x000f번째(0x000f 000f)의 형태로 전달
// 예) enemy -> player에게 전달(param = 0x0002 000e)
enum e_EVENT_TYPE
{
	ET_EVENT	= 0x1,
	ET_OBJECT	= 0x2,
	ET_PATTEN	= 0x3,
	ET_EFFECT	= 0x4,
	ET_SKILL	= 0x5,
	ET_QUEST	= 0x6,
	ET_FIELD	= 0x7,
	ET_BUFF		= 0x8,
	ET_BULLET	= 0x9,
	ET_WINDOW	= 0xa,
	ET_ITEM		= 0xb,
	ET_SHOP		= 0xc,
	ET_SYSETM	= 0xd,
	ET_PLAYER	= 0xe,

	ET_NONE = 0
};

// ----- kind : 0x00f0 ----- //
// 이벤트로 전달되는 인자의 세부형태
// 각 sour, destParam의 0x00f0번째(0x00f0 00f0)의 형태로 전달
// 세부형태가 딱히 없으면 비워둠(0)

// kind : object
enum e_EVENT_KIND_OBJECT
{
	EK_OBJECT_BASE			= 0x10,
	EK_OBJECT_CHARACTER		= 0x20,
	EK_OBJECT_ENEMY			= 0x30,
	EK_OBJECT_BOSS			= 0x40,
	EK_OBJECT_NPC			= 0x50,
	EK_OBJECT_ITEM			= 0x60,
	EK_OBJECT_BULLET		= 0x70,

	EK_OBJECT_NONE = 0
};

// kind : item
enum e_EVENT_KIND_ITEM
{
	EK_ITEM_EQUIPMENT	= 0x10,
	EK_ITEM_CONSUMEABLE	= 0x20,
	EK_ITEM_FIT			= 0x30,
	EK_ITEM_ETC			= 0x40,
	EK_ITEM_CACHE		= 0x50,

	EK_ITEM_NONE = 0
};

enum e_EVENT_KIND_SKILL
{
	EK_SKILL_NONE = 0
};

enum e_EVENT_KIND_PLAYER
{
	EK_PLAYER_NONE = 0
};

// ----- act : 0x0f00 ----- //
// 인자 간 이벤트의 실행 형태
// 각 sour, destParam의 0x0f00번째(0x0f00 0f00)의 형태로 전달
// 각 enum에 원하는 구분요소가 없을때마다 임의로 추가

// act : object - enemy
enum e_EVENT_ACT_OBJ_ENEMY
{
	EA_OBJ_ENEMY_NONE = 0
};

// act : obeject - item
enum e_EVENT_ACT_OBJ_ITEM
{
	EA_OBJ_ITEM_DROP	= 0x100,	// 떨굼 ( player, monster )
	EA_OBJ_ITEM_TAKE	= 0x200,	// 획득
	EA_OBJ_ITEM_USE		= 0x300,	// 사용 (인벤토리 내)

	EA_OBJ_ITEM_NONE = 0
};

// act : item - equipment
enum e_EVENT_ACT_ITEM_EQUIPMENT
{
	EA_ITEM_EQUIPMENT_USE		= 0x100,	// 사용
	EA_ITEM_EQUIPMENT_TAKE_ON	= 0x200,	// 장착
	EA_ITEM_EQUIPMENT_TAKE_OFF	= 0x300,	// 탈착

	EA_ITEM_EQUIPMENT_NONE = 0
};

// act : item - consumeable
enum e_EVENT_ACT_ITEM_CONSUMEABLE
{
	EA_ITEM_CONSUMEABLE_USE			= 0x100,
	EA_ITEM_CONSUMEABLE_INCREASE	= 0x200,
	EA_ITEM_CONSUMEABLE_DECREASE	= 0x300,
	EA_ITEM_CONSUMEABLE_DELETE		= 0x400,

	EA_ITEM_CONSUMEABLE_NONE = 0
};

// act : player - status
enum e_EVENT_ACT_PLAYER_STATUS
{
	EA_PLAYER_STATUS_STR		= 0x100,
	EA_PLAYER_STATUS_DEX		= 0x200,
	EA_PLAYER_STATUS_INT		= 0x300,
	EA_PLAYER_STATUS_LUK		= 0x400,
	EA_PLAYER_STATUS_LEVEL		= 0x500,
	EA_PLAYER_STATUS_EXP		= 0x600,

	EA_PLAYER_STATUS_NONE = 0
};

// ----- call : 0xf000 ---- //
// 위 사항의 형태에 따른 캐쳐 호출형태(index)
// 각 sour, destParam의 0xf000번째(0xf000 f000)의 형태로 전달
// 세부형태가 딱히 없으면 비워둠(0)

// call : player - status - change
enum e_EVENT_CALL_PLAYER_STATUS_CHANGE
{
	EC_PLAYER_STATUS_CHANGE_INCREASE	= 0x1000,
	EC_PLAYER_STATUS_CHANGE_DECREASE	= 0x2000,
	
	EC_PLAYER_STATUS_CHANGE_NONE	= 0
};