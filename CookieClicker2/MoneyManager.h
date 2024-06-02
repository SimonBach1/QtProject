#ifndef MONEYMANAGER_H
#define MONEYMANAGER_H

#include <QSettings>
#include <QCoreApplication>
#include <QDir>

class MoneyManager {
public:
    static MoneyManager& instance() {
        static MoneyManager instance;
        return instance;
    }

    int getMoney() const { return money; }
    int setMoney(int newMoney) {
        money = newMoney;
        saveMoney(); // Sauvegarder la nouvelle valeur de money
        return money;
    }

private:
    MoneyManager() {
        loadMoney(); // Charger la valeur de money au démarrage
    }

    int money = 0;

    void saveMoney() {
        QString buildPath = QDir(QCoreApplication::applicationDirPath()).filePath("build_settings.ini");
        QSettings settings(buildPath, QSettings::IniFormat);
        settings.setValue("money", money);
        settings.sync();
    }

    void loadMoney() {
        QString buildPath = QDir(QCoreApplication::applicationDirPath()).filePath("build_settings.ini");
        QSettings settings(buildPath, QSettings::IniFormat);
        money = settings.value("money", 0).toInt();
    }

    // Suppression des méthodes de copie et d'assignation pour garantir la singularité
    MoneyManager(MoneyManager const&) = delete;
    void operator=(MoneyManager const&) = delete;
};

#endif // MONEYMANAGER_H
