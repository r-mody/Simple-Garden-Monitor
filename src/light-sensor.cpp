#include "light-sensor.h"

static bool _analog_config = false;
static bool _digital_config = false;

void LightSensor::set_analog_pin(int pin)
{
    if(pin < 0)
    {
        _analog_config = false;
    }
    else
    {
        _analog_pin = pin;
        pinMode(_analog_pin, INPUT);
        _analog_config = true;
    }
    
}

void LightSensor::set_digital_pin(int pin)
{
    if(pin < 0)
    {
        _digital_config = false;
    }
    else
    {
        _digital_pin = pin;
        pinMode(_digital_pin, INPUT);
        _digital_config = true;
    }
    
}

float LightSensor::get_analog_val(void)
{
    return  analogRead(_analog_pin);
}

int LightSensor::get_digital_state(void)
{
    return digitalRead(_digital_pin);
}

void LightSensor::set_comparator(float val)
{
    _compare_value = val;
}

bool LightSensor::compare_is_greater(void)
{
    return (get_analog_val() > _compare_value) ? true : false;
}

bool LightSensor::compare_is_lesser(void)
{
    return (get_analog_val() < _compare_value) ? true : false;
}

UV::UV(int refpin)
{
    _ref_pin = refpin;
    pinMode(_ref_pin, INPUT);
}

void UV::set_ref_pin(int pin)
{
    _ref_pin = pin;
    pinMode(_ref_pin, INPUT);
}

float UV::get_analog_val(void)
{
    return analogRead(_analog_pin) * 3.3 / analogRead(_ref_pin); 
}

float UV::measure_uv_intensity(void)
{
    float val = get_analog_pin();
    return (val - 0.99) * (15 - 0.0) / (2.8 - 0.99) + 0.0;
}
