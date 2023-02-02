#ifndef __SOIL_MOSITURE_H
#define __SOIL_MOSITURE_H

#include <Arduino.h>
#include <stdint.h>
#include <stdio.h>

class SoilMositure {

    private:
        int _analog_pin;
        int _digital_pin;
        int _en_pin;
        int _curr_analog_val;
        int _mositure_state_level;
        
        bool isEnabled;
        bool analogDefined;
        bool digitalDefined;
        bool moistureState;

    public:

        /**
         * @brief SoilMositure constructor. Write 0 to analog or digital pin to disable it.
         * @param en_pin Enable pin to turn sensor on and off
         * @param a_pin  Analog pin to read mositure value
        */
        SoilMositure(int en_pin, int a_pin, int d_pin);

        /**
         * @brief read analog mositure level 
         * @return uint16_t indicating soil measure adc reading from ADC 0-1023
        */
        uint16_t read_mositure();

        /**
         * @brief enable the soil mositure sensor
        */
        void enable_sensor();

        /**
         * @brief disable the soil mositure sensor
        */
        void disable_sensor();

        /**
         * @brief check whether the soil mositure is below threshold
         * @return uint16_t 0= sufficient mositure, 1= insufficient mositure
        */
        uint16_t check_soil_state();

        /* Getters and Setters */
        int get_analog_pin() const { return _analog_pin; }
        void set_analog_pin(int pin);
        
        int get_digital_pin() const { return _analog_pin; }
        void set_digital_pin(int pin);
        
        int get_en_pin() const { return _en_pin; }
        void set_en_pin(int pin);

        int get_mositure_level() const { return _mositure_state_level; }
        void set_mositure_level(int val) { _mositure_state_level = val; }       

        bool get_mositure_state() { return moistureState; }

        int get_soil_mositure_val() { return _curr_analog_val; }

        enum Error {
            ANALOG_NOT_DEFINED = 0xFFF0,
            DIGITAL_NOT_DEFINED = 0xFFF1,
            EN_NOT_ENABLED = 0xFFF2,
        };

    
};

#endif /* __SOIL_MOSITURE_H */