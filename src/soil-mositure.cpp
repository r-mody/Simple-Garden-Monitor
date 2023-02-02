#include "soil-mositure.h"

// Constructor
SoilMositure::SoilMositure(int en_pin, int a_pin, int d_pin)
{
    set_en_pin(en_pin);
    set_analog_pin(a_pin);
    set_digital_pin(d_pin);
}

uint16_t SoilMositure::read_mositure()
{
    if(!isEnabled)
        return EN_NOT_ENABLED;
    
    if(analogDefined)
    {
        _curr_analog_val = analogRead(_analog_pin);
        return _curr_analog_val;
    }
    else
        return ANALOG_NOT_DEFINED;
}

void SoilMositure::enable_sensor()
{
    if(!isEnabled)
    {
        digitalWrite(_analog_pin, HIGH);
        isEnabled = true;
    }
}

void SoilMositure::disable_sensor()
{
    if(isEnabled)
    {
        digitalWrite(_analog_pin, LOW);
        isEnabled = false;
    }
}

uint16_t SoilMositure::check_soil_state()
{
    if(!isEnabled)
       return EN_NOT_ENABLED;

    if(digitalDefined)
    {
        // High means below threshold
        if(digitalRead(_digital_pin))
            return 0x00;
        else
            return 0x01;
    }

    if(analogDefined)
    {
        if(_curr_analog_val < _mositure_state_level)
            return 0x01;
        else
            return 0x00;
    }

    return DIGITAL_NOT_DEFINED;
}

void SoilMositure::set_analog_pin(int pin)
{
    if(pin == 0)
        analogDefined = false;
    else
    {
        analogDefined = true;
        pinMode(_analog_pin, INPUT);
        _analog_pin = pin;
    }
}

void SoilMositure::set_digital_pin(int pin)
{
    if(pin == 0)
        digitalDefined = false;
    else
    {
        digitalDefined = true;
        pinMode(_digital_pin, INPUT);
        _digital_pin = pin;
    }
}

void SoilMositure::set_en_pin(int pin)
{
    _en_pin = pin;
    pinMode(_en_pin, OUTPUT);

    digitalWrite(_en_pin, LOW);
    isEnabled = false;
}
