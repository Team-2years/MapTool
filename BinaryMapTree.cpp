#include "stdafx.h"
#include "BinaryMapTree.h"
#include "TileClass.h"

BinaryMapTree::BinaryMapTree() :
	_maxWidth(TILESIZEX), _level(0), _maxIndexX(TILEX), _maxIndexY(TILEX)
{
}

BinaryMapTree::~BinaryMapTree()
{
}

void BinaryMapTree::createMap()
{
	if (_level == 1)
		return;

	int tmpX = RND->getFromIntTo(_maxIndexX * 0.4, _maxIndexX * 0.6);
	int tmpY = RND->getFromIntTo(_maxIndexY * 0.4, _maxIndexY * 0.6);
	int tmp = RND->getInt(DUNGEONNUM);
	_leftTree = new BinaryMapTree;
	_leftTree->setTileAddress(_tile);
	_leftTree->setLevel(_level + 1);
	_leftTree->setParentTree(this);
	if (_level % 2 == 0)
	{	
		_leftTree->setIndexX(0);
		_leftTree->setMaxIndexX(tmpX);
	}
	else
	{
		_leftTree->setIndexY(0);
		_leftTree->setMaxIndexY(tmpY);
		
	}
	_leftTree->createMap();

	_rightTree = new BinaryMapTree;
	_rightTree->setTileAddress(_tile);
	_rightTree->setLevel(_level + 1);
	_rightTree->setParentTree(this);
	if (_level % 2 == 0)
	{
		_rightTree->setIndexX(_maxIndexX - tmpX);
		_rightTree->setMaxIndexX(_maxIndexX);
	}
	else
	{
		_rightTree->setIndexY(tmpY);
		_rightTree->setMaxIndexY(_maxIndexY - tmpY);
	}
	_rightTree->createMap();
}

void BinaryMapTree::deleteAllTree()
{
	if (_leftTree == nullptr && _rightTree == nullptr)
		return;
	
	_leftTree->deleteAllTree();
	_rightTree->deleteAllTree();
	SAFE_DELETE(_leftTree);
	SAFE_DELETE(_rightTree);
}
