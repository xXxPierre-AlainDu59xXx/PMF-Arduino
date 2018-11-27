#define ThermistorPIN 0// Analog Pin 0 
#include <math.h>

long Resistance ; 
int analogPin = 0;     // potentiometer wiper (middle terminal) connected to analog pin 3
                       // outside leads to ground and +5V
int val = 0;           // variable to store the value read

double Thermistor(int RawADC) {
  double temp;
  Resistance = 10000.0/(1023.0/RawADC - 1);
  temp = log(Resistance); //Finds the log of Resistance
  temp = 1 / (0.001125294 + (0.000234715 + (0.0000000856502 * temp * temp ))* temp); //Transforms temp to Kelvin
  temp = temp - 273.15; //Transforms temp to Celsius
  return temp;
 };



void setup()
{
  Serial.begin(115200);
}

void loop()
{
  Serial.print("Humidity: ");
  Serial.println(analogRead(5)); //display humidity
  Serial.print("Temperature: ");
  Serial.println(int(Thermistor(analogRead(ThermistorPIN))));  // display Celsius
  delay(100);
}
