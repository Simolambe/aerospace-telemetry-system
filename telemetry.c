#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include "telemetry.h"

static uint32_t packet_counter = 0;

// Funzione per ottenere timestamp in millisecondi
static uint64_t get_timestamp_ms(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

// Funzione principale per generare dati telemetry realistici
void telemetry_generate(TelemetryPacket *pkt) {
    // Contatori e valori precedenti statici
    static float prev_temperature = 25.0f;
    static float prev_pressure    = 1013.0f;
    static float prev_roll        = 0.0f;
    static float prev_pitch       = 0.0f;
    static float prev_yaw         = 0.0f;
    static float prev_airspeed    = 250.0f;
    static float prev_altitude    = 2000.0f;

    pkt->packet_id = packet_counter++;
    pkt->timestamp_ms = get_timestamp_ms();

    // --- Dati ambientali ---
    // Piccole variazioni rispetto al pacchetto precedente
    pkt->temperature_c = prev_temperature + ((rand() % 21 - 10) / 10.0f); // ±1°C
    if (pkt->temperature_c < -50.0f) pkt->temperature_c = -50.0f;
    if (pkt->temperature_c > 50.0f)  pkt->temperature_c = 50.0f;
    prev_temperature = pkt->temperature_c;

    pkt->pressure_hpa = prev_pressure + ((rand() % 21 - 10) / 10.0f); // ±1 hPa
    if (pkt->pressure_hpa < 900.0f) pkt->pressure_hpa = 900.0f;
    if (pkt->pressure_hpa > 1100.0f) pkt->pressure_hpa = 1100.0f;
    prev_pressure = pkt->pressure_hpa;

    // --- Assetto (gradi) ---

    // Roll
    pkt->roll_deg  = prev_roll  + ((rand() % 21 - 10) / 10.0f); // ±1°
    if (pkt->roll_deg < -60.0f) pkt->roll_deg = -60.0f;
    if (pkt->roll_deg > 60.0f)  pkt->roll_deg = 60.0f;

    // Pitch
    pkt->pitch_deg = prev_pitch + ((rand() % 21 - 10) / 10.0f); // ±1°
    if (pkt->pitch_deg < -20.0f) pkt->pitch_deg = -20.0f;
    if (pkt->pitch_deg > 20.0f)  pkt->pitch_deg = 20.0f;

    //Yaw
    pkt->yaw_deg   = prev_yaw   + ((rand() % 21 - 10) / 10.0f); // ±1°, può "girare" lentamente
    if (pkt->yaw_deg < 0) pkt->yaw_deg += 360.0f;
    if (pkt->yaw_deg >= 360.0f) pkt->yaw_deg -= 360.0f;

    prev_roll  = pkt->roll_deg;
    prev_pitch = pkt->pitch_deg;
    prev_yaw   = pkt->yaw_deg;

    // --- Dati di volo ---
    pkt->airspeed_mps = prev_airspeed + ((rand() % 21 - 10) / 10.0f); // ±1 m/s
    if (pkt->airspeed_mps < 0.0f) pkt->airspeed_mps = 0.0f; // non negativo
    prev_airspeed = pkt->airspeed_mps;

    pkt->altitude_m = prev_altitude + (rand() % 21 - 10); // ±10 m
    if (pkt->altitude_m < 0.0f) pkt->altitude_m = 0.0f;   // non sotto il suolo
    prev_altitude = pkt->altitude_m;
}
