#include <WiFi.h>
#include <Servo.h>

Servo myservo; // create servo object to control a servo
// twelve servo objects can be created on most boards

// GPIO the servo is attached to
static const int servoPin = 15;

// Replace with your network credentials
const char *ssid = "Maverick";
const char *password = "unarmthawys3Jcq";

String currentScene = "0";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Decode HTTP GET value
String valueString = String(5);
int pos1 = 0;
int pos2 = 0;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;
// Speed can be 0-90, closer to zero the faster

int threemin = 110;
int onemin = 110/3l;

void tick(int time, int speed)
{
  myservo.write(speed); //forward
  delay(time); // time it is spinning
  myservo.write(90); // stop
}

void C1()
{
  tick(threemin,20); // tick quickly into 9:30
  delay(1100); // wait 1.1 second
  tick(threemin,20); // tick quickly into 9:30
  delay(1100); // wait 1.1 second
  tick(threemin,20); // tick quickly into 9:33
  delay(1100); // wait 1.1 second
  tick(threemin,20); // tick quickly into 9:36
}

void C2()
{
  tick(threemin,20); // tick quickly into 9:39
  delay(1100); // wait 1.1 second
  tick(threemin,20); // tick quickly into 9:42
  delay(1100); // wait 1.1 second
  tick(threemin,20); // tick quickly into 9:45
}

void C3()
{
  //Deleted
}

void C4()
{
  tick(900000,80);
}

void C5()
{
  //Deleted
}

void C6()
{
  tick(threemin,20); // tick quickly into 1323
  delay(1100); // wait 1.1 second
  tick(threemin,20); // tick quickly into 1326
  delay(1100); // wait 1.1 second
  tick(threemin,20); // tick quickly into 1329
  tick(7*60000,80);
}

void C7()
{
  tick(4*60000,80);
}

void C8()
{
  tick(threemin,20); // tick quickly into 1640
  delay(1100); // wait 1.1 second
  tick(threemin,20); // tick quickly into 1643
  delay(1100); // wait 1.1 second
  tick(threemin,20); // tick quickly into 1646
  delay(1100); // wait 1.1 second
  tick(threemin,20); // tick quickly into 1649
  tick(7*60000,80);
}

void C85()
{
  tick(15000,30);
}

void C9()
{
  tick(30000,0);
}

void C10()
{
  for (int i = 0; i < 60; i++)
  {
    tick(threemin,0);
    delay(1150);
  }
}

void C11()
{
  //Deleted
}

void C12()
{
  //Deleted
}

void C13()
{
  for (int i = 0; i < 100; i++)
  {
    tick(threemin,0);
    delay(1500);
  }
}

void C14()
{
  tick(onemin,20);
}

void C15()
{
  tick(onemin,20);
}

void C16()
{
  tick(onemin,20);
}

void C17()
{
  tick(onemin,20);
}

void C18()
{
  tick(onemin,20);
}

void C19()
{
  tick(5000,80);
}

void C20()
{
  tick(300000,0);
}

void forward()
{
  tick(50,30);
}

void backward()
{
  tick(50,180);
}

void stop()
{
  myservo.write(90);
}

void setup()
{
  Serial.begin(9600);

  myservo.attach(servoPin); // attaches the servo on the servoPin to the servo object

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop()
{
  WiFiClient client = server.available(); // Listen for incoming clients

  if (client)
  { // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client."); // print a message out in the serial port
    String currentLine = "";       // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime)
    { // loop while the client's connected
      currentTime = millis();
      if (client.available())
      {                         // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
        Serial.write(c);        // print it out the serial monitor
        header += c;
        if (c == '\n')
        { // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0)
          {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Sends command to spin servo
            if (header.indexOf("GET /C1/go") >= 0)
            {
              Serial.println("C1 Go");
              C1();
              currentScene = "1";
            }
            if (header.indexOf("GET /C2/go") >= 0)
            {
              Serial.println("C2 Go");
              C2();
              currentScene = "2";
            }
            if (header.indexOf("GET /C3/go") >= 0)
            {
              Serial.println("C3 Go");
              C3();
              currentScene = "3";
            }
            if (header.indexOf("GET /C4/go") >= 0)
            {
              Serial.println("C4 Go");
              C4();
              currentScene = "4";
            }
            if (header.indexOf("GET /C5/go") >= 0)
            {
              Serial.println("C5 Go");
              C5();
              currentScene = "5";
            }
            if (header.indexOf("GET /C6/go") >= 0)
            {
              Serial.println("C6 Go");
              C6();
              currentScene = "6";
            }
            if (header.indexOf("GET /C7/go") >= 0)
            {
              Serial.println("7 Go");
              C7();
              currentScene = "7";
            }
            if (header.indexOf("GET /C8/go") >= 0)
            {
              Serial.println("C8 Go");
              C8();
              currentScene = "8";
            }
            if (header.indexOf("GET /C85/go") >= 0)
            {
              Serial.println("C8.5 Go");
              C85();
              currentScene = "8.5";
            }
            if (header.indexOf("GET /C9/go") >= 0)
            {
              Serial.println("C9 Go");
              C9();
              currentScene = "9";
            }
            if (header.indexOf("GET /C10/go") >= 0)
            {
              Serial.println("C10 Go");
              C10();
              currentScene = "10";
            }
            if (header.indexOf("GET /C11/go") >= 0)
            {
              Serial.println("C11 Go");
              C11();
              currentScene = "C11";
            }
            if (header.indexOf("GET /C12/go") >= 0)
            {
              Serial.println("C12 Go");
              C12();
              currentScene = "C12";
            }
            if (header.indexOf("GET /C13/go") >= 0)
            {
              Serial.println("C13 Go");
              C13();
              currentScene = "C13";
            }
            if (header.indexOf("GET /C14/go") >= 0)
            {
              Serial.println("C14 Go");
              C14();
              currentScene = "C14";
            }
            if (header.indexOf("GET /C15/go") >= 0)
            {
              Serial.println("C15 Go");
              C15();
              currentScene = "C15";
            }
            if (header.indexOf("GET /C16/go") >= 0)
            {
              Serial.println("C16 Go");
              C16();
              currentScene = "C16";
            }
            if (header.indexOf("GET /C17/go") >= 0)
            {
              Serial.println("C17 Go");
              C17();
              currentScene = "C17";
            }
            if (header.indexOf("GET /C18/go") >= 0)
            {
              Serial.println("C18 Go");
              C18();
              currentScene = "C18";
            }
            if (header.indexOf("GET /C19/go") >= 0)
            {
              Serial.println("C19 Go");
              C19();
              currentScene = "C19";
            }
            if (header.indexOf("GET /C19/go") >= 0)
            {
              Serial.println("C19 Go");
              C19();
              currentScene = "C19";
            }
            if (header.indexOf("GET /C20/go") >= 0)
            {
              Serial.println("C20 Go");
              C20();
              currentScene = "C20";
            }



            if (header.indexOf("GET /forward") >= 0)
            {
              Serial.println("forward");
              forward();
            }
            if (header.indexOf("GET /backward") >= 0)
            {
              Serial.println("backward");
              backward();
            }
            if (header.indexOf("GET /stop") >= 0)
            {
              Serial.println("stop");
              stop();
              currentScene = "Stop";
            }

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>body { text-align: center; font-family: \"Trebuchet MS\", Arial; margin-left:auto; margin-right:auto;}");
            client.println(".slider { width: 300px; }</style>");
            client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");

            // Web Page
            client.println("</head><body><h1>Clock</h1>");
            client.println("<p>Current Scene " + currentScene + "</p>");
            // If the output26State is off, it displays the ON button
            client.println("<p><a href=\"/C1/go\"><button class=\"button\">C1</button></a></p>");
            client.println("<p><a href=\"/C2/go\"><button class=\"button\">C2</button></a></p>");
            //client.println("<p><a href=\"/C3/go\"><button class=\"button\">C3</button></a></p>");
            client.println("<p><a href=\"/C4/go\"><button class=\"button\">C4</button></a></p>");
            //client.println("<p><a href=\"/C5/go\"><button class=\"button\">C5</button></a></p>");
            client.println("<p><a href=\"/C6/go\"><button class=\"button\">C6</button></a></p>");
            client.println("<p><a href=\"/C7/go\"><button class=\"button\">C7</button></a></p>");
            client.println("<p><a href=\"/C8/go\"><button class=\"button\">C8</button></a></p>");
            client.println("<p><a href=\"/C85/go\"><button class=\"button\">C85</button></a></p>");
            client.println("<p><a href=\"/C9/go\"><button class=\"button\">C9</button></a></p>");
            client.println("<p><a href=\"/C10/go\"><button class=\"button\">C10</button></a></p>");
            //client.println("<p><a href=\"/C11/go\"><button class=\"button\">C11</button></a></p>");
            //client.println("<p><a href=\"/C12/go\"><button class=\"button\">C12</button></a></p>");
            client.println("<p><a href=\"/C13/go\"><button class=\"button\">C13</button></a></p>");
            client.println("<p><a href=\"/C14/go\"><button class=\"button\">C14</button></a></p>");
            client.println("<p><a href=\"/C15/go\"><button class=\"button\">C15</button></a></p>");
            client.println("<p><a href=\"/C16/go\"><button class=\"button\">C16</button></a></p>");
            client.println("<p><a href=\"/C17/go\"><button class=\"button\">C17</button></a></p>");
            client.println("<p><a href=\"/C18/go\"><button class=\"button\">C18</button></a></p>");
            client.println("<p><a href=\"/C19/go\"><button class=\"button\">C19</button></a></p>");
            client.println("<p><a href=\"/C20/go\"><button class=\"button\">C20</button></a></p>");

            client.println("<p><a href=\"/forward\"><button class=\"button\">Forward 50</button></a></p>");
            client.println("<p><a href=\"/backward\"><button class=\"button\">Backward 50</button></a></p>");
            client.println("<p><a href=\"/stop\"><button class=\"button\">Stop</button></a></p>");

            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          }
          else
          { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        }
        else if (c != '\r')
        {                   // if you got anything else but a carriage return character,
          currentLine += c; // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}