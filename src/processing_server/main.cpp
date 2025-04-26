#include "../net/TcpClient.hpp"
#include "../net/TcpServer.hpp"
#include "../processing/TextProcessor.hpp"
#include <iostream>

int main(int argc, char** argv) {
    
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <listen port> <display host> <display port>" << std::endl;
        return 2;
    }

    uint16_t listenPort = static_cast<uint16_t>(std::stoi(argv[1]));
    std::string displayHost = argv[2];
    uint16_t displayPort = static_cast<uint16_t>(std::stoi(argv[3]));

    try {
        net::TcpServer server(listenPort);
        std::cout << "Processing server listening on port " << listenPort << std::endl;

        net::TcpClient displayClient;
        displayClient.connect(displayHost, displayPort);

        while (true) {
            net::TcpClient incoming = server.accept();
            std::cout << "Client connected to processing server.\n";

            while (true) {
                std::string request = incoming.recvLine();
                if (request.empty()) {
                    std::cout << "Client disconnected.\n";
                    break;
                }
                std::cout << "Received: " << request;
                incoming.sendString("Recieved: " + request);
            
                std::string processed = processing::TextProcessor::process(request);
                displayClient.sendString(processed + '\n');
                std::cout << "Sent processed data to display server: " << processed << "\n";
            }
        }
    } catch (const std::exception& err) {
        std::cerr << "Processing server error: " << err.what() << std::endl;
        return 2;
    }
    
    return 0;
}