//
// Created by vorop on 30.10.2023.
//

#include "Queen.h"


Queen::Queen(bool color, short int y,short int x,bool specialCondition): Figure(color,y,x,specialCondition),shift(Rook::shift) {
   for(Coordinates temp :  Bishop::shift)
        shift.push_back(temp);
}

TypeFigure Queen::getType() {  return TypeFigure::Queen;   }

std::vector<Coordinates>& Queen::getCoordinatesShift() {
    return shift;
}

bool Queen::isAvailableSquare(Coordinates& tempCoord, Board& board) {
    if( coordinates.x==tempCoord.x || coordinates.y==tempCoord.y) {   // если ходы как у ферзя
        if (Rook::isAvailableSquare(tempCoord, board))
            return true;
    }
    else{
        if (Bishop::isAvailableSquare(tempCoord, board) )            // ходы как у слона
            return true;
    }
    return false;
}