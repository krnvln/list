#include <iostream>

/*
 * параметризованный класс "элемент списка".
 */
template<typename T>
class Element {
public:
    /* пользовательские данные */
    T data;
    /* указатель на следующий элемент*/
    Element<T> *next;
    /* указатель на предыдущий элемент списка*/
    Element<T> *prev;

    /* конструктор */
    Element(const T& data, Element *next, Element *prev) : data(data), next(next), prev(prev) {}

    Element(const Element<T> &el) : data(el.data), next(el.next), prev(el.prev) {}
};

/* Параметризованный класс "двунаправленный список". Отвечает за создание/удаление объектов класса Element. */
template<typename T>
class List {
    /* указатель на начало списка*/
    Element<T> *start;

    /* получить элемент списка с номером index*/
    Element<T> *getElement(int index) const { // const - функция не меняет состояние списка
        if (size() > index && index >= 0) {
            Element<T> *el = start;
            for (int i = 0; i != index; ++i) {
                el = el->next;
            }
            return el;
        } else {
            return 0;
        }
    }

public:
    /* Конструктор по умолчанию. Может использоваться неявно при передаче объекта в функцию*/
    List() {
        start = 0;
    }

    /* деструктор. Удаляет все элементы списка */
    virtual ~List() {
        if (isEmpty()) {
            return;
        }
        while (start != 0) {
            Element<T> *nextEl = start->next;
            delete start;
            start = nextEl;
        }
    }

    /**
     * конструктор копирования
     * list - ссылка на копируемый список
     */
    List(const List &list) {
        if (list.isEmpty()) {
            start = 0;
            return;
        }
        start = new Element<T>(*list.start);
        Element<T> *listEl = list.start;
        Element<T> *newEl = start;
        while (listEl->next != 0) {
            Element<T> *element = new Element<T>(*listEl->next);
            newEl->next = element;
            element->prev = newEl;

            listEl = listEl->next;
            newEl = newEl->next;
        }
    }

    /**
     * добавить данные в начало списка. В список кладется копия объекта.
     * @param data данные
     */
    void add(const T& data) {
        if (start == 0) {
            start = new Element<T>(data, 0, 0);
        } else {
            Element<T> *newElement = new Element<T>(data, start, 0);
            start->prev = newElement;
            start = newElement;
        }
    }

    /**
     * удалить элемент на позиции index. Если на позиции index нет лемента - ниего не делать.
     */
    bool remove(int index) {
        Element<T> *foundElement = getElement(index);
        if (foundElement == 0) {
            return false;
        }
        bool isMiddleElement = foundElement->next != 0 && foundElement->prev != 0;
        bool isLastElement = foundElement->next == 0 && foundElement->prev != 0;
        bool isFirstElement = foundElement->next != 0 && foundElement->prev == 0;
        bool isOnlyElement = foundElement->prev == 0 && foundElement->next == 0;
        if (isOnlyElement) {
            start = 0;
        } else if (isMiddleElement) {
            foundElement->next->prev = foundElement->prev;
            foundElement->prev->next = foundElement->next;
        } else if (isLastElement) {
            foundElement->prev->next = 0;
        } else if (isFirstElement) {
            start = foundElement->next;
            foundElement->next->prev = 0;
        }
        delete foundElement;
        return true;
    }

    /**
     * получить элемент по номеру
     */
    T &get(int index) const {
        return getElement(index)->data;
    }

    /**
     ** @return true, если в списке есть элементы
     */
    bool isEmpty() const {
        return start == 0;
    }

    /**
     * @return количество элементов в списке
     */
    int size() const {
        if (start == 0) {
            return 0;
        }
        int i = 1;
        Element<T> *el = start;
        while (el->next != 0) {
            el = el->next;
            i++;
        }
        return i;
    }

    /**
     * перегрузка оператора << для вывода списка в поток ввода-вывода
     * @param os поток
     * @param dt список
     * @return os
     */
    friend std::ostream &operator<<(std::ostream &os, const List &dt) {
        Element<T> *el = dt.start;
        int i=0;
        while (el != 0) {
            os << i++ <<". " << el->data << "\n";
            el = el->next;
        }
        return os;
    }
};