#include "../net/TcpServer.hpp"
#include "../net/TcpClient.hpp"
#include <iostream>

int main(int argc, char** argv) {
    
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <listen port>" << std::endl;
        return 1;
    }
    
    uint16_t port = static_cast<uint16_t>(std::stoi(argv[1]));

    try {
        net::TcpServer server(port);
        std::cout << "Display server listening on port " << port << std::endl;

        while (true) {
            net::TcpClient client = server.accept();
            std::cout << "Processing server connected" << std::endl;

            while (true) {
            
                std::string result = client.recvLine();
                if (result.empty()) {
                    std::cout << "Processing server disconnected" << std::endl;
                    break;
                }
                std::cout << "Processed result: " << result;
            }
        }
    } catch(const std::exception& err) {
        std::cerr << "Display server error: " << err.what() << "\n";
        return 1;
    }
    return 0;
}