#include "../net/TcpClient.hpp"
#include <iostream>


int main(int argc, char** argv) {
    
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <host> <port>" << std::endl;
        return 1;
    }

    std::string host = argv[1];
    uint16_t port = static_cast<uint16_t>(std::stoi(argv[2]));

    try {
        net::TcpClient client;
        client.connect(host, port);
        std::cout << "Connected to " << host << ":" << port << std::endl;

        std::string line;
        while (std::cout << ">" && std::getline(std::cin, line)) {
            if (line.empty())
                continue;
            client.sendString(line + "\n");
            std::string response = client.recvLine();
            if (response.empty()) {
                std::cerr << "Server is unavailable" << std::endl;
                break;
            }
            std::cout << "Server: " << response;
        }
    } catch (const std::exception& err) {
        std::cerr << "Client error: " << err.what() << std::endl;
        return 1;
    }
}