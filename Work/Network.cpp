//
// Created by bobr on 28/04/24.
//


#include "Network.h"
#define PORT 9999


#ifdef _WIN32

void *Network::establishConnectionHost(int& serverSocket, std::mutex& mutex, int& result) {
    sockaddr_in serveAddress{}, clientAddress{};
    int addrLen = sizeof(serveAddress);
    WSADATA wsaData;
    int iResult;

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed with error: " << iResult << std::endl;
        mutex.lock();
        result = 2;
        mutex.unlock();
        return nullptr;
    }

    if ((serverSocket = static_cast<int>(socket(AF_INET, SOCK_STREAM, 0))) == INVALID_SOCKET) {
        std::cerr << "Socket creation failed" << std::endl;
        mutex.lock();
        result = 2;
        mutex.unlock();
        return nullptr;
    }

    int optVal = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (const char *) &optVal, sizeof(optVal)) == SOCKET_ERROR) {
        std::cerr << "Error: Could not set SO_REUSEADDR option." << std::endl;
    }

    serveAddress.sin_family = AF_INET;
    serveAddress.sin_addr.s_addr = INADDR_ANY;
    serveAddress.sin_port = htons(PORT);  // 9999

    // Bind the socket to address and port
    if (bind(serverSocket, (struct sockaddr *) &serveAddress, sizeof(serveAddress)) == SOCKET_ERROR) {
        std::cerr << "Bind failed" << std::endl;
        mutex.lock();
        result = 2;
        mutex.unlock();
        return nullptr;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 1) == SOCKET_ERROR) {
        std::cerr << "Listen failed" << std::endl;
        mutex.lock();
        result = 2;
        mutex.unlock();
        return nullptr;
    }

    // Set the socket to non-blocking mode
    u_long mode = 1;
    if (ioctlsocket(serverSocket, FIONBIO, &mode) != NO_ERROR) {
        std::cerr << "Failed to set socket to non-blocking mode" << std::endl;
        mutex.lock();
        result = 2;
        mutex.unlock();
        return nullptr;
    }

    // Accept incoming connection
    std::cout << "wait connect\n";
    while ((this->clientSocket = static_cast<int>(accept(serverSocket, (struct sockaddr *) &clientAddress, (socklen_t *) &addrLen))) ==
           INVALID_SOCKET) {
        if (WSAGetLastError() == WSAEWOULDBLOCK) {
            std::this_thread::sleep_for(std::chrono::milliseconds(400));
            continue;
        } else {
            std::cerr << "Accept failed" << std::endl;
            mutex.lock();
            result = 2;
            mutex.unlock();
            WSACleanup();
            return nullptr;
        }
    }
    closesocket(serverSocket);

    mutex.lock();
    result = 1;
    mutex.unlock();
    mode = 0; // 0 для блокирующего режима
    ioctlsocket(this->clientSocket, FIONBIO, &mode);
    return nullptr;
}

std::string Network::getIpAddress() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    char hostname[256];
    gethostname(hostname, sizeof(hostname));

    addrinfo hints = {};
    hints.ai_family = AF_INET;  // AF_INET for IPv4
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    addrinfo *result;
    if (getaddrinfo(hostname, nullptr, &hints, &result) != 0) {
        WSACleanup();
        return "Undefined";
    }
    auto *socketAddr = reinterpret_cast<sockaddr_in *>(result->ai_addr);
    char ipStr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(socketAddr->sin_addr), ipStr, INET_ADDRSTRLEN);

    freeaddrinfo(result);
    WSACleanup();
    return strcmp(ipStr, "127.0.0.1") == 0 ? "No connection" : ipStr;
}

bool Network::establishConnectionClient(const std::string& ipAddress) {
    sockaddr_in serverAddress{};
    std::cout << ipAddress;
    fflush(stdout);
    // Инициализация Winsock
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed: " << iResult << std::endl;
        return false;
    }
    // Создание сокета
    if ((clientSocket = static_cast<int>(socket(AF_INET, SOCK_STREAM, 0))) == INVALID_SOCKET) {
        std::cerr << "Socket creation failed" << std::endl;
        WSACleanup();
        return false;
    }
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    inet_pton(AF_INET, ipAddress.c_str(), &serverAddress.sin_addr);

    struct timeval timeout{};
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    int optVal = 1;
    setsockopt(clientSocket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char *>(&optVal), sizeof(optVal));
    setsockopt(clientSocket, SOL_SOCKET, SO_SNDTIMEO, (char *) &timeout, sizeof(timeout));
    if ((clientSocket = static_cast<int>(socket(AF_INET, SOCK_STREAM, 0))) == INVALID_SOCKET) {
        std::cerr << "Socket creation failed" << std::endl;
        WSACleanup();
        return false;
    }

// Установка сокета в неблокирующий режим
    u_long mode = 1;
    if (ioctlsocket(clientSocket, FIONBIO, &mode) != NO_ERROR) {
        std::cerr << "Failed to set socket to non-blocking mode" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return false;
    }

// Попытка соединения с сервером
    int ret = connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
    if (ret == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK) {
        std::cerr << "Error connect" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return false;
    }

// Ожидание установки соединения
    fd_set write_fds;
    FD_ZERO(&write_fds);
    FD_SET(clientSocket, &write_fds);
    ret = select(clientSocket + 1, nullptr, &write_fds, nullptr, &timeout);
    if (ret <= 0) {
        std::cerr << "Error wait connect" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return false;
    }
    std::cout << "TRUE" << std::endl;
    mode = 0; // 0 для блокирующего режима
    ioctlsocket(this->clientSocket, FIONBIO, &mode);
    return true;
}

void Network::closeConnection() {
    shutdown(this->clientSocket,SD_BOTH);
    closesocket(this->clientSocket);
    std::cout << "ERRORCLOSE" << std::endl;
    if (threadId.joinable())
        threadId.join();
}

void Network::sendMsg(const std::string& msg) const {
    send(this->clientSocket, msg.c_str(), 100, 0);
}

char* Network::waitMsg(char* msg) const{
    ssize_t bytesReceived = recv(clientSocket, msg, 100, 0);
    std::cout << "Before IF" << std::endl;
    if (bytesReceived == 0 || bytesReceived < 0){
        std::cerr << "Error receiving data" << std::endl;
        strcpy(msg, "Exit");
        return msg;      // Считаю что игрок вышел и == победе
    }
    std::cout << "MSG GET: ";
    std::cout << msg;
    return msg;
}
#endif

#ifdef __linux__
#include <arpa/inet.h>
#include <sys/socket.h>
#include <csignal>
#include <cstring>

void *Network::establishConnectionHost(int& serverSocket,std::mutex& mutex, int& result) {
    sockaddr_in serveAddress{}, clientAddress{};
    int addrLen = sizeof(serveAddress);
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Socket creation failed" << std::endl;
        mutex.lock();
        result = 2;
        mutex.unlock();
    }
    int optVal = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &optVal, sizeof(optVal)) < 0) {
        std::cerr << "Error: Could not set SO_REUSEADDR option." << std::endl;
    }
    serveAddress.sin_family = AF_INET;
    serveAddress.sin_addr.s_addr = INADDR_ANY;
    serveAddress.sin_port = htons(PORT);  // 9999
    // Привязка сокета к адресу и порту
    if (bind(serverSocket, (struct sockaddr *) &serveAddress, sizeof(serveAddress)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        mutex.lock();
        result = 2;
        mutex.unlock();
    }
    // Слушаем входящие соединения
    if (listen(serverSocket, 1) < 0) {
        std::cerr << "Listen failed" << std::endl;
        mutex.lock();
        result = 2;
        mutex.unlock();
    }
    int flags = fcntl(serverSocket, F_GETFL, 0);
    fcntl(serverSocket, F_SETFL, flags | O_NONBLOCK);
    // Принимаем входящее соединение
    while ((this->clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, (socklen_t *) &addrLen)) == -1) {
        if (errno == EBADF) {
            mutex.lock();
            result = 2;
            mutex.unlock();
            pthread_exit(nullptr);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }

    close(serverSocket);
    mutex.lock();
    result = 1;
    mutex.unlock();
    pthread_exit(nullptr);
}

//std::string Network::getIpAddress() {
//    std::string ipAddress;
//    system("hostname -I > tmp.txt");
//    std::ifstream file("tmp.txt");
//    std::getline(file, ipAddress);
//    file.close();
//    std::cout << ipAddress << std::endl << std::endl;
//    std::string firstIpAddress;
//    for(int i = 0; i < ipAddress.length(); i++)
//        if (ipAddress[i] == ' ') {
//            firstIpAddress = ipAddress.substr(0, i);
//            break;
//        }
//    remove("tmp.txt");
//    return firstIpAddress;
//}
#include <ifaddrs.h>
#include <arpa/inet.h>

std::string Network::getIpAddress() {
    std::string ipAddress;
    struct ifaddrs *ifAddr,* ifAddrTmp;
    struct sockaddr_in *addr;
    char addrStr[INET_ADDRSTRLEN];

    if (getifaddrs(&ifAddr) == 0) {
        ifAddrTmp = ifAddr;
        while (ifAddrTmp != nullptr) {
            if (ifAddrTmp->ifa_addr->sa_family == AF_INET) {
                addr = (struct sockaddr_in *) ifAddrTmp->ifa_addr;
                inet_ntop(AF_INET, &addr->sin_addr, addrStr, INET_ADDRSTRLEN);
                ipAddress = addrStr;
                if (ipAddress != "127.0.0.1"){
                    freeifaddrs(ifAddr);
                    return ipAddress;
                }
            }
            ifAddrTmp = ifAddrTmp->ifa_next;
        }
        freeifaddrs(ifAddr);
    } else {
        std::cerr << "Error getting IP address" << std::endl;
        return "Undefined";
    }
    return "No connection";
}

bool Network::establishConnectionClient(const std::string& ipAddress) {
    sockaddr_in serverAddress{};
    std::cout << ipAddress;
    fflush(stdout);
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation failed" << std::endl;
        return false;
    }
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    if (inet_pton(AF_INET, ipAddress.c_str(), &serverAddress.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return false;
    }
    struct timeval timeout{};
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    int optVal = 1;
    setsockopt(clientSocket, SOL_SOCKET, SO_REUSEADDR, &optVal, sizeof(optVal));
    setsockopt(clientSocket, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout));

    int ret = connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if (ret < 0 && errno != EINPROGRESS) {
        perror("Ошибка при попытке подключения");
        return false;
    }
    // Ожидание установки соединения
    fd_set write_fds;
    FD_ZERO(&write_fds);
    FD_SET(clientSocket, &write_fds);
    ret = select(clientSocket + 1, NULL, &write_fds, NULL, &timeout);
    if (ret <= 0) {
        perror("Ошибка при ожидании установки соединения");
        return false;
    }
    return true;
}

void Network::closeConnection() {
    shutdown(this->clientSocket, SHUT_RDWR);
    close(this->clientSocket);
    if (threadId.joinable())
        threadId.join();
}

void Network::sendMsg(const std::string& msg) const {
    send(this->clientSocket, msg.c_str(), 100, 0);
}

char* Network::waitMsg(char* msg) const{
    ssize_t bytesReceived = read(clientSocket, msg, 100);
    //    ssize_t bytesReceived = recv(network.getClientSocket(), msg, 100, 0);
    if (bytesReceived == 0 || bytesReceived == 1){
        std::cerr << "Error receiving data" << std::endl;
        strcpy(msg, "Exit");
        return msg;      // Считаю что игрок вышел и == победе
    }
    std::cout << "MSG GET: ";
    std::cout << msg;
    return msg;
}

#endif

