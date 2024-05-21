//
// Created by bobr on 28/04/24.
//

#ifndef COURSEWORK_NETWORK_H
#define COURSEWORK_NETWORK_H
#include "Header.h"
#include <fstream>
#include <csignal>
#include <atomic>
#include <mutex>
#include <thread>

#ifdef _WIN32
//#include <winsock2.h>

#include <winsock.h>
#include <chrono>
#include <mutex>

#pragma comment(lib, "ws2_32.lib")
#endif

class Network {
private:
    NetworkClient typeClient{};
    std::thread threadId;
#ifdef _WIN32
    SOCKET clientSocket{};
#endif
#ifdef __linux__
    int clientSocket{};
#endif
public:
    void setTypeClient(NetworkClient client) {  typeClient = client;    }
    NetworkClient getTypeClient() const { return typeClient;      }
    std::thread& getThreadId() {    return threadId;    }

    static std::string getIpAddress();
    void* establishConnectionHost(int& serverSocket, std::mutex& mutex, int& result);
    bool establishConnectionClient(const std::string& ipAddress);
    void closeConnection();

    void sendMsg(const std::string& msg) const;
    char* waitMsg(char* msg) const;
};


#endif //COURSEWORK_NETWORK_H
