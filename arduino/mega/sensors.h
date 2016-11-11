class Sensors {
  public:
    static void Init();
    //getters
    static int GetGasLevel();
    static int GetGasType();
    static int GetFlame();
    static float GetHumidity();
    static float GetTemperature();
    static float GetGroundHumidity();
    //watchers
    static void WatchFlame();
    static void WatchGasLevel();
    static void WatchTemperature();
};
