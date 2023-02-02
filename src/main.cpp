#include <Arduino.h>

// https://github.com/contrem/arduino-timer
#include <arduino-timer.h>
#include <Wire.h>
#include "soil-mositure.h"

#define LIGHT_SENSE_PIN     A3
#define SOIL_MOIS_SENSE_PIN A0
#define SENSE_3V3_PIN       A2
#define UV_SENSE_PIN        A1

#define EN_SOIL_MOIS_PIN  3

#define RTC_ADDR  0b11011111

bool isSoilEn = false;

/********** Functional Prototypes **********/

// Soil Mositure Prototypes
void enable_soil_sense(void);
uint16_t measure_soil_sense(void);
void disable_soil_sense(void);

// Light Sensor
uint16_t measure_light(void);

//UV Sensor
float measure_uv_intensity(void);

//RTC Commands
bool rtc_check_conn(void);
void rtc_read_reg(void);
void rtc_write_reg(void);

SoilMositure* yl69 = new SoilMositure(EN_SOIL_MOIS_PIN, SOIL_MOIS_SENSE_PIN, 0);

void setup() {
  // put your setup code here, to run once:
  pinMode(LIGHT_SENSE_PIN, INPUT);
  pinMode(SENSE_3V3_PIN, INPUT);
  pinMode(UV_SENSE_PIN, INPUT);

  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(100000);
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:

  yl69->enable_sensor();
  delay(5000);

  Serial.print("SOIL: ");
  Serial.println(yl69->read_mositure());
  Serial.print("LIGHT: ");
  Serial.println(measure_light());
  Serial.print("UV: ");
  Serial.println(measure_uv_intensity());
  yl69->disable_sensor();
  delay(5000);
}



void enable_soil_sense(void)
{
  if(isSoilEn)
  {}
  else
  {
    digitalWrite(EN_SOIL_MOIS_PIN, HIGH);
    isSoilEn = true;
  }

}

uint16_t measure_soil_sense(void)
{
  if(!isSoilEn)
    return 0; //ERROR NOT ENABLED
  else
  {
    uint16_t val = analogRead(SOIL_MOIS_SENSE_PIN);
    return val;
  }
}

void disable_soil_sense(void)
{
  if(!isSoilEn)
  {}
  else
  {
    digitalWrite(EN_SOIL_MOIS_PIN, LOW);
    isSoilEn = false;
  }
}

uint16_t measure_light(void)
{
  return analogRead(LIGHT_SENSE_PIN);
}

float measure_uv_intensity(void)
{
  uint16_t uv = analogRead(UV_SENSE_PIN);
  uint16_t refV = analogRead(SENSE_3V3_PIN);
  Serial.print("DEBUG: uv: ");
  Serial.print(uv);
  Serial.print(" ref voltage: ");
  Serial.println(refV);
  float val = 3.3/refV * uv;

  return (val - 0.99) * (15 - 0.0) / (2.8 - 0.99) + 0.0;
  
}
