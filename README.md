# AVR Bluetooth RC Car

![Car Preview](https://github.com/user-attachments/assets/b46615ba-02f9-4d01-a0ad-2cea0865527a)

An autonomous and remote-controlled car project built on an AVR microcontroller. The vehicle can be controlled via Bluetooth and features environmental scanning using an ultrasonic sensor mounted on a servo motor. Real-time data, such as the distance to obstacles, is displayed on an onboard OLED screen.

### Project Videos
* [Video 1 (Google Drive)](https://drive.google.com/file/d/1qy2Mbw8LA4zGydc3bXe6Jg8ZI4z9pSgT/view?usp=sharing)
* [Video 2 (Google Drive)](https://drive.google.com/file/d/1imyjXtySzG7IEu7ZLUgXDeHx-lYytnAa/view?usp=sharing)

## Key Features & Hardware
* **Microcontroller:** AVR family (programmed in pure C)
* **Drive System:** DC motors configured with a motor driver
* **Remote Control:** Bluetooth module (UART communication) receiving gamepad inputs
* **Environment Scanning:** Ultrasonic sensor (measuring distance) mounted on a Servo Motor (PWM control)
* **Display:** SSD1306 OLED screen communicating via SPI

## Development Environment
* **IDE:** Atmel Studio / Microchip Studio
* **Language:** C
* **Structure:** Custom libraries for hardware peripherals (SPI, UART, Timers, OLED, Sensors)

## Hardware Setup / Gallery
![Hardware Details](https://github.com/user-attachments/assets/89896b8c-7cfc-4de8-aae4-0de68716ff35)
![Hardware Details](https://github.com/user-attachments/assets/8e805add-fab8-4978-8653-f2431b09f99d)

## License
This project is open-source and available under the **MIT License**.
