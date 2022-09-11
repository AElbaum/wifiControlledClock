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

void C1()
{
  myservo.write(0);  // CW down shaft
  delay(1000);       // delay 1 second
  myservo.write(90); // stop
}

void C2()
{
  myservo.write(180); // CCW down shaft
  delay(1000);        // delay 1 second
  myservo.write(90);  // stop
}

void C3()
{
  myservo.write(0);  // CW down shaft
  delay(1000);       // delay 1 second
  myservo.write(90); // stop
  delay(1000);
  myservo.write(180); // CCW down shaft
  delay(1000);        // delay 1 second
  myservo.write(90);  // stop
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
            }
            if (header.indexOf("GET /C2/go") >= 0)
            {
              Serial.println("C2 Go");
              C2();
            }
            if (header.indexOf("GET /C3/go") >= 0)
            {
              Serial.println("C3 Go");
              C3();
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
            client.println("<p><a href=\"/C3/go\"><button class=\"button\">C3</button></a></p>");
            // if (currentScene=="0") {

            // } else {
            //   //client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
            // }

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