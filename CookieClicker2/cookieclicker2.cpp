#include "cookieclicker2.h"
#include "./ui_cookieclicker2.h"
#include <QPixmap>
#include <clickableImage.h>
#include <QString>
#include "MoneyManager.h"
#include "ItemManager.h"
#include <QStackedWidget>
#include <QStandardItemModel>
#include "ui_market.h"
#include "ui_cookieclicker2.h"
#include "ui_item.h"
#include "customdelegate.h"
#include "StatManager.h"
#include <QDebug>
#include "CustomGraph.cpp"
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>


CookieClicker2::CookieClicker2(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CookieClicker2)
    , animationGroup(nullptr)
    ,isAnimationRunning(false)

{


    std::string itemImagePath[] = {"patissier.png","four.png","machine.png","usine.png","zone.png","ville.png"};
    //std::string itemPrice[] = {"100","2 000","10 000","75 000","200 000","1 000 000"};
    //int itemNumber[] = {0,0,0,0,0,0};

    std::string itemName[] = {"Le patissier","Le four automatisé","La machine futuriste","L'usine à cookie","La zone industrielle","La ville cookie"};
    std::string itemFormatName[] = {"patissier(s)","four automatisé(s)","machine(s) futuriste(s)","usine(s) à cookies","zone(s) industrielle(s)","ville(s) cookie(s)"};
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

    QString label_money =
            "background-color: rgb(100,100,100);"
            "font: bold 20px;"
            "border-radius: 15px;"
            "padding: 10px 20px;"
            "color: white;"
            ;

    // Configuration du QTimer
       timer = new QTimer(this);
       connect(timer, &QTimer::timeout, this, &CookieClicker2::onTimeout);
       timer->start(1000); // Démarrer le timer avec un intervalle de 1000 ms (1 seconde)

    ui->setupUi(this);
    market.setupUi(this);
    itemWindow.setupUi(this);
    stat.setupUi(this);
    int money = MoneyManager::instance().getMoney();
    QString money_string = QString::number(money);
    ui->money->setText(money_string);
    market.money->setText(money_string);
    stat.money_2->setText(money_string);
    market.money->setStyleSheet(label_money);
    market.label->setStyleSheet(label_money);
    ui->money->setStyleSheet(label_money);
    ui->label->setStyleSheet(label_money);
    itemWindow.money->setStyleSheet(label_money);
    itemWindow.label->setStyleSheet(label_money);
    stat.money_2->setStyleSheet(label_money);
    stat.label_2->setStyleSheet(label_money);



       ui->marketButton->setStyleSheet(buttonStyle);
       market.pushButton->setStyleSheet(buttonStyle);
       itemWindow.returnButton->setStyleSheet(buttonStyle);
       itemWindow.buy->setStyleSheet(buttonStyle);
       ui->statButton->setStyleSheet(buttonStyle);
       stat.cookieButton->setStyleSheet(buttonStyle);

       stat.nbClick->setStyleSheet("font-size: 18pt;");
       stat.nbArgentTotal->setStyleSheet("font-size: 18pt;");
       stat.timeTotal->setStyleSheet("font-size: 18pt;");



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


       QWidget *fourthPageWidget = stat.statPage;
       stackedWidget->addWidget(fourthPageWidget);


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
             QString money_string = QString::number(money);
             market.money->setText(money_string);
          });

        QObject::connect(ui->statButton, &QPushButton::clicked, [=]() {
             stackedWidget->setCurrentWidget(fourthPageWidget);

             int money = MoneyManager::instance().getMoney();
             QString money_string = QString::number(money);
             stat.money_2->setText(money_string);

             money = StatManager::instance().getTotalMoney();
             money_string = QString::number(money);
             stat.nbArgentTotal->setText("Nombre total d'argent gagné : "+money_string);

             int clickcount = StatManager::instance().getClickCount();
             QString click_string = QString::number(clickcount);
             stat.nbClick->setText("Nombre total de clique effectué : "+click_string);

             QTime tempsTotal = StatManager::instance().getTempsTotal();
             stat.timeTotal->setText("Temps de jeu total : "+tempsTotal.toString("hh:mm:ss"));

             CustomGraph *graph = new CustomGraph(stat.graph);
             graph->show();

          });

        QObject::connect(market.pushButton, &QPushButton::clicked, [=]() {
             stackedWidget->setCurrentWidget(firstPageWidget);
          });

        QObject::connect(stat.cookieButton, &QPushButton::clicked, [=]() {
             stackedWidget->setCurrentWidget(firstPageWidget);
          });
        QObject::connect(itemWindow.returnButton, &QPushButton::clicked, [=]() {
             stackedWidget->setCurrentWidget(secondPageWidget);
          });

        connect(clickableImage, &ClickableImage::clicked, this, &CookieClicker2::onImageClicked);
        //connect(delegate, &CustomDelegate::buttonClicked, this, &CookieClicker2::handleButtonClicked);

        QObject::connect(delegate, &CustomDelegate::buttonClicked,[=](const QModelIndex &index){
            itemWindow.description->setText(QString::fromStdString(itemDescription[index.row()]));
            itemWindow.description->setStyleSheet("font-size: 18pt;");
            itemWindow.prix->setStyleSheet("font-size: 18pt;");
            itemWindow.nbItem->setStyleSheet("font-size: 18pt;");
            itemWindow.description->adjustSize();
            itemWindow.descriptionLayout->update();
            itemWindow.prix->setText("Prix : "+ItemManager::instance().getItemPrice(index.row()));
            QString s = ":/img/resources/"+ QString::fromStdString(itemImagePath[index.row()]);
            QPixmap pix(s);
            itemWindow.image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
            stackedWidget->setCurrentWidget(thirdPageWidget);
            int money = MoneyManager::instance().getMoney();
            QString money_string = QString::number(money);
            itemWindow.money->setText(money_string);
            itemWindow.nbItem->setText("Vous avez actuellement "+QString::number(ItemManager::instance().getItemNumber(index.row()))+" "+QString::fromStdString(itemFormatName[index.row()]));
            int row = index.row();
            this->currentIndex = index.row();
        });

        QObject::connect(delegate, &CustomDelegate::buttonHoverStateChanged,[=](const QModelIndex &index, bool hovered){
          //qDebug() << "emit ";
          listItems->update(index);
        });

        QObject::connect(itemWindow.buy, &QPushButton::clicked,[=](){
            qDebug() << currentIndex;
            int money = MoneyManager::instance().getMoney();
            if(money >= ItemManager::instance().getItemPrice(currentIndex).toInt()){
                ItemManager::instance().setItemNumber(currentIndex,ItemManager::instance().getItemNumber(currentIndex)+1);
                int newMoney = MoneyManager::instance().getMoney() - ItemManager::instance().getItemPrice(currentIndex).toInt();
                MoneyManager::instance().setMoney(newMoney);
            }
            itemWindow.nbItem->setText("Vous avez actuellement "+QString::number(ItemManager::instance().getItemNumber(currentIndex))+" "+QString::fromStdString(itemFormatName[currentIndex]));

        });





}

void CookieClicker2::handleButtonClicked(const QModelIndex &index) {
    //qDebug() << "delegate cliquée!";

}



void CookieClicker2::onImageClicked() {
    // Vérifiez si une animation est en cours


    qDebug() << "Image cliquée!";
    int money = MoneyManager::instance().getMoney() + 1;
    MoneyManager::instance().setMoney(money);
    QString s = QString::number(money);
    ui->money->setText(s);
    StatManager::instance().addToTotalMoney(1);
    StatManager::instance().incrementClickCount();

    if (isAnimationRunning) {
            return;
        }


    // Scale animation
    QPropertyAnimation *scaleUp = new QPropertyAnimation(ui->cookieImage, "geometry");
    scaleUp->setDuration(100);
    QRect startRect = ui->cookieImage->geometry();
    QRect endRect = QRect(startRect.x() - 10, startRect.y() - 10, startRect.width() + 20, startRect.height() + 20);
    scaleUp->setStartValue(startRect);
    scaleUp->setEndValue(endRect);

    QPropertyAnimation *scaleDown = new QPropertyAnimation(ui->cookieImage, "geometry");
    scaleDown->setDuration(100);
    scaleDown->setStartValue(endRect);
    scaleDown->setEndValue(startRect);

    QSequentialAnimationGroup *scaleGroup = new QSequentialAnimationGroup;
    scaleGroup->addAnimation(scaleUp);
    scaleGroup->addAnimation(scaleDown);



    if (animationGroup) {
        animationGroup->deleteLater();
    }

    animationGroup = new QParallelAnimationGroup;
    animationGroup->addAnimation(scaleGroup);

        connect(animationGroup, &QParallelAnimationGroup::finished, this, [=]() {
            isAnimationRunning = false;
            animationGroup->deleteLater();
            animationGroup = nullptr;
        });
        isAnimationRunning = true;

    animationGroup->start(QAbstractAnimation::DeleteWhenStopped);
}

CookieClicker2::~CookieClicker2()
{
    delete ui;
}

void CookieClicker2::onTimeout()
{
    int nbCookies[] = {1,5,25,100,500,1000};
    int n1 = ItemManager::instance().getItemNumber(0);
    int n2 = ItemManager::instance().getItemNumber(1);
    int n3 = ItemManager::instance().getItemNumber(2);
    int n4 = ItemManager::instance().getItemNumber(3);
    int n5 = ItemManager::instance().getItemNumber(4);
    int n6 = ItemManager::instance().getItemNumber(5);

    int moneyAdd = n1*nbCookies[0] + n2*nbCookies[1] + n3*nbCookies[2] + n4*nbCookies[3] + n5*nbCookies[4] + n6*nbCookies[5];
    int money = MoneyManager::instance().getMoney();
    MoneyManager::instance().setMoney(money+moneyAdd);
    money = MoneyManager::instance().getMoney();
    QString s = QString::number(money);
    ui->money->setText(s);
    itemWindow.money->setText(s);
    market.money->setText(s);
    stat.money_2->setText(s);
    StatManager::instance().addToTotalMoney(moneyAdd);

    money = StatManager::instance().getTotalMoney();
    QString money_string = QString::number(money);
    stat.nbArgentTotal->setText("Nombre total d'argent gagné : "+money_string);
    QString smoney = QString::number(moneyAdd);

    StatManager::instance().updateTempsTotal();

    QTime tempsTotal = StatManager::instance().getTempsTotal();
    stat.timeTotal->setText("Temps de jeu total : "+tempsTotal.toString("hh:mm:ss"));

    CustomGraph *graph = new CustomGraph(stat.graph);
    graph->show();

    qDebug() << "nb cookie : "+smoney;

}

