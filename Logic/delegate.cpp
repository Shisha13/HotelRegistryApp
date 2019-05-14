#include "delegate.h"
#include <QtWidgets>
#include <QApplication>
#include "Controls/dateseditdialog.h"
#include "model.h"
#include "room.h"

using namespace logic;

Delegate::Delegate(QObject* parent)
    : QStyledItemDelegate(parent)
{

}

QWidget* Delegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if(index.column() == static_cast<int>(COLUMNS::BOOK_DAYS))
    {
        return new DatesEditDialog(parent);
    }
    return QStyledItemDelegate::createEditor(parent,option,index);
}

void Delegate::paint(QPainter* painter, const QStyleOptionViewItem &option, const QModelIndex& index) const
{
    if(index.column() == static_cast<int>(COLUMNS::BOOK_DAYS))
    {
        QStyleOptionButton button;
        button.rect = option.rect;
        button.text = "edit";
        button.state = QStyle::State_Editing;
        button.features = QStyleOptionButton::Flat;
        button.icon = QIcon(":/Resources/Icons/calendar.png");
        button.iconSize = QSize(20,20);
        button.palette.setColor(QPalette::Button, QColor(Qt::blue));
        QApplication::style()->drawControl( QStyle::CE_PushButtonLabel, &button, painter);
        return;
    }
    if(index.column() == static_cast<int>(COLUMNS::FREE_TODAY))
    {
        QColor background = QColor(Qt::GlobalColor::red);
         painter->fillRect(option.rect, background);
    }
    QStyledItemDelegate::paint(painter,option,index);
}

void Delegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    if(index.column() == static_cast<int>(COLUMNS::BOOK_DAYS))
    {

    }
    QStyledItemDelegate::setEditorData(editor, index);
}

void Delegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    QStyledItemDelegate::setModelData(editor, model ,index);
}

void Delegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(dynamic_cast<QDialog*>(editor))
    {
//        QRect desktopRect = QApplication::desktop()->availableGeometry();
//        editor->move(desktopRect.center() - QPoint(editor->geometry().width(), editor->geometry().height()));
        return;
    }
    QStyledItemDelegate::updateEditorGeometry(editor,option,index);
}




