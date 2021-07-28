#include "stdafx.h"
#include "TileClass.h"
HRESULT TileClass::init(const char* fileName)
{
	_tileImage[0] = IMAGEMANAGER->findDImage("MapAir");
	_tileImage[1] = IMAGEMANAGER->findDImage("MapCastleBase");
	_tileImage[2] = IMAGEMANAGER->findDImage("MapCastle");
	_tileImage[3] = IMAGEMANAGER->findDImage("MapCourtyard");
	_tileImage[4] = IMAGEMANAGER->findDImage("MapEarth");
	_tileImage[5] = IMAGEMANAGER->findDImage("MapFire");
	_tileImage[6] = IMAGEMANAGER->findDImage("MapHome");
	_tileImage[7] = IMAGEMANAGER->findDImage("MapIce");
	_tileImage[8] = IMAGEMANAGER->findDImage("MapLightning");
	_tileImage[9] = IMAGEMANAGER->findDImage("MapMuseum");
	_tileImage[10] = IMAGEMANAGER->findDImage("MapPlaza");
	_tileImage[11] = IMAGEMANAGER->findDImage("MapBlack");
	_tileImage[12] = IMAGEMANAGER->findDImage("Obj1");
	_tileImage[13] = IMAGEMANAGER->findDImage("Obj2");
	_tileImage[14] = IMAGEMANAGER->findDImage("ObjStore");
	_tileImage[15] = IMAGEMANAGER->findDImage("ObjWood");
	_tileImage[16] = IMAGEMANAGER->findDImage("MapPrison");
	_tileImage[17] = IMAGEMANAGER->findDImage("ObjIce1");
	_tileImage[18] = IMAGEMANAGER->findDImage("ObjIce2");
	_tileImage[19] = IMAGEMANAGER->findDImage("ObjTrees");
	_tileImage[20] = IMAGEMANAGER->findDImage("ObjStatue");

	_fileName = fileName;
	setup();
	for (int i = 0; i < 2; ++i)
	{
		_selectIndexX[i] = 0;
		_selectIndexY[i] = 0;
	}
	load(_fileName);
	return S_OK;
}

void TileClass::release()
{

}

void TileClass::update()
{
	setMap();
}

void TileClass::render()
{
	_tileImage[_selectMapIndex]->render(ORIGINWINSIZEX - _tileImage[_selectMapIndex]->getWidth(),0);
	//지형 그리기
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < TILEX; ++i)
		{
			for (int j = 0; j < TILEY; ++j)
			{
				_tileImage[_tiles[i][j].terrainImageIndex]->frameRender(ORIGINWINSIZEX - MINITILESIZE * TILEX + i * MINITILESIZE,
					520 + j * MINITILESIZE,
					_tiles[i][j].terrainFrameX,
					_tiles[i][j].terrainFrameY,
					MINITILESIZE, MINITILESIZE);

				if (_tiles[i][j].obj == OBJ_NONE) continue;
				for (int k = 0; k < OBJLEVEL; ++k)
				{
					if (_tiles[i][j].objImage[k] == nullptr) continue;

					_tiles[i][j].objImage[k]->frameRender(ORIGINWINSIZEX - MINITILESIZE * TILEX + i * MINITILESIZE,
						520 + j * MINITILESIZE,
						_tiles[i][j].objFrameX[k],
						_tiles[i][j].objFrameY[k],
						MINITILESIZE, MINITILESIZE);
				}
			}
		}
	}
	for (int i = 0; i < RENDERTILEX; ++i)
	{
		for (int j = 0; j < RENDERTILEY; ++j)
		{
			_tileImage[_tiles[_startX + i][_startY + j].terrainImageIndex]->frameRender(i * TILESIZE, j * TILESIZE,
				_tiles[_startX + i][_startY + j].terrainFrameX,
				_tiles[_startX + i][_startY + j].terrainFrameY,
				TILESIZE, TILESIZE);
			/*switch (_tiles[_startX + i][_startY + j].attrID)
			{
			case 0:
				DTDMANAGER->printText(L"1", i * TILESIZE, j * TILESIZE, TILESIZE, TILESIZE);
				break;
			case 1:
				DTDMANAGER->printText(L"2", i * TILESIZE, j * TILESIZE, TILESIZE, TILESIZE);
				break;
			case 2:
				DTDMANAGER->printText(L"3", i * TILESIZE, j * TILESIZE, TILESIZE, TILESIZE);
				break;
			case 3:
				DTDMANAGER->printText(L"4", i * TILESIZE, j * TILESIZE, TILESIZE, TILESIZE);
				break;
			default:
				break;
			}*/
			if (_tiles[_startX + i][_startY + j].obj == OBJ_NONE) continue;
			for (int k = 0; k < OBJLEVEL; ++k)
			{
				if (_tiles[_startX + i][_startY + j].objImage[k] == nullptr) continue;

				RENDERMANAGER->push_BackFrameRenderInfo(
					_tiles[_startX + i][_startY + j].tileObjZOrder[k],
					_tiles[_startX + i][_startY + j].objImage[k],
					i * TILESIZE, j * TILESIZE,
					_tiles[_startX + i][_startY + j].objFrameX[k],
					_tiles[_startX + i][_startY + j].objFrameY[k],
					TILESIZE, TILESIZE);
			}
		}
	}
	RECT rc = RectMake(ORIGINWINSIZEX - (MINITILESIZE * TILEX) + (MINITILESIZE * _startX),
		520 + (MINITILESIZE * _startY),
		MINITILESIZE * RENDERTILEX,
		MINITILESIZE * RENDERTILEY);
	DTDMANAGER->Rectangle(rc);
	for (int i = 0; i < 6; ++i)
	{
		DTDMANAGER->Rectangle(_btnRc[i]);
	}
	for (int i = 0; i < 4; ++i)
	{
		DTDMANAGER->Rectangle(_objType[i]);
	}
	for (int i = 0; i < IMAGENUM; ++i)
	{
		DTDMANAGER->Rectangle(_selectMap[i]);
	}
	for (int i = 0; i < 4; ++i)
	{
		DTDMANAGER->Rectangle(_selectAttrType[i]);
	}
	DTDMANAGER->printText(L"Save", 810, 545, 100, 100);
	DTDMANAGER->printText(L"Load", 910, 545, 100, 100);
	DTDMANAGER->printText(L"Rnd", 1010, 545, 100, 100);
	DTDMANAGER->printText(L"Terrain", 805,585, 100, 100);
	DTDMANAGER->printText(L"Object", 910, 585, 100, 100);
	DTDMANAGER->printText(L"Erase", 1010, 585, 100, 100);
	DTDMANAGER->printText(L"Normal", 785, 635, 120, 100);
	DTDMANAGER->printText(L"Unmove", 925, 635, 120, 100);
	DTDMANAGER->printText(L"Fall", 1065, 635, 120, 100);
	DTDMANAGER->printText(L"None", 1205, 635, 120, 100);
	DTDMANAGER->printText(L"True", 1050, 680, 80, 40);
	DTDMANAGER->printText(L"False", 1060, 720, 80, 40);
	DTDMANAGER->printText(L"1", 820, 50, 80, 30);
	DTDMANAGER->printText(L"2", 820, 80, 80, 30);
	DTDMANAGER->printText(L"3", 820, 110, 80, 30);
	rc = RectMake(_sampleTile[_selectIndexX[0]][_selectIndexY[0]].rcTile.left,
		_sampleTile[_selectIndexX[0]][_selectIndexY[0]].rcTile.top,
		(_selectIndexX[1] + 1 - _selectIndexX[0])*SAMPLETILESIZE,
		(_selectIndexY[1] + 1 - _selectIndexY[0])*SAMPLETILESIZE);
	DTDMANAGER->Rectangle(rc);
	if (PtInRect(&_allMapRc, _ptMouse))
	{
		int tmpX = (_selectIndexX[1] - _selectIndexX[0]) * 0.5f;
		int tmpY = (_selectIndexY[1] - _selectIndexY[0]) * 0.5f;

		if (_mouseX - tmpX >= 0 &&
			_mouseY - tmpY >= 0 &&
			_mouseX - tmpX < TILEX &&
			_mouseY - tmpY < TILEY)
		{
			rc = RectMake(
				_tileRc[_mouseX - tmpX][_mouseY - tmpY].left,
				_tileRc[_mouseX - tmpX][_mouseY - tmpY].top,
				TILESIZE + TILESIZE * (_selectIndexX[1] - _selectIndexX[0]),
				TILESIZE + TILESIZE * (_selectIndexY[1] - _selectIndexY[0]));
		}
	}
	for (int i = 0; i < OBJLEVEL; ++i)
	{
		DTDMANAGER->Rectangle(_objLevelRc[i]);
	}
	for (int i = 0; i < 2; ++i)
	{
		DTDMANAGER->Rectangle(_objModeRc[i]);
	}
	DTDMANAGER->Rectangle(_objAllErase);
	DTDMANAGER->printText(L"jar", 895, 695, 130, 100);
	DTDMANAGER->printText(L"frame", 895, 745, 130, 100);
	DTDMANAGER->printText(L"tree", 895, 795, 130, 100);
	DTDMANAGER->printText(L"rug", 895, 845, 130, 100);
	DTDMANAGER->Rectangle(rc);
}

void TileClass::setup()
{
	_btnRc[0] = RectMake(750, 500, 100, 30);
	_btnRc[1] = RectMake(850, 500, 100, 30);
	_btnRc[2] = RectMake(950, 500, 100, 30);
	_btnRc[3] = RectMake(750, 540, 100, 30);
	_btnRc[4] = RectMake(850, 540, 100, 30);
	_btnRc[5] = RectMake(950, 540, 100, 30);
	_selectAttrType[0] = RectMake(710, 590, 140, 30);
	_selectAttrType[1] = RectMake(850, 590, 140, 30);
	_selectAttrType[2] = RectMake(990, 590, 140, 30);
	_selectAttrType[3] = RectMake(1130, 590, 140, 30);
	_objType[0] = RectMake(800,650, 150 , 50);
	_objType[1] = RectMake(800,700, 150 , 50);
	_objType[2] = RectMake(800,750, 150 , 50);
	_objType[3] = RectMake(800,800, 150 , 50);
	_objModeRc[0] = RectMake(1000, 650, 80, 40);
	_objModeRc[1] = RectMake(1000, 690, 80, 40);
	_objAllErase = RectMake(710, 800, 70, 70);
	for (int i = 0; i < 3; ++i)
	{
		_objLevelRc[i] = RectMake(750, 40 + i * 30, 80, 30);
	}
	for (int i = 0; i < 12; ++i)
	{
		_selectMap[i] = RectMake(850, 40 + i * 30, 80, 30);
	}
	for (int i = 12; i < IMAGENUM; ++i)
	{
		_selectMap[i] = RectMake(930, 40 + (i-12) * 30, 80, 30);
	}
	_attrType = ATTR_NORMAL;
	_moveNum = ONE;
	_startX = 0;
	_startY = 0;
	_mouseX = _ptMouse.x / TILESIZE;
	_mouseY = _ptMouse.y / TILESIZE;
	_allMapRc = RectMake(0, 0, RENDERTILEX * TILESIZE, RENDERTILEY * TILESIZE);
	_allSampleRc = RectMake(ORIGINWINSIZEX - SAMPLETILESIZE * SAMPLETILEX, 0, SAMPLETILESIZE*SAMPLETILEX, SAMPLETILESIZE*SAMPLETILEY);
	_selectMapIndex = 0;
	//처음 컨트롤 상태는 지형으로
	_ctrSelect = CTRL_TERRAINDRAW;
	_objMode = false;
	//타일셋 먼저 세팅
	for (int i = 0; i < SAMPLETILEY; ++i)
	{
		for (int j = 0; j < SAMPLETILEX; ++j)
		{
			_sampleTile[j][i].terrainFrameX = j;
			_sampleTile[j][i].terrainFrameY = i;

			//타일셋에 렉트를 씌움
			SetRect(&_sampleTile[j][i].rcTile,
				(ORIGINWINSIZEX - _tileImage[_selectMapIndex]->getWidth()) + j * SAMPLETILESIZE,
				i * SAMPLETILESIZE,
				(ORIGINWINSIZEX - _tileImage[_selectMapIndex]->getWidth()) + j * SAMPLETILESIZE + SAMPLETILESIZE,
				i * SAMPLETILESIZE + SAMPLETILESIZE);
		}
	}
	//타일 영역
	for (int i = 0; i < RENDERTILEY; ++i)
	{
		for (int j = 0; j < RENDERTILEX; ++j)
		{
			SetRect(&_tileRc[j][i],
				j *TILESIZE,
				i *TILESIZE,
				j *TILESIZE + TILESIZE,
				i *TILESIZE + TILESIZE);
		}
	}
	for (int i = 0; i < TILEX; ++i)
	{
		for (int j = 0; j < TILEY; ++j)
		{
			_tiles[i][j].terrainImageIndex = 11;
			_tiles[i][j].terrainFrameX = 0;
			_tiles[i][j].terrainFrameY = 0;
			for (int k = 0; k < OBJLEVEL; ++k)
			{
				_tiles[i][j].objImage[k] = nullptr;
				_tiles[i][j].objImageIndex[k] = 100;
				_tiles[i][j].objFrameX[k] = 0;
				_tiles[i][j].objFrameY[k] = 0;
			}
			_tiles[i][j].attrID = ATTR_NORMAL;
			_tiles[i][j].rc = RectMake(i * TILESIZE, j*TILESIZE, TILESIZE, TILESIZE);
			_tiles[i][j].terrain = terrainSelect(_tiles[i][j].terrainFrameX, _tiles[i][j].terrainFrameY);
			_tiles[i][j].obj = OBJ_NONE;
		}
	}
}

void TileClass::setMap()
{
	if (PtInRect(&_allMapRc, _ptMouse))
	{
		_mouseX = _ptMouse.x / TILESIZE;
		_mouseY = _ptMouse.y / TILESIZE;
	}
	if (PtInRect(&_allSampleRc, _ptMouse))
	{
		_mouseX = (_ptMouse.x -(ORIGINWINSIZEX - SAMPLETILESIZE*SAMPLETILEX)) / SAMPLETILESIZE;
		_mouseY = _ptMouse.y / SAMPLETILESIZE;
	}
	//타일셋에 내가 그리고싶은 타일 또는 오브젝트 클릭
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_allSampleRc, _ptMouse))
		{
			_selectIndexX[0] = _mouseX;
			_selectIndexY[0] = _mouseY;
		}
		for (int i = 0; i < 6; ++i)
		{
			if (PtInRect(&_btnRc[i], _ptMouse))
			{
				switch (i)
				{
				case 0:
					save(_fileName);
					break;
				case 1:
					load(_fileName);
					break;
				case 2:
					//setAllTileBlack();
					setRandomDungeon("tile_Ice.map");
					//setBossDungeon("tile_Ice.map");
					break;
				case 3:
					_ctrSelect = CTRL_TERRAINDRAW;
					break;
				case 4:
					_ctrSelect = CTRL_OBJDRAW;
					break;
				case 5:
					_ctrSelect = CTRL_ERASER;
					break;
				default:
					break;
				}
			}
		}
		for (int i = 0; i < 4; i++)
		{
			if (PtInRect(&_objType[i], _ptMouse))
			{
				switch (i)
				{
				case 0:
					_obj = OBJ_JAR;
					break;
				case 1:
					_obj = OBJ_FRAME;
					break;
				case 2:
					_obj = OBJ_TREE;
					break;
				case 3:
					_obj = OBJ_RUG;
					break;
				default:
					break;
				}
			}
		}
		for (int i = 0; i < IMAGENUM; i++)
		{
			if (PtInRect(&_selectMap[i], _ptMouse))
			{
				_selectMapIndex = i;
			}
		}
		for (int i = 0; i < 4; i++)
		{
			if (PtInRect(&_selectAttrType[i], _ptMouse))
			{
				_attrType = i;
			}
		}
		for (int i = 0; i < OBJLEVEL; ++i)
		{
			if (PtInRect(&_objLevelRc[i], _ptMouse))
			{
				_objLevel = i;
			}
		}
		if (PtInRect(&_objModeRc[0], _ptMouse))
		{
			_objMode = true;
		}
		if (PtInRect(&_objModeRc[1], _ptMouse))
		{
			_objMode = false;
		}
		if (PtInRect(&_objAllErase, _ptMouse))
		{
			eraseAllObj();
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_allMapRc, _ptMouse))
		{
			int tmpX = (_selectIndexX[1] - _selectIndexX[0]) * 0.5f;
			int tmpY = (_selectIndexY[1] - _selectIndexY[0]) * 0.5f;
			for (int i = 0; i <= _selectIndexX[1] - _selectIndexX[0]; ++i)
			{
				for (int j = 0; j <= _selectIndexY[1] - _selectIndexY[0]; ++j)
				{
					if (_startX + _mouseX - tmpX + i >= 0 &&
						_startY + _mouseY - tmpY + j >= 0 &&
						_startX + _mouseX - tmpX + i < TILEX &&
						_startY + _mouseY - tmpY + j < TILEY)
					{
						if (!_objMode)
						{
							setTileImage(
								_startX + _mouseX - tmpX + i,
								_startY + _mouseY - tmpY + j,
								_selectIndexX[0] + i,
								_selectIndexY[0] + j,
								_startY + _mouseY - tmpY + j);
						}
						else
						{
							setTileImage(
								_startX + _mouseX - tmpX + i,
								_startY + _mouseY - tmpY + j,
								_selectIndexX[0] + i,
								_selectIndexY[0] + j,
								_startY + _mouseY - tmpY + _selectIndexY[1] - _selectIndexY[0]);
						}
					}
				}
			}
			//InvalidateRect(_hWnd, NULL, false);
		}
		if (PtInRect(&_allSampleRc, _ptMouse))
		{
			_selectIndexX[1] = _mouseX;
			_selectIndexY[1] = _mouseY;
		}
	}
	
	if (KEYMANAGER->isStayKeyDown(VK_UP) || KEYMANAGER->isStayKeyDown('W'))
	{
		moveTileCamera(0);
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown('A'))
	{
		moveTileCamera(1);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) || KEYMANAGER->isStayKeyDown('S'))
	{
		moveTileCamera(2);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) || KEYMANAGER->isStayKeyDown('D'))
	{
		moveTileCamera(3);
	}
	
}

void TileClass::save(const char * name)
{
	HANDLE file;
	DWORD write;

	file = CreateFile(name, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);
	CloseHandle(file);
}

void TileClass::load(const char * name)
{
	HANDLE file;
	DWORD read;
	file = CreateFile(name, GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	for (int i = 0; i < TILEX; ++i)
	{
		for (int j = 0; j < TILEY; ++j)
		{
			for (int k = 0; k < OBJLEVEL; ++k)
			{
				if(_tiles[i][j].objImageIndex[k] != 100)
					_tiles[i][j].objImage[k] = _tileImage[_tiles[i][j].objImageIndex[k]];
			}
		}
	}
	CloseHandle(file);
}

void TileClass::setRandomDungeon(const char* name)
{
	HANDLE file;
	DWORD read;
	
	file = CreateFile(name, GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tmpTile, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);
	for (int i = 0; i < TILEX; ++i)
	{
		for (int j = 0; j < TILEY; ++j)
		{
			for (int k = 0; k < OBJLEVEL; ++k)
			{
				if (_tmpTile[i][j].objImageIndex[k] != 100)
					_tmpTile[i][j].objImage[k] = _tileImage[_tmpTile[i][j].objImageIndex[k]];
			}
		}
	}
	for (int i = 0; i < TILEX; ++i)
	{
		for (int j = 0; j < TILEY; ++j)
		{
			if (_tiles[i][j].attrID == ATTR_NONE &&
				_tiles[i][j].terrainImageIndex == 14)
			{
				if (_tiles[i][j].terrainFrameX == 0 &&
					_tiles[i][j].terrainFrameY == 0)
				{
					_vWidthDungeonStartPoint.push_back(make_pair(i, j));
				}
				else if (_tiles[i][j].terrainFrameX == 1 &&
					_tiles[i][j].terrainFrameY == 0)
				{
					_vLengthDungeonStartPoint.push_back(make_pair(i, j));
				}
				else if (_tiles[i][j].terrainFrameX == 0 &&
					_tiles[i][j].terrainFrameY == 1)
				{
					_pairBossDungeonStartPoint.first = i;
					_pairBossDungeonStartPoint.second = j;
				}
			}
		}
	}
	for (int i = 0; i < WIDTHDUNGEONNUM; ++i)
	{
		_dungeonShape[i].startX = 22 * i;
		_dungeonShape[i].lastX = _dungeonShape[i].startX + 21;
		_dungeonShape[i].startY = 0;
		_dungeonShape[i].lastY = 9;
	}
	for (int i = 0; i < LENGTHDUNGEONNUM; ++i)
	{
		_dungeonShape2[i].startX = 10 * i;
		_dungeonShape2[i].lastX = _dungeonShape2[i].startX + 9;
		_dungeonShape2[i].startY = 10;
		_dungeonShape2[i].lastY = 31;
	}
	_dungeonShape3.startX = 0;
	_dungeonShape3.lastX = 14;
	_dungeonShape3.startY = 40;
	_dungeonShape3.lastY = 58;
	
	for (int i = 0; i < _vWidthDungeonStartPoint.size(); ++i)
	{
		int tmp = RND->getInt(WIDTHDUNGEONNUM);
		for (int j = 0; j <= _dungeonShape[tmp].lastX - _dungeonShape[tmp].startX; ++j)
		{
			for (int k = 0; k <= _dungeonShape[tmp].lastY - _dungeonShape[tmp].startY; ++k)
			{
				_tiles[_vWidthDungeonStartPoint[i].first + j][_vWidthDungeonStartPoint[i].second + k].attrID = _tmpTile[_dungeonShape[tmp].startX + j][_dungeonShape[tmp].startY + k].attrID;
				_tiles[_vWidthDungeonStartPoint[i].first + j][_vWidthDungeonStartPoint[i].second + k].obj = _tmpTile[_dungeonShape[tmp].startX + j][_dungeonShape[tmp].startY + k].obj;
				_tiles[_vWidthDungeonStartPoint[i].first + j][_vWidthDungeonStartPoint[i].second + k].terrain = _tmpTile[_dungeonShape[tmp].startX + j][_dungeonShape[tmp].startY + k].terrain;
				_tiles[_vWidthDungeonStartPoint[i].first + j][_vWidthDungeonStartPoint[i].second + k].terrainFrameX = _tmpTile[_dungeonShape[tmp].startX + j][_dungeonShape[tmp].startY + k].terrainFrameX;
				_tiles[_vWidthDungeonStartPoint[i].first + j][_vWidthDungeonStartPoint[i].second + k].terrainFrameY = _tmpTile[_dungeonShape[tmp].startX + j][_dungeonShape[tmp].startY + k].terrainFrameY;
				_tiles[_vWidthDungeonStartPoint[i].first + j][_vWidthDungeonStartPoint[i].second + k].terrainImageIndex = _tmpTile[_dungeonShape[tmp].startX + j][_dungeonShape[tmp].startY + k].terrainImageIndex;
				for (int l = 0; l < OBJLEVEL; ++l)
				{
					_tiles[_vWidthDungeonStartPoint[i].first + j][_vWidthDungeonStartPoint[i].second + k].objImage[l] = nullptr;
					_tiles[_vWidthDungeonStartPoint[i].first + j][_vWidthDungeonStartPoint[i].second + k].objImageIndex[l] = 100;
					_tiles[_vWidthDungeonStartPoint[i].first + j][_vWidthDungeonStartPoint[i].second + k].objFrameX[l] = 0;
					_tiles[_vWidthDungeonStartPoint[i].first + j][_vWidthDungeonStartPoint[i].second + k].objFrameY[l] = 0;
					if (_tmpTile[_dungeonShape[tmp].startX + j][_dungeonShape[tmp].startY + k].objImage[l] == nullptr) continue;

					if (_tmpTile[_dungeonShape[tmp].startX + j][_dungeonShape[tmp].startY + k].tileObjZOrder[l] != 0)
						_tiles[_vWidthDungeonStartPoint[i].first + j][_vWidthDungeonStartPoint[i].second + k].tileObjZOrder[l] = _tmpTile[_dungeonShape[tmp].startX + j][_dungeonShape[tmp].startY + k].tileObjZOrder[l] + (_vWidthDungeonStartPoint[i].second - _dungeonShape[tmp].startY);
					else
						_tiles[_vWidthDungeonStartPoint[i].first + j][_vWidthDungeonStartPoint[i].second + k].tileObjZOrder[l] = _tmpTile[_dungeonShape[tmp].startX + j][_dungeonShape[tmp].startY + k].tileObjZOrder[l];

					_tiles[_vWidthDungeonStartPoint[i].first + j][_vWidthDungeonStartPoint[i].second + k].objImage[l] = _tmpTile[_dungeonShape[tmp].startX + j][_dungeonShape[tmp].startY + k].objImage[l];
					_tiles[_vWidthDungeonStartPoint[i].first + j][_vWidthDungeonStartPoint[i].second + k].objFrameX[l] = _tmpTile[_dungeonShape[tmp].startX + j][_dungeonShape[tmp].startY + k].objFrameX[l];
					_tiles[_vWidthDungeonStartPoint[i].first + j][_vWidthDungeonStartPoint[i].second + k].objFrameY[l] = _tmpTile[_dungeonShape[tmp].startX + j][_dungeonShape[tmp].startY + k].objFrameY[l];
					_tiles[_vWidthDungeonStartPoint[i].first + j][_vWidthDungeonStartPoint[i].second + k].objImageIndex[l] = _tmpTile[_dungeonShape[tmp].startX + j][_dungeonShape[tmp].startY + k].objImageIndex[l];
				}
			}
		}
	}
	for (int i = 0; i < _vLengthDungeonStartPoint.size(); ++i)
	{
		int tmp = RND->getInt(LENGTHDUNGEONNUM);

		for (int j = 0; j <= _dungeonShape2[tmp].lastX - _dungeonShape2[tmp].startX; ++j)
		{
			for (int k = 0; k <= _dungeonShape2[tmp].lastY - _dungeonShape2[tmp].startY; ++k)
			{
				_tiles[_vLengthDungeonStartPoint[i].first + j][_vLengthDungeonStartPoint[i].second + k].attrID = _tmpTile[_dungeonShape2[tmp].startX + j][_dungeonShape2[tmp].startY + k].attrID;
				_tiles[_vLengthDungeonStartPoint[i].first + j][_vLengthDungeonStartPoint[i].second + k].obj = _tmpTile[_dungeonShape2[tmp].startX + j][_dungeonShape2[tmp].startY + k].obj;
				_tiles[_vLengthDungeonStartPoint[i].first + j][_vLengthDungeonStartPoint[i].second + k].terrain = _tmpTile[_dungeonShape2[tmp].startX + j][_dungeonShape2[tmp].startY + k].terrain;
				_tiles[_vLengthDungeonStartPoint[i].first + j][_vLengthDungeonStartPoint[i].second + k].terrainFrameX = _tmpTile[_dungeonShape2[tmp].startX + j][_dungeonShape2[tmp].startY + k].terrainFrameX;
				_tiles[_vLengthDungeonStartPoint[i].first + j][_vLengthDungeonStartPoint[i].second + k].terrainFrameY = _tmpTile[_dungeonShape2[tmp].startX + j][_dungeonShape2[tmp].startY + k].terrainFrameY;
				_tiles[_vLengthDungeonStartPoint[i].first + j][_vLengthDungeonStartPoint[i].second + k].terrainImageIndex = _tmpTile[_dungeonShape2[tmp].startX + j][_dungeonShape2[tmp].startY + k].terrainImageIndex;
				for (int l = 0; l < OBJLEVEL; ++l)
				{
					_tiles[_vLengthDungeonStartPoint[i].first + j][_vLengthDungeonStartPoint[i].second + k].objImage[l] = nullptr;
					_tiles[_vLengthDungeonStartPoint[i].first + j][_vLengthDungeonStartPoint[i].second + k].objImageIndex[l] = 100;
					_tiles[_vLengthDungeonStartPoint[i].first + j][_vLengthDungeonStartPoint[i].second + k].objFrameX[l] = 0;
					_tiles[_vLengthDungeonStartPoint[i].first + j][_vLengthDungeonStartPoint[i].second + k].objFrameY[l] = 0;
					if (_tmpTile[_dungeonShape2[tmp].startX + j][_dungeonShape2[tmp].startY + k].objImage[l] == nullptr) continue;

					if (_tmpTile[_dungeonShape2[tmp].startX + j][_dungeonShape2[tmp].startY + k].tileObjZOrder[l] != 0)
						_tiles[_vLengthDungeonStartPoint[i].first + j][_vLengthDungeonStartPoint[i].second + k].tileObjZOrder[l] = _tmpTile[_dungeonShape2[tmp].startX + j][_dungeonShape2[tmp].startY + k].tileObjZOrder[l] + (_vLengthDungeonStartPoint[i].second - _dungeonShape[tmp].startY);
					else
						_tiles[_vLengthDungeonStartPoint[i].first + j][_vLengthDungeonStartPoint[i].second + k].tileObjZOrder[l] = _tmpTile[_dungeonShape2[tmp].startX + j][_dungeonShape2[tmp].startY + k].tileObjZOrder[l];
					_tiles[_vLengthDungeonStartPoint[i].first + j][_vLengthDungeonStartPoint[i].second + k].objImage[l] = _tmpTile[_dungeonShape2[tmp].startX + j][_dungeonShape2[tmp].startY + k].objImage[l];
					_tiles[_vLengthDungeonStartPoint[i].first + j][_vLengthDungeonStartPoint[i].second + k].objFrameX[l] = _tmpTile[_dungeonShape2[tmp].startX + j][_dungeonShape2[tmp].startY + k].objFrameX[l];
					_tiles[_vLengthDungeonStartPoint[i].first + j][_vLengthDungeonStartPoint[i].second + k].objFrameY[l] = _tmpTile[_dungeonShape2[tmp].startX + j][_dungeonShape2[tmp].startY + k].objFrameY[l];
					_tiles[_vLengthDungeonStartPoint[i].first + j][_vLengthDungeonStartPoint[i].second + k].objImageIndex[l] = _tmpTile[_dungeonShape2[tmp].startX + j][_dungeonShape2[tmp].startY + k].objImageIndex[l];
				}
			}
		}
	}
	for (int i = 0; i <= _dungeonShape3.lastX - _dungeonShape3.startX; ++i)
	{
		for (int j = 0; j <= _dungeonShape3.lastY - _dungeonShape3.startY; ++j)
		{
			_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].attrID = _tmpTile[_dungeonShape3.startX + i][_dungeonShape3.startY + j].attrID;
			_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].obj = _tmpTile[_dungeonShape3.startX + i][_dungeonShape3.startY + j].obj;
			_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].terrain = _tmpTile[_dungeonShape3.startX + i][_dungeonShape3.startY + j].terrain;
			_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].terrainFrameX = _tmpTile[_dungeonShape3.startX + i][_dungeonShape3.startY + j].terrainFrameX;
			_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].terrainFrameY = _tmpTile[_dungeonShape3.startX + i][_dungeonShape3.startY + j].terrainFrameY;
			_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].terrainImageIndex = _tmpTile[_dungeonShape3.startX + i][_dungeonShape3.startY + j].terrainImageIndex;
			for (int k = 0; k < OBJLEVEL; ++k)
			{
				_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].objImage[k] = nullptr;
				_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].objImageIndex[k] = 100;
				_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].objFrameX[k] = 0;
				_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].objFrameY[k] = 0;
				if (_tmpTile[_dungeonShape3.startX + i][_dungeonShape3.startY + j].objImage[k] == nullptr) continue;

				if (_tmpTile[_dungeonShape3.startX + i][_dungeonShape3.startY + j].tileObjZOrder[k] != 0)
					_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].tileObjZOrder[k] = _tmpTile[_dungeonShape3.startX + i][_dungeonShape3.startY + j].tileObjZOrder[k] + (_pairBossDungeonStartPoint.second - _dungeonShape3.startY);
				else
					_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].tileObjZOrder[k] = _tmpTile[_dungeonShape3.startX + i][_dungeonShape3.startY + j].tileObjZOrder[k];
				_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].objImage[k] = _tmpTile[_dungeonShape3.startX + i][_dungeonShape3.startY + j].objImage[k];
				_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].objFrameX[k] = _tmpTile[_dungeonShape3.startX + i][_dungeonShape3.startY + j].objFrameX[k];
				_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].objFrameY[k] = _tmpTile[_dungeonShape3.startX + i][_dungeonShape3.startY + j].objFrameY[k];
				_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].objImageIndex[k] = _tmpTile[_dungeonShape3.startX + i][_dungeonShape3.startY + j].objImageIndex[k];
			}
		}
	}
	_vWidthDungeonStartPoint.clear();
	_vWidthDungeonStartPoint.resize(0);
	_vLengthDungeonStartPoint.clear();
	_vLengthDungeonStartPoint.resize(0);
}

void TileClass::setBossDungeon(const char * name)
{
	HANDLE file;
	DWORD read;

	file = CreateFile(name, GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tmpTile, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);
	for (int i = 0; i < TILEX; ++i)
	{
		for (int j = 0; j < TILEY; ++j)
		{
			for (int k = 0; k < OBJLEVEL; ++k)
			{
				if (_tmpTile[i][j].objImageIndex[k] != 100)
					_tmpTile[i][j].objImage[k] = _tileImage[_tmpTile[i][j].objImageIndex[k]];
			}
		}
	}

	_dungeonShape3.startX = 38;
	_dungeonShape3.lastX = 69;
	_dungeonShape3.startY = 24;
	_dungeonShape3.lastY = 99;
	for (int i = 0; i < TILEX; ++i)
	{
		for (int j = 0; j < TILEY; ++j)
		{
			if (_tiles[i][j].attrID == ATTR_NONE &&
				_tiles[i][j].terrainImageIndex == 14)
			{
				if (_tiles[i][j].terrainFrameX == 1 &&
					_tiles[i][j].terrainFrameY == 1)
				{
					_pairBossDungeonStartPoint.first = i;
					_pairBossDungeonStartPoint.second = j;
				}
			}
		}
	}
	for (int i = 0; i <= _dungeonShape3.lastX - _dungeonShape3.startX; ++i)
	{
		for (int j = 0; j <= _dungeonShape3.lastY - _dungeonShape3.startY; ++j)
		{
			_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].attrID = _tmpTile[_dungeonShape3.startX + i][_dungeonShape3.startY + j].attrID;
			_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].obj = _tmpTile[_dungeonShape3.startX + i][_dungeonShape3.startY + j].obj;
			_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].terrain = _tmpTile[_dungeonShape3.startX + i][_dungeonShape3.startY + j].terrain;
			_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].terrainFrameX = _tmpTile[_dungeonShape3.startX + i][_dungeonShape3.startY + j].terrainFrameX;
			_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].terrainFrameY = _tmpTile[_dungeonShape3.startX + i][_dungeonShape3.startY + j].terrainFrameY;
			_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].terrainImageIndex = _tmpTile[_dungeonShape3.startX + i][_dungeonShape3.startY + j].terrainImageIndex;
			for (int k = 0; k < OBJLEVEL; ++k)
			{
				_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].objImage[k] = nullptr;
				_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].objImageIndex[k] = 100;
				_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].objFrameX[k] = 0;
				_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].objFrameY[k] = 0;
				if (_tmpTile[_dungeonShape3.startX + i][_dungeonShape3.startY + j].objImage[k] == nullptr) continue;

				if (_tmpTile[_dungeonShape3.startX + i][_dungeonShape3.startY + j].tileObjZOrder[k] != 0)
					_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].tileObjZOrder[k] = _tmpTile[_dungeonShape3.startX + i][_dungeonShape3.startY + j].tileObjZOrder[k] + (_pairBossDungeonStartPoint.second - _dungeonShape3.startY);
				else
					_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].tileObjZOrder[k] = _tmpTile[_dungeonShape3.startX + i][_dungeonShape3.startY + j].tileObjZOrder[k];
				_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].objImage[k] = _tmpTile[_dungeonShape3.startX + i][_dungeonShape3.startY + j].objImage[k];
				_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].objFrameX[k] = _tmpTile[_dungeonShape3.startX + i][_dungeonShape3.startY + j].objFrameX[k];
				_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].objFrameY[k] = _tmpTile[_dungeonShape3.startX + i][_dungeonShape3.startY + j].objFrameY[k];
				_tiles[_pairBossDungeonStartPoint.first + i][_pairBossDungeonStartPoint.second + j].objImageIndex[k] = _tmpTile[_dungeonShape3.startX + i][_dungeonShape3.startY + j].objImageIndex[k];
			}
		}
	}
}

void TileClass::setTileImage(int tileIndexX, int tileIndexY, int imageIndexX, int imageIndexY, int ZOrder)
{
	if (_ctrSelect == CTRL_TERRAINDRAW)
	{
		_tiles[tileIndexX][tileIndexY].terrainImageIndex = _selectMapIndex;
		_tiles[tileIndexX][tileIndexY].terrainFrameX = imageIndexX;
		_tiles[tileIndexX][tileIndexY].terrainFrameY = imageIndexY;
		_tiles[tileIndexX][tileIndexY].attrID = _attrType;
		_tiles[tileIndexX][tileIndexY].terrain = terrainSelect(imageIndexX, imageIndexY);
	}
	else if (_ctrSelect == CTRL_OBJDRAW)
	{
		_tiles[tileIndexX][tileIndexY].objImage[_objLevel] = _tileImage[_selectMapIndex];
		_tiles[tileIndexX][tileIndexY].objImageIndex[_objLevel] = _selectMapIndex;
		_tiles[tileIndexX][tileIndexY].objFrameX[_objLevel] = imageIndexX;
		_tiles[tileIndexX][tileIndexY].objFrameY[_objLevel] = imageIndexY;
		_tiles[tileIndexX][tileIndexY].attrID = _attrType;
		_tiles[tileIndexX][tileIndexY].obj = _obj;
		switch (_objLevel)
		{
		case 0:
			_tiles[tileIndexX][tileIndexY].tileObjZOrder[_objLevel] = 0;
			break;
		default:
			_tiles[tileIndexX][tileIndexY].tileObjZOrder[_objLevel] = ZOrder;
			break;
		}
	}
	else if (_ctrSelect == CTRL_ERASER)
	{
		for (int i = 0; i < OBJLEVEL; ++i)
		{
			_tiles[tileIndexX][tileIndexY].objImage[i] = nullptr;
			_tiles[tileIndexX][tileIndexY].objImageIndex[i] = 100;
			_tiles[tileIndexX][tileIndexY].objFrameX[i] = NULL;
			_tiles[tileIndexX][tileIndexY].objFrameY[i] = NULL;
			_tiles[tileIndexX][tileIndexY].obj = OBJ_NONE;
		}
	}
}

void TileClass::moveTileCamera(int direction)
{
	int tmpNum = 0;
	switch (_moveNum)
	{
	case ONE:
		tmpNum = 1;
		break;
	case TEN:
		tmpNum = 10;
		break;
	case HUNDRED:
		tmpNum = 100;
		break;
	default:
		break;
	}
	switch (direction)
	{
	case DIRECTION_UP:
		_startY -= tmpNum;
		if (_startY < 0)
			_startY = 0;
		break;
	case DIRECTION_LEFT:
		_startX -= tmpNum;
		if (_startX < 0)
			_startX = 0;
		break;
	case DIRECTION_DOWN:
		_startY += tmpNum;
		if (_startY >= TILEY - RENDERTILEY)
			_startY = TILEY - RENDERTILEY;
		break;
	case DIRECTION_RIGHT:
		_startX += tmpNum;
		if (_startX >= TILEX - RENDERTILEX)
			_startX = TILEX - RENDERTILEX;
		break;
	default:
		break;
	}
	
}

void TileClass::setAllTileBlack()
{
	for (int i = 0; i < TILEX; ++i)
	{
		for (int j = 0; j < TILEY; ++j)
		{
			/*_tiles[i][j].terrainImageIndex = 11;
			_tiles[i][j].terrainFrameX = 0;
			_tiles[i][j].terrainFrameY = 0;
			_tiles[i][j].attrID = ATTR_NORMAL;
			_tiles[i][j].terrain = terrainSelect(_tiles[i][j].terrainFrameX, _tiles[i][j].terrainFrameY);
			_tiles[i][j].obj = OBJ_NONE;
			for (int k = 0; k < OBJLEVEL; ++k)
			{
				_tiles[i][j].objImage[k] = nullptr;
				_tiles[i][j].objImageIndex[k] = 100;
				_tiles[i][j].objFrameX[k] = 0;
				_tiles[i][j].objFrameY[k] = 0;
			}*/
			/*if (_tiles[i][j].terrainImageIndex == 7)
			{
				_tiles[i][j].terrainImageIndex = 4;
			}*/
			if (_tiles[i][j].terrainImageIndex == 6 &&
				_tiles[i][j].terrainFrameX > 0 &&
				_tiles[i][j].terrainFrameX < 18 &&
				_tiles[i][j].terrainFrameY <= 4)
			{
				if (_tiles[i][j].objImage[0] == nullptr)
				{
					_tiles[i][j].attrID = 1;
					_tiles[i][j].objImage[0] = _tileImage[_tiles[i][j].terrainImageIndex];
					_tiles[i][j].objImageIndex[0] = _tiles[i][j].terrainImageIndex;
					_tiles[i][j].objFrameX[0] = _tiles[i][j].terrainFrameX;
					_tiles[i][j].objFrameY[0] = _tiles[i][j].terrainFrameY;
					_tiles[i][j].tileObjZOrder[0] = 0;
					_tiles[i][j].obj = OBJ_JAR;
				}
			}
			else if (_tiles[i][j].terrainImageIndex == 6 &&
				_tiles[i][j].terrainFrameX > 0 &&
				_tiles[i][j].terrainFrameX < 4 &&
				_tiles[i][j].terrainFrameY >= 2 &&
				_tiles[i][j].terrainFrameY <= 5)
			{
				if (_tiles[i][j].objImage[0] == nullptr)
				{
					_tiles[i][j].attrID = 1;
					_tiles[i][j].objImage[0] = _tileImage[_tiles[i][j].terrainImageIndex];
					_tiles[i][j].objImageIndex[0] = _tiles[i][j].terrainImageIndex;
					_tiles[i][j].objFrameX[0] = _tiles[i][j].terrainFrameX;
					_tiles[i][j].objFrameY[0] = _tiles[i][j].terrainFrameY;
					_tiles[i][j].tileObjZOrder[0] = 0;
					_tiles[i][j].obj = OBJ_JAR;
				}
			}
			else if (_tiles[i][j].terrainImageIndex == 6 &&
				_tiles[i][j].terrainFrameX > 14 &&
				_tiles[i][j].terrainFrameX < 19 &&
				_tiles[i][j].terrainFrameY >= 2 &&
				_tiles[i][j].terrainFrameY <= 5)
			{
				if (_tiles[i][j].objImage[0] == nullptr)
				{
					_tiles[i][j].attrID = 1;
					_tiles[i][j].objImage[0] = _tileImage[_tiles[i][j].terrainImageIndex];
					_tiles[i][j].objImageIndex[0] = _tiles[i][j].terrainImageIndex;
					_tiles[i][j].objFrameX[0] = _tiles[i][j].terrainFrameX;
					_tiles[i][j].objFrameY[0] = _tiles[i][j].terrainFrameY;
					_tiles[i][j].tileObjZOrder[0] = 0;
					_tiles[i][j].obj = OBJ_JAR;
				}
			}
			else if (_tiles[i][j].terrainImageIndex == 6 &&
				_tiles[i][j].terrainFrameX == 0 &&
				_tiles[i][j].terrainFrameY >= 2 &&
				_tiles[i][j].terrainFrameY <= 9)
			{
				if (_tiles[i][j].objImage[0] == nullptr)
				{
					_tiles[i][j].attrID = 1;
					_tiles[i][j].objImage[0] = _tileImage[_tiles[i][j].terrainImageIndex];
					_tiles[i][j].objImageIndex[0] = _tiles[i][j].terrainImageIndex;
					_tiles[i][j].objFrameX[0] = _tiles[i][j].terrainFrameX;
					_tiles[i][j].objFrameY[0] = _tiles[i][j].terrainFrameY;
					_tiles[i][j].tileObjZOrder[0] = 0;
					_tiles[i][j].obj = OBJ_JAR;
				}
			}
			else if (_tiles[i][j].terrainImageIndex == 6 &&
				_tiles[i][j].terrainFrameX == 18 &&
				_tiles[i][j].terrainFrameY >= 2 &&
				_tiles[i][j].terrainFrameY <= 9)
			{
				if (_tiles[i][j].objImage[0] == nullptr)
				{
					_tiles[i][j].attrID = 1;
					_tiles[i][j].objImage[0] = _tileImage[_tiles[i][j].terrainImageIndex];
					_tiles[i][j].objImageIndex[0] = _tiles[i][j].terrainImageIndex;
					_tiles[i][j].objFrameX[0] = _tiles[i][j].terrainFrameX;
					_tiles[i][j].objFrameY[0] = _tiles[i][j].terrainFrameY;
					_tiles[i][j].tileObjZOrder[0] = 0;
					_tiles[i][j].obj = OBJ_JAR;
				}
			}
			else if (_tiles[i][j].terrainImageIndex == 6 &&
				_tiles[i][j].terrainFrameX > 2 &&
				_tiles[i][j].terrainFrameX < 16 &&
				_tiles[i][j].terrainFrameY == 10)
			{
				if (_tiles[i][j].objImage[0] == nullptr)
				{
					_tiles[i][j].attrID = 1;
					_tiles[i][j].objImage[0] = _tileImage[_tiles[i][j].terrainImageIndex];
					_tiles[i][j].objImageIndex[0] = _tiles[i][j].terrainImageIndex;
					_tiles[i][j].objFrameX[0] = _tiles[i][j].terrainFrameX;
					_tiles[i][j].objFrameY[0] = _tiles[i][j].terrainFrameY;
					_tiles[i][j].tileObjZOrder[0] = 0;
					_tiles[i][j].obj = OBJ_JAR;
				}
			}
		}
	}
}


void TileClass::eraseAllObj()
{
	for (int i = 0; i < TILEX; ++i)
	{
		for (int j = 0; j < TILEY; ++j)
		{
			/*if (_tiles[i][j].terrainImageIndex == 11)
			{
				for (int k = 0; k < OBJLEVEL; ++k)
				{
					_tiles[i][j].objImage[k] = nullptr;
					_tiles[i][j].objImageIndex[k] = 100;
					_tiles[i][j].objFrameX[k] = 0;
					_tiles[i][j].objFrameY[k] = 0;
				}
			}*/
			for (int k = 0; k < OBJLEVEL; ++k)
			{
				_tiles[i][j].objImage[k] = nullptr;
				_tiles[i][j].objImageIndex[k] = 100;
				_tiles[i][j].objFrameX[k] = 0;
				_tiles[i][j].objFrameY[k] = 0;
			}
		}
	}
}

TERRAIN TileClass::terrainSelect(int frameX, int frameY)
{
	if (frameX == 1 && frameY == 0)
	{
		return TR_CEMENT;
	}
	else if (frameX == 2 && frameY == 0)
	{
		return TR_DESERT;
	}
	else if (frameX == 3 && frameY == 0)
	{
		return TR_GRASS;
	}
	else if (frameX == 4 && frameY == 0)
	{
		return TR_WATER;
	}

	return TR_GRASS;
}

OBJECT TileClass::objSelect(int frameX, int frameY)
{
	return OBJ_JAR;
}
