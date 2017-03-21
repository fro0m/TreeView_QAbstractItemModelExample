#include "treemodel.h"
#include <QDebug>
int Item::counter = -1;

TreeModel::TreeModel()
    : QAbstractItemModel()
{
    rootItem.setParent(&rootItem);
    auto item = rootItem.addChild();
    item->addChild();
    item = item->addChild();
    item = item->addChild();
    rootItem.addChild();
    rootItem.addChild();
    rootItem.addChild();
    rootItem.addChild();
    rootItem.addChild();
    rootItem.addChild();
    rootItem.addChild();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const {
    if (parent.isValid()) {
        Item * item =  static_cast<Item *>(parent.internalPointer())->childAt(row);
        return createIndex(row, 0, item);
    }
    Item * item = rootItem.childAt(row);
    return createIndex(row, 0, item);
}


int TreeModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 1;
}
int TreeModel::rowCount(const QModelIndex &parent) const
{
    Item * parentPtr;
    if (parent.isValid()) {
        parentPtr = static_cast<Item *>(parent.internalPointer());
    } else {
        parentPtr = const_cast<Item *>(&rootItem);
    }
    return parentPtr->numberOfChildren();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const {
    if (!index.isValid()) {
        return QModelIndex();
    }
    Item * item = static_cast<Item *>(index.internalPointer());
    if (item == &rootItem)
        return QModelIndex();
    Item * parent = item->getParent();
    if (parent == &rootItem) {
        return QModelIndex();
    }
    int row = parent->row();
    QModelIndex parentIndex = createIndex(row, 0, parent);
    return parentIndex;
}

void TreeModel::moveRow(const QModelIndex &sourceIndex, const QModelIndex &targetIndex)
{
    qDebug(Q_FUNC_INFO);
    QModelIndex sourceParentIndex = sourceIndex.parent();
    QModelIndex targetParentIndex = targetIndex.parent();
    int sourceRow = sourceIndex.row();
    int targetRow = targetIndex.row();
    int count = 1;
    //we do not check if sourceitem is offespring of targetitem
    Item * sourceItemPtr = static_cast<Item *>(sourceIndex.internalPointer());
    Item * targetItemPtr = static_cast<Item *>(targetIndex.internalPointer());
    Item * targetParentPtr = targetItemPtr->getParent();
    Item * sourceParentPtr = sourceItemPtr->getParent();

    if (sourceParentIndex == targetParentIndex) {
        if (sourceRow == targetRow) {
            return;
        }
        if (sourceRow < targetRow) {
            beginMoveRows(sourceParentIndex, sourceRow, sourceRow + count - 1, targetParentIndex, targetRow + count);
            Item *movedItem = sourceParentPtr->getChildren().takeAt(sourceRow);
            targetParentPtr->getChildren().insert(targetRow, movedItem);
        } else {
            beginMoveRows(sourceParentIndex, sourceRow, sourceRow + count - 1, targetParentIndex, targetRow);
            qDebug() << sourceParentPtr->getChildren().size();
            Item * movedItem = sourceParentPtr->getChildren().takeAt(sourceRow);
            targetParentPtr->getChildren().insert(targetRow, movedItem);
        }
    } else {
        beginMoveRows(sourceParentIndex, sourceRow, sourceRow + count - 1, targetParentIndex, targetRow + 1);
        targetParentPtr->getChildren().insert(targetRow + 1, sourceParentPtr->getChildren().takeAt(sourceRow));
    }
    endMoveRows();
}

QVariant TreeModel::data(const QModelIndex &index, int /*role*/) const {
    Item * item = static_cast<Item *>(index.internalPointer());
    return QVariant(QString("%1 , index: r:%3 ptr:0x%4").arg(item->getText()).arg(index.row()).arg((quintptr)index.internalPointer(), QT_POINTER_SIZE * 2, 16, QChar('0')));
}

Item *Item::getParent() const
{
    return parent;
}

void Item::setParent(Item *value)
{
    parent = value;
}

QList<Item *> &Item::getChildren()
{
    return children;
}



