//
// Created by vorop on 24.10.2023.
//
#pragma once
#ifndef COURSEWORK_BOARD_H
#define COURSEWORK_BOARD_H

#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"
#include "Header.h"
#include "ImageBoard.h"
#include "MyDeque.h"

static const int marginUp = 62;         // Отступы для отрисовки поля и фигур px
static const int marginLeft = 53;
static const int sizeBox = 101;         // Размер клетки px
static const int sizeBoardPX = 811;     // Размер доски px

class Board {                                   // Класс представляющий игровую доску
public:
    Figure* map[SIZEBOARD][SIZEBOARD]{};        // представление игровой доски
    Coordinates whiteKingCoord;                 // координаты белого короля
    Coordinates darkKingCoord;                  // координаты черного короля
    ImageBoard texture;                         // изображение доски
private:
    StateGame stateGame;                        // состояние партии (победа, ничья, выход из партии)
    bool whiteMoveNow;                          // принадлежность хода
    int count50moves;                           // Счетчик полу-ходов для реализации правила 50ти ходов
    int numberOfMoves;                          // Кол-во ходов
    MyDeque<std::string> dequeFen;              // двунаправленная очередь, в которую записывается история партии
    const std::string startFEN{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"};         // Fen Start Board
public:
    Board() = default;
    ~Board();

    std::vector<Coordinates> getMove(int y, int x){ return map[y][x]->getAvailableMoveSquares(*this, true); } // получение доступных ходов для фигуры с координатами у, х
    short int checkOnMate();                    // Проверка на мат
    std::string generationFenString() const;    // Генерация строки FEN по текущему состоянию доски
    void setBoardByFen(std::string fen);        // установки доски в соответствии с FEN
    void move(Coordinates& oldCoord,Coordinates& newCoord); // перемещение фигуры

    void stepBack();                             // Отмена хода
    void giveUp();                              // Игрок сдался
    void clearBoard();                          // Очистка доски

    std::string getStartFEN() {  return startFEN;    }  // Получение FEN начала игры
    void setStateGame(StateGame state) {    stateGame = state;  }   // Установка состояния игры
    StateGame getStateGame() {  return stateGame;    }  // получение состояние партии
    bool itWhiteMoveNow() const    {   return whiteMoveNow;   } // получение принадлежность хода

    void writeDeqInFile(std::ofstream& fileName) const; // Запись дека в файл
    std::string extractFenOfBeginDeq();                 // извлечь элемент из начала дека
    std::string extractFenOfEndDeq();                   // извлечь элемент и конца дека
    unsigned int deqFenSize() { return dequeFen.size();    }    // Получение размера дека
    void addFenInDeq(const std::string& fen);           // добавление FEN в дек

    void pawnPromotion(sf::RenderWindow& window,Coordinates& coordinates);  // Проход пешки
    void drawBoard(sf::RenderWindow& window);           // Отрисовка игровой доски
    void drawAvailableMove(sf::RenderWindow& window, const std::vector<Coordinates>& availableMove);    // отрисовка доступных ходов
    void moveTransition()   {   whiteMoveNow = !whiteMoveNow;  }                // Передача хода

private:
    bool checkOnDraw();                                 // Проверка на ничью
    void changeCoordinatesKing(Coordinates& oldCoord,Coordinates& newCoord);    // Изменить координаты короля
    void changeSpecialCondition(Coordinates& oldCoordinates,Coordinates& newCoordinates);   // Изменить спец. состояние фигур
    void captureEnPassant(Coordinates& oldCoord,Coordinates& newCoord);         // взятие на проходе
    void castling(Coordinates& oldCoord, Coordinates& newCoord);                // Рокировка

};


#endif //COURSEWORK_BOARD_H
