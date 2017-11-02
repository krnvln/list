#include <cstdio>
#include "logic.cpp"

/* объект поиска агенств с завышенной ценой */
AgencyFinder finder = AgencyFinder();

/* читать данные из консоли в новую строку */
char *readNewString(const char *message) {
    char *buffer = new char[256]();
    printf(message);
    gets(buffer);
    return buffer;
}

/* читать из консоли целое число */
int readInt(const char *message) {
    int input = 0;
    printf(message);
    scanf("%d", &input);
    char t[256];
    gets(t);
    return input;
}

/* выполнить поиск агенств с завышенной ценой, вывести результат */
void findBigPriceAgenciesAction(List<Tour> list) {
    int maxPrice = readInt("Enter maximum price value: ");
    List<char *> names = finder.getBigPriceAgencyNames(list, maxPrice);
    std::cout << "Big price agenies: \n" << names << std::endl;
}

/* вывести весь список туров */
void showAllToursAction(List<Tour> list) {
    std::cout << "List of tours:\n" << list << std::endl;
}

/* удалить элемент списка, вывести результат удаления */
void removeTourAction(List<Tour> &list) {
    int index = readInt("Enter index of tour to delete: ");
    if (list.size() <= index) {
        printf("index too big: size of list = %d \n", list.size());
    } else {
        bool deleted = list.remove(index);
        if (deleted) {
            printf("tour was deleted");
        }else{
            printf("tour wasn't deleted");
        }
    }
}

/* добавить новый тур */
void addNewTourAction(List<Tour> &list) {
    // создаются строки и записываются в тур. далее объект класса тур следит за их удалением.
    char *agencyName = readNewString("Enter agency name: ");
    char *tourName = readNewString("Enter tour name: ");
    int daysCount = readInt("Enter days count: ");
    int dayPrice = readInt("Enter day price: ");
    list.add(Tour(agencyName, tourName, daysCount, dayPrice));
}

/* вывести меню на экран */
void printMenu() {
    std::cout << "\n########################\n";
    std::cout << "1. Add tour\n";
    std::cout << "2. Remove tour\n";
    std::cout << "3. Show all tours\n";
    std::cout << "4. Find big price agencies\n";
    std::cout << "5. Exit\n";
    std::cout << "########################\n";
}

/* НАЧАЛО РАБОТЫ ПРОГРАММЫ */
int main() {
    std::cout << "Welcome\n";
    List<Tour> tours = List<Tour>();
    int input = 0;
    while (input != 5) {
        printMenu();
        input = readInt("Enter command: ");
        switch (input) {
            case 1:
                addNewTourAction(tours);
                break;
            case 2:
                removeTourAction(tours);
                break;
            case 3:
                showAllToursAction(tours);
                break;
            case 4:
                findBigPriceAgenciesAction(tours);
                break;
            case 5:
                break;
            default:
                printf("Bad command\n");
                break;
        }
    }
}
