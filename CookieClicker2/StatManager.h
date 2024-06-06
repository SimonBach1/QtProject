#ifndef STATMANAGER_H
#define STATMANAGER_H

#include <QSettings>
#include <QCoreApplication>
#include <QDir>
#include <QTime>
#include <QVector>
#include <QPair>
#include <QObject>

class StatManager : public QObject {
    Q_OBJECT

public:
    static StatManager& instance() {
        static StatManager instance;
        return instance;
    }

    int getClickCount() const { return clickCount; }

    void incrementClickCount() {
        clickCount++;
        saveStats();
    }

    int getTotalMoney() const { return totalMoney; }

    void addToTotalMoney(int amount) {
        totalMoney += amount;
        updateDataPoint(amount);
        saveStats();
    }

    QTime getTempsTotal() const { return tempsTotal; }

    void updateTempsTotal() {
        tempsTotal = tempsTotal.addSecs(1); // Increment by 1 second
        saveStats();
    }

    QVector<QPair<QTime, int>> getDataPoints() const { return dataPoints; }

private:
    StatManager() {
        loadStats();
    }

    int clickCount = 0;
    int totalMoney = 0;
    QTime tempsTotal = QTime(0, 0);
    QVector<QPair<QTime, int>> dataPoints;

    void saveStats() {
        QString buildPath = QDir(QCoreApplication::applicationDirPath()).filePath("build_settings.ini");
        QSettings settings(buildPath, QSettings::IniFormat);
        settings.setValue("clickCount", clickCount);
        settings.setValue("totalMoney", totalMoney);
        settings.setValue("tempsTotal", tempsTotal.toString());

        QVariantList dataPointsVariant;
        for (const auto& point : dataPoints) {
            dataPointsVariant << QVariant::fromValue(point.first.toString() + "," + QString::number(point.second));
        }
        settings.setValue("dataPoints", dataPointsVariant);

        settings.sync();
    }

    void loadStats() {
        QString buildPath = QDir(QCoreApplication::applicationDirPath()).filePath("build_settings.ini");
        QSettings settings(buildPath, QSettings::IniFormat);
        clickCount = settings.value("clickCount", 0).toInt();
        totalMoney = settings.value("totalMoney", 0).toInt();
        tempsTotal = QTime::fromString(settings.value("tempsTotal", "00:00:00").toString());

        QVariantList dataPointsVariant = settings.value("dataPoints").toList();
        for (const auto& point : dataPointsVariant) {
            QStringList parts = point.toString().split(",");
            if (parts.size() == 2) {
                dataPoints.append(qMakePair(QTime::fromString(parts[0]), parts[1].toInt()));
            }
        }
    }

    void updateDataPoint(int amount) {
        for (auto& point : dataPoints) {
            if (point.first == tempsTotal) {
                point.second += amount;
                return; // Exit the function after updating
            }
        }
        dataPoints.append(qMakePair(tempsTotal, amount));
        if (dataPoints.size() > 120) {
               dataPoints.removeFirst(); // Remove the first point if the limit is reached
        }
    }

    StatManager(StatManager const&) = delete;
    void operator=(StatManager const&) = delete;
};

#endif // STATMANAGER_H
