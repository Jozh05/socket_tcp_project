#include <gtest/gtest.h>
#include "../src/net/Socket.hpp"
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>

using net::Socket;

TEST(Socket, DefaultConstructor) {
    Socket s;
    EXPECT_EQ(s.getFd(), -1);
}

TEST(Socket, SendRecvRaw) {
    int fds[2];
    ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, fds), 0) << "socketpair failed";

    Socket a(fds[0]);
    Socket b(fds[1]);

    const char msg[] = "Hello";
    ssize_t sent = a.sendRaw(msg, sizeof(msg));
    EXPECT_EQ(sent, static_cast<ssize_t>(sizeof(msg)));

    char buf[16] = {0};
    ssize_t rec = b.recvRaw(buf, sizeof(msg));
    EXPECT_EQ(rec, static_cast<ssize_t>(sizeof(msg)));
    EXPECT_EQ(std::memcmp(buf, msg, sizeof(msg)), 0);
}

TEST(Socket, MoveConstructorAndAssignment) {
    int fds[2];
    ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, fds), 0) << "socketpair failed";

    Socket orig(fds[0]);
    Socket mc(std::move(orig));
    EXPECT_EQ(orig.getFd(), -1);
    EXPECT_GE(mc.getFd(), 0);

    Socket s2;
    s2 = std::move(mc);
    EXPECT_EQ(mc.getFd(), -1);
    EXPECT_GE(s2.getFd(), 0);
}

TEST(Socket, Close) {
    int fds[2];
    ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, fds), 0) << "socketpair failed";
    Socket s(fds[0]);
    EXPECT_GE(s.getFd(), 0);
    s.close();
    EXPECT_EQ(s.getFd(), -1);
    ::close(fds[1]);
}