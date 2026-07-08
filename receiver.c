#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "telemetry.h"

#define RECEIVER_PORT 5000

int main() {
    int sock;
    struct sockaddr_in receiver_addr;
    TelemetryPacket pkt;
    socklen_t addr_len = sizeof(receiver_addr);

    // 1. Creazione socket UDP
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Errore creazione socket");
        return 1;
    }

    // 2. Configurazione indirizzo locale
    memset(&receiver_addr, 0, sizeof(receiver_addr));
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(RECEIVER_PORT);
    receiver_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, (struct sockaddr*)&receiver_addr, sizeof(receiver_addr)) < 0) {
        perror("Errore bind");
        return 1;
    }

    printf("Receiver in ascolto sulla porta %d...\n", RECEIVER_PORT);

    // 3. Loop di ricezione pacchetti
    while (1) {
        ssize_t n = recvfrom(sock, &pkt, sizeof(pkt), 0,
                             (struct sockaddr*)&receiver_addr, &addr_len);
        if (n < 0) {
            perror("Errore recvfrom");
            continue;
        }

        printf("Pacchetto %u ricevuto: temp=%.2f°C, roll=%.2f°, pitch=%.2f°, yaw=%.2f°, alt=%.1fm, airspeed=%.1fm/s\n",
               pkt.packet_id,
               pkt.temperature_c,
               pkt.roll_deg,
               pkt.pitch_deg,
               pkt.yaw_deg,
               pkt.altitude_m,
               pkt.airspeed_mps);
    }

    close(sock);
    return 0;
}
