#include "powerSaving.h"

void EnablePowerSaving() {
    Serial.println("Enable power saving mode\n");

    setCpuFrequencyMhz(80);  // Reduce the CPU frequency to 80 MHz (default is 240 MHz)
    esp_wifi_set_ps(WIFI_PS_MIN_MODEM);  // Use minimum power save mode for Wi-Fi
    esp_wifi_set_max_tx_power(20);  // Default is 78 (units in 0.25 dBm steps, 20 = 5 dBm)

    Serial.println("Power consumption reduced: CPU at 80MHz, Wi-Fi in power save mode.");
}

void DisablePowerSaving() {
    Serial.println("Disable power saving mode\n");

    setCpuFrequencyMhz(240);
    esp_wifi_set_ps(WIFI_PS_NONE);
    esp_wifi_set_max_tx_power(78);  // Maximum power (19.5 dBm)

    Serial.println("System restored: CPU at 240MHz, peripherals enabled, Wi-Fi at full power.");
}