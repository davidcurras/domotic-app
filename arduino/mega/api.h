class Api {
  public:
    static void Send404(EthernetClient client);
    static void SendStatus(EthernetClient client, DHT dht);
    static void URL(String httpReq, EthernetClient client, DHT dht);
    static void SetLeds(String httpReq);
};
