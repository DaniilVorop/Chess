//
// Created by vorop on 30.10.2023.
//
#pragma once
#ifndef COURSEWORK_HEADER_H
#define COURSEWORK_HEADER_H

#include <vector>
#include <iostream>
#include "Exceptions.h"


const int SIZEBOARD = 8;
// Типы фигур
enum class TypeFigure{
    Pawn = 1,
    Knight,
    Bishop,
    Rook,
    Queen,
    King
};
enum class ActionInternetOpponent{
    Move,
    GiveUp,
    Exit,
    Undefined
};

enum class NetworkClient{
    Host,
    Client
};
// Кнопки стартового меню
enum class SelectStartMenu{
    Default,
    NewGameWithFriend = 1,
    NewGameWithComputer,
    NewNetworkGame,
    RestoreGameWithFriend,
    RestoreGameWithComputer,
    ViewingCompletedGames,
    ChangeStyle,
    Exit
};
// Действия ввода файла
enum class ClickToSaveOrReturnFile{
    InputText,
    RemoveSymbol,
    Save,
    Exit,
    Default
};
// Кнопки бокового меню
enum class SidebarInOnlineGameProcess{
    GiveUp,
    Save,
    Exit
};
enum class SidebarInGameProcess{
    GiveUp,
    StepBack,
    Save,
    Exit
};
// Кнопки бокового меню в режиме просмотра
enum class SidebarForWatch{
    StepForward,
    StepBack,
    Exit,
    Default
};
// Состояние игры
enum class StateGame{
    GameOn,
    WhiteWin,
    BlackWin,
    Draw,
    View,
    Exit
};

#endif //COURSEWORK_HEADER_H
