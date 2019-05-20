
#include "model.h"



using namespace logic;

namespace
{
    QList<int> unUsedRoles = {
        Qt::CheckStateRole,
        Qt::ToolTipRole
    };
}

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

void Model::saveToXmlConfig()
{
    QFile file("Config/roomsConfigTest.xml");
    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("rooms");
    for(const auto& room : _rooms)
    {
        xmlWriter.writeStartElement("room");
        xmlWriter.writeAttribute("number",room.getData(logic::COLUMNS::NUMBER).toString());
        xmlWriter.writeTextElement("class",  room.getData(logic::COLUMNS::CLASS).toString());
        xmlWriter.writeTextElement("price", room.getData(logic::COLUMNS::PRICE).toString());
        xmlWriter.writeStartElement("orders");
        const auto& orders = room.getData(logic::COLUMNS::ORDERS).value<OrdersList>().orders;
        for(const auto& order : orders)
        {
            xmlWriter.writeStartElement("order");
            xmlWriter.writeTextElement("dateIn", order.dateIn.toString("dd/MM/yyyy"));
            xmlWriter.writeTextElement("dateOut", order.dateOut.toString("dd/MM/yyyy"));
            xmlWriter.writeStartElement("persons");
            for(const auto& person : order.persons)
            {
                xmlWriter.writeTextElement("person", person.name);
            }
            xmlWriter.writeEndElement();
            xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndElement();

        xmlWriter.writeTextElement("LivingSpace", room.getData(logic::COLUMNS::LIVING_SPACE).toString());
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();

    xmlWriter.writeEndDocument();
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
    if(unUsedRoles.contains(role))
    {
        return QVariant();
    }
    if (!index.isValid())
    {
        return QVariant();
    }
    if (index.row() >= _rooms.size() || index.row() < 0)
    {
        return QVariant();
    }
    if (index.column() == index.column() && role == Qt::TextAlignmentRole)
    {
        return Qt::AlignCenter;
    }
    const auto& room  = _rooms.at(index.row());
    COLUMNS column = static_cast<COLUMNS>(index.column());

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
            case  COLUMNS::CLASS:
                return  tr("Class");
            case  COLUMNS::PRICE:
                return  tr("Price");
            case  COLUMNS::LIVING_SPACE:
                return  tr("Living Space");
            case  COLUMNS::ORDERS :
                return  tr("Orders");
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
           room.setData(static_cast<COLUMNS>(index.column()),value);
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

void Model::registryRoom(const Room& room)
{
   _rooms.push_back(room);
}

bool Model::hasRoom(int number) const
{
    for(const auto& room : _rooms)
    {
        if(number == room.getData(COLUMNS::NUMBER).toInt())
        {
            return true;
        }
    }
    return false;
}

void Model::removeRoom(int number)
{
    auto it = std::find_if(_rooms.begin(), _rooms.end(),[number](const Room& room)
    {
        return number == room.getData(COLUMNS::NUMBER).toInt();
    });
    if(it != _rooms.end())
    {
        _rooms.erase(it);
    }
}

void Model::readXML(const QDomNode& node)
{
    QDomNode domNode = node.firstChild();
    while(!domNode.isNull())
    {
        if(domNode.isElement())
        {
            QDomElement domEl = domNode.toElement();
            auto nodes = domEl.childNodes();
            logic::Room newRoom;
            newRoom.setData(logic::COLUMNS::NUMBER, QVariant(domEl.attribute("number")));
            for(int i = 0; i < nodes.count(); ++i)
            {
                auto topNode = nodes.at(i);
                QDomElement el = topNode.toElement();
                if(!el.isNull())
                {
                    if("price" == el.tagName())
                    {
                        newRoom.setData(logic::COLUMNS::PRICE, QVariant(el.text()));
                    }
                    if("class" == el.tagName())
                    {
                        newRoom.setData(logic::COLUMNS::CLASS, QVariant(el.text()));
                    }
                    if("livingSpace" == el.tagName())
                    {
                        newRoom.setData(logic::COLUMNS::LIVING_SPACE, QVariant(el.text()));
                    }
                    if("orders" == el.tagName())
                    {
                        auto firstOrder = topNode.firstChild();
                        QList<Order> orders;
                        while(!firstOrder.isNull())
                        {
                            Order newOrder;
                            newOrder.dateIn = QDate::fromString(firstOrder.firstChildElement("dateIn").text(),"dd/MM/yyyy");
                            newOrder.dateOut =  QDate::fromString(firstOrder.firstChildElement("dateOut").text(),"dd/MM/yyyy");
                            QDomElement personsNode = firstOrder.firstChildElement("persons");
                            QDomNode person = personsNode.firstChild();
                            while(!person.isNull())
                            {
                                QString name = person.toElement().text();
                                newOrder.persons.push_back({name});

                                person = person.nextSibling();
                            }
                            firstOrder = firstOrder.nextSibling();
                            orders.push_back(newOrder);
                        }
                        QVariant orderVar;
                        orderVar.setValue(OrdersList{orders});
                        newRoom.setData(COLUMNS::ORDERS, orderVar);
                    }
                }
            }
            _rooms.push_back(newRoom);
        }
        domNode = domNode.nextSibling();
    }
}

