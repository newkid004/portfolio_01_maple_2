#pragma once

namespace itemDef
{
	enum ITEM_TYPE {
		ITEM_TYPE_NONE					=	0,
		ITEM_TYPE_EQUIP					=	0x1000,
		ITEM_TYPE_USEABLE				=	0x2000,
		ITEM_TYPE_COUNTABLE				=	0x4000,
		ITEM_TYPE_CHECK					=	0x00ff,

		ITEM_TYPE_WEAPON				=	0x0001,
		ITEM_TYPE_ARMOR					=	0x0002,
		ITEM_TYPE_EQUIPMENT				=	0x0003,

		ITEM_TYPE_CONSUMABLE			=	0x0004,

		ITEM_TYPE_ETC					=	0x0008,
		ITEM_TYPE_FIT					=	0x0010,
		ITEM_TYPE_CACHE					=	0x0020
	};

	enum ITEM_KIND_WEAPON
	{
		ITEM_KIND_ONEHAND				=	0x1000, 
		ITEM_KIND_TWOHAND				=	0x2000,

		ITEM_KIND_ONEHANDSWORD			=	0x1001,
		ITEM_KIND_ONEHANDMACE			=	0x1002,
		ITEM_KIND_ONEHANDAXE			=	0x1004,
		ITEM_KIND_WAND					=	0x1008,
		ITEM_KIND_DAGGER				=	0x1010,
		ITEM_KIND_SHILED				=	0x1020,

		ITEM_KIND_TWOHANDSWORD			=	0x2001,
		ITEM_KIND_SPEAR					=	0x2002,
		ITEM_KIND_POLARM				=	0x2004,
		ITEM_KIND_TWOHANDMACE			=	0x2008,
		ITEM_KIND_TWOHANDAXE			=	0x2010,
		ITEM_KIND_STEFF					=	0x2020,
		ITEM_KIND_WARP					=	0x2040,
		ITEM_KIND_BOW					=	0x2080,
		ITEM_KIND_CROSSBOW				=	0x2100,
	};

	enum ITEM_KIND_AMMOR
	{
		ITEM_KIND_HAT,
		ITEM_KIND_UPPERCLOTHES,
		ITEM_KIND_LOWERCLOTHES,
		ITEM_KIND_SHOES,
		ITEM_KIND_GLOVE,
		ITEM_KIND_CAPE,
	};

	enum ITEM_KIND_CONSUMABLE
	{
		ITEM_KIND_PORSION,
		ITEM_KIND_WEAPON_THIEF,
		ITEM_KIND_WEAPON_ARCHER,
		ITEM_KIND_ORDERSHEET,
	};

	enum ITEM_KIND_FIT
	{
		

	};

	enum ITEM_KIND_ETC
	{


	};
	enum ITEM_KIND_CACHE
	{
		ITEM_KIND_EQUIP					=	0x1000,
		ITEM_KIND_CONSUMABLE			=	0x2000,



	};
	

	enum ITEM_ID
	{
		TWOHANDSWORD				= 0,

	};

}