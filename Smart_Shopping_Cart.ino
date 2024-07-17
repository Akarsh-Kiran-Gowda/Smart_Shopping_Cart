#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266WebServer.h>
#include <LiquidCrystal_I2C.h>
#include<Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const char* ssid = "test";//Replace with your network SSID
const char* password = "12345678";//Replace with your network password

ESP8266WebServer server(80);

String page = "";
char input[12];
int count = 0;


int a;
int p1=0,p2=0,p3=0,p4=0;
int c1=0,c2=0,c3=0,c4=0;

double total = 0;
int count_prod = 0;
void setup()
{
  pinMode(D3,INPUT_PULLUP);
  pinMode(D4,OUTPUT);
  
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Wire.begin(D2, D1);
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("   WELCOME TO       ");
  lcd.setCursor(0, 1);
  lcd.print("   SMART CART       ");

  delay(2000);

  lcd.clear();

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connecting...  ");
  }
  Serial.print(WiFi.localIP());
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  delay(1000);
  
  lcd.setCursor(0, 0);
  lcd.print(" PLZ ADD ITEMS     ");
  lcd.setCursor(0, 1);
  lcd.print("    TO CART          ");

server.on("/", [](){
    String page = "<!DOCTYPE html>\
        <html>\
        <head>\
            <title>E Cart using IoT</title>\
            <style>\
                body {\
                    font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;\
                    background-color: #f0f0f0;\
                    margin: 0;\
                    padding: 0;\
                }\
                .container {\
                    max-width: 1200px;\
                    margin: 20px auto;\
                    padding: 20px;\
                    background-color: #fff;\
                    border-radius: 10px;\
                    box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);\
                }\
                h1 {\
                    text-align: center;\
                    color: #3498db;\
                }\
                table {\
                    width: 100%;\
                    border-collapse: collapse;\
                    margin-top: 20px;\
                }\
                th, td {\
                    padding: 12px;\
                    text-align: center;\
                    border-bottom: 1px solid #ddd;\
                }\
                th {\
                    background-color: #3498db;\
                    color: white;\
                }\
                input[type='button'] {\
                    display: block;\
                    margin: 20px auto;\
                    padding: 10px 20px;\
                    font-size: 16px;\
                    background-color: #3498db;\
                    color: white;\
                    border: none;\
                    border-radius: 5px;\
                    cursor: pointer;\
                    transition: background-color 0.3s;\
                }\
                input[type='button']:hover {\
                    background-color: #2980b9;\
                }\
            </style>\
        </head>\
        <body>\
            <div class='container'>\
                <h1>Smart Shopping Cart using IoT</h1>\
                <table>\
                    <thead>\
                        <tr>\
                            <th>ITEMS</th>\
                            <th>QUANTITY</th>\
                            <th>COST</th>\
                        </tr>\
                    </thead>\
                    <tbody>\
                        <tr>\
                            <td>Biscuit</td>\
                            <td>" + String(p1) + "</td>\
                            <td>" + String(c1) + "</td>\
                        </tr>\
                        <tr>\
                            <td>Soap</td>\
                            <td>" + String(p2) + "</td>\
                            <td>" + String(c2) + "</td>\
                        </tr>\
                        <tr>\
                            <td>Rice(1KG)</td>\
                            <td>" + String(p3) + "</td>\
                            <td>" + String(c3) + "</td>\
                        </tr>\
                        <tr>\
                            <td>Tea(50g)</td>\
                            <td>" + String(p4) + "</td>\
                            <td>" + String(c4) + "</td>\
                        </tr>\
                        <tr>\
                            <th>Grand Total</th>\
                            <th>" + String(count_prod) + "</th>\
                            <th>" + String(total) + "</th>\
                        </tr>\
                    </tbody>\
                </table>\
                <input type='button' name='Pay Now' value='Pay Now'>\
            </div>\
        </body>\
        </html>";
    
    server.send(200, "text/html", page);
});

server.begin();

}
void loop()
{
  int a=digitalRead(D3);
  if (Serial.available())
  {
    count = 0;
    while (Serial.available() && count < 12)
    {
      input[count] = Serial.read();
      count++;
      delay(5);
    }
    if (count == 12)
    {
      if ((strncmp(input, "3B00B6548A53", 12) == 0) && (a == 1))
      {
        lcd.setCursor(0, 0);
        lcd.print("Biscuit Added       ");
        lcd.setCursor(0, 1);
        lcd.print("Price(Rs):35.00      ");
        p1++;
        digitalWrite(D4,HIGH);
        delay(2000);
        total = total + 35.00;
        count_prod++;
        digitalWrite(D4,LOW);
        lcd.clear();
      }
      else if ((strncmp(input, "3B00B6548A53", 12) == 0) && (a == 0))
      {
        if(p1>0)
        {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Biscuit Removed!!!        ");
        digitalWrite(D4,HIGH);
        delay(2000);
        p1--;
        total = total - 35.00;
        count_prod--;
        lcd.clear();
        digitalWrite(D4,LOW);
        }
        else
        {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Not in cart!!!        ");
        digitalWrite(D4,HIGH);
        delay(2000);
        digitalWrite(D4,LOW);
        lcd.clear();
        }
      }
      else if ((strncmp(input, "3B00B6549A43", 12) == 0) && (a == 1))
      {
        lcd.setCursor(0, 0);
        lcd.print("Soap Added          ");
        lcd.setCursor(0, 1);
        lcd.print("Price(Rs):38.00         ");
        total = total + 38.00;
        digitalWrite(D4,HIGH);
        delay(2000);
        p2++;
        count_prod++;
        digitalWrite(D4,LOW);
        lcd.clear();
      }
      else if ((strncmp(input, "3B00B6549A43", 12) == 0) && (a == 0))
      {
         if(p2>0)
        {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Soap Removed!!!        ");
        digitalWrite(D4,HIGH);
        delay(2000);
        p2--;
        total = total - 38.00;
        count_prod--;
        lcd.clear();
        digitalWrite(D4,LOW);
        }
        else
        {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Not in cart!!!        ");
        digitalWrite(D4,HIGH);
        delay(2000);
        lcd.clear();
        digitalWrite(D4,LOW);
        }
      }
      else if ((strncmp(input, "3B00B6548950", 12) == 0) && (a == 1))
      {
        lcd.setCursor(0, 0);
        lcd.print("Rice(1KG) Added       ");
        lcd.setCursor(0, 1);
        lcd.print("Price(Rs):55.00      ");
        total = total + 55.00;
        digitalWrite(D4,HIGH);
        delay(2000);
        count_prod++;
        p3++;
        lcd.clear();
        digitalWrite(D4,LOW);
      }
      else if ((strncmp(input, "3B00B6548950", 12) == 0) && (a==0))
      {
        if(p3>0)
        {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Rice(1KG) Removed!!!        ");
        digitalWrite(D4,HIGH);
        delay(2000);
        total = total - 55.00;
        p3--;
        count_prod--;
        lcd.clear();
        digitalWrite(D4,LOW);
        }
        else
        {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Not in cart!!!        ");
        digitalWrite(D4,HIGH);
        delay(2000);
        lcd.clear();
        digitalWrite(D4,LOW);
        }
      }
      else if ((strncmp(input, "3B00B6547BA2", 12) == 0) && (a == 1))
      {
        lcd.setCursor(0, 0);
        lcd.print("Tea(50g) Added            ");
        lcd.setCursor(0, 1);
        lcd.print("Price(Rs):45.00        ");
        total = total + 45.00;
        count_prod++;
        digitalWrite(D4,HIGH);
        p4++;
        delay(2000);
        lcd.clear();
        digitalWrite(D4,LOW);
      }
      else if ((strncmp(input, "3B00B6547BA2", 12) == 0) && (a == 0))
      {
        if(p4>0)
        {
        lcd.clear();
        total = total - 45.00;
        lcd.setCursor(0, 0);
        count_prod--;
        p4--;
        lcd.print("Tea(50g) Removed!!!        ");
        digitalWrite(D4,HIGH);
        delay(2000);
        lcd.clear();
        digitalWrite(D4,LOW);
        }
        else
        {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Not in cart!!!        ");
        digitalWrite(D4,HIGH);
        delay(2000);
        lcd.clear();
        digitalWrite(D4,LOW);
        }
      }
      else if (strncmp(input, "3B00B6549940", 12) == 0)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Total Prod:");
        lcd.setCursor(11, 0);
        lcd.print(count_prod);
        lcd.setCursor(0, 1);
        lcd.print("Price:");
        lcd.setCursor(6, 1);
        lcd.print(total);
        
        digitalWrite(D4,HIGH);
        delay(2000);

        lcd.clear();
        digitalWrite(D5,LOW);
        lcd.setCursor(0, 0);
        lcd.print("   Thank you        ");
        lcd.setCursor(0, 1);
        lcd.print("  for Shopping        ");
        digitalWrite(D4,LOW);
      }
    }
    c1=p1*35.00;
    c2=p2*38.00;
    c3=p3*55.00;
    c4=p4*45.00;
  }
server.handleClient();
}