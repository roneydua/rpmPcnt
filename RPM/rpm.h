/**
 * @Author: Roney
 * @Date:   2020-12-08T11:03:38-02:00
 * @Email:  roneyddasilva@gmail.com
 * @Filename: rpm.h
 * @Last modified by:   Roney
 * @Last modified time: 2020-12-09T18:12:30-02:00
 */

#include "driver/pcnt.h"
#include <Arduino.h>

class Rpm {

public:
  Rpm(gpio_num_t sensor, pcnt_unit_t pcnt_unit = PCNT_UNIT_0,
      uint32_t sample_period_millisecond = 1000);
  float rpm;
  void update_rpm();

private:
  int16_t pulses = 0;
  gpio_num_t sensor;
  void init();
  float sample_periode_second;
  void restart_conter();

protected:
  pcnt_unit_t pcnt_unit; // numero da contadora de pulso
};
