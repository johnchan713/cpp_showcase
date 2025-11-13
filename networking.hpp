#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <format>

// Platform-specific socket headers
#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
    using socket_t = SOCKET;
    #define INVALID_SOCKET_VALUE INVALID_SOCKET
    #define CLOSE_SOCKET closesocket
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <netinet/in.h>
    #include <unistd.h>
    using socket_t = int;
    #define INVALID_SOCKET_VALUE -1
    #define CLOSE_SOCKET close
#endif

namespace cpp26_networking {

// ============================================================================
// SOCKET BASICS - Demonstrates basic socket creation and configuration
// ============================================================================
void demonstrate_socket_creation() {
    std::cout << "\n=== SOCKET CREATION ===\n";

#ifdef _WIN32
    // Windows requires WSA initialization
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cout << "WSAStartup failed: " << result << "\n";
        return;
    }
    std::cout << "WSA initialized\n";
#endif

    // Create a TCP socket (SOCK_STREAM)
    socket_t tcp_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (tcp_socket == INVALID_SOCKET_VALUE) {
        std::cout << "TCP socket creation failed\n";
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }
    std::cout << "TCP socket created successfully\n";

    // Create a UDP socket (SOCK_DGRAM)
    socket_t udp_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (udp_socket == INVALID_SOCKET_VALUE) {
        std::cout << "UDP socket creation failed\n";
        CLOSE_SOCKET(tcp_socket);
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }
    std::cout << "UDP socket created successfully\n";

    // Socket address family options:
    // - AF_INET: IPv4
    // - AF_INET6: IPv6
    // - AF_UNIX: Unix domain sockets (local IPC)

    // Socket types:
    // - SOCK_STREAM: TCP (connection-oriented, reliable)
    // - SOCK_DGRAM: UDP (connectionless, unreliable)
    // - SOCK_RAW: Raw IP packets

    std::cout << "Socket parameters:\n";
    std::cout << "  AF_INET = IPv4 addressing\n";
    std::cout << "  SOCK_STREAM = TCP (reliable, connection-oriented)\n";
    std::cout << "  SOCK_DGRAM = UDP (fast, connectionless)\n";

    // Close sockets
    CLOSE_SOCKET(tcp_socket);
    CLOSE_SOCKET(udp_socket);
    std::cout << "Sockets closed\n";

#ifdef _WIN32
    WSACleanup();
    std::cout << "WSA cleanup complete\n";
#endif
}

// ============================================================================
// SOCKET ADDRESS - Demonstrates sockaddr_in structure
// ============================================================================
void demonstrate_socket_address() {
    std::cout << "\n=== SOCKET ADDRESS (sockaddr_in) ===\n";

    // IPv4 socket address structure
    struct sockaddr_in server_addr;

    // Zero out the structure
    std::memset(&server_addr, 0, sizeof(server_addr));

    // Set address family to IPv4
    server_addr.sin_family = AF_INET;

    // Set port (convert to network byte order with htons)
    server_addr.sin_port = htons(8080);

    // Set IP address
    // INADDR_ANY = 0.0.0.0 (bind to all interfaces)
    server_addr.sin_addr.s_addr = INADDR_ANY;

    std::cout << "Socket address structure:\n";
    std::cout << "  Family: AF_INET (IPv4)\n";
    std::cout << "  Port: 8080 (network byte order: " << ntohs(server_addr.sin_port) << ")\n";
    std::cout << "  Address: INADDR_ANY (0.0.0.0)\n";

    // Specific IP address example
    struct sockaddr_in client_addr;
    std::memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(3000);

    // Convert IP string to binary form
    const char* ip = "127.0.0.1";
    if (inet_pton(AF_INET, ip, &client_addr.sin_addr) <= 0) {
        std::cout << "Invalid IP address\n";
        return;
    }

    std::cout << "\nClient address:\n";
    std::cout << "  Port: 3000\n";
    std::cout << "  Address: " << ip << " (localhost)\n";

    // Convert back to string
    char ip_str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_addr.sin_addr, ip_str, INET_ADDRSTRLEN);
    std::cout << "  Converted back: " << ip_str << "\n";
}

// ============================================================================
// SOCKET OPTIONS - Demonstrates setsockopt and getsockopt
// ============================================================================
void demonstrate_socket_options() {
    std::cout << "\n=== SOCKET OPTIONS ===\n";

#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

    socket_t sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET_VALUE) {
        std::cout << "Socket creation failed\n";
#ifdef _WIN32
        WSACleanup();
#endif
        return;
    }

    // SO_REUSEADDR - allows reusing address/port
    int reuse = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
                   reinterpret_cast<char*>(&reuse), sizeof(reuse)) == 0) {
        std::cout << "SO_REUSEADDR enabled\n";
    }

    // SO_KEEPALIVE - enables TCP keepalive
    int keepalive = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE,
                   reinterpret_cast<char*>(&keepalive), sizeof(keepalive)) == 0) {
        std::cout << "SO_KEEPALIVE enabled\n";
    }

    // Get socket type
    int sock_type;
    socklen_t optlen = sizeof(sock_type);
    if (getsockopt(sock, SOL_SOCKET, SO_TYPE,
                   reinterpret_cast<char*>(&sock_type), &optlen) == 0) {
        std::cout << "Socket type: " << (sock_type == SOCK_STREAM ? "SOCK_STREAM (TCP)" : "Other") << "\n";
    }

    // SO_RCVBUF - receive buffer size
    int rcvbuf = 65536;
    setsockopt(sock, SOL_SOCKET, SO_RCVBUF,
               reinterpret_cast<char*>(&rcvbuf), sizeof(rcvbuf));
    std::cout << "Receive buffer set to 64KB\n";

    // SO_SNDBUF - send buffer size
    int sndbuf = 65536;
    setsockopt(sock, SOL_SOCKET, SO_SNDBUF,
               reinterpret_cast<char*>(&sndbuf), sizeof(sndbuf));
    std::cout << "Send buffer set to 64KB\n";

    std::cout << "\nCommon socket options:\n";
    std::cout << "  SO_REUSEADDR - Reuse address/port\n";
    std::cout << "  SO_KEEPALIVE - TCP keepalive\n";
    std::cout << "  SO_RCVBUF - Receive buffer size\n";
    std::cout << "  SO_SNDBUF - Send buffer size\n";
    std::cout << "  SO_BROADCAST - Allow broadcast\n";
    std::cout << "  SO_LINGER - Control connection close behavior\n";

    CLOSE_SOCKET(sock);
#ifdef _WIN32
    WSACleanup();
#endif
}

// ============================================================================
// SOCKET OPERATIONS - bind, listen, accept, connect
// ============================================================================
void demonstrate_socket_operations() {
    std::cout << "\n=== SOCKET OPERATIONS (Conceptual) ===\n";

    std::cout << "\nServer-side operations:\n";
    std::cout << "  1. socket()  - Create socket\n";
    std::cout << "  2. bind()    - Bind to address/port\n";
    std::cout << "  3. listen()  - Mark socket as passive (listening)\n";
    std::cout << "  4. accept()  - Accept incoming connections\n";
    std::cout << "  5. recv()    - Receive data\n";
    std::cout << "  6. send()    - Send data\n";
    std::cout << "  7. close()   - Close socket\n";

    std::cout << "\nClient-side operations:\n";
    std::cout << "  1. socket()  - Create socket\n";
    std::cout << "  2. connect() - Connect to server\n";
    std::cout << "  3. send()    - Send data\n";
    std::cout << "  4. recv()    - Receive data\n";
    std::cout << "  5. close()   - Close socket\n";

    std::cout << "\nUDP operations:\n";
    std::cout << "  1. socket()    - Create socket\n";
    std::cout << "  2. bind()      - Bind to address (receiver)\n";
    std::cout << "  3. sendto()    - Send data to specific address\n";
    std::cout << "  4. recvfrom()  - Receive data with sender address\n";
    std::cout << "  5. close()     - Close socket\n";

    // Demonstrate bind operation (conceptual)
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

    socket_t server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock != INVALID_SOCKET_VALUE) {
        struct sockaddr_in addr;
        std::memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(0);  // Let OS assign a port

        // Note: We won't actually bind to avoid conflicts
        std::cout << "\nBind example (not executed):\n";
        std::cout << "  bind(socket, (sockaddr*)&addr, sizeof(addr))\n";
        std::cout << "  Would bind to 0.0.0.0 on an OS-assigned port\n";

        CLOSE_SOCKET(server_sock);
    }

#ifdef _WIN32
    WSACleanup();
#endif
}

// ============================================================================
// BYTE ORDER - Network vs Host byte order
// ============================================================================
void demonstrate_byte_order() {
    std::cout << "\n=== BYTE ORDER (Network vs Host) ===\n";

    uint16_t host_port = 8080;
    uint16_t network_port = htons(host_port);

    std::cout << std::format("Host byte order port: {}\n", host_port);
    std::cout << std::format("Network byte order port: {}\n", network_port);
    std::cout << std::format("Converted back: {}\n", ntohs(network_port));

    uint32_t host_ip = 0x7F000001;  // 127.0.0.1
    uint32_t network_ip = htonl(host_ip);

    std::cout << std::format("\nHost byte order IP: 0x{:08X}\n", host_ip);
    std::cout << std::format("Network byte order IP: 0x{:08X}\n", network_ip);
    std::cout << std::format("Converted back: 0x{:08X}\n", ntohl(network_ip));

    std::cout << "\nByte order functions:\n";
    std::cout << "  htons() - Host to Network Short (16-bit)\n";
    std::cout << "  ntohs() - Network to Host Short (16-bit)\n";
    std::cout << "  htonl() - Host to Network Long (32-bit)\n";
    std::cout << "  ntohl() - Network to Host Long (32-bit)\n";

    std::cout << "\nWhy? Network byte order is Big Endian\n";
    std::cout << "Host byte order varies by architecture\n";
}

// ============================================================================
// Main demonstration function
// ============================================================================
void run_all_demos() {
    demonstrate_socket_creation();
    demonstrate_socket_address();
    demonstrate_socket_options();
    demonstrate_socket_operations();
    demonstrate_byte_order();
}

} // namespace cpp26_networking
