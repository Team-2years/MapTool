#pragma once
#include "gameNode.h"

#define TILESIZE 32

#define TILEX 100	//���� Ÿ�� ����
#define TILEY 100	//���� Ÿ�� ����
#define RENDERTILEX 20 //�׸� ���� Ÿ�� ����
#define RENDERTILEY 20 //�׸� ���� Ÿ�� ����
#define MINITILESIZE 4.f //�̴ϸ� Ÿ�� ũ��
#define TILESIZEX TILESIZE * TILEX	//640 32 * 20
#define TILESIZEY TILESIZE * TILEY	//640 32 * 20
#define WIDTHDUNGEONNUM 3
#define LENGTHDUNGEONNUM 2
#define IMAGENUM 21
#define OBJLEVEL 3

//Ÿ�ϼ� ����
#define SAMPLETILEX 32
#define SAMPLETILEY 32
#define SAMPLETILESIZE 16

enum CTRL
{
	CTRL_SAVE,			//���̺�		��ư
	CTRL_LOAD,			//�ε�		��ư
	CTRL_TERRAINDRAW,	//����		��ư
	CTRL_OBJDRAW,		//������Ʈ	��ư
	CTRL_ERASER,		//���찳		��ư
	CTRL_END
};
//����
enum TERRAIN
{
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_END
};

//������Ʈ
enum OBJECT
{
	OBJ_JAR,
	OBJ_FRAME,
	OBJ_TREE,
	OBJ_RUG,
	OBJ_NONE
};


//Ÿ�� �����϶� �󸶳� �����ϰǰ�
enum MOVENUM
{
	ONE,
	TEN,
	HUNDRED
};
//������ ����
enum MOVEDIRECTION
{
	DIRECTION_UP,
	DIRECTION_LEFT,
	DIRECTION_DOWN,
	DIRECTION_RIGHT
};
enum ATTRIBUTE_ID
{
	ATTR_NORMAL,
	ATTR_UNMOVE,
	ATTR_FALL,
	ATTR_NONE
};

//Ÿ�� ���� ���� ����ü

struct tagTile
{
	dImage*		objImage[OBJLEVEL];
	TERRAIN		terrain;
	OBJECT		obj;
	RECT		rc;
	int			attrID;
	int			tileObjZOrder[OBJLEVEL];
	int			terrainImageIndex;
	int			objImageIndex[OBJLEVEL];
	int			terrainFrameX;
	int			terrainFrameY;
	int			objFrameX[OBJLEVEL];
	int			objFrameY[OBJLEVEL];
};

//Ÿ�ϼ� ���� ���� ����ü
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};

//���� ����� �о�� �ε���
struct tagDungeonTileIndex
{
	int startX, lastX;
	int startY, lastY;
};

class TileClass : public gameNode
{
private:
	vector<pair<int, int>> _vWidthDungeonStartPoint;
	vector<pair<int, int>> _vLengthDungeonStartPoint;
	dImage* _tileImage[IMAGENUM];
	tagSampleTile _sampleTile[SAMPLETILEX][SAMPLETILEY];
	tagTile _tiles[TILEX][TILEY];
	tagTile _tmpTile[TILEX][TILEY];
	RECT _tileRc[RENDERTILEX][RENDERTILEY];
	RECT _btnRc[6];
	RECT _objType[4];
	RECT _selectMap[IMAGENUM];
	RECT _selectAttrType[4];
	RECT _allMapRc;
	RECT _allSampleRc;
	RECT _objLevelRc[OBJLEVEL];
	tagDungeonTileIndex _dungeonShape[WIDTHDUNGEONNUM];
	tagDungeonTileIndex _dungeonShape2[LENGTHDUNGEONNUM];
	tagDungeonTileIndex _dungeonShape3;
	RECT _objModeRc[2];
	RECT _objAllErase;
	MOVENUM _moveNum;
	OBJECT _obj;
	pair<int, int> _pairBossDungeonStartPoint;
	bool _objMode;
	const char* _fileName;
	int _selectMapIndex;
	int _objLevel;
	int _attrType;
	int _ctrSelect;
	int _startX;
	int _startY;
	int _mouseX;
	int _mouseY;
	int _selectIndexX[2];
	int _selectIndexY[2];
public:
	virtual HRESULT init(const char* fileName);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void setup();
	virtual void setMap();

	virtual void save(const char * name);
	virtual void load(const char * name);

	void setRandomDungeon(const char* name);
	void setBossDungeon(const char* name);
	void setCtrlSelect(int num) { _ctrSelect = num; }
	void setTileImage(int tileIndexX, int tileIndexY, int imageIndexX, int imageIndexY, int ZOrder);
	void moveTileCamera(int direction);
	void setAllTileBlack();
	void eraseAllObj();
	
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objSelect(int frameX, int frameY);
};

