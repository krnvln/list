#include <cstdio>
#include "list.cpp"

class Data {
public:
    static int created;
    static int deleted;
    int i;

    virtual ~Data() {
        deleted++;
    };

    Data() {
        created++;
    }

    Data(const Data &d) {
        created++;
        i = d.i;
    }

    Data(int i) {
        created++;
        this->i = i;
    }

// сделать такую-же в классе Tour !!!!!!!!!!!!!!!!!!!!!!!!!!
    friend
    std::ostream &operator<<(std::ostream &os, const Data &dt) {
        os << dt.i;
        return os;
    }
};

void testOverrideMethod();

int Data::created = 0;
int Data::deleted = 0;

void printList(List<Data> &list) {
    printf("list: ");
    for (int i = 0; i < list.size(); ++i) {
        printf(" %d,  ", list.get(i).i);
    }
    printf("\n");
    printf("\n");
}

void copyAndPrint(List<Data>& list) {
    printList(list);
}

void createAndCopyList() {

    List<Data> list = List<Data>();
    Data data = Data(10);
    list.add(data);
    list.add(Data(20));
    list.add(Data(30));
    copyAndPrint(list);
}

void testDestructors() {
    createAndCopyList();

    printf(" created = %d ", Data::created);
    printf(" deleted = %d ", Data::deleted);
}

void testList() {
    List<Data> list = List<Data>();
    list.add(Data(100));
    list.add(Data(200));
    list.add(Data(300));
    printList(list);

    list.remove(1);
    printList(list);

    list.remove(3);
    printList(list);

    list.remove(0);
    printList(list);

    list.remove(0);
    printList(list);

    list.add(5);
    printList(list);
}

void testOverrideMethod() {
    List<Data> list = List<Data>();
    Data data = Data(10);
    list.add(data);
    list.add(Data(20));
    list.add(Data(30));
    // использование перегруженного оператора
    std::cout << "list: \n" << list << std::endl;
}

int main1() {
//    testList();
    testDestructors();
//    testOverrideMethod();
    std::cout << "End program!" << std::endl;
    getchar();
    return 0;
}
