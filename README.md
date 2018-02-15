# Button Serial Controller

The button serial controller is responsible for start the gif booth sequence of:

- Countdown
- Capture a static image for high quality print
- Capture 5 second video
- Convert to gif
- Printout the pick up strip and queue up the high quality print

This Arduino Sketch is reponsible for communicating with the main computer over the serial port

An Arduino Uno is used for the main micro controller

## Diagram

![Circuit](https://github.com/gif-booth/button-serial-controller/blob/master/assets/circuit.png)

## Required components

| Component             | Quantity | Description                                     |
| --------------------- | -------- | ------------------------------------------------|
| Momentary Push Switch | 2        | Used to trigger print and reprint of last strip |
| LED                   | 1        | To signal activity                              |
| 220 Ohm resister      | 1        | Inline for the LED                              |
| 10k Ohm resister      | 2        | Inline for the Momtary Push Switch              |
| Project box           | 1        | Used to house the project                       |
| Usb connector         | 1        | Used to have an easy connection                 |

Alternatively, the momtary push switch can be replaced with a giant dome button, which contains a switch, and a LED.
