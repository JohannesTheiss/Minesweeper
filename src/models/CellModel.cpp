#include "../../inc/models/CellModel.h"

namespace models
{

// <summary> Custom constructor for CellModel-objects </summary>
// <param name="hidden"> Boolean value that determines if the cell content is hidden </param>
// <param name="flagged"> Boolean value that determines if the cell is flagged </param>
// <param name="isBomb"> Boolean value that determines if the cell is a bomb </param>
// <param name="surroundingBombs"> quint64 number of mines surrounding the cell </param>
CellModel::CellModel(const bool hidden,
                     const bool flagged,
                     const bool isBomb,
                     quint64 surroundingBombs)
    : mHidden(hidden),
      mFlagged(flagged),
      mIsBomb(isBomb),
      mSurroundingBombs(surroundingBombs)
{
}

// <summary> Getter for member mHidden </summary>
// <returns> bool mHidden </returns>
bool CellModel::hidden()
{
    return mHidden;
}

// <summary> Getter for member mFlagged </summary>
// <returns> bool mFlagged </returns>
bool CellModel::flagged()
{
    return mFlagged;
}

// <summary> Getter for member mIsBomb </summary>
// <returns> bool mIsBomb </returns>
bool CellModel::isBomb()
{
    return mIsBomb;
}

// <summary> Getter for member mSurroundingBombs </summary>
// <returns> bool mSurroundingBombs </returns>
quint64 CellModel::surroundingBombs()
{
    return mSurroundingBombs;
}

// <summary> Setter for member mHidden </summary>
// <param name="hidden"> Boolean value for "mHidden" </param>
// <returns> Nothing </returns>
void CellModel::setHidden(const bool hidden)
{
    mHidden = hidden;
    emit hiddenChanged();
}

// <summary> Setter for member mFlagged </summary>
// <param name="flagged"> Boolean value for "mFlagged" </param>
// <returns> Nothing </returns>
void CellModel::setFlagged(const bool flagged)
{
    mFlagged = flagged;
    emit flaggedChanged();
}

// <summary> Setter for member mIsBomb </summary>
// <param name="isBomb"> Boolean value for "mIsBomb" </param>
// <returns> Nothing </returns>
void CellModel::setIsBomb(const bool isBomb)
{
    mIsBomb = isBomb;
    emit isBombChanged();
}

// <summary> Setter for member mSurroundingBombs </summary>
// <param name="surroundingBombs"> quint64 value for "mSurroundingBombs" </param>
// <returns> Nothing </returns>
void CellModel::setSurroundingBombs(const quint64 surroundingBombs)
{
    mSurroundingBombs = surroundingBombs;
    emit surroundingBombsChanged();
}

// <summary> Function that increments the member mSurroundingBombsCount by 1 </summary>
// <returns> Nothing </returns>
void CellModel::increaseSurroundingBombsCount()
{
    mSurroundingBombs++;
    emit surroundingBombsChanged();
}

} // namespace models
