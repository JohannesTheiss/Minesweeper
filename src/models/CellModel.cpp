#include "../../inc/models/CellModel.h"

namespace models
{

CellModel::CellModel()
    : mHidden(true),
      mFlagged(false),
      mIsBomb(false),
      mSurroundingBombs(0)
{
}

bool CellModel::hidden()
{
    return mHidden;
}

bool CellModel::flagged()
{
    return mFlagged;
}

bool CellModel::isBomb()
{
    return mIsBomb;
}

unsigned int CellModel::surroundingBombs()
{
    return mSurroundingBombs;
}

void CellModel::setHidden(const bool hidden)
{
    mHidden = hidden;
    emit hiddenChanged();
}

void CellModel::setFlagged(const bool flagged)
{
    mFlagged = flagged;
    emit flaggedChanged();
}

void CellModel::setIsBomb(const bool isBomb)
{
    mIsBomb = isBomb;
    emit isBombChanged();
}

void CellModel::setSurroundingBombs(const unsigned int surroundingBombs)
{
    mSurroundingBombs = surroundingBombs;
    emit surroundingBombsChanged();
}

} // namespace models
