# Parts

Relevant information about the parts that MORT uses will be detailed here.

**Table of Contents**
<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [Parts](#parts)
  - [Chassis](#chassis)
  - [Motors](#motors)
  - [Motor Drivers](#motor-drivers)
  - [Brake/Reverse Lights](#brakereverse-lights)
  - [Buzzer](#buzzer)
  - [Range Sensor(s)](#range-sensors)
  - [IR Remote and Receiver](#ir-remote-and-receiver)
  - [Microcontroller](#microcontroller)
  - [Battery](#battery)

<!-- /code_chunk_output -->


## Chassis

[TP101 Tank Chassis](https://www.amazon.com/dp/B09TFN2Z56?psc=1&ref=ppx_yo2ov_dt_b_product_details)

Notes:
- Motors are included with the kit.

## Motors

2 x doit.am 33GB-520-18.7f

Notes:
- Included with the [TP101 Tank Chassis](https://www.amazon.com/dp/B09TFN2Z56?psc=1&ref=ppx_yo2ov_dt_b_product_details) kit.
- Brushed DC motor
- Operating voltage: 6-12V
- Stall current: 1.2A
- No-load current: 100mA

## Motor Drivers

2 x [TB6612FNGC8EL Motor Driver IC](https://www.digikey.com/en/products/detail/toshiba-semiconductor-and-storage/TB6612FNG-C-8-EL/1730070)

Notes:
- Output current: 1.2A
- Supply voltage: 2.7V - 5.5V
- Load voltage: 2.5V - 13.5V
- Microcontroller interface: AIN1/2, BIN1/2, PWMA/B, STBY (7 pins), timer if no dedicated pwm

## Brake/Reverse Lights

[10 Segment Bar Graph LED Display - Red](https://www.adafruit.com/product/1921)

A generic white LED will do for reverse lights

Notes:
- Microcontroller interface: 2 pins, 74HC595, timer

## Buzzer

[Generic Buzzer](https://www.amazon.com/Cylewet-Electronic-Magnetic-Continuous-Arduino/dp/B01N7NHSY6/ref=sr_1_3?keywords=arduino+buzzer&qid=1681794656&sr=8-3)

Notes:
- Input voltage: 4-8VDC
- Input current: <25mA
- Microcontroller interface: ON/OFF (1 pin)

## Range Sensor(s)

[VL53L0X Time of Flight Distance Sensor](https://www.adafruit.com/product/3317)

Notes:
- Microcontroller interface: I2C, GPIO, SHDN (4 pins)

## IR Remote and Receiver

[Generic Remote](https://www.adafruit.com/product/389)

[IR Receiver](https://www.adafruit.com/product/157)

Notes:
- Microcontroller interface: IN (1 pin), timer

## Microcontroller

[Arduino Nano (or compatible clone)](https://www.amazon.com/Deegoo-ATmega328P-Microcontroller-Board-Arduino/dp/B07R9VWD39/ref=asc_df_B07R9VWD39/?tag=hyprod-20&linkCode=df0&hvadid=459728334703&hvpos=&hvnetw=g&hvrand=898811443164575780&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9011071&hvtargid=pla-945070251730&th=1)

Notes:
- ATMega328P microcontroller
- Board package is used to avoid having to design the PCB around an SMD chip footprint for this project
- Slightly better choice than the MSP430 because it has three timers as opposed to two
- No Arduino code or libraries will be used; this microcontroller will be programmed using only bare-metal C

## Battery

[AA Battery Holder](https://www.amazon.com/CO-RODE-Battery-Holder-Wired-Switch/dp/B00VE7HBMS/ref=asc_df_B00VE7HBMS/?tag=hyprod-20&linkCode=df0&hvadid=216534554317&hvpos=&hvnetw=g&hvrand=13817666111780128804&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9011071&hvtargid=pla-350870493113&psc=1)

Notes:
- 8-slot AA battery holder
