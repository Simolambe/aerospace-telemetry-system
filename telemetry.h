#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <stdint.h>

/*
 * Struttura del pacchetto di telemetria
 * Simula dati tipici di un sistema aerospace
 */
typedef struct {
    uint32_t packet_id;
    uint64_t timestamp_ms;

    float temperature_c;
    float pressure_hpa;

    float roll_deg;
    float pitch_deg;
    float yaw_deg;

    float airspeed_mps;
    float altitude_m;
} TelemetryPacket;

void telemetry_generate(TelemetryPacket *pkt);


#endif
