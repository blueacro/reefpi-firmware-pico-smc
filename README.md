# reefpi-firmware-pico-smc

This package contains the firmware for the SMC / System Management
Controller of the [blueAcro](https://blueacro.com)[reef-pi Pico base
board](https://github.com/blueacro/reefpi-pico).

 * Microcontroller: Atmel SAMD10D14AM (QFN24).  
 * Peripherals: RGB LED, buzzer, load switch (can cut power to 
   on-board Raspberry Pi), voltage sensing (3.3V), user button.

   
## I2C Commands

### Base address

The SMC responds at address 0x75

### Register

The SMC responds to writes using a single byte payload. The byte
is split between two functions:

* Beeper on/off
* Watchdog timer countdown


#### Beeper
Bit 0 of the write payload is the beeper. Set bit 0 to 
turn on the beeper, clear it to reset. For example, using i2cset:

```
i2cset -y 1 0x75 0x1
```

#### Watchdog Timer

Bit 1-7 define the number of 30-second blocks to set or reset the internal watchdog
counter to. For example, setting the payload 0x2 will set/reset the watchdog to 30 seconds.

```

value = (seconds / 30) << 1

```

Writing all 1s to the watchdog register will clear the register (e..g, 0xFE).

Example using i2cset:

```
i2cset -y 1 0x75 0xfe # Clear watchdog
i2cset -y 1 0x75 0x2 # Set to 30s watchdog
```

Writing 0 to the watchdog register has no effect. The watchdog timer will turn off all Raspberry Pi
and I2C functions for five seconds, and power them back on. The watchdog timer will restart from the last set time
after performing this reset. If the unit is fully power cycled, no watchdog functionality is present at boot.