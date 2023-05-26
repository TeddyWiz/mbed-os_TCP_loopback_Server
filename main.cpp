#include "mbed.h"
#include "WIZnetInterface.h"

#define ECHO_SERVER_PORT   5005
// Network interface
//NetworkInterface *net;
WIZnetInterface net;
// Socket demo
int main() {
    int remaining;
    int rcount;
    char *p;
    char *buffer = new char[256];
    nsapi_size_or_error_t result;
    

    // Bring up the ethernet interface
    printf("Mbed OS Socket example\n");

#ifdef MBED_MAJOR_VERSION
    printf("Mbed OS version: %d.%d.%d\n\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
#endif
    net.init();
    result = net.connect();
    const char *ip = net.get_ip_address();
    const char *netmask = net.get_netmask();
    const char *gateway = net.get_gateway();
    printf("IP address: %s\n", ip ? ip : "None");
    printf("Netmask: %s\n", netmask ? netmask : "None");
    printf("Gateway: %s\n", gateway ? gateway : "None");

    TCPSocket socket;
    result = socket.open(&net);
    if (result != 0) {
        printf("Error! socket.open() returned: %d\n", result);
    }
    #if 1
    // Set local Port with ECHO_PORT
    socket.bind(ECHO_SERVER_PORT);

    // Can handle 1 simultaneous connection
    socket.listen(1);

    printf("\nTCP echo server started\n");
    while (true) {
        TCPSocket* client = socket.accept();

        SocketAddress client_addr;
        client->getpeername(&client_addr);
        printf("Client connected: %s\n", client_addr.get_ip_address());

        char buffer1[1024];
        int con_count = 0;
        while (true) {
            nsapi_size_or_error_t size = client->recv(buffer1, sizeof(buffer));
            #if 0
            if (size <= 0) {
                break;
            }
            #endif
            if (size > 0) {
                client->send(buffer1, size);
            }
            if(con_count > 10000)
                break;
            con_count++;
            
        }

        client->close();
        
        

        printf("Client disconnected\n");
    }
    delete[] buffer;
    #endif
}
