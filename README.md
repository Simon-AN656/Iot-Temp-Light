# IoT Temperature and Light Sensor (Bare-Metal STM32F103)

Este proyecto implementa una solución IoT de bajo nivel utilizando un microcontrolador
**STM32F103** en entorno **bare-metal** (sin HAL ni CMSIS), enfocándose en la lectura 
precisa del sensor **DS18B20** (temperatura digital 1-Wire) y sensores de luz analógica (LDR).

## Características

- Programación 100% bare-metal en C
- Lectura de temperatura mediante protocolo 1-Wire
- Lectura de sensor de luz tipo LDR
- Precisión en delays usando timers del STM32
- Enfoque educativo y modular para crear librerías desde cero

## Hardware Utilizado

- STM32F103C8T6 ("Blue Pill")
- Sensor de temperatura **DS18B20**
- LDR con divisor resistivo
- Pull-up de 4.7kΩ para línea 1-Wire
- Fuente de alimentación de 3.3V
- Conexiones en protoboard
