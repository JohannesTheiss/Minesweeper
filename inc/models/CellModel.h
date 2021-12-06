#ifndef CELLMODEL_H
#define CELLMODEL_H

#include <QObject>

namespace models
{

class CellModel : public QObject
{

    Q_OBJECT

    Q_PROPERTY(bool hidden READ hidden NOTIFY hiddenChanged)
    Q_PROPERTY(bool flagged READ flagged NOTIFY flaggedChanged)
    Q_PROPERTY(bool isBomb READ isBomb NOTIFY isBombChanged)
    Q_PROPERTY(quint64 surroundingBombs READ surroundingBombs NOTIFY surroundingBombsChanged)

    public:
        // delete default constructor
        CellModel() = delete;

        // custom constructor
        CellModel(const bool hidden,
                  const bool flagged,
                  const bool isBomb,
                  quint64 surroundingBombs);

        // default destructor
        ~CellModel() = default;

        // property getters
        bool hidden();
        bool flagged();
        bool isBomb();
        quint64 surroundingBombs();

        // property setters
        void setHidden(const bool hidden);
        void setFlagged(const bool flagged);
        void setIsBomb(const bool isBomb);
        void setSurroundingBombs(const quint64 surroundingBombs);

        void increaseSurroundingBombsCount();

    signals:
        void hiddenChanged();
        void flaggedChanged();
        void isBombChanged();
        void surroundingBombsChanged();

    private:

        // properties
        bool mHidden;
        bool mFlagged;
        bool mIsBomb;
        quint64 mSurroundingBombs;

};

} // namespace models
#endif // CELLMODEL_H
