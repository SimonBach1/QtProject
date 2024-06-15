#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QPen>
#include <QVector>
#include <QPair>
#include <QTime>
#include "StatManager.h"

class CustomGraph : public QGraphicsView {
public:
    CustomGraph(QWidget *parent = nullptr) : QGraphicsView(parent) {
        scene = new QGraphicsScene(this);
        this->setScene(scene);
        this->setRenderHint(QPainter::Antialiasing);
        this->setFixedSize(600, 550);
        QVector<QPair<QTime, int>> dataPoints = StatManager::instance().getDataPoints();
        drawGraph(dataPoints);
    }

    void drawGraph(const QVector<QPair<QTime, int>> &dataPoints) {
        if (dataPoints.isEmpty()) return;

        int numPoints = dataPoints.size();
        int startIndex = 0;

        int maxX = 0;
        int minY = INT_MAX;
        int maxY = INT_MIN;

        for (int i = startIndex; i < numPoints; ++i) {
                    const auto &point = dataPoints[i];
                    int seconds = point.first.hour() * 3600 + point.first.minute() * 60 + point.first.second();
                    if (seconds > maxX) maxX = seconds;
                    if (point.second > maxY) maxY = point.second;
                    if (point.second < minY) minY = point.second;
                }

        float xSize = 500.0;
        float ySize = 450.0;
        float xScale = xSize / maxX;
        float yScale = ySize / maxY;

        QPen pen(Qt::blue, 2);

        for (int i = startIndex; i < numPoints - 1; ++i) {
            int x1 = dataPoints[i].first.hour() * 3600 + dataPoints[i].first.minute() * 60 + dataPoints[i].first.second();
            int y1 = dataPoints[i].second;
            int x2 = dataPoints[i + 1].first.hour() * 3600 + dataPoints[i + 1].first.minute() * 60 + dataPoints[i + 1].first.second();
            int y2 = dataPoints[i + 1].second;

            int xPos1 = (i * xSize) / (numPoints - 1);
            int xPos2 = ((i + 1) * xSize) / (numPoints - 1);

            float yPos1 = ySize - ((y1 - minY) / float(maxY - minY) * ySize);
            float yPos2 = ySize - ((y2 - minY) / float(maxY - minY) * ySize);

            //qDebug() << "yPos1:" << yPos1 << " yPos2:" << yPos2;
            //qDebug() << "ymin:" << minY << " maxY:" << maxY;



            scene->addLine(xPos1, yPos1, xPos2, yPos2, pen);
        }

        if (numPoints > 0) {
            QGraphicsTextItem *timeLabelStart = new QGraphicsTextItem(dataPoints[startIndex].first.toString("hh:mm:ss"));
            timeLabelStart->setPos(-20, ySize + 10);
            scene->addItem(timeLabelStart);

            QGraphicsTextItem *timeLabelEnd = new QGraphicsTextItem(dataPoints[numPoints - 1].first.toString("hh:mm:ss"));
            timeLabelEnd->setPos(xSize - timeLabelEnd->boundingRect().width()+20, ySize + 10);
            scene->addItem(timeLabelEnd);

            QGraphicsTextItem *moneyLabelStart = new QGraphicsTextItem(QString::number(maxY));
            moneyLabelStart->setPos(-30,-20);
            scene->addItem(moneyLabelStart);

            QGraphicsTextItem *moneyLabelEnd = new QGraphicsTextItem(QString::number(minY));
            moneyLabelEnd->setPos(-30, ySize - moneyLabelEnd->boundingRect().height()+10);
            scene->addItem(moneyLabelEnd);
        }

        QPen axisPen(Qt::black, 1);
        scene->addLine(0, 0, 0, ySize, axisPen);
        scene->addLine(0, ySize, xSize, ySize, axisPen);

        for (int i = 0; i <= 10; ++i) {
            int xPos = (i * xSize) / 10;
            scene->addLine(xPos, ySize, xPos, ySize + 5, axisPen);

            float yInterval = ySize / 10;
            float yPos = ySize - (i * yInterval);

            scene->addLine(-5, yPos, 0, yPos, axisPen);
        }


        QGraphicsTextItem *xLabel = new QGraphicsTextItem("Temps");
        xLabel->setPos(xSize / 2 - xLabel->boundingRect().width() / 2, ySize);
        scene->addItem(xLabel);

        QGraphicsTextItem *yLabel = new QGraphicsTextItem("Argent");
        yLabel->setRotation(-90);
        yLabel->setPos(-yLabel->boundingRect().width() - 10, ySize / 2 - yLabel->boundingRect().height() / 2);
        scene->addItem(yLabel);
    }

private:
    QGraphicsScene *scene;
};
