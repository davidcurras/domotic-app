class Actuators {
  public:
    static byte LEDS[5];
    static void Init();
    //setters
    static void SetLed(int index, int ledState);
    static void SetFan(int fanState);
    static void SetFireAlarm(int alarmState);
    static bool SetGas(int gasType);
    //getters
    static String GetIrrigationState();
    static String GetFanState();
    static String GetLedsState();
};
