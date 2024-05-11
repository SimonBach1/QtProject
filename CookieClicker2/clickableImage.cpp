#include "clickableImage.h"
#include <QMouseEvent>

// Constructeur
ClickableImage::ClickableImage(QString text, QWidget *parent)
    : QLabel(text, parent) {
}


void ClickableImage::mousePressEvent(QMouseEvent *event) {

    QLabel::mousePressEvent(event);

    emit clicked();
}
