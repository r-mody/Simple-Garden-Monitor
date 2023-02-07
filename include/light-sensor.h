#ifndef __LIGHT_SENSOR_H
#define __LIGHT_SENSOR_H

#include <Arduino.h>

class LightSensor {
    protected:
        int _analog_pin;
        int _digital_pin;
        float _a_val;
        int _digital_state;
        int _compare_value;
        bool _compare_rising_trigger;
        bool _compare_falling_trigger;

    public:
        int get_analog_pin(void) { return _analog_pin; };
        void set_analog_pin(int pin);

        int get_digital_pin(void) { return _digital_pin; };
        void set_digital_pin(int pin);
        
        virtual float get_analog_val(void);

        int get_digital_state(void);

        /// @brief Set's the compare voltage for analog pin
        /// @param val voltage level to compare to
        virtual void set_comparator(float val);

        virtual bool compare_is_greater(void);
        virtual bool compare_is_lesser(void);


        LightSensor() {};
        ~LightSensor() {};

};

class UV : public LightSensor {
    private:
        int _ref_pin;

    public:
        UV(int refpin);
        ~UV(){};

        int get_ref_pin(void) { return _ref_pin; };
        void set_ref_pin(int pin);
        float get_analog_val(void);
        float measure_uv_intensity(void);
};

class Ambient : public LightSensor {
    private:


    public:
        Ambient(){};
        ~Ambient(){};
};

#endif /* __UV_SENSOR_H */