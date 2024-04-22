#ifndef CLICKABLEIMAGE_H
#define CLICKABLEIMAGE_H



#include <QLabel>

class ClickableImage : public QLabel
{
   Q_OBJECT
public:
   ClickableImage(QString text, QWidget *parent = 0);

signals:
   void clicked();

protected:
   void mousePressEvent(QMouseEvent *event);
};

#endif // CLICKABLEIMAGE_H
