//
// Created by vorop on 02.12.2023.
//

#ifndef COURSEWORK_STOCKFISH_H
#define COURSEWORK_STOCKFISH_H


#ifdef _WIN32
    #include <Windows.h>
#endif

#include "iostream"
#include "chrono"
#include "vector"

class StockFish {                   // Класс взаимодействия с "Stockfish"
private:
#ifdef _WIN32
    PROCESS_INFORMATION pi{0};      // Информация в процессе работы потока
    HANDLE hStdinRead{},hStdinWrite{},hStdoutRead{},hStdoutWrite{},hStderrRead{},hStderrWrite{};
#endif
#ifdef __linux__
//    std::thread threadForNetwork;
    std::string sendMsg;
    std::string readMsg;
    int stdinWrite;
    int stdoutRead;
#endif

public:
    StockFish()= default;
    bool startStockFish();          // Создание потока и запуск Stockfish
    void sendStockFishCommand(std::string msg) const;
    std::string readStockFishOutput() const;
    void closeStockFish() const;          // Закрыть поток
    ~StockFish();                   // деструктор закрывает поток
};


#endif //COURSEWORK_STOCKFISH_H
