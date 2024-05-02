#include "cookieclicker2.h"
#include "./ui_cookieclicker2.h"
#include <QPixmap>
#include <clickableImage.h>
#include <QString>
#include "MoneyManager.h"
#include <QStackedWidget>
#include <QStandardItemModel>
#include "ui_market.h"
#include "ui_cookieclicker2.h"
#include "customdelegate.h"


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
    market.setupUi(this);


       QStackedWidget *stackedWidget = new QStackedWidget(this);
       setCentralWidget(stackedWidget);

       QWidget *firstPageWidget = ui->cookiePage;
       stackedWidget->addWidget(firstPageWidget);


       QWidget *secondPageWidget = market.marketPage;
       stackedWidget->addWidget(secondPageWidget);

       QStandardItemModel *model = new QStandardItemModel();


       QListView * listItems = market.listView;

       listItems->setModel(model);

       for (int i = 0;i <10 ;i++ ) {
           QStandardItem *item = new QStandardItem();
               QString text = "Exemple d'Item n°" + QString::number(i);
               item->setText(text);
               item->setIcon(QIcon("/home/clonestriker/Bureau/Cours/BUT2/C++/CookieClicker2/resources/cookie.png"));
               model->appendRow(item);
       }



       CustomDelegate *delegate = new CustomDelegate();
       listItems->setItemDelegate(delegate);






        ClickableImage* clickableImage = new ClickableImage("", ui->cookieImage);
        QPixmap pix("/home/clonestriker/Bureau/Cours/BUT2/C++/CookieClicker2/resources/cookie.png");
        int w = ui->cookieImage->width();
        int h = ui->cookieImage->height();
        clickableImage->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));



        QObject::connect(ui->marketButton, &QPushButton::clicked, [=]() {
             stackedWidget->setCurrentWidget(secondPageWidget);
          });

        QObject::connect(market.pushButton, &QPushButton::clicked, [=]() {
             stackedWidget->setCurrentWidget(firstPageWidget);
          });
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

