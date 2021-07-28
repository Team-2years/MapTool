#pragma once

struct MAP_STAT
{
	int indexX, indexY;
};

class TileClass;
class BinaryMapTree
{
private:
	TileClass* _tile;
	BinaryMapTree* _leftTree;
	BinaryMapTree* _rightTree;
	BinaryMapTree* _parentTree;
	MAP_STAT _mapStat;
	float _maxWidth;
	int _maxIndexX, _maxIndexY;
	int _level;
public:
	BinaryMapTree();
	~BinaryMapTree();
	void createMap();
	void setLevel(int level) { _level = level; }
	void setMaxWidth(float maxWidth) { _maxWidth = maxWidth; }
	void setParentTree(BinaryMapTree* ptr) { _parentTree = ptr; }
	void setMaxIndexX(int index) { _maxIndexX = index; }
	void setMaxIndexY(int index) { _maxIndexY = index; }
	void setIndexX(int index) { _mapStat.indexX = index; }
	void setIndexY(int index) { _mapStat.indexY = index; }
	int getMaxIndexX() { return _maxIndexX; }
	int getMaxIndexY() { return _maxIndexY; }
	BinaryMapTree* getLeftTree() { return _leftTree; }
	BinaryMapTree* getRightTree() { return _rightTree; }
	BinaryMapTree* getParentTree() { return _parentTree; }
	void setTileAddress(TileClass* tile) { _tile = tile; }
	void deleteAllTree();
};

