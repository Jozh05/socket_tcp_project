#include <gtest/gtest.h>
#include "../src/net/TcpServer.hpp"
#include "../src/net/TcpClient.hpp"
#include <thread>
#include <atomic>
#include <string>

using net::TcpServer;
using net::TcpClient;

TEST(TcpServer, AcceptAndEcho) {
    const uint16_t port = 33333;
    std::atomic<bool> ready{false};
    std::atomic<bool> done{false};

    // Запускаем сервер в отдельном потоке
    std::thread server_thread([&]() {
        try {
            TcpServer server(port);
            ready.store(true);
            // Ждём подключения одного клиента
            TcpClient client = server.accept();
            // Принимаем одну строку
            std::string msg = client.recvLine();
            // Отвечаем эхо
            client.sendString(msg);
        } catch (const std::exception& e) {
            ADD_FAILURE() << "Server exception: " << e.what();
        }
        done.store(true);
    });

    // Ждём, пока сервер начнёт слушать (таймаут 5 секунд)
    {
        auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
        while (!ready.load()) {
            if (std::chrono::steady_clock::now() > deadline) {
                FAIL() << "Server did not start within timeout";
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    // Подключаемся к серверу и отправляем тестовую строку
    TcpClient test_client;
    test_client.connect("127.0.0.1", port);
    const std::string send_str = "HelloServer\n";
    test_client.sendString(send_str);
    std::string resp = test_client.recvLine();
    EXPECT_EQ(resp, send_str);

    // Дожидаемся завершения потока сервера (таймаут 5 секунд)
    {
        auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(5);
        while (!done.load()) {
            if (std::chrono::steady_clock::now() > deadline) {
                FAIL() << "Server did not finish within timeout";
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    server_thread.join();
}