#define ThermistorPIN 0// Analog Pin 0 
#include <DHT.h>
#include <math.h>

#define FRIDGE 5
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

long Resistance ; 
int analogPin = 0;     // potentiometer wiper (middle terminal) connected to analog pin 3
                       // outside leads to ground and +5V
int val = 0;           // variable to store the value read

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  dht.begin();
}

void loop()
{
  float humWhite = getInHumidity();
  float tempWhite = getInTemp();
  float tempSonde = float(getOutTemp(analogRead(ThermistorPIN)));
  
  Serial.print(humWhite); //display humidity
  Serial.print(";");
  
  Serial.print(tempWhite); //display humidity
  Serial.print(";");
  
  Serial.println(tempSonde);  // display Celsius

  /*------------------------*/

  if(tempWhite>=15)
    getCold();

  else
    stopCold();

  /*------------------------*/
  
  delay(1500);
}

void getCold()
{
  digitalWrite(FRIDGE, HIGH);
}

void stopCold()
{
  digitalWrite(FRIDGE, LOW);
}

double getInHumidity()
{
  // Reading humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float humidity = dht.readHumidity();

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity))
    Serial.println("Failed to read humidity from DHT sensor!");

  return humidity;
}

double getInTemp()
{
  // Reading temperature takes about 250 milliseconds!
  // Read temperature as Celsius
  float temperature = dht.readTemperature();
  
  if(isnan(temperature))
    Serial.println("Failed to read temperature from DHT sensor!");

  return temperature;
}

double getOutTemp(int RawADC)
{
  double temp;
  Resistance = 10000.0/(1023.0/RawADC - 1);
  temp = log(Resistance); //Finds the log of Resistance
  temp = 1 / (0.001125294 + (0.000234715 + (0.0000000856502 * temp * temp ))* temp); //Transforms temp to Kelvin
  temp = temp - 273.15; //Transforms temp to Celsius
  return temp;
}
