# Classe para medir RPM
Classe que implementa um contador de RPM com o API da Espressif [PCNT](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/pcnt.html). O contador PCNT é um contador de pulso da Espressif. A classe obtém a rotação dividindo o número de pulsos acumulados no contador PCNT por um intervalo de tempo que pode ser definido no contrutor.

Fizicamente isso pode ser feito com um Fotodiodo ou um fototransistor como os sensor

![TCRT5000 sensor](/images/2020/12/TCRT5000.png) 

A instância `RPM rpm_instancia(gpio_num_t sensor, uint8_t pulses_per_cicle, pcnt_unit_t pcnt_unit,    uint32_t sample_period_millisecond)` recebe a porta que o sensor está conectado, o número de interceptações em cada ciclo, o contador PCNT e o tempo que o número de pulso foi contabilizado. Por exemplo, se o sensor utilziado é um sensor de barreira óptica ligado na `GPIO_NUM_12` e o pode-se fazer
