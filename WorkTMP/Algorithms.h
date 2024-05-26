//
// Created by vorop on 23.12.2023.
//

#ifndef COURSEWORK_ALGORITHMS_H
#define COURSEWORK_ALGORITHMS_H

class Algorithm {
public:
    //поиск
    template<typename T, typename Iterator>
    static Iterator find(Iterator begin, Iterator end, const T &value) {
        for (Iterator temp = begin; temp != end; temp++) {
            if (*temp == value)
                return temp;
        }
        return end;
    }

    // for_each
    template<typename T, typename Iterator, typename Comp>
    static void for_each(Iterator begin, Iterator end, Comp func) {
        for (Iterator temp = begin; temp != end; temp++) {
            func(*temp);
        }
    }

    // Удаление повторяющихся элементов
//    template<typename Iterator>
//    static void unique(Iterator begin, Iterator end) {
//        for (Iterator iter1 = begin; iter1 != end; ++iter1) {
//            for (Iterator iter2 = iter1 + 1; iter2 != end; ++iter2)
//                if (*iter1 == *iter2) {
//                    (*(iter2++)).deleteNode;
//                    --iter2;
//                }
//        }
//    }
    // поменять значение местами
    template<typename Iterator>
    static void swapElement(Iterator iter1, Iterator iter2) {
        auto temp = *iter1;
        *iter1 = *iter2;
        *iter2 = temp;
    }
// сравнение в диапазоне
    template<typename Iterator>
    static bool equal(Iterator first1, Iterator last1, Iterator first2) {
        while (first1 != last1) {
            if (*first1 != *first2)
                return false;
            ++first1;
            ++first2;
        }
        return true;
    }
    // Кол-во объектов между итераторами
    template<typename Iterator>
    static int totalCount(Iterator begin, Iterator end) {
        int count = 0;
        for (Iterator it = begin; it != end; ++it) {
            ++count;
        }
        return count;
    }
};

#endif //COURSEWORK_ALGORITHMS_H
