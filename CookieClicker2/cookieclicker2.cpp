#include "cookieclicker2.h"
#include "./ui_cookieclicker2.h"
#include <QPixmap>
#include <clickableImage.h>
#include <QString>
#include "MoneyManager.h"
#include <QStackedWidget>
#include "ui_market.h"
#include "ui_cookieclicker2.h"


CookieClicker2::CookieClicker2(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CookieClicker2)
{
    //ui->setupUi(this);
    //QPixmap pix("/home/clonestriker/Bureau/Cours/BUT2/C++/CookieClicker2/resources/cookie.png");
    //int w = ui->cookieImage->width();
    //int h = ui->cookieImage->height();

    //ui->cookieImage->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    //ClickableImage* clickable = new ClickableImage("",ui->cookieImage);
    //clickable->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    //connect(clickable, &ClickableImage::clicked, this, &CookieClicker2::onImageClicked);

    ui->setupUi(this);



        QStackedWidget *stackedWidget = new QStackedWidget;

        // Création du premier widget et configuration via l'UI générée
        QMainWindow *firstPageWindow = new QMainWindow;
        Ui::CookieClicker2 firstPageUi;
        firstPageUi.setupUi(firstPageWindow);
        stackedWidget->addWidget(firstPageWindow);




        ClickableImage* clickableImage = new ClickableImage("", ui->cookieImage);
        QPixmap pix("/home/clonestriker/Bureau/Cours/BUT2/C++/CookieClicker2/resources/cookie.png");
        int w = ui->cookieImage->width();
        int h = ui->cookieImage->height();
        clickableImage->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));




        connect(clickableImage, &ClickableImage::clicked, this, &CookieClicker2::onImageClicked);









}

void CookieClicker2::onImageClicked(){
    qDebug() << "Image cliquée!";

    int money = MoneyManager::instance().getMoney()+1;
    money = MoneyManager::instance().setMoney(money);
    QString s = QString::number(money);
    ui->money->setText(s);
}

CookieClicker2::~CookieClicker2()
{
    delete ui;
}

