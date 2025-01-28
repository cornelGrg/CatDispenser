#ifndef CATDISPENSER_TIMER_H
#define CATDISPENSER_TIMER_H
#include "time.h"
#include <Arduino.h>

// Synchronization interval (e.g., every 12 hours)
extern unsigned int lastSyncTime;

// Initialize time synchronization with NTP
void initTime();

// Synchronize time with NTP
void syncTimeWithNTP();
void startWebServer();

// Get the current time as a formatted string
String getCurrentTime();

// Check if synchronization is due
bool isSyncDue(int lastSyncTime);

#endif