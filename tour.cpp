#include <iostream>
#include <cstring>
#include <cstdio>

/* класс тур */
class Tour {
    char *agencyName;
    char *tourName;
    int daysCount;
    float dayPrice;

public:
    Tour() {
    }

    Tour(const Tour &tour) {
        // конструктор копирования создает копии строковых полей,
        // т.к. эти поля уничтожаются деструктором
        agencyName = copyString(tour.agencyName);
        tourName = copyString(tour.tourName);
        daysCount = tour.daysCount;
        dayPrice = tour.dayPrice;
    }

    /**
     * Строки agencyName и tourName удаляются при удалении тура
     */
    Tour(char *agencyName, char *tourName, int daysCount, float dayPrice)
            : agencyName(agencyName), tourName(tourName), daysCount(daysCount), dayPrice(dayPrice) {
    }

    /* деструктор */
    virtual ~Tour() {
        delete agencyName;
        delete tourName;
    }

    /* копирование строки */
    char *copyString(const char *str) {
        char *newStr = new char[strlen(str) + 10]();
        strcpy(newStr, str);
        return newStr;
    }

    char *getAgencyName() const {
        return agencyName;
    }

    char *getTourName() const {
        return tourName;
    }

    int getDaysCount() const {
        return daysCount;
    }

    float getDayPrice() const {
        return dayPrice;
    }

    /* метод вывод информации о туре в консоль*/
    friend std::ostream &operator<<(std::ostream &os, const Tour &tour) {
        os << "agencyName: " << tour.agencyName << " tourName: " << tour.tourName << " daysCount: " << tour.daysCount
           << " dayPrice: " << tour.dayPrice;
        return os;
    }
};


