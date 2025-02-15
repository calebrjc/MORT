# Parts

Relevant information about the parts that MORT uses will be detailed here.

**Table of Contents**
<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [Parts](#parts)
  - [Chassis](#chassis)
  - [Motors](#motors)
  - [Motor Drivers](#motor-drivers)
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

## IR Remote and Receiver

[Generic Remote](https://www.adafruit.com/product/389)

[IR Receiver](https://www.adafruit.com/product/157)

Notes:
- Microcontroller interface: IN (1 pin), timer

## Microcontroller

STM32G0 Series Microcontroller (undecided on part number)

Notes:
- STM32G0 microcontroller
- Zephyr RTOS

## Battery

[AA Battery Holder](https://www.amazon.com/CO-RODE-Battery-Holder-Wired-Switch/dp/B00VE7HBMS/ref=asc_df_B00VE7HBMS/?tag=hyprod-20&linkCode=df0&hvadid=216534554317&hvpos=&hvnetw=g&hvrand=13817666111780128804&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9011071&hvtargid=pla-350870493113&psc=1)

Notes:
- 8-slot AA battery holder
