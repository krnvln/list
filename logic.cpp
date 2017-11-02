#include <cstring>
#include "tour.cpp"
#include "list.cpp"


/* вспомогательный класс для вычисления процента туров с большой ценой */
struct Agency {
    /* имя агенства */
    char *agencyName;
    /* количество туров со стоимостью > X */
    int bigPriceTourCount;
    /* общее количество туров */
    int tourCount;

    /* Конструктор по умолчанию. Может использоваться неявно при передаче объекта в функцию*/
    Agency() {}

    /* конструктор копирования */
    Agency(const Agency &agency) {
        agencyName = copyString(agency.agencyName); // сделать копию agency.agencyName
        bigPriceTourCount = agency.bigPriceTourCount;
        tourCount = agency.tourCount;
    }

    /* параметризованный конструктор*/
    Agency(char *agencyName, int bigPriceTourCount, int tourCount) : bigPriceTourCount(bigPriceTourCount),
                                                                     tourCount(tourCount) {
        this->agencyName = copyString(agencyName); // сделать копию agencyName
    }

    /* деструктор */
    virtual ~Agency() {
        delete agencyName;
    }

    char *copyString(const char *str) {
        char *newStr = new char[strlen(str) + 10]();
        strcpy(newStr, str);
        return newStr;
    }
};


/* Класс, выполняющий поиск агенств с завышенными ценами*/
class AgencyFinder {
    /* true, если стоимость тура больше значения price */
    bool isBigPriceTour(Tour tour, float price) {
        return tour.getDayPrice() * tour.getDaysCount() > price;
    }

    /* найти агенство по имени, вернуть индекс агенства из списка, или -1, если агенство не найдено */
    int findAgencyIndexByName(List<Agency> list, char *name) {
        for (int i = 0; i < list.size(); ++i) {
            Agency agency = list.get(i);
            if (strcmp(agency.agencyName, name) == 0) {
                return i;
            }
        }
        return -1;
    }

    /* возвращает имена агенств, у которых количество туров со стоимостью > price больше 50% */
    List<Agency> findBigPriceAgencies(const List<Tour> &tours, float price) {
        List<Agency> agencies = List<Agency>();
        for (int i = 0; i < tours.size(); ++i) {
            Tour tour = tours.get(i);
            bool bigPriceTour = isBigPriceTour(tour, price);
            int agencyIndex = findAgencyIndexByName(agencies, tour.getAgencyName());
            if (agencyIndex < 0) { // если запись об агенстве не найдена
                // создать новое агенство:
                // общее кол-во туров = 1; кол-во туров с завышенной ценой =1 если bigPriceTour=true
                Agency agency = Agency(tour.getAgencyName(), bigPriceTour ? 1 : 0, 1);
                agencies.add(agency);
            } else {
                // получить имеющуюся запись об агенстве
                Agency agency = agencies.get(agencyIndex);
                // увеличить общее кол-во туров
                agency.tourCount++;
                if (bigPriceTour) {
                    // увеличить кол-во туров с завышенной ценой
                    agency.bigPriceTourCount++;
                }
            }
        }
        return agencies;
    }

public:
    /* получить имена агенств с завышенными ценами */
    List<char *> getBigPriceAgencyNames(const List<Tour> &tours, float maxPrice) {
        List<char *> result = List<char *>();
        const List<Agency> &agencies = findBigPriceAgencies(tours, maxPrice);
        for (int i = 0; i < agencies.size(); ++i) {
            const Agency &agency = agencies.get(i);
            if ( (double) agency.bigPriceTourCount / agency.tourCount > 0.5) { // todo get float value!!!!!
                result.add(copyString(agency.agencyName));
            }
        }

        return result;
    }

    /* копировать строку */
    char *copyString(const char *string) {
        char *nStr = new char[strlen(string) + 10]();
        strcpy(nStr, string);
        return nStr;
    }

    /* тестовый пример поиска агенств с завышенными ценами */
    void testTour1() {
        List<Tour> tours = List<Tour>();
        tours.add(Tour(copyString("agency 1"), copyString("agency1_tour1"), 100, 10));
        tours.add(Tour(copyString("agency 1"), copyString("agency1_tour2"), 1, 10));
        tours.add(Tour(copyString("agency 1"), copyString("agency1_tour3"), 100, 10));

        tours.add(Tour(copyString("agency 2"), copyString("agency2_tour1"), 1, 10));
        tours.add(Tour(copyString("agency 2"), copyString("agency2_tour2"), 100, 10));
        tours.add(Tour(copyString("agency 2"), copyString("agency2_tour3"), 1, 10));

        const List<char *> &result = getBigPriceAgencyNames(tours, 100);
        std::cout << "result = \n" << result << std::endl;
        std::cout << "expected resut: " << "agency 1" << std::endl;
        getchar();
    }
};


