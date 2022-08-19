#include <ESP8266WiFi.h>

const char *ssid = "SISTEMAS";
const char *password = "12345678";

IPAddress ip(192, 168, 0, 10);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

int led1 = 4; //D2
int led2 = 5; //D1
int led3 = 0; //D3

WiFiServer server(80);

void setup()
{
  Serial.begin(115200); 
  delay(10);

  pinMode(led1, OUTPUT);   
  digitalWrite(led1, LOW); 

  pinMode(led2, OUTPUT);   
  digitalWrite(led2, LOW); 

  pinMode(led3, OUTPUT);   
  digitalWrite(led3, LOW);

  Serial.println();
  Serial.println();
  Serial.print("INICIANDO :");
  Serial.println(ssid);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  WiFi.printDiag(Serial);

  server.begin();
  Serial.println("SERVIDOR INICIADO ");

  Serial.print("URL DEL ESP : ");
  Serial.print("http://");
  Serial.print(WiFi.softAPIP());
  Serial.println("/");
}

void loop()
{
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }

  Serial.println("Nuevo cliente"); 
  while (!client.available())
  { 
    delay(1);
  }

  String request = client.readStringUntil('\r');
  Serial.println(request); 
  client.flush();          

  if (request.indexOf("/LED1=OFF") != -1)
  {
    digitalWrite(led1, LOW);
  }
  if (request.indexOf("/LED1=ON") != -1)
  {
    digitalWrite(led1, HIGH);
  }

  if (request.indexOf("/LED2=OFF") != -1)
  {
    digitalWrite(led2, LOW);
  }
  if (request.indexOf("/LED2=ON") != -1)
  {
    digitalWrite(led2, HIGH);
  }

  if (request.indexOf("/LED3=OFF") != -1)
  {
    digitalWrite(led3, LOW);
  }
  if (request.indexOf("/LED3=ON") != -1)
  {
    digitalWrite(led3, HIGH);
  }


  client.println("HTTP/1.1 200 OK");         
  client.println("Content-Type: text/html"); 
  client.println("");                        
  client.println("<!DOCTYPE HTML>");         
  client.println("<html lang=\"en\">");
  client.println("<head>");
  client.println("<meta charset=\"UTF-8\">");
  client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"); 
  client.println("<title>Servidor Web ESP8266</title>");
  client.println("</head>");
  client.println("<body>");
  client.println("<br><br>");

  client.println("<h1 style=\"text-align: center;\">Encender y apagar LEDS</h1>");

  client.println("<p style=\"text-align: center;\">");

  client.println("<h3 style=\"text-align: center;\">LED 1</h3>");

  client.println("<button onclick=location.href=\"/LED1=ON\"> Encender LED </button> <br> <br>"); 
  client.println("<button onclick=location.href=\"/LED1=OFF\" >Apagar LED </button> <br> <br>");
  client.println("<h3 style=\"text-align: center;\">LED 2</h3>");

  client.println("<button onclick=location.href=\"/LED2=ON\"> Encender LED </button> <br> <br>"); 
  client.println("<button onclick=location.href=\"/LED2=OFF\" >Apagar LED </button> <br> <br>");

  client.println("<h3 style=\"text-align: center;\">LED 3</h3>");

  client.println("<button onclick=location.href=\"/LED3=ON\"> Encender LED </button> <br> <br>"); 
  client.println("<button onclick=location.href=\"/LED3=OFF\" >Apagar LED </button> <br> <br>");

  client.println("</p>");
  client.println("</body>");

  client.println("</html>"); 

  delay(1);
  Serial.println("Cliente desconectado"); 
  Serial.println("");
}
