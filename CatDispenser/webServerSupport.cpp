#include "webServerSupport.h"

AsyncWebServer server(80);

//const char index_html[] PROGMEM = R"rawliteral(
//    <!DOCTYPE HTML><html>
//    <head>
//      <title>ESP Web Server</title>
//      <meta name="viewport" content="width=device-width, initial-scale=1">
//      <link rel="icon" href="data:,">
//      <style>
//        html {font-family: Arial; display: inline-block; text-align: center;}
//        h2 {font-size: 3.0rem;}
//        p {font-size: 3.0rem;}
//        body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
//        .switch {position: relative; display: inline-block; width: 120px; height: 68px}
//        .switch input {display: none}
//        .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 6px}
//        .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 3px}
//        input:checked+.slider {background-color: #b30000}
//        input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
//      </style>
//    </head>
//    <body>
//      <h2>ESP Web Server</h2>
//      %BUTTONPLACEHOLDER%
//    <script>function toggleCheckbox(element) {
//      var xhr = new XMLHttpRequest();
//      if(element.checked){ xhr.open("GET", "/update?output="+element.id+"&state=1", true); }
//      else { xhr.open("GET", "/update?output="+element.id+"&state=0", true); }
//      xhr.send();
//    }
//    </script>
//    </body>
//    </html>
//)rawliteral";

//String processor(const String& var){
//    //Serial.println(var);
//    if(var == "BUTTONPLACEHOLDER"){
//        String buttons = "";
//        buttons += "<h4>Output - GPIO 2</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"2\" ><span class=\"slider\"></span></label>";
//        buttons += "<h4>Output - GPIO 4</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"4\" ><span class=\"slider\"></span></label>";
//        buttons += "<h4>Output - GPIO 33</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"33\" ><span class=\"slider\"></span></label>";
//        return buttons;
//    }
//    return String();
//}

void startWebServer(){
//    WiFiClient client = server.available();   // Listen for incoming clients
//
//    if (client) {                             // If a new client connects,
//        currentTime = millis();
//        previousTime = currentTime;
//        Serial.println("New Client.");          // print a message out in the serial port
//        String currentLine = "";                // make a String to hold incoming data from the client
//        while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
//            currentTime = millis();
//            if (client.available()) {             // if there's bytes to read from the client,
//                char c = client.read();             // read a byte, then
//                Serial.write(c);                    // print it out the serial monitor
//                header += c;
//                if (c == '\n') {                    // if the byte is a newline character
//                    // if the current line is blank, you got two newline characters in a row.
//                    // that's the end of the client HTTP request, so send a response:
//                    if (currentLine.length() == 0) {
//                        // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
//                        // and a content-type so the client knows what's coming, then a blank line:
//                        client.println("HTTP/1.1 200 OK");
//                        client.println("Content-type:text/html");
//                        client.println("Connection: close");
//                        client.println();
//
//                        // Display the HTML web page
//                        client.println("<!DOCTYPE html><html>");
//                        client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
//                        client.println("<link rel=\"icon\" href=\"data:,\">");
//                        client.println("<meta http-equiv=\"refresh\" content=\"10\">");
//                        // CSS to style the on/off buttons
//                        // Feel free to change the background-color and font-size attributes to fit your preferences
//                        client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
//                        client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
//                        client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
//                        client.println(".button2 {background-color: #555555;}</style></head>");
//
//                        // Web Page Heading
//                        client.println("<body><h1>ESP32 Web Server</h1>");
//
//
//                        // Display current state, and ON/OFF buttons for GPIO 27
//                        client.println("Current time " + getCurrentTime() + "</p>");
//                        // If the output27State is off, it displays the ON button
//
//                        client.println("</body></html>");
//
//                        // The HTTP response ends with another blank line
//                        client.println();
//                        // Break out of the while loop
//                        break;
//                    } else { // if you got a newline, then clear currentLine
//                        currentLine = "";
//                    }
//                } else if (c != '\r') {  // if you got anything else but a carriage return character,
//                    currentLine += c;      // add it to the end of the currentLine
//                }
//            }
//        }
//        // Clear the header variable
//        header = "";
//        // Close the connection
//        client.stop();
//        Serial.println("Client disconnected.");
//        Serial.println("");
//    }

}

std::vector<String> splitString(const String &str, char delimiter) {
    std::vector<String> result;
    char buf[str.length() + 1];  // Create a modifiable char array
    str.toCharArray(buf, sizeof(buf));  // Convert String to char array

    char *token = strtok(buf, &delimiter);  // Get first token
    while (token != nullptr) {
        result.push_back(String(token));  // Convert token back to String and store
        token = strtok(nullptr, &delimiter);  // Get next token
    }

    return result;
}