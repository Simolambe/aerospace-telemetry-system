#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>        // per sleep
#include <arpa/inet.h>     // per socket UDP
#include "telemetry.h"     // i pacchetti e la funzione telemetry_generate
#define SERVER_IP "127.0.0.1" // IP del receiver
#define SERVER_PORT 5000 // porta su cui il receiver ascolta
#define INTERVAL_MS 500 // intervallo tra pacchetti (500 ms)

int main() {
    int sock;
    struct sockaddr_in server_addr;
    TelemetryPacket pkt;

    // 1. Creazione socket UDP
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Errore creazione socket");
        return 1;
    }

    // 2. Configurazione indirizzo server
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    // 3. Loop di invio pacchetti
    while (1) {
        telemetry_generate(&pkt); // genera dati
        sendto(sock, &pkt, sizeof(pkt), 0,
               (struct sockaddr*)&server_addr, sizeof(server_addr));

        printf("Pacchetto %u inviato\n", pkt.packet_id);
        usleep(INTERVAL_MS * 1000); // pausa in microsecondi
    }

    close(sock);
    return 0;
}
