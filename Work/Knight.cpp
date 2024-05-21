//
// Created by vorop on 26.10.2023.
//
#include "Knight.h"
    // Получить тип
TypeFigure Knight::getType() {  return TypeFigure::Knight;  }

Knight::Knight(bool color, short int y,short int x,bool specialCondition): Figure(color,y,x,specialCondition) {}
std::vector<Coordinates>& Knight::getCoordinatesShift(){
    return shift;   // Получить координаты сдвигов
}