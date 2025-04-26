#pragma once

#include "Socket.hpp"
#include <string>

namespace net {

    class TcpClient : public Socket {

    public:
        TcpClient();
        explicit TcpClient(int fd) noexcept;
        ~TcpClient() noexcept;

        void connect(const std::string& host, uint16_t port);

        void sendString(const std::string& message);

        std::string recvLine();

        std::string recvBytes(size_t size);
    };
}