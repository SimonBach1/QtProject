#ifndef COOKIECLICKER2_H
#define COOKIECLICKER2_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class CookieClicker2; }
QT_END_NAMESPACE

class CookieClicker2 : public QMainWindow
{
    Q_OBJECT

public:
    CookieClicker2(QWidget *parent = nullptr);
    ~CookieClicker2();

private slots: // La section où vous déclarez vos slots
    void onImageClicked();

private:
    Ui::CookieClicker2 *ui;
};
#endif // COOKIECLICKER2_H
