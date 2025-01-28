#ifndef CATDISPENSER_WEBSERVERSUPPORT_H
#define CATDISPENSER_WEBSERVERSUPPORT_H
#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Set web server port number to 80
//WiFiServer server(80);

void startWebServer();

#endif //CATDISPENSER_WEBSERVERSUPPORT_H
