#ifndef CUSTOMDELEGATE_H
#define CUSTOMDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QPushButton>
#include <QEvent>
#include <QApplication>

class CustomDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    CustomDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    bool buttonHovered = false;

signals:
    void buttonClicked(const QModelIndex &index);
    void buttonHoverStateChanged(const QModelIndex &index, bool hovered);
};

#endif // CUSTOMDELEGATE_H
