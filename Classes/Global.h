//��Ϸȫ���þ�

#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "cocos2d.h"

USING_NS_CC;

/* ȡ���ֵ */
#define max(x,y) (x>y?x:y)
/* ȡ��Сֵ */
#define min(x,y) (x>y?y:x)

/* ȫ�ֳ������� */
#define SCREEN_WIDTH			720			//��Ļ�߶�
#define SCREEN_HEIGHT			1280		//��Ļ���
#define SCREEN_FORM_NAME		"Arrow.io"	//���ڱ���

#define WORLD_LENGTH			200			//���糤��
#define WORLD_WIDTH				200			//������
#define WORLD_HEIGHT			1			//����߶�
#define ELEMENT_HEIGHT			20			//ǽ�ĸ߶�

#define CHARACTER_CACHE_SIZE	50			//������󻺴�ش�С
#define WEAPONS_CACHE_SIZE		100			//�������󻺴�ش�С
#define AWARD_CACHE_SIZE		100			//�������󻺴�ش�С

#define INITIAL_LIFE_VALUE		100.f		//�����ʼ����ֵ

#define MAPS_FILE_LENGTH		50			//��ͼ�ļ���
#define MAPS_FILE_WIDTH			50			//��ͼ�ļ���


enum GlobalType
{
	kGlobalStage,		//�������ϰ�
	kGlobalCharacter,	//����
	kGlobalWeapon,		//����
	kGlobalAward		//����
};

enum WeaponType
{
	kWeaponArrow,		//��ʸ
	kWeaponBomb,		//ը��
	kWeaponDart			//����
};

/* �ж� a �� b �Ƿ�ֱ�����ĳ���ֶ��� */
#define gObjectEqual(a,b,_a,_b) ((a==_a&&b==_b)||(a==_b&&b==_a))
#define u8 
//#pragma execution_character_set("utf-8")
const std::string CHARACTER_NAME[] = {
	u8"һϮ����",
	u8"�����䡩",
	u8"֦������",
	u8"һ�����Ҩr",
	u8"�羢�ǹ���",
	u8"׷������",
	u8"��÷���Ծ�",
	u8"�������",
	u8"��֬�G�˛�",
	u8"��������J��",
	u8"��Щ���ܲ���˵",
	u8"�ϻ����г�",
	u8"���һ���",
	u8"��Լؼ�κ���",
	u8"�ϸ����μ��",
	u8"����Ĭǧ�Ҧ�",
	u8"�޴��ļ�",
	u8"�����ջ���",
	u8"΢�������",
	u8"��ɢ����",
	u8"��ò��������",
	u8"˧ը����",
	u8"�һ�����",
	u8"��ħ�����d",
	u8"tomahawk",
	u8"����͹���",
	u8"˧��һ����",
	u8"�������ħ��",
	u8"Ϊ��װ��Ϊ���",
	u8"����������",
	u8"��U�ǿ�",
	u8"ɢ����ӵ��",
	u8"���ǽ���",
	u8"�����ھ��㹻",
	u8"��˿һö",
	u8"Ҷȼ��ʫ",
	u8"���ĵ�1001����",
	u8"��Ѫ����",
	u8"��Ǯ�����׬",
	u8"�������ļ��ֳ�",
	u8"Ѫᦺ���",
	u8"Ұս����",
	u8"��̫����",
	u8"�ʵ�ʱ��",
	u8"����Ϊһ��",
	u8"���ʲ���i",
	u8"���b�ѳ��",
	u8"����������`",
	u8"�µ�����",
	u8"��קni��what"
};
// ����ʹ��
#include <iostream>
using namespace std;

#endif
