#ifndef CATDISPENSER_WEBSERVERSUPPORT_H
#define CATDISPENSER_WEBSERVERSUPPORT_H
#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <vector>
#include <cstring>
#include <HTTPClient.h>
#include <UrlEncode.h>
#include "stateMachine.h"


// Set web server port number to 80
extern float portionReading;
extern float dispenserReading;
volatile extern float portionSize;
//extern AsyncWebServer server;
volatile extern State_t currentState;
static String savedTimes;


void startWebServer();
void sendNotification(String message);
String processor(const String& var);
std::vector<String> splitString(const String &str, char delimiter);


#endif //CATDISPENSER_WEBSERVERSUPPORT_H
