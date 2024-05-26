//
// Created by vorop on 12.12.2023.
//

#ifndef COURSEWORK_EXCEPTIONS_H
#define COURSEWORK_EXCEPTIONS_H
#include <exception>

class Exception : public std::exception{
protected:
    const char* message;                 // Сообщение ошибки
    int codeError;                       // Код ошибки
public:
    Exception(const char* msg, int codeError): message(msg), codeError(codeError){}
    Exception(): message("undefined"), codeError(0){}
    const char* what() const noexcept override { return message; }  // получить сообщение ошибки
    int code() const  {   return codeError;   }     // получить код ошибки
};

class ExceptionStockFish: public Exception{     // Ошибки "Stockfish"
public:
    ExceptionStockFish(const char* msg, int codeError): Exception(msg, codeError){}
};

class ExceptionFile : public Exception{         // Ошибки работы с файлами
public:
    ExceptionFile(const char* msg, int codeError): Exception(msg,codeError){}
};

class ExceptionDeque: public Exception{         // Ошибки дека
public:
    ExceptionDeque(const char* msg, int codeError): Exception(msg, codeError){}
};
#endif //COURSEWORK_EXCEPTIONS_H
