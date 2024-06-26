#ifndef COOKIECLICKER2_H
#define COOKIECLICKER2_H

#include <QMainWindow>
#include <QStackedWidget>
#include "ui_market.h"
#include "ui_item.h"
#include "ui_stat.h"
#include <QTimer>
#include <QParallelAnimationGroup>


QT_BEGIN_NAMESPACE
namespace Ui { class CookieClicker2; }
QT_END_NAMESPACE

class CookieClicker2 : public QMainWindow
{
    Q_OBJECT

public:
    CookieClicker2(QWidget *parent = nullptr);
    ~CookieClicker2();

public slots: // La section où vous déclarez vos slots
    void onImageClicked();
    void handleButtonClicked(const QModelIndex &index);
    void onTimeout();


private:
    QParallelAnimationGroup *animationGroup;
    Ui::CookieClicker2 *ui;
    Ui::marketWIndow market;
    Ui::itemWindow itemWindow;
    Ui::Stat stat;
    int currentIndex;
    QTimer *timer;
    bool isAnimationRunning;


};
#endif // COOKIECLICKER2_H
