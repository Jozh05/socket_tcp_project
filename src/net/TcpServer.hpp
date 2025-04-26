#pragma once

#include "TcpClient.hpp"
#include <cstdint>


namespace net {

    class TcpServer {
    
    private:
        Socket listenSock_;

    public:
        explicit TcpServer(uint16_t port, int backlog = 5);
        ~TcpServer() noexcept;
        TcpClient accept();
    };
}