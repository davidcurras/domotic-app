class Api {
  public:
    static void Send404(EthernetClient client);
    static String GetSensors();
    static String GetActuators();
    static String GetStatus(EthernetClient client);
    static void ProcessURL(String httpReq, EthernetClient client);
    static void SetLeds(String httpReq);
};
