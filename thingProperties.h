#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

// Create a thing to Iot Cloud and insert the thing's ID to this variable
const char THING_ID[] = "ADD_YOUR_THING_ID_TO_THIS_VARIABLE";

const char APPEUI[]   = SECRET_APP_EUI;
const char APPKEY[]   = SECRET_APP_KEY;

CloudTemperatureSensor temperature;
float batterylevel;
float humidity;
int pressure;
int lux;
int uvi;
int uva;
int uvb;

void initProperties(){
  ArduinoCloud.setThingId(THING_ID);
  ArduinoCloud.addProperty(temperature, 1, READ, 15 * SECONDS, NULL);
  ArduinoCloud.addProperty(humidity, 2, READ, 15 * SECONDS, NULL);
  ArduinoCloud.addProperty(pressure, 3, READ, 15 * SECONDS, NULL);
  ArduinoCloud.addProperty(lux, 4, READ, 21 * SECONDS, NULL);
  ArduinoCloud.addProperty(uvi, 5, READ, 21 * SECONDS, NULL);
  ArduinoCloud.addProperty(uva, 6, READ, 21 * SECONDS, NULL);
  ArduinoCloud.addProperty(uvb, 7, READ, 21 * SECONDS, NULL);
  ArduinoCloud.addProperty(batterylevel, 8, READ, 21 * SECONDS, NULL);
}

LoRaConnectionHandler ArduinoIoTPreferredConnection(APPEUI, APPKEY);

