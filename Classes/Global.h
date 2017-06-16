//游戏全局用具

#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "cocos2d.h"

USING_NS_CC;

/* 取最大值 */
#define max(x,y) (x>y?x:y)
/* 取最小值 */
#define min(x,y) (x>y?y:x)

/* 全局常量设置 */
#define SCREEN_WIDTH			720			//屏幕高度
#define SCREEN_HEIGHT			1280		//屏幕宽度
#define SCREEN_FORM_NAME		"Arrow.io"	//窗口标题

#define WORLD_LENGTH			200			//世界长度
#define WORLD_WIDTH				200			//世界宽度
#define WORLD_HEIGHT			1			//世界高度
#define ELEMENT_HEIGHT			20			//墙的高度

#define CHARACTER_CACHE_SIZE	50			//人物对象缓存池大小
#define WEAPONS_CACHE_SIZE		100			//武器对象缓存池大小
#define AWARD_CACHE_SIZE		100			//奖励对象缓存池大小

#define INITIAL_LIFE_VALUE		100.f		//人物初始生命值

#define MAPS_FILE_LENGTH		50			//地图文件长
#define MAPS_FILE_WIDTH			50			//地图文件宽


enum GlobalType
{
	kGlobalStage,		//场景，障碍
	kGlobalCharacter,	//人物
	kGlobalWeapon,		//武器
	kGlobalAward		//奖励
};

enum WeaponType
{
	kWeaponArrow,		//箭矢
	kWeaponBomb,		//炸弹
	kWeaponDart			//飞镖
};

/* 判断 a 与 b 是否分别属于某两种对象 */
#define gObjectEqual(a,b,_a,_b) ((a==_a&&b==_b)||(a==_b&&b==_a))
#define u8 
//#pragma execution_character_set("utf-8")
const std::string CHARACTER_NAME[] = {
	u8"一袭白衣",
	u8"厌生′々",
	u8"枝上绵蛮",
	u8"一曲断弦╮",
	u8"风劲角弓鸣",
	u8"追梦少年",
	u8"青梅佐以酒",
	u8"踽踽独行",
	u8"胭脂蒅ㄋ洃",
	u8"回眸泪倾↗城",
	u8"有些秘密不能说",
	u8"韵华镜中池",
	u8"蓦地一相逢",
	u8"相约丶奈何桥",
	u8"笙歌醉梦间℃",
	u8"←琴默千弦︶",
	u8"无处寄笺",
	u8"是梦终会醒",
	u8"微凉·雅娅",
	u8"聚散如烟",
	u8"美貌征服祢娘",
	u8"帅炸宇宙",
	u8"我还爱你",
	u8"恶魔尊主卍",
	u8"tomahawk",
	u8"有你就够了",
	u8"帅死一条街",
	u8"┉至尊狂魔┈",
	u8"为你装逼为你疯",
	u8"我这种无赖",
	u8"狂刄星空",
	u8"散场的拥抱",
	u8"九星剑临",
	u8"有你在就足够",
	u8"屌丝一枚",
	u8"叶燃化诗",
	u8"王的第1001个梦",
	u8"嗜血超神",
	u8"向钱看向厚赚",
	u8"几分伤心几分痴",
	u8"血幡海盗",
	u8"野战霸王",
	u8"朕太高冷",
	u8"邮递时光",
	u8"七年为一梦",
	u8"柠檬不萌i",
	u8"爱鉨已成瘾",
	u8"←龙霸天下`",
	u8"孤的王朝",
	u8"别拽ni算what"
};
// 调试使用
#include <iostream>
using namespace std;

#endif
