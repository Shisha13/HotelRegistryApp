#ifndef DELEGATE_H
#define DELEGATE_H
#include <QStyledItemDelegate>

namespace logic
{
    class Delegate : public QStyledItemDelegate
    {
        Q_OBJECT
    public:
        Delegate(QObject* parent = nullptr);

        QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                              const QModelIndex& index) const override;
        void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

        void setEditorData(QWidget* editor, const QModelIndex& index) const override;
        void setModelData(QWidget* editor, QAbstractItemModel* model,
                         const QModelIndex &index) const override;

        void updateEditorGeometry(QWidget *editor,
            const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    };
}

#endif // DELEGATE_H
