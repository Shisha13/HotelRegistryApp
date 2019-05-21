#ifndef MODEL_H
#define MODEL_H
#include <QAbstractItemModel>
#include <QDateTime>
#include <QtXml>
#include "room.h"

namespace logic
{
    struct HotelSettings
    {
        int minRoom = 101;
        int maxRoom = 909;
        int maxPrice = 500;
        int minPrice = 10;
    };

    class Model : public QAbstractTableModel
    {
        Q_OBJECT

    public:
        explicit Model(QObject *parent = nullptr);
        explicit Model(QList<Room> rooms, QObject* parent = nullptr);
        void LoadFromXML(const QString& filePath);
        void saveToXmlConfig();
        const HotelSettings& getHotelSettings() const { return _settings; }

        int rowCount(const QModelIndex &parent) const override;
        int columnCount(const QModelIndex &parent) const override;
        QVariant data(const QModelIndex &index, int role) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
        Qt::ItemFlags flags(const QModelIndex &index) const override;
        bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
        //bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
//        bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
        const QList<Room>& getRooms() const;
        void registryRoom(const Room& room);
        bool hasRoom(int number) const;
        void removeRoom(int number);

    protected:
        void readXML(const QDomNode &node);

    private:
        QList<Room> _rooms;
        HotelSettings _settings;
    };
}

#endif // MODEL_H
