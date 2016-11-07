#include "DHT.h"

class Sensors {
  public:
    static void Init();
    //getters
    static String GetHumidity(DHT dht);
    static String GetTemperature(DHT dht);
    static String GetFlame();
    static String GetGroundHumidity();
    static String GetGasLevel();
    //watchers
    static void WatchFlame();
    static void WatchGasLevel();
    static void WatchTemperature(DHT dht);
};
