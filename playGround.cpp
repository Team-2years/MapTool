#include "stdafx.h"
#include "playGround.h"
#include "IceScene.h"
#include "testScene.h"
#include "LineVariation.h"
#include "villageScene.h"
#include "IceBoss.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ�� ����� �ϼ��� ����
HRESULT playGround::init()
{
	gameNode::init(true);
	IMAGEMANAGER->addFrameDImage("MapAir", L"img/mapSprite/MapTileset_Air.png", 512,512, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("MapCastleBase", L"img/mapSprite/MapTileset_CastleBase.png", 512,512, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("MapCastle", L"img/mapSprite/MapTileset_Castle.png", 512,512, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("MapCourtyard", L"img/mapSprite/MapTileset_Courtyard.png", 512,512, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("MapEarth", L"img/mapSprite/MapTileset_Earth.png", 512,512, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("MapFire", L"img/mapSprite/MapTileset_Fire.png", 512,512, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("MapHome", L"img/mapSprite/MapTileset_Home.png", 512,512, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("MapIce", L"img/mapSprite/MapTileset_Ice.png", 512,512, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("MapLightning", L"img/mapSprite/MapTileset_Lightning.png", 512,512, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("MapMuseum", L"img/mapSprite/MapTileset_Museum.png", 512,512, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("MapPlaza", L"img/mapSprite/MapTileset_Plaza.png", 512, 512, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("MapPrison", L"img/mapSprite/MapTileset_Prison.png", 512, 512, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("MapBlack", L"img/mapSprite/MapTileset_Black.png", 512, 512, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Obj1",L"img/objSprite/obj1.png", 512, 512, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("Obj2", L"img/objSprite/obj2.png", 512, 512, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("ObjStore", L"img/objSprite/objStore.png", 512, 512, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("ObjWood", L"img/objSprite/objWood.png", 512, 512, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("ObjIce1", L"img/objSprite/objIce1.png", 512, 512, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("ObjIce2", L"img/objSprite/objIce2.png", 512, 512, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("ObjTrees", L"img/objSprite/objTrees.png", 512, 512, SAMPLETILEX, SAMPLETILEY);
	IMAGEMANAGER->addFrameDImage("ObjStatue", L"img/objSprite/objStatue.png", 512, 512, SAMPLETILEX, SAMPLETILEY);


	CAMERAMANAGER->setBackScreenSize(5000, 5000);
	SCENEMANAGER->addScene("�׽�Ʈ", new testScene);
	SCENEMANAGER->addScene("���̽�", new IceScene);
	SCENEMANAGER->addScene("���̽�����", new IceBoss);
	SCENEMANAGER->addScene("����", new LineVariation);
	SCENEMANAGER->addScene("����", new villageScene);
	SCENEMANAGER->changeScene("����");
	return S_OK;
}

//�޸� ������ ����� �ϼ��� ����
void playGround::release()
{
	gameNode::release();
	
}


void playGround::update()
{
	gameNode::update();
	SCENEMANAGER->update();
}


void playGround::render()
{
	
	DTDMANAGER->beginDraw();
	//================���� �� ���̿� �� �׸��ô�==========================

	SCENEMANAGER->render();
	RENDERMANAGER->render();

	DTDMANAGER->endDraw();
	//==================================================s
	//this->getBackBuffer()->render(getHDC(), 0, 0);
	//CAMERAMANAGER->render(getHDC(), 0, 0, getMemDC());
	DTDMANAGER->render();
}