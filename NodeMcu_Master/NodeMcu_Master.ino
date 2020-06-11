#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
WiFiClient client;
WiFiServer server(80);
boolean connectWifi();

const char* ssid     = "TurkTelekom_T798A"; //enter your ssid/ wi-fi(case sensitive) router name - 2.4 Ghz only
const char* password = "9aZeEQfA";

String API = "F1BBQA33IPXL4O0O";
String HOST = "api.thingspeak.com";
String PORT = "80";

String field1 = "field1";
String field2 = "field2";
String field3 = "field3";
String field4 = "field4";
String field5 = "field5";
String field6 = "field6";


boolean wifiConnected = false;
String data = "";

String deneme;

void setup()
{
  Serial.begin(115200);
  Serial.begin(9600); /* begin serial for debug */
  Wire.begin(D1, D2);
  wifiConnected = connectWifi();
  server.begin();
  Serial.print("Kontrol edilmesi için girilmesi gerekilen URL: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {

    client = server.available();
    if (!client) return;
    data = checkClient();
    Serial.println(data);


          if (data.indexOf("connectOn") != -1)  {
            Serial.print("IP address: ");
            Serial.println(WiFi.localIP());
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("");
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("CONNECTED");
            client.println("</html>");
            client.stop();
          }
          else if (data.indexOf("connectOff") != -1)  {
            connectOff();
            Serial.print("IP address: ");
            Serial.println(WiFi.localIP());
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("");
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("CONNECTION OFF");
            client.println("</html>");
            client.stop();
          }
          else if (data.indexOf("up") != -1)  {
            Wire.beginTransmission(8);
            Wire.write("up"); 
            Wire.endTransmission(); 
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("");
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("İLERİ");
            client.println("</html>");
            client.stop();
          }
          else if (data.indexOf("down") != -1)  {
            Wire.beginTransmission(8); 
            Wire.write("down");  
            Wire.endTransmission();  
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("");
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("GERİ");
            client.println("</html>");
            client.stop();
          }
          else if (data.indexOf("leff") != -1)  {
            Wire.beginTransmission(8); 
            Wire.write("leff"); 
            Wire.endTransmission();   
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("");
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("SOL");
            client.println("</html>");
            client.stop();
          }
          else if (data.indexOf("right") != -1)  {
            Wire.beginTransmission(8);
            Wire.write("right"); 
            Wire.endTransmission();   
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("");
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("SAĞ");
            client.println("</html>");
            client.stop();
          }
          else if (data.indexOf("stop") != -1)  {
            Wire.beginTransmission(8); 
            Wire.write("stop"); 
            Wire.endTransmission();   
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("");
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("DUR");
            client.println("</html>");
            client.stop();
          }
         /* else if (data.indexOf("distance") != -1)  {
            Wire.beginTransmission(8); 
            Wire.write("stop");  
            Wire.endTransmission();   
        
            String distance = "";
            Wire.requestFrom(8, 13); 
            while (Wire.available()) {
              char c = Wire.read();
              Serial.print(c);
              distance = distance + c;
            }
            Serial.println();
            delay(1000);
        
          }
          else if (data.indexOf("temp_c") != -1)  {
            Wire.beginTransmission(8); 
            Wire.write("temp_c"); 
            Wire.endTransmission();   
        
            String temp_c = "";
            Wire.requestFrom(8, 13); 
            while (Wire.available()) {
              char c = Wire.read();
              Serial.print(c);
              temp_c = temp_c + c;
            }
            Serial.println();
            delay(1000);
          }
          else if (data.indexOf("temp_f") != -1)  {
            Wire.beginTransmission(8);
            Wire.write("temp_f");  
            Wire.endTransmission();   
        
            String temp_f = "";
            Wire.requestFrom(8, 13); 
            while (Wire.available()) {
              char c = Wire.read();
              Serial.print(c);
              temp_f = temp_f + c;
            }
            Serial.println();
            delay(1000);
          }
          else if (data.indexOf("temp_k") != -1)  {
            Wire.beginTransmission(8); 
            Wire.write("temp_k");  
            Wire.endTransmission();   
        
            String temp_k = "";
            Wire.requestFrom(8, 13);
            while (Wire.available()) {
              char c = Wire.read();
              Serial.print(c);
              temp_k = temp_k + c;
            }
            Serial.println();
            delay(1000);
          }
          else if (data.indexOf("humidity") != -1)  {
            Wire.beginTransmission(8); 
            Wire.write("humidity");  
            Wire.endTransmission();  
        
            String _humidity = "";
            Wire.requestFrom(8, 13);
            while (Wire.available()) {
              char c = Wire.read();
              Serial.print(c);
              _humidity = _humidity + c;
            }
            Serial.println();
            delay(1000);
          }*/
          else if (data.indexOf("gas") != -1)  {
              Wire.beginTransmission(8); 
              Wire.write("gas"); 
              Wire.endTransmission();    
              client.println("HTTP/1.1 200 OK");
              client.println("Content-Type: text/html");
              client.println("");
              client.println("<!DOCTYPE HTML>");
              client.println("<html>");
              client.println("DUR");
              client.println("</html>");
              client.stop();
            }
             else if (data.indexOf("humudity") != -1)  {
              Wire.beginTransmission(8); 
              Wire.write("humudity"); 
              Wire.endTransmission();    
              client.println("HTTP/1.1 200 OK");
              client.println("Content-Type: text/html");
              client.println("");
              client.println("<!DOCTYPE HTML>");
              client.println("<html>");
              client.println("DUR");
              client.println("</html>");
              client.stop();
            }
             else if (data.indexOf("distance") != -1)  {
              Wire.beginTransmission(8); 
              Wire.write("distance"); 
              Wire.endTransmission();    
              client.println("HTTP/1.1 200 OK");
              client.println("Content-Type: text/html");
              client.println("");
              client.println("<!DOCTYPE HTML>");
              client.println("<html>");
              client.println("DUR");
              client.println("</html>");
              client.stop();
            }
}

void receiveDqata() {
  Wire.requestFrom(8, 13); /* request & read data of size 13 from slave */
  while (Wire.available()) {
    char c = Wire.read();
    Serial.print(c);
  }
  Serial.println();
  delay(1000);
}


boolean connectOff() {
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("DUR");
  client.println("</html>");
  client.stop();
}

// connect to wifi – returns true if successful or false if not
boolean  connectWifi() {
  boolean state = true;

  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting ...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 10) {
      state = false;
      break;
    }
    i++;
  }

  if (state) {
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("");
    Serial.println("Connection failed.");
  }

  return state;
}

String checkClient (void)
{
  while (!client.available()) delay(1);
  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  request.remove(request.length() - 9, 9);
  return request;
}
