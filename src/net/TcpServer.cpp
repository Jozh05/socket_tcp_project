#include "TcpServer.hpp"
#include <netinet/in.h>
#include <stdexcept>

namespace net {

    TcpServer::TcpServer(uint16_t port, int backlog) : 
        listenSock_(::socket(AF_INET, SOCK_STREAM, 0)) 
    {
        if (listenSock_.getFd() < 0) {
            perror("socket");
            throw std::runtime_error("Failed to create listen socket");
        }

        int opt = 1;
        if (setsockopt(listenSock_.getFd(), SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
            perror("setsockopt");
            throw std::runtime_error("Failed to set SO_REUSEADDR");
        }

        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(port);

        if (bind(listenSock_.getFd(), reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
            perror("bind");
            throw std::runtime_error("Failed to bind listen socket");
        }
        if (listen(listenSock_.getFd(), backlog) < 0) {
            perror("listen");
            throw std::runtime_error("Failed to listen on socket");
        }
    }

    TcpServer::~TcpServer() noexcept = default;

    TcpClient TcpServer::accept() {
        sockaddr_in client_addr{};
        socklen_t len = sizeof(client_addr);
        int client_fd = ::accept(listenSock_.getFd(), reinterpret_cast<sockaddr*>(&client_addr), &len);
        if (client_fd < 0) {
            perror("accept");
            throw std::runtime_error("Failed to accept client");
        }
        return TcpClient(client_fd);
    }
}
