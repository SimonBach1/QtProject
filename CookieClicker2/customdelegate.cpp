// customdelegate.cpp
#include "customdelegate.h"
#include <QMouseEvent>
#include <QDebug>

CustomDelegate::CustomDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {}

void CustomDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    painter->save();


    QFont textFont = painter->font();
    textFont.setPointSize(24);
    painter->setFont(textFont);

    QRect entireRect = option.rect;
    int buttonWidth = 200;
    int iconSize = entireRect.height() / 1.2;
    QRect iconRect = QRect(entireRect.left() + 5, entireRect.top() + (entireRect.height() - iconSize) / 2, iconSize, iconSize);
    QRect textRect = QRect(entireRect.left()+60 + iconRect.width(), entireRect.top(), entireRect.width() - iconRect.width() - buttonWidth, entireRect.height());
    QRect buttonRect = QRect(entireRect.right() - buttonWidth-10, entireRect.top()+entireRect.height()/4, buttonWidth, entireRect.height()/2);

    QIcon icon = qvariant_cast<QIcon>(index.data(Qt::DecorationRole));
    icon.paint(painter, iconRect, Qt::AlignCenter);

    QString text = index.data(Qt::DisplayRole).toString();
    painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);

    QStyleOptionButton buttonOption;
    buttonOption.rect = buttonRect;
    buttonOption.text = "Acheter";
    buttonOption.state = QStyle::State_Enabled | QStyle::State_Active;

    QString buttonStyle =                    "QPushButton {"
                                             "    background-color: rgb(171,171,171);"
                                             "    color: white;"
                                             "font: bold 20px;"
                                             "    border-radius: 15px;"
                                             "    padding: 10px 20px;"
                                             "    border: none;"
                                             "}"
                                             "QPushButton:hover {"
                                             "    background-color: rgb(100,100,100);"
                                             "}";



    QFont buttonFont = painter->font();
       buttonFont.setBold(true);
       buttonFont.setPointSize(20);
       QColor defaultColor = QColor(171, 171, 171);
       QColor buttonColor = QColor(171, 171, 171);
       QColor textColor = QColor("white");
       QColor hoverColor = QColor(100, 100, 100);
       if (buttonHovered) {
               qDebug() << "refresh";
               buttonColor = hoverColor;
           } else {
               buttonColor = defaultColor;
           }
           // Dessiner le bouton avec les styles spécifiés
           painter->setPen(Qt::NoPen);
           painter->setBrush(buttonColor);

           // Dessiner le rectangle arrondi
           painter->drawRoundedRect(buttonRect, 15, 15);
           painter->setBrush(Qt::NoBrush);
           // Dessiner le texte du bouton
           painter->setPen(textColor);
           painter->setFont(buttonFont);
           painter->drawText(buttonRect, Qt::AlignCenter, "Acheter");




    //QApplication::style()->drawControl(QStyle::CE_PushButton, &buttonOption, painter);
    QPen pen(Qt::black, 2);  // Noir, épaisseur de 2 pixels
            painter->setPen(pen);
            painter->drawRect(entireRect.adjusted(1, 1, -1, -1));

    painter->restore();
}

bool CustomDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) {
    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            int buttonWidth = 200;
        QRect entireRect = option.rect;
        QRect buttonRect = QRect(entireRect.right() - buttonWidth-10, entireRect.top()+entireRect.height()/4, buttonWidth, entireRect.height()/2);
        if (buttonRect.contains(mouseEvent->pos())) {
            qDebug() << "Button clicked at release";
            emit buttonClicked(index);
            buttonHovered = false;
            return true;
        }
    }else if (event->type() == QEvent::MouseMove) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        int buttonWidth = 200;
        QRect entireRect = option.rect;
        QRect buttonRect = QRect(entireRect.right() - buttonWidth-10, entireRect.top()+entireRect.height()/4, buttonWidth, entireRect.height()/2);
        if (buttonRect.contains(mouseEvent->pos())) {
            if(!buttonHovered){
                emit buttonHoverStateChanged(index, buttonHovered);
            }
            buttonHovered = true;

        } else {
            if(buttonHovered){
                emit buttonHoverStateChanged(index, buttonHovered);
            }
            buttonHovered = false;


        }
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}


QSize CustomDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    // Taille par défaut de l'élément, peut-être basée sur le contenu
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    size.setHeight(200);  // Hauteur personnalisée
    size.setWidth(size.width());  // Largeur - modifier si nécessaire
    return size;
}
