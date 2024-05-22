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


    std::string itemImagePath[] = {"patissier.png","four.png","machine.png","usine.png","zone.png","ville.png"};
    std::string itemName[] = {"Le patissier","Le four automatisé","La machine futuriste","L'usine à cookie","La zone industrielle","La ville cookie"};
    std::string itemDescription[] = {"Le patissier va travailler jour et nuit pour faire des cookies ! Il va en faire 1 par seconde",
                                     "Le four automatisé est très fiable, il va pouvoir faire des cookies sans s'arrêter au nombre de 5 par seconde",
                                    "La machine futuriste est incroyable ! Elle produit des cookies à la chaine , 25 par seconde",
                                    "L'usine est petite mais efficace ! Elle permet une production de cookie au nombre de 100 par seconde",
                                    "La zone industrielle est vaste, elle permet de produire plein de cookie, 500 par seconde",
                                    "La ville cookie est magnifique ! Elle permet une production de 1000 par seconde"};

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


    ui->setupUi(this);
    market.setupUi(this);
    itemWindow.setupUi(this);

       ui->marketButton->setStyleSheet(buttonStyle);
       market.pushButton->setStyleSheet(buttonStyle);
       itemWindow.returnButton->setStyleSheet(buttonStyle);
       itemWindow.buy->setStyleSheet(buttonStyle);


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

       for (int i = 0;i <6 ;i++ ) {
           QStandardItem *item = new QStandardItem();
               QString text =QString::fromStdString(itemName[i]);
               item->setText(text);
               item->setIcon(QIcon(":/img/resources/"+QString::fromStdString(itemImagePath[i])));
               model->appendRow(item);


       }



       CustomDelegate *delegate = new CustomDelegate();
       listItems->setItemDelegate(delegate); listItems->setMouseTracking(true);





        ClickableImage* clickableImage = new ClickableImage("", ui->cookieImage);
        w= ui->cookieImage->width();
        h = ui->cookieImage->height();
        clickableImage->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));



        QObject::connect(ui->marketButton, &QPushButton::clicked, [=]() {
             stackedWidget->setCurrentWidget(secondPageWidget);
             int money = MoneyManager::instance().getMoney();
             QString s = QString::number(money);
            market.argent->setText("Argent : " +s);
          });

        QObject::connect(market.pushButton, &QPushButton::clicked, [=]() {
             stackedWidget->setCurrentWidget(firstPageWidget);
          });
        QObject::connect(itemWindow.returnButton, &QPushButton::clicked, [=]() {
             stackedWidget->setCurrentWidget(secondPageWidget);
             int money = MoneyManager::instance().getMoney();
             QString s = QString::number(money);
            market.argent->setText("Argent : " +s);
          });

        connect(clickableImage, &ClickableImage::clicked, this, &CookieClicker2::onImageClicked);
        //connect(delegate, &CustomDelegate::buttonClicked, this, &CookieClicker2::handleButtonClicked);

        QObject::connect(delegate, &CustomDelegate::buttonClicked,[=](const QModelIndex &index){
            itemWindow.description->setText(QString::fromStdString(itemDescription[index.row()]));
            itemWindow.description->setStyleSheet("font-size: 18pt;");
            itemWindow.description->adjustSize();
            itemWindow.descriptionLayout->update();
            QString s = ":/img/resources/"+ QString::fromStdString(itemImagePath[index.row()]);
            QPixmap pix(s);
            itemWindow.image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
            stackedWidget->setCurrentWidget(thirdPageWidget);
        });

        QObject::connect(delegate, &CustomDelegate::buttonHoverStateChanged,[=](const QModelIndex &index, bool hovered){
          qDebug() << "emit ";
          listItems->update(index);
        });





}

void CookieClicker2::handleButtonClicked(const QModelIndex &index) {
    qDebug() << "delegate cliquée!";

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

