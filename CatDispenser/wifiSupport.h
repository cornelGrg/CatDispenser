#ifndef CATDISPENSER_WIFI_H
#define CATDISPENSER_WIFI_H
#include "WiFi.h"

void initWiFi(const char* ssid, const char* password);
void disconnectWiFi();

#endif