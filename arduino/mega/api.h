class Api {
  public:
    static void Send404(EthernetClient client);
    static String GetStatus(EthernetClient client, DHT dht);
    static void ProcessURL(String httpReq, EthernetClient client, DHT dht);
    static void SetLeds(String httpReq);
};
