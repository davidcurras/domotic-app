class Sensors {
  public:
    static void Init();
    //getters
    static int GetGroundHumidity();
    //watchers
    static void WatchLight();
    static void WatchPIR1();
    static void WatchPIR2();
};
