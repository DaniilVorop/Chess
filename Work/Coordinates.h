#ifndef COURSEWORK_COORDINATES_H
#define COURSEWORK_COORDINATES_H


class Coordinates {         // Класс координат
public:
    short int y;            // Координата по у
    short int x;            // Координата по х
    Coordinates() = default;
Coordinates (short int y,short int x): y(y),x(x){}

    Coordinates newCoordinates(Coordinates& shift) const { // Получение новых координат путем сложения старых и координат сдвига
        return Coordinates(static_cast<short int>(this->y+shift.y), static_cast<short int>(this->x+shift.x));
    }

    bool isCanShift(Coordinates& shift) const {    // Проверка координат на выход за границы доски
        if (this->y+shift.y > 7 || this->y+shift.y < 0) return false;
        if (this->x+shift.x > 7 || this->x+shift.x < 0) return false;
        return true;
    }

    bool operator== (Coordinates& anyCoordinates) const {   // Перегрузка оператора ==
         if (this->y == anyCoordinates.y && this->x == anyCoordinates.x)
            return true;
        else return false;
    }
};




#endif //COURSEWORK_COORDINATES_H
