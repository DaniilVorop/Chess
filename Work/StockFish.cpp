//
// Created by vorop on 02.12.2023.
//
#include <thread>
#include "StockFish.h"
#include "Exceptions.h"
#include <unistd.h>
#include <iostream>

#ifdef __linux__
#include "sys/wait.h"
bool StockFish::startStockFish() {
    int stdin_pipe[2];
    int stdout_pipe[2];
    // Создание каналов
    if (pipe(stdin_pipe) == -1 || pipe(stdout_pipe) == -1) {
        std::cerr << "Failed to create pipes\n";
        return false;
    }

    // Создание нового процесса
    pid_t pid = fork();
    if (pid == -1) {
        std::cerr << "Failed to fork\n";
        return false;
    } else if (pid == 0) { // В дочернем процессе
        // Замена стандартного ввода и вывода дочернего процесса на каналы
        close(stdin_pipe[1]);
        dup2(stdin_pipe[0], STDIN_FILENO);
        close(stdout_pipe[0]);
        dup2(stdout_pipe[1], STDOUT_FILENO);
        execl("./stockfish/stockfish-ubuntu-x86-64-sse41-popcnt", "stockfish", nullptr);
        // Если execl вернется, значит возникла ошибка
        std::cerr << "Failed to execute Stockfish\n";
        exit(EXIT_FAILURE);
    }
    // В родительском процессе закрываем концы каналов, которые не используются
    close(stdin_pipe[0]);
    close(stdout_pipe[1]);
     this->stdinWrite = stdin_pipe[1];
     this->stdoutRead = stdout_pipe[0];
    return true;
}

void StockFish::closeStockFish() const {
     write(this->stdinWrite, "quit\n", 5);
     close(this->stdinWrite);
     close(this->stdoutRead);
     wait(nullptr);
}

void StockFish::sendStockFishCommand(std::string msg) const {
    msg += '\n';
    std::cout << msg << std::endl;
    write(this->stdinWrite, msg.c_str(), msg.length());
}

std::string StockFish::readStockFishOutput() const {
    std::this_thread::sleep_for(std::chrono::milliseconds (200));
    char buffer[2048];
    std::string str;
    ssize_t bytesRead;
    do{
        bytesRead = read(this->stdoutRead, buffer, sizeof(buffer));
        str += buffer;
    } while (sizeof(buffer) == bytesRead);
    // Поиска подстроки bestmove
    int n = static_cast<int>(str.find("bestmove"));
    if (n == -1)    // Если подстрока не найдена
        throw (ExceptionStockFish("Error read StockFish output", -3));
    return str.substr(n+9,4); // Извлечение данных о ходе (e4e6)
}

StockFish::~StockFish() {
    closeStockFish();
}
#endif

#ifdef _WIN32

bool StockFish::startStockFish() {
    STARTUPINFO si{0};              // Информация для создания второго потока
    SECURITY_ATTRIBUTES saAttr{0};  // атрибуты доступа
    // Обнуление памяти
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    // Установка необходимых параметров
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle=TRUE;
    saAttr.lpSecurityDescriptor=nullptr;
    // Создание канала для стандартного ввода
    if (!CreatePipe(&hStdinRead, &hStdinWrite, &saAttr, 0)) {
        std::cout << "CreatePipeInp failed (error code:" << GetLastError() << ")" << std::endl;
        return false;
    }
    // Создание канала для стандартного вывода
    if (!CreatePipe(&hStdoutRead, &hStdoutWrite, &saAttr, 0)) {
        std::cout << "CreatePipeOut failed (error code:" << GetLastError() << ")" << std::endl;
        return false;
    }
    // Создание канала для стандартного вывода ошибки
    if(!CreatePipe(&hStderrRead,&hStderrWrite,&saAttr,0))
    {
        std::cout << "CreatePipeErr failed (error code:" << GetLastError() << ")" << std::endl;
        return false;
    }
    // Задание дескрипторов файловых потоков для стандартного ввода, вывода и ошибок нового процесса.
    si.hStdOutput = hStdoutWrite;       // Мне выводится, то что пишет тот поток
    si.hStdInput = hStdinRead;          // я ввожу туда, где читает тот поток
    si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    si.dwFlags |= STARTF_USESTDHANDLES;
    // Запуск процесса
    if (!CreateProcessA
            (
                    "stockfish/stockfish-windows-x86-64-avx2.exe",   // the path
                    nullptr,                       // Command line
                    nullptr,                   // Process handle not inheritable
                    nullptr,                   // Thread handle not inheritable
                    TRUE,                  // Set handle inheritance to FALSE
                    CREATE_NO_WINDOW,             // Opens file in a separate console
                    nullptr,           // Use parent's environment block
                    nullptr,           // Use parent's starting directory
                    &si,            // Pointer to STARTUPINFO structure
                    &pi           // Pointer to PROCESS_INFORMATION structure
            )) {
        std::cout << "CreateProcess failed" << GetLastError() << std::endl;
        return false;
    }
    std::cout << "StockFish start" << std::endl;
    return true;
}
// Завершение работы Stockfish и освобождение занимаемых ресурсов
void StockFish::closeStockFish() const {
    if(WriteFile(hStdinWrite, "quit\n", 5,nullptr, nullptr))
        std::cout << "StockFish End" << std::endl;
    if(hStdinRead != nullptr) CloseHandle(hStdinRead);
    if(hStdinWrite != nullptr) CloseHandle(hStdinWrite);
    if(hStdoutRead != nullptr) CloseHandle(hStdoutRead);
    if(hStdoutWrite != nullptr) CloseHandle(hStdoutWrite);
    if(hStderrRead != nullptr) CloseHandle(hStderrRead);
    if(hStderrWrite != nullptr) CloseHandle(hStderrWrite);
    if(pi.hProcess != nullptr) CloseHandle(pi.hProcess);
    if(pi.hThread != nullptr) CloseHandle(pi.hThread);
}

void StockFish::sendStockFishCommand(std::string msg) const{
    msg += '\n';
    DWORD bytesWritten;
    if ( WriteFile(hStdinWrite,msg.c_str(),msg.length(),&bytesWritten,nullptr))
        std::cout << "msg: " << msg;
    else throw(Exception("Error send command StockFish", -4));
}


// Чтение вывода Stockfish
std::string StockFish::readStockFishOutput() const{
    // Время ожидания, пауза
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    DWORD bytesRead = 0;
    char buffer[2048];
    std::string str;
    // Чтение всего вывода в str
    do {
        if (!ReadFile(hStdoutRead, buffer, sizeof(buffer), &bytesRead, nullptr))
            throw (ExceptionStockFish("Error read StockFish output", -3));
        str += buffer;
    } while (sizeof(buffer)  == bytesRead);
    // Поиска подстроки bestmove
    int n = static_cast<int>(str.find("bestmove"));
    if (n == -1)    // Если подстрока не найдена
        throw (ExceptionStockFish("Error read StockFish output", -3));
    return str.substr(n+9,4); // Извлечение данных о ходе (e4e6)
}
// Деструктор
StockFish::~StockFish() {
    closeStockFish();
}

#endif
