class Actuators {
  public:
    static void Init();
    //setters
    static void SetSpeaker(int speakerState);
    static void SetLedLight(int ledLightState);
    static void SetLedPir(int ledPirState);
    //getters
    static int GetSpeaker();
    static int GetLedLight();
    static int GetLedPir();
};
