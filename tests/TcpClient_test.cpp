#include <gtest/gtest.h>
#include "../src/net/TcpClient.hpp"
#include <sys/socket.h>
#include <unistd.h>
#include <string>

using net::TcpClient;

TEST(TcpClient, SendStringWritesAllBytes) {
    int fds[2];
    ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, fds), 0) << "socketpair failed";

    TcpClient client(fds[0]);

    const std::string msg = "TestMessage";
    client.sendString(msg);

    char buf[256] = {0};
    ssize_t n = ::read(fds[1], buf, msg.size());
    EXPECT_EQ(n, static_cast<ssize_t>(msg.size()));
    EXPECT_EQ(std::string(buf, n), msg);

    close(fds[1]);
}

TEST(TcpClient, RecvLineStopsAtNewline) {
    int fds[2];
    ASSERT_EQ(socketpair(AF_UNIX, SOCK_STREAM, 0, fds), 0);

    TcpClient client(fds[0]);

    const std::string payload = "Line1\nLine2\n";
    ::write(fds[1], payload.data(), payload.size());

    std::string line1 = client.recvLine();
    EXPECT_EQ(line1, "Line1\n");

    std::string line2 = client.recvLine();
    EXPECT_EQ(line2, "Line2\n");

    close(fds[1]);
}
