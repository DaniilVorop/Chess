//
// Created by vorop on 19.12.2023.
//

#ifndef INC_2KYRSLABS_MYDEQUE_H
#define INC_2KYRSLABS_MYDEQUE_H



#include "iostream"
#include "Exceptions.h"

template<typename T>
class MyDeque {             // Контейнер "двунаправленная очередь"
private:
    struct Node{            // Узел
    public:
        T data;
        Node* prev;
        Node* next;
        Node() : prev(nullptr),next(nullptr){}
        explicit Node(const T& data): data(data), prev(nullptr), next(nullptr){}
    };

    Node* head;             // Указатель на первый элемент
    Node* tail;             // Указатель на последний элемент
    int depth = 0;          // Размер дека
public:
    class Iterator{         // Класс Итератора
    private:
        Node* current;      // Указатель на текущий элемент
    public:
        Iterator(): current(nullptr){}
        explicit Iterator(Node* node) : current(node) {}
        Iterator(const Iterator& iter): current(iter.current) {}
        ~Iterator() = default;

        Iterator&  operator++();    // Перегрузка оператора префиксный ++
        Iterator operator++(int);   // Перегрузка оператора постфиксный ++

        Iterator& operator--();     // Перегрузка оператора префиксный --
        Iterator operator--(int);   // Перегрузка оператора префиксный --

        Iterator operator+(int value);  // Перегрузка оператора + (int)
        Iterator operator-(int value);  // Перегрузка оператора - (int)
        T& operator*()  {   return current->data;   }       // Оператор разыменования
        bool operator==(const Iterator other){    return (this->current == other.current);  }   // Оператор ==
        bool operator!=(const Iterator other){  return (this->current != other.current);    }   // Оператор !=

        void deleteNode();                      // Удаление current
        void addNode(T value);                  // Добавление после current
    };
    MyDeque(): head(nullptr),tail(nullptr){}
    MyDeque(const MyDeque & deq);
    MyDeque(std::initializer_list<int> args);  // Конструктор с переменных числом параметров
    ~MyDeque(){     this->clear();   }

    Iterator begin() const {  return Iterator(head);    }     // Получить итератор на начало
    Iterator end()  const {  return Iterator(tail->next);    } // Получить итератор на конец

    void push_back(T data);                             // Добавление в конец
    void push_front(T data);                            // Добавление в начало
    void emplace_back(const T& elem);                    // Добавление в конец без лишнего копирования
    void emplace_front(const T& elem);                   // Добавление в начало без лишнего копирования

    void pop_front();                                   // Удалить первый элемент
    void pop_back();                                    // Удалить последний элемент
    Iterator erase(Iterator pos);                       // Удалить по позиции итератора
    Iterator erase(Iterator begin, Iterator end);       // Удалить в диапазоне итераторов
    void clear();                                       // Очистить дек

    T& at(int index) const;                             // Получить элемент по индексу
    T& front() {    return head->data;     }            // Получить первый элемент
    T& back()  {     return tail->data;    }            // Получить последний элемент
    int size() const;                                   // Получить размер
    T& operator[](int index);                           // Перегрузка оператора []
    Iterator insert(Iterator pos,T value);              // Добавить элемент после итератора
    void reverse();                                     // Перевернуть дек
    void operator=(MyDeque<T>& deque);                  // Перегрузка оператора =
};

template<typename T>
MyDeque<T>::MyDeque(const MyDeque &deq): head(nullptr), tail(nullptr) {
    for (T tmp: deq)
        this->emplace_back(tmp);
}

template<typename T>        // Перегрузка оператора=
void MyDeque<T>::operator=(MyDeque<T>& deque) {
    this->clear();
    for(T tmp:deque)
        this->emplace_back(tmp);    // Добавление в конец
}


template<typename T>        // Перевернуть дек
void MyDeque<T>::reverse() {
    T tmp;
    Iterator it1 = this->begin();
    Iterator it2 = this->begin() + depth;
    for(int i = depth - 1; i > depth/2 - 1; i--, it1++, it2--){     // Содержимое контейнера меняб местами
        tmp = at(i);
        at(i) = at(depth - i - 1);
        at(depth - i - 1) = tmp;
    }
}

template<typename T>                // Конструктор с переменным числом параметров
MyDeque<T>::MyDeque(std::initializer_list<int> args):head(nullptr),tail(nullptr) {
    for (T data: args)
        this->push_back(data);
}

template<typename T>
void MyDeque<T>::Iterator::addNode(T value) {           // Добавление узла по позиции итератора
    Node *temp = current->next;
    current->next = new Node(value);
    temp->prev = current->next;
    current->next->next = temp;
    current->next->prev = current;
    ++(*this);
}

template<typename T>                                     // Удаление узла по позиции итератора
void MyDeque<T>::Iterator::deleteNode() {
    Node *temp = current;
    current = current->next;
    temp->prev->next = current;
    current->prev = temp->prev;
    delete temp;
}

template<typename T>                                    // Перегрузка оператора -(int) для итератора
typename MyDeque<T>::Iterator MyDeque<T>::Iterator::operator-(int value) {
    Iterator tmp(current);
    for (int i = 0; i < value; i++)
        tmp--;
    return tmp;
}

template<typename T>                                    // Перегрузка оператора +(int) для итератора
typename MyDeque<T>::Iterator MyDeque<T>::Iterator::operator+(int value) {
    Iterator tmp(current);
    for(int i = 0; i < value; i++)
        tmp++;
    return tmp;
}

template<typename T>            // Перегрузка постфиксного оператора--
typename MyDeque<T>::Iterator MyDeque<T>::Iterator::operator--(int) {
    Iterator tmp(current);
    if (current)
        --(*this);
    return tmp;
}

template<typename T>           // Перегрузка префиксного оператора--
typename MyDeque<T>::Iterator &MyDeque<T>::Iterator::operator--() {
    if (current)
        current = current->prev;
    return *this;
}

template<typename T>           // Перегрузка постфиксного оператора++
typename MyDeque<T>::Iterator MyDeque<T>::Iterator::operator++(int) {
    Iterator tmp(current);
    if (current)
        ++(*this);
    return tmp;
}

template<typename T>           // Перегрузка префиксного оператора++
typename MyDeque<T>::Iterator &MyDeque<T>::Iterator::operator++() {
    if (current)
        current = current->next;
    return *this;
}

template<typename T>            // Добавление элемента по позиции итератора
typename MyDeque<T>::Iterator MyDeque<T>::insert(MyDeque::Iterator pos, T value) {
    if (pos == begin()){
        push_front(value);
        return begin();
    }
    else if (pos == begin() + (this->depth - 1)){
        push_back(value);
        return begin() + (this->depth - 1);
    }
    else {
        pos.addNode(value);
        this->depth++;
        return pos;
    }
}

template<typename T>                // Удаление элементов в диапазоне итераторов
typename MyDeque<T>::Iterator MyDeque<T>::erase(MyDeque::Iterator begin, MyDeque::Iterator end) {
    while(begin != end)
        begin = erase(begin);
    begin = erase(begin);
    return begin;
}

template<typename T>                // Удаление по итератору
typename MyDeque<T>::Iterator MyDeque<T>::erase(MyDeque<T>::Iterator pos) {
    if (pos == begin()){
        pop_front();
        return begin();
    }
    else if (pos == begin() + (this->depth - 1) ) {
        pop_back();
        return end();
    }
    else {
        pos.deleteNode();
        this->depth--;
        return pos;
    }
}

template<typename T>            // Перегрузка []
T& MyDeque<T>::operator[](int index) {
    return *(begin() + index);
}

template<typename T>            // Добавление элемента без доп. копирования
void MyDeque<T>::emplace_front(const T& elem) {
    this->depth++;
    Node* newNode = new Node(elem);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

template<typename T>        // Добавление элемента без доп. копирования
void MyDeque<T>::emplace_back(const T& elem) {
    this->depth++;
    Node* newNode = new Node(elem);
    if (tail == nullptr) {
        head = tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
}

template<typename T>        // Получить элемент по индексу
T& MyDeque<T>::at(int index) const {
    if (index <= depth) {
        return *(begin() + index);
    }
    else {
        throw(ExceptionDeque("No element", 4));
    }
}

template<typename T>       // Очистка дека
void MyDeque<T>::clear() {
    Node* temp;
    depth = 0;
    while(head != nullptr) {
        temp = head->next;
        delete head;
        head = temp;
    }
    head = tail = nullptr;
}

template<typename T>        // Получить размер дека
int MyDeque<T>::size() const {
    return depth;
}

template<typename T>        // Добавить элемент в начало
void MyDeque<T>::push_front(T data) {
    this->depth++;
    if (head != nullptr) {
        head->prev = new Node(data);
        head->prev->next = head;
        head = head->prev;
    }
    else {
        head = new Node(data);
        tail = head;
    }
}

template<typename T>        // Добавить элемент в конец
void MyDeque<T>::push_back(T data) {
    this->depth++;
    if (head != nullptr) {
        tail->next = new Node(data);
        tail->next->prev = tail;
        tail = tail->next;
    }
    else {
        head = tail = new Node(data);
    }
}

template<typename T>            // Удалить первый элемент
void MyDeque<T>::pop_front() {
    if (head != nullptr) {
        depth--;
        head = head->next;
        if (head != nullptr) {
            delete head->prev;
            head->prev = nullptr;
        }
        if (depth == 0)
            head = tail = nullptr;
    }
}

template<typename T>        // Удалить последний элемент
void MyDeque<T>::pop_back() {
    if (tail != nullptr) {
        depth--;
        tail = tail->prev;
        if (tail != nullptr) {
            delete tail->next;
            tail->next = nullptr;
        }
        if (depth == 0)
            head = tail = nullptr;
    }
}

#endif //INC_2KYRSLABS_MYDEQUE_H
