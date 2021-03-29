// ====================================================================================================================
// Libraries
// ====================================================================================================================

#include "arduino_secrets.h"
#include <Adafruit_SleepyDog.h>     //Needed to initiate reboots by the SAMD WatchDog 
#include "thingProperties.h"        //Arduino IoT Library
#include <WAA_Arduino_MKRENV.h>     //include <Arduino_MKRENV.h> from Andreas Waldherr
#include <Wire.h>                   //Needed to use the I²C Scanner

// ====================================================================================================================
// Variables
// ====================================================================================================================

// Timer for IoT Cloud Update
unsigned long previousMillisIOT = 0;
float intervalIOT = 1000;                               // IoT-Update interval = 1 seconds

// For battery measurements
int LiPo_BATTERY = A1;

// For the power management (Standby) 
unsigned long JustStarted_Timer = 42000;
int sleep_cycles = 52;
boolean sleep_now = false;

// Altitude (in metres) for the place where weather station is located. 
// Change the value based on yout own location
int altitude = 147;

// ====================================================================================================================
// Main SETUP
// ====================================================================================================================

void setup() {

  // Initialize the serial interface and wait for port to open:
  Serial.begin(38400);

  // Info if MKRENV failed to start  
  if (!ENV.begin()) {
    Serial.println("Failed to initialize MKR ENV shield!");
    while (1);
  }
  
  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  /*
  The following function allows you to obtain more information
  related to the state of network and IoT Cloud connection and errors
  the higher number the more granular information you’ll get.
  The default is 0 (only errors).
  Maximum is 4
  */
  setDebugMessageLevel(0);
  ArduinoCloud.printDebugInfo();

  // The MKR WAN 1310 3.3V reference voltage for battery measurements
  analogReference(AR_DEFAULT);

}

// ====================================================================================================================
// Main LOOP
// ====================================================================================================================

void loop() {
  
  // Timer for IoT Cloud Update
  unsigned long currentMillisIOT = millis();
  if (currentMillisIOT - previousMillisIOT >= intervalIOT) {
      previousMillisIOT = currentMillisIOT;
    
    // Get the MKRENV values 
    humidity = roundf(ENV.readHumidity() * 10) /10;
    lux = int(ENV.readIlluminance());
    pressure = int(ENV.readPressure(MILLIBAR_MSL, altitude));
    temperature = roundf(ENV.readTemperature(CELSIUS) * 10) /10;
    uvi = int(ENV.readUVIndex());
    uva = int(ENV.readUVA());
    uvb = int(ENV.readUVB());

    // read the input on analog pin 0 (A1) and calculate the voltage
    batterylevel = analogRead(LiPo_BATTERY) * 3.3f / 1023.0f / 1.2f * (1.2f+0.33f);

    // Send and get updates from the Arduino IoT Cloud
    ArduinoCloud.update();

  }
  
  // 42 seconds have past after MKR startup
  if (millis() > JustStarted_Timer) {
    sleep_now = true;
  }

  // Go to STANDBY Mode for 51 times 
  if (sleep_now == true) {
    for (int i = 0; i < sleep_cycles; i++) {
      Watchdog.sleep();                           // Enter the Standby Mode for 16,5 seconds (MKR WAN 1310 specific)
    }

    // Now restart the MKR
    int countdownMS = Watchdog.enable(100);      // WatchDog timeout in 0.1 seconds
    delay(countdownMS+1000);                     // Wait for 1.1 second!!!
    Watchdog.disable();                          // The WatchDog WILL time out and therefore restart the CPU
  }
  
}
