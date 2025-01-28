#include "timerSupport.h"

const char* ntpServer = "pool.ntp.org";
const short gmtOffsetSec = 3600;    // GMT+1
const short daylightOffsetSec = 3600;
// Synchronization interval (e.g., every 12 hours)
const unsigned int syncInterval = 6 * 60 * 60 * 1000;  // 6 hours in ms

void initTime() {
    configTime(gmtOffsetSec, daylightOffsetSec, ntpServer);
    Serial.println("Time synchronization initialized");
}

void syncTimeWithNTP() {
    // Synchronize time with NTP server
    initTime();
    // Verify synchronization
    struct tm timeinfo;
    if (getLocalTime(&timeinfo)) {
        Serial.println("Time synchronized successfully");
    } else {
        Serial.println("Failed to synchronize time");
    }
}

String getCurrentTime() {
    struct tm timeinfo;
    if (getLocalTime(&timeinfo)) {
        char buffer[64];
        strftime(buffer, sizeof(buffer), "%H:%M:%S", &timeinfo);
        return String(buffer);
    } else {
        return "Time not available";
    }
}

bool isSyncDue(int lastSyncTime) {
    return (millis() - lastSyncTime >= syncInterval);
}