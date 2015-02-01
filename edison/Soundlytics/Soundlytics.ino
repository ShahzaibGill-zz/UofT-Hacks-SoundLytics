#include <SPI.h>
#include <WiFi.h>
#include <math.h>

byte id[6];

float temperature;
float resistance;

const int sound = A0;
const int light = A1;
const int temp = A2;
int soundval = 0;
float lightval = 0;
float tempval = 0;

char ssid[] = "AndroidAP-1137"; //  your network SSID (name) 
char pass[] = "justinpaulin";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
char server[] = "www.justinpaulin.com";
WiFiClient client;

void setup() {
  //Serial.begin(9600);
  
  if (WiFi.status() == WL_NO_SHIELD) {
    //Serial.println("WiFi shield not present"); 
    // don't continue:
    while(true);
  }
  //String fv = WiFi.firmwareVersion();
  //if( fv != "1.1.0" )
    //Serial.println("Please upgrade the firmware");
  
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) { 
    //Serial.print("Attempting to connect to SSID: ");
    //Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid, pass);
  
    // wait 10 seconds for connection:
    delay(5000);
  }
  
  WiFi.macAddress(id);
  
  //Serial.println("Connected to wifi");
  //printWifiStatus();
}

void loop() {
  soundval = analogRead(sound);
  lightval = analogRead(light);
  tempval = analogRead(temp);
  
  resistance = (float)(1023-tempval)*10000/tempval;
  temperature = 1/(log(resistance/10000)/3975+1/298.15)-273.15;
  tempval = temperature;
  
  lightval=(float)(1023-lightval)*10/lightval;

  /*Serial.print("sound = " );
  Serial.println(soundval);
  Serial.print("light = ");
  Serial.println(lightval);
  Serial.print("temp = ");
  Serial.println(tempval);*/
  
  client.stop();
  if (client.connect(server, 80)) {
  // Make a HTTP request:
    client.print("GET /demos/dev/soundlytics/servlet/postback.php?id=");
    client.print(id[5]);
    client.print(id[4]);
    client.print(id[3]);
    client.print(id[2]);
    client.print(id[1]);
    client.print(id[0]);
    client.print("&sound=");
    client.print(soundval);
    client.print("&light=");
    client.print(lightval);
    client.print("&temp=");
    client.print(tempval);
    client.println(" HTTP/1.1");
    client.println("Host: www.justinpaulin.com");
    client.println("User-Agent: IntelEdison/1.1");
    client.println("Connection: close");
    client.println();
  }
  
  /*while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }*/
  
  delay(5000);
  
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
