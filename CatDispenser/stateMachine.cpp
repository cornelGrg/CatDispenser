#include "stateMachine.h"

unsigned int lastSyncTime = 0;
StateMachine_t StateMachine[] = {
        {INIT, fn_StateINIT},
        {STAND_BY, fn_StateSTANDBY},
        {DISPENSE, fn_StateDISPENSE},
        {REFILL, fn_StateREFILL},
};

void fn_StateINIT(){

    Serial.println("State: INIT \n");
    //init scale values and update for the first time
    //update reading values
    dispenserReading = 150;  //update with real values!!!
    portionReading = 30;
//    portionReading = scale_portion.get_units(10);
//    dispenserReading = scale_dispenser.get_units(10);

    lastReturnedSlot = "";

    //wait until portion size and dispense time slots are set for the first time (show notification on web server)
    while((portionSize == 0.0 || sizeof(portionSize) != sizeof(float)) || dispenseTimes[0]=="") { //PERFORM INPUT SANITATION AND CHECKS
        Serial.println("Insert valid parameters to start :)");
        delay(5000);
    }

    if (portionSize != 0.0){
        Serial.println("Portion Size --> " + String(portionSize));
    }else{
        Serial.println("Invalid input for portion size");
    }
//    Serial.println("dispensetime size= " + String(dispenseTimes.size()));
    if(dispenseTimes.size() != 0){
        Serial.println("Saved time slots:");
        for (auto &time : dispenseTimes) {
            Serial.print(time + " | ");
        }
        Serial.println();
    }else{
        Serial.println("Invalid input for dispense times");
    }

    if (portionSize > (dispenserReading - 0.1 * portionSize)){
        currentState = REFILL;
    }else{
        currentState = STAND_BY;
    }

}

void fn_StateSTANDBY(){
    //update reading values
    Serial.println("State: STANDBY \n");
//    portionReading = scale_portion.get_units(10);
//    dispenserReading = scale_dispenser.get_units(10);

    if (isSyncDue(lastSyncTime)) { //checks if it's time to synchronize
        syncTimeWithNTP();
        lastSyncTime = millis();
    }
//    Serial.println(getCurrentTime());
    EnablePowerSaving(); //low power mode (lower CPU frequency)

    String nextSlot = getNextTimeSlot();
    Serial.println(getCurrentTime() + " ---> " + nextSlot);
    while (getCurrentTime() != nextSlot){
        if(currentState == INIT || currentState == DISPENSE){  //override standby for buttons
            return;
        }
    }
    DisablePowerSaving();

    //dispense after being woken up

    currentState = DISPENSE;
}

void fn_StateDISPENSE(){
    Serial.println("State: DISPENSE \n");
    //update scale values
//    portionReading = scale_portion.get_units(10);
//    dispenserReading = scale_dispenser.get_units(10);

    if (portionSize > (dispenserReading - 0.1 * portionSize)) {
        currentState = REFILL;
    }

    Serial.println("Currently dispensing... (5seconds) \n");
    //dispense();
    delay(5000);

    if (portionSize > (dispenserReading - 0.1 * portionSize)){
        currentState = REFILL;
    }else{
        currentState = STAND_BY;
    }

    if(dispenseTimes.size() == 2) { //delay for limit case of only one
        delay(60000);
    }
}

void fn_StateREFILL(){ //includes empty
    //update reading values
    sendNotification("Refill needed!");
    Serial.println("State: REFILL \n");
    events.send("REFILL", "alert", millis());
    //activate webserver allert to say that refill is needed
    Serial.println("Refill is needed, please refill dispenser! \n");
    EnablePowerSaving();

    while(portionSize > (dispenserReading - 0.1 * portionSize)){
        //dispenserReading = 75; //update reading (USE REAL VALUES!!!)
    //  dispenserReading = scale_dispenser.get_units(10);
        //FOR TESTING PURPOSES TO SIMULATE A REFILL
        delay(2000);
        dispenserReading = 200;
    }
    Serial.println("Refill has been performed!");
    DisablePowerSaving();
    events.send("HIDE", "alert", millis());

    currentState = STAND_BY;
}

void initDevices(){
    //configure servo motor
    servoInternal.attach(SERVO_INT_PIN);
    servoExternal.attach(SERVO_EXT_PIN);

    //configure vibration motor
    pinMode(VIBRATION_PIN, OUTPUT);

    //configure scale portion
    scale_portion.begin(LOADCELL_PORTION_DOUT_PIN, LOADCELL_PORTION_SCK_PIN);

     Serial.println("Calibrating portion scale \n");
     delay(1000);
//     calibrateScale(scale_portion);
     Serial.println("Portion scale calibrated! \n");

    //configure scale dispenser
    scale_dispenser.begin(LOADCELL_DISPENSER_DOUT_PIN, LOADCELL_DISPENSER_SCK_PIN);
    Serial.println("Calibrating dispenser scale \n");
    delay(1000);
//    calibrateScale(scale_dispenser);
    Serial.println("Dispenser scale calibrated! \n");

    scale_portion.tare();
    scale_dispenser.tare();
}

String getNextTimeSlot() {
//    lastReturnedSlot = ""; // static variable to store the last returned time slot
    struct tm timeinfo;

    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        return "00:00";
    }

    int currentHour = timeinfo.tm_hour;
    int currentMinute = timeinfo.tm_min;
    int currentSeconds = timeinfo.tm_sec;

    for (const String& timeSlot : dispenseTimes) {
        String hour = timeSlot.substring(0, 2);
        String minute = timeSlot.substring(3, 5);

        // Check if the time slot is valid and it's not the same as the last returned one
        if ((hour.toInt() > currentHour || (hour.toInt() == currentHour && minute.toInt() > currentMinute)) && timeSlot != lastReturnedSlot) {
            lastReturnedSlot = timeSlot; // Update the last returned slot
//            Serial.println("Next slot: " + hour + ":" + minute);
            return timeSlot; // Return the next valid time slot
        }
    }

    lastReturnedSlot = dispenseTimes[0]; // Update to the first slot for tomorrow if there are no more valid slots for today
    return dispenseTimes[0];
}

void dispense(){
    Serial.println("Dispensing...");
//digitalWrite(VIBRATION_PIN, HIGH);
    servoExternal.write(140); //open external servo
    String support_timer = getCurrentTime();
    float last_portionReading = portionReading;
    while(portionReading < portionSize - 3){  //estimate 3gr of stuck kibbles
        openServo(&servoInternal, 170, 2);
        openServo(&servoInternal, 30, 2);
        portionReading = scale_portion.get_units(10);
    }
    //digitalWrite(VIBRATION_PIN, LOW);
    servoExternal.write(180); //close external servo, maybe set to 190?

    dispenserReading = scale_dispenser.get_units(10);
}
