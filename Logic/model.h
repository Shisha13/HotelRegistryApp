#ifndef MODEL_H
#define MODEL_H
#include <QAbstractItemModel>
#include <QDateTime>
#include <QtXml>
#include "room.h"

namespace logic
{

    class Model : public QAbstractTableModel
    {
        Q_OBJECT

    public:
        explicit Model(QObject *parent = nullptr);
        explicit Model(QList<Room> rooms, QObject* parent = nullptr);
        void LoadFromXML(const QString& filePath);

        int rowCount(const QModelIndex &parent) const override;
        int columnCount(const QModelIndex &parent) const override;
        QVariant data(const QModelIndex &index, int role) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
        Qt::ItemFlags flags(const QModelIndex &index) const override;
        bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
//        bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
//        bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
        const QList<Room>& getRooms() const;

    protected:
        void readXML(const QDomNode &node);

    private:
        QList<Room> _rooms;
    };
}

#endif // MODEL_H
