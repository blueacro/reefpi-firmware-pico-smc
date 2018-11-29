=============================
I2C Slave asynchronous driver
=============================

I2C (Inter-Integrated Circuit) is a two wire serial interface commonly used
for on-board low-speed bi-directional communication between controllers and
peripherals. There can be several slave devices on I2C bus.
I2C uses only two bidirectional open-drain lines, usually designated SDA
(Serial Data Line) and SCL (Serial Clock Line), with pull up resistors.

I2C Modes (standard mode/fastmode+/highspeed mode) can only be selected in
Atmel Start. Make sure that the selected speed mode is within the expected SCL
clock frequency range of the i2c bus.

The error callback is executed as soon as an error is detected by the hardware.

The rx callback is invoked each time a byte is received by an I2C slave device,
the byte is put into the ring buffer in prior to callback calling. Received data
can be read out in the callback via I/O read function.

The tx pending callback is invoked when a master device requests data from a
slave device via sending slave device address with r/w bit set to one. A slave
device can send data to a master device via I/O write function.

The tx callback is invoked at the end of buffer transfer caused by a call
to I/O write function.

Features
--------

	* I2C Slave support
	* Initialization and de-initialization
	* Enabling and disabling
	* 10- and 7- bit addressing
	* Setting slave address
	* I2C Modes supported
	       +----------------------+-------------------+
	       |* Standard/Fast mode  | (SCL: 1 - 400kHz) |
	       +----------------------+-------------------+
	       |* Fastmode+           | (SCL: 1 - 1000kHz)|
	       +----------------------+-------------------+
	       |* Highspeed mode      | (SCL: 1 - 3400kHz)|
	       +----------------------+-------------------+
	* Callback on byte receipt, data request, end of data trasnmission to a master device and error events

Applications
------------

* Sensors, device to device communication, memory.

Dependencies
------------

* I2C Slave capable hardware

Concurrency
-----------

N/A

Limitations
-----------

* System Management Bus (SMBus) not supported
* Power Management Bus (PMBus) not supported
* During the write operation buffer content should not be changed before transfer is complete

Known issues and workarounds
----------------------------

N/A


