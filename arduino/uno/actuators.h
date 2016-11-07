class Actuators {
  public:
    static void Init();
    //setters
    static void SetSpeaker(int speakerState);
    static void SetLed1(int led1State);
    static void SetLed2(int led2State);
    //getters
    static int GetIrrigationState();
};
