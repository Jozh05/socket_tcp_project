#include "Socket.hpp"

#include <sys/socket.h>
#include <utility>
#include <cerrno>
#include <cstdio>

namespace net {

    Socket::Socket() noexcept : fd_(-1){}

    Socket::Socket(int fd) noexcept : fd_(fd){}

    Socket::~Socket() noexcept {
        if (fd_ >= 0)
            ::close(fd_);
    }

    Socket::Socket(Socket&& other) noexcept : fd_(std::exchange(other.fd_, -1)) {}

    Socket& Socket::operator = (Socket&& other) noexcept {
        if (this != &other) {
            if (fd_ >= 0)
                ::close(fd_);
            fd_ = std::exchange(other.fd_, -1);
        }
        return *this;
    }

    int Socket::getFd() const noexcept {
        return fd_;
    }

    ssize_t Socket::sendRaw(const void* buf, size_t len) noexcept {
        return ::send(fd_, buf, len, 0);
    }

    ssize_t Socket::recvRaw(void* buf, size_t len) noexcept {
        return ::recv(fd_, buf, len, 0);
    }

    void Socket::close() noexcept {
        if (fd_ >= 0){
            ::close(fd_);
            fd_ = -1;
        }
    }
}