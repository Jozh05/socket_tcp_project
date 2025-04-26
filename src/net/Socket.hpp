#pragma once

#include <cstddef>
#include <unistd.h>

namespace net {

    class Socket {

    protected:
        int fd_;

    public:
        Socket() noexcept;
        explicit Socket(int fd) noexcept;
        virtual ~Socket() noexcept;

        Socket(const Socket&) = delete;
        Socket& operator = (const Socket&) = delete;

        Socket(Socket&& other) noexcept;
        Socket& operator = (Socket&& other) noexcept;

        int getFd() const noexcept;

        ssize_t sendRaw(const void* buf, size_t len) noexcept;

        ssize_t recvRaw(void* buf, size_t len) noexcept;

        void close() noexcept;
    };
}