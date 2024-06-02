#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <QSettings>
#include <QString>
#include <vector>
#include <QDir>
#include <QCoreApplication>

class ItemManager {
public:
    static ItemManager& instance() {
        static ItemManager instance;
        return instance;
    }

    QString getItemPrice(int index) const {
        if (index >= 0 && index < itemPrices.size()) {
            return itemPrices[index];
        }
        return QString();
    }

    int getItemNumber(int index) const {
        if (index >= 0 && index < itemNumbers.size()) {
            return itemNumbers[index];
        }
        return -1;
    }

    void setItemPrice(int index, const QString& newPrice) {
        if (index >= 0 && index < itemPrices.size()) {
            itemPrices[index] = newPrice;
            saveItemPrices();
        }
    }

    void setItemNumber(int index, int newNumber) {
        if (index >= 0 && index < itemNumbers.size()) {
            itemNumbers[index] = newNumber;
            saveItemNumbers();
        }
    }

private:
    ItemManager() {
        loadItemPrices();
        loadItemNumbers();
    }

    std::vector<QString> itemPrices = {"100", "2000", "10000", "75000", "200000", "1000000"};
    std::vector<int> itemNumbers = {0, 0, 0, 0, 0, 0};

    void saveItemPrices() {
        QString buildPath = QDir(QCoreApplication::applicationDirPath()).filePath("build_settings.ini");
        QSettings settings(buildPath, QSettings::IniFormat);
        for (int i = 0; i < itemPrices.size(); ++i) {
            settings.setValue(QString("itemPrice%1").arg(i), itemPrices[i]);
        }
    }

    void loadItemPrices() {
        QString buildPath = QDir(QCoreApplication::applicationDirPath()).filePath("build_settings.ini");
        QSettings settings(buildPath, QSettings::IniFormat);
        for (int i = 0; i < itemPrices.size(); ++i) {
            itemPrices[i] = settings.value(QString("itemPrice%1").arg(i), itemPrices[i]).toString();
        }
    }

    void saveItemNumbers() {
        QString buildPath = QDir(QCoreApplication::applicationDirPath()).filePath("build_settings.ini");
        QSettings settings(buildPath, QSettings::IniFormat);
        for (int i = 0; i < itemNumbers.size(); ++i) {
            settings.setValue(QString("itemNumber%1").arg(i), itemNumbers[i]);
        }
    }

    void loadItemNumbers() {
        QString buildPath = QDir(QCoreApplication::applicationDirPath()).filePath("build_settings.ini");
        QSettings settings(buildPath, QSettings::IniFormat);
        for (int i = 0; i < itemNumbers.size(); ++i) {
            itemNumbers[i] = settings.value(QString("itemNumber%1").arg(i), itemNumbers[i]).toInt();
        }
    }

    // Suppression des méthodes de copie et d'assignation pour garantir la singularité
    ItemManager(ItemManager const&) = delete;
    void operator=(ItemManager const&) = delete;
};

#endif // ITEMMANAGER_H
