#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>
#include <DHT.h>

#define DHTPIN 12     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino


//Right motor
int enableRightMotor=5; 
int rightMotorPin1=7;
int rightMotorPin2=8;

//Left motor
int enableLeftMotor=6;
int leftMotorPin1=9;
int leftMotorPin2=10;

int chk;
float hum; 
float temp; 

void setup()
{
  // put your setup code here, to run once:
  pinMode(enableRightMotor,OUTPUT);
  pinMode(rightMotorPin1,OUTPUT);
  pinMode(rightMotorPin2,OUTPUT);

  pinMode(enableLeftMotor,OUTPUT);
  pinMode(leftMotorPin1,OUTPUT);
  pinMode(leftMotorPin2,OUTPUT);
  Serial.begin(9600);
  dht.begin();
  rotateMotor(0,0);
  Dabble.begin(9600, 2, 3);

}



void loop()
{
  int rightMotorSpeed=0;
  int leftMotorSpeed=0;
  Dabble.processInput();
  if (GamePad.isUpPressed())
  {
    rightMotorSpeed = -150;//255
    leftMotorSpeed = 150;//255
  }

  if (GamePad.isDownPressed())
  {
    rightMotorSpeed = 150;//-255
    leftMotorSpeed = -150;//-255
  }

  if (GamePad.isLeftPressed())
  {
    rightMotorSpeed = -150;//255
    leftMotorSpeed = 100; // 50
  }

  if (GamePad.isRightPressed())
  {
    rightMotorSpeed = -100; // 50
    leftMotorSpeed = 150;//255
  }
  if (GamePad.isTrianglePressed())
  {
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    delay(1000);
   }

  rotateMotor(rightMotorSpeed, leftMotorSpeed);
}

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
  if (rightMotorSpeed < 0)
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,HIGH);
  }
  else if (rightMotorSpeed >= 0)
  {
    digitalWrite(rightMotorPin1,HIGH);
    digitalWrite(rightMotorPin2,LOW);
  }

  if (leftMotorSpeed < 0)
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,HIGH);
  }
  else if (leftMotorSpeed >= 0)
  {
    digitalWrite(leftMotorPin1,HIGH);
    digitalWrite(leftMotorPin2,LOW);
  }
  

  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));
}
