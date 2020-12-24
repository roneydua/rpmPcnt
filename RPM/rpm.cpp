/**
 * @Author: Roney
 * @Date:   2020-12-08T12:41:06-02:00
 * @Email:  roneyddasilva@gmail.com
 * @Filename: rpm.cpp
 * @Last modified by:   roney
 * @Last modified time: 2020-12-23T23:06:17-02:00
 */

#include "rpm.h"
#include <Arduino.h>

Rpm::Rpm(gpio_num_t sensor, uint8_t pulses_per_cicle, pcnt_unit_t pcnt_unit,
         uint32_t time_update_sensors_millisecond) {
  this->sensor = sensor;
  this->pcnt_unit = pcnt_unit;
  sample_periode_second =
      float(pulses_per_cicle) * float(time_update_sensors_millisecond) / 1000.f;
  init();
}
void Rpm::init() {
  gpio_set_pull_mode(this->sensor, GPIO_PULLUP_ONLY);
  pcnt_config_t pcnt_config = {
      .pulse_gpio_num = this->sensor, // configura a gpiou de leitura
      .ctrl_gpio_num = -1,            // define o controle
      .lctrl_mode = PCNT_MODE_KEEP,   // when control signal is low, keep the
                                      // primary counter mode
      .hctrl_mode = PCNT_MODE_KEEP,   // when control signal is high, keep the
                                      // primary counter mode
      .pos_mode = PCNT_COUNT_INC,     // incrementa com a subida do sinal
      .neg_mode = PCNT_COUNT_DIS,     // ignora a contagem com a decida
      .counter_h_lim = 2500,
      .counter_l_lim = 0,
      .unit = this->pcnt_unit, /*!< PCNT unit number */
      .channel = PCNT_CHANNEL_0};
  pcnt_unit_config(&pcnt_config);
  restart_conter();
  pcnt_get_counter_value(this->pcnt_unit, &pulses);
  update_rpm();
  calcula_rpm(float dt);
}
void Rpm::restart_conter() {
  pcnt_counter_pause(this->pcnt_unit);
  pcnt_counter_clear(this->pcnt_unit);
  pcnt_counter_resume(this->pcnt_unit);
}
void Rpm::update_rpm() {
  /**
   * @brief update the rpm variable withe constante sample time.
   */
  pcnt_get_counter_value(this->pcnt_unit, &pulses);
  restart_conter();
  rpm = float(pulses) / this->sample_periode_second;
}
void Rpm::calcula_rpm(float dt) {
  /**
   * @brief update rpm variable with dividing the pulse by dt parameter
   * @param [dt] elapsed time between conter update
   */

  pcnt_get_counter_value(this->pcnt_unit, &pulses);
  restart_conter();
  rpm = float(pulses) / dt;
}
