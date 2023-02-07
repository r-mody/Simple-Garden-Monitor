#include <Arduino.h>

// https://github.com/contrem/arduino-timer
#include <arduino-timer.h>
#include <Wire.h>
#include "soil-mositure.h"
#include "light-sensor.h"

#define LIGHT_SENSE_PIN     A3
#define SOIL_MOIS_SENSE_PIN A0
#define SENSE_3V3_PIN       A2
#define UV_SENSE_PIN        A1

#define EN_SOIL_MOIS_PIN  3

// Light Sensor
Ambient* ambient_sensor = new Ambient();

//UV Sensor
UV* uv_sensor = new UV(SENSE_3V3_PIN);

// Soil Mositure Sensor
SoilMositure* yl69 = new SoilMositure(EN_SOIL_MOIS_PIN, SOIL_MOIS_SENSE_PIN, 0);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  yl69->enable_sensor();
  uv_sensor->set_analog_pin(UV_SENSE_PIN);
  ambient_sensor->set_analog_pin(LIGHT_SENSE_PIN);
  delay(10);
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.print("SOIL: ");
  Serial.print(yl69->read_mositure());
  Serial.print("| LIGHT: ");
  Serial.print(ambient_sensor->get_analog_val());
  Serial.print("| UV: ");
  Serial.println(uv_sensor->measure_uv_intensity());
  delay(1000);
}

