class Sensors {
  public:
    static void Init();
    //getters
    static int GetLight();
    static int GetPir1();
    static int GetPir2();
    //watchers
    static void WatchLight();
    static void WatchPIR1();
    static void WatchPIR2();
};
