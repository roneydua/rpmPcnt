# Classe para medir RPM
Classe que implementa um contador de RPM com o API da Espressif [PCNT](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/pcnt.html). O contador PCNT é um contador de pulso da Espressif. A classe obtém a rotação dividindo o número de pulsos acumulados no contador PCNT por um intervalo de tempo que pode ser definido no contrutor.

Fizicamente isso pode ser feito com um Fotodiodo ou um fototransistor com o sensor TCRT5000 por exemplo.

<p align="center">
<img  src="/imagens/TCRT5000.png" width="50%"/>
</p>

Neste caso, o sensor pode detectar a mudança de uma cor no corpo do rotor por exemplo, assim tem-se um pulso por rotação. Caso fosse usado um barreira na hélice, tem-se, no mínimo, dois pulso por rotação completa.

A instância `RPM rpm_instancia(gpio_num_t sensor, uint8_t pulses_per_cicle, pcnt_unit_t pcnt_unit,    uint32_t sample_period_millisecond)` recebe a porta que o sensor está conectado, o número de interceptações em cada ciclo, o contador PCNT e o tempo que o número de pulso foi contabilizado. Por exemplo, se o sensor utilziado é um sensor de barreira óptica ligado na `GPIO_NUM_12` e o pode-se fazer

    RPM rpm_instancia(GPIO_NUM_12, 1, PCNT_UNIT_0, 1000);

Quando o método `rpm_instancia.update_rpm()`  for chamado, a variável `rpm_instancia.rpm` é atulizado divindo o número de pulsos  
