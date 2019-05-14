
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

void Model::LoadFromXML(const QString& filePath)
{
    QDomDocument doc;
    QFile file(filePath);

    if(!file.exists())
    {
        assert(false);
        return;
    }
    if(file.open(QIODevice::ReadWrite))
    {
        QString errorStr;
        int line = 0;
        if(doc.setContent(&file,true,&errorStr,& line))
        {
            QDomElement el = doc.documentElement();
            readXML(el);
        }
    }
}

int Model::rowCount(const QModelIndex&) const
{
    return _rooms.count();
}

int Model::columnCount(const QModelIndex&) const
{
    return static_cast<int>(COLUMNS::COUNT);
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
    COLUMNS column = static_cast<COLUMNS >(index.column());
    return room.getData(column);
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal)
        {
            COLUMNS column = static_cast<COLUMNS>(section);
            switch (column)
            {
            case  COLUMNS::NUMBER:
                return  tr("Number");
            case  COLUMNS::PRICE:
                return  tr("Price");
            case  COLUMNS::LIVING_SPACE:
                return  tr("Living Space");
            case  COLUMNS::BOOK_DAYS :
                return  tr("Book Dates");
            case  COLUMNS::FREE_TODAY:
                return  tr("Free Today");
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

bool Model::setData(const QModelIndex& index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
           int row = index.row();

           auto room = _rooms.at(row);
           room.setData(static_cast<COLUMNS >(index.column()),value);
           _rooms.replace(row, room);
           emit dataChanged(index, index, {role});
           return true;
       }
    return false;
}

const QList<Room>& Model::getRooms() const
{
    return _rooms;
}

void Model::readXML(const QDomNode& node)
{
    QDomNode domNode = node.firstChild();
    while(!domNode.isNull())
    {
        if(domNode.isElement())
        {
            auto domEl = domNode.toElement();
            auto nodes = domEl.childNodes();
            logic::Room newRoom;
            newRoom.setData(logic::COLUMNS::NUMBER,QVariant(domEl.attribute("number")));
            for(int i = 0; i < nodes.count(); ++i)
            {
                auto el = nodes.at(i).toElement();
                if(!el.isNull())
                {
                    if("price" == el.tagName())
                    {
                        newRoom.setData(logic::COLUMNS::PRICE,QVariant(el.text()));
                    }
//                    else if("booked" == el.tagName())
//                    {
//                        newRoom.setData(logic::Room::COLUMNS::IS_BOOKED,QVariant(el.text()));
//                    }
//                    else if("dateIn" == el.tagName())
//                    {
//                        newRoom.setData(logic::Room::COLUMNS::DATE_IN,QVariant(el.text()));
//                    }
//                    else if("dateOut" == el.tagName())
//                    {
//                        newRoom.setData(logic::Room::COLUMNS::DATE_OUT,QVariant(el.text()));
//                    }
                }
            }
            _rooms.push_back(newRoom);
        }
        domNode = domNode.nextSibling();
    }
}

