class Api {
  public:
    static void Send404(EthernetClient client);
    static void SendStatus(EthernetClient client, String data);
    static void SetLeds(String httpReq);
};
