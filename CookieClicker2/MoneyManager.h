#ifndef MONEYMANAGER_H
#define MONEYMANAGER_H

class MoneyManager {
public:
    static MoneyManager& instance() {
        static MoneyManager instance; // Garanti d'être détruit.
                                      // Instancié à la première utilisation.
        return instance;
    }

    int getMoney() const { return money; }
    int setMoney(int newMoney) { money = newMoney; return money; }

private:
    MoneyManager() {} // Constructeur privé
    int money = 0;

    // C++ 11
    // Suppression des méthodes de copie et d'assignation pour garantir la singularité
    MoneyManager(MoneyManager const&) = delete;
    void operator=(MoneyManager const&) = delete;
};

#endif // MONEYMANAGER_H
