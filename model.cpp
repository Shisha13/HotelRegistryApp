#include "model.h"

using namespace logic;

Model::Model(QObject* parent)
    : QAbstractTableModel(parent)
{

}

Model::Model(QList<Room> rooms, QObject* parent)
    : QAbstractTableModel(parent),
      _rooms(rooms)
{

}

int Model::rowCount(const QModelIndex&) const
{
    return _rooms.count();
}

int Model::columnCount(const QModelIndex&) const
{
    return static_cast<int>(Room::COLUMNS::COUNT);
}

QVariant Model::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }
    if (index.row() >= _rooms.size() || index.row() < 0)
    {
        return QVariant();
    }
    Q_UNUSED(role);
    const auto& room  = _rooms.at(index.row());
    Room::COLUMNS column = static_cast<Room::COLUMNS >(index.column());
    switch (column)
    {
    case  Room::COLUMNS::NUMBER:
        return  room.number;
    case  Room::COLUMNS::PRICE:
        return  room.price;
    case  Room::COLUMNS::LIVING_SPACE:
        return  room.livivngSpace;
    case  Room::COLUMNS::DATE_IN:
        return  room.dateIn;
    case  Room::COLUMNS::DATE_OUT:
        return  room.dateOut;
    case  Room::COLUMNS::PERSONS:
        return  room.number;
    case  Room::COLUMNS::IS_BOOKED:
        return  room.isBooked;
    default:
        return QVariant();
    }
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal)
        {
            Room::COLUMNS column = static_cast<Room::COLUMNS>(section);
            switch (column)
            {
            case  Room::COLUMNS::NUMBER:
                return  tr("Number");
            case  Room::COLUMNS::PRICE:
                return  tr("Price");
            case  Room::COLUMNS::LIVING_SPACE:
                return  tr("Living Space");
            case  Room::COLUMNS::DATE_IN:
                return  tr("Date In");
            case  Room::COLUMNS::DATE_OUT:
                return  tr("Date Out");
            case  Room::COLUMNS::PERSONS:
                return  tr("Persons");
            case  Room::COLUMNS::IS_BOOKED:
                return  tr("Booked");

                default:
                    return QVariant();
            }
        }
        return QVariant();
}

Qt::ItemFlags Model::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return Qt::ItemIsEnabled;
    }
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}
