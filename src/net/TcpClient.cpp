#include "TcpClient.hpp"
#include <arpa/inet.h>
#include <netdb.h>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <cstdio>

namespace net {

    TcpClient::TcpClient() : Socket(::socket(AF_INET, SOCK_STREAM, 0)){

        if (getFd() < 0) {
            perror("socket");
            throw std::runtime_error("Failed to create socket");
        }
    }

    TcpClient::TcpClient(int fd) noexcept : Socket(fd)  {}

    TcpClient::~TcpClient() noexcept = default;

    void TcpClient::connect(const std::string& host, uint16_t port) {
        sockaddr_in serv_addr{};
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);

        if (::inet_pton(AF_INET, host.c_str(), &serv_addr.sin_addr) <= 0) {
            throw std::invalid_argument("Invalid host IP: " + host);
        }

        if (::connect(getFd(), reinterpret_cast<sockaddr*>(&serv_addr), sizeof(serv_addr)) < 0) {
            perror("connect");
            throw std::runtime_error("Failed to connect to " + host + ":" + std::to_string(port));
        }
    }

    void TcpClient::sendString(const std::string& message) {
        
        size_t total = 0;
        const char* data = message.data();
        size_t len = message.size();
        
        while(total < len) {
            ssize_t sent = sendRaw(data + total, len - total);
            if (sent <= 0) {
                perror("send");
                throw std::runtime_error("Failed to send data");
            }
            total += static_cast<size_t>(sent);
        }
    }

    std::string TcpClient::recvLine() {
        
        std::string line;
        char ch;

        while (true) {
            ssize_t n = recvRaw(&ch, 1);

            if (n < 0) {
                perror("recv");
                throw std::runtime_error("Error on recvLine");
            }

            if (n == 0)
                break;
            line.push_back(ch);
            if (ch == '\n')
                break;
        }
        return line;
    }

    std::string TcpClient::recvBytes(size_t size) {
        std::vector<char> buf;
        size_t total = 0;
        while (total < size) {
            ssize_t n = recvRaw(buf.data() + total, size - total);
            if (n < 0) {
                perror("recv");
                throw std::runtime_error("Error on recvBytes");
            }
            if (n == 0) 
                break;
            total += static_cast<size_t>(n);
        }
        return std::string(buf.data(), total);
    }
    
}