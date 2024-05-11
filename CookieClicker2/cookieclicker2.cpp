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
#include "ui_item.h"
#include "customdelegate.h"
#include <QDebug>


CookieClicker2::CookieClicker2(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CookieClicker2)

{

    ui->setupUi(this);
    market.setupUi(this);
    itemWindow.setupUi(this);


       QStackedWidget *stackedWidget = new QStackedWidget(this);
       setCentralWidget(stackedWidget);

       QWidget *firstPageWidget = ui->cookiePage;
       stackedWidget->addWidget(firstPageWidget);


       QWidget *secondPageWidget = market.marketPage;
       stackedWidget->addWidget(secondPageWidget);

       QWidget *thirdPageWidget = itemWindow.itemPage;
       QPixmap pix(":/img/resources/cookie.png");
       int w = ui->cookieImage->width();
       int h = ui->cookieImage->height();
       itemWindow.image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
       stackedWidget->addWidget(thirdPageWidget);

       QStandardItemModel *model = new QStandardItemModel();


       QListView * listItems = market.listView;

       listItems->setModel(model);

       for (int i = 0;i <10 ;i++ ) {
           QStandardItem *item = new QStandardItem();
               QString text = "Exemple d'Item n°" + QString::number(i);
               item->setText(text);
               item->setIcon(QIcon(":/img/resources/cookie.png"));
               model->appendRow(item);

       }



       CustomDelegate *delegate = new CustomDelegate();
       listItems->setItemDelegate(delegate);






        ClickableImage* clickableImage = new ClickableImage("", ui->cookieImage);
        w= ui->cookieImage->width();
        h = ui->cookieImage->height();
        clickableImage->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));



        QObject::connect(ui->marketButton, &QPushButton::clicked, [=]() {
             stackedWidget->setCurrentWidget(secondPageWidget);
          });

        QObject::connect(market.pushButton, &QPushButton::clicked, [=]() {
             stackedWidget->setCurrentWidget(firstPageWidget);
          });
        connect(clickableImage, &ClickableImage::clicked, this, &CookieClicker2::onImageClicked);


        QObject::connect(delegate, &CustomDelegate::buttonClicked,[=]() {
            stackedWidget->setCurrentWidget(thirdPageWidget);
        });



}

void CookieClicker2::handleButtonClicked(const QModelIndex &index) {

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

