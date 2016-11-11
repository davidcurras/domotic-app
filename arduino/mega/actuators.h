class Actuators {
  public:
    static void Init();
    //setters
    static void SetAutoFan(int fanState);
    static void SetIrrigation(int ledState);
    static void SetGasLed(int ledState);
    static void SetFireLed(int ledState);
    static void SetFan(int fanState);
    static void SetLight(int lightState);
    static void SetLed(int pin, int ledState);
    //getters
    static int GetAutoFan();
    static int GetIrrigation();
    static int GetGasLed();
    static int GetFireLed();
    static int GetFan();
    static int GetLight();
    static int GetLed(int pin);
};
