# AVR Bluetooth RC Car

![Car Preview](https://github.com/user-attachments/assets/0875d0db-1e85-42e4-a2f8-9a2f1cba3b80)

An autonomous and remote-controlled car project built on an AVR microcontroller. The vehicle can be controlled via Bluetooth and features environmental scanning using an ultrasonic sensor mounted on a servo motor. Real-time data, such as the distance to obstacles, is displayed on an onboard OLED screen.

### 🎬 Project Videos
* [Watch the robot in action - Video 1 (Google Drive)](https://drive.google.com/file/d/1qy2Mbw8LA4zGydc3bXe6Jg8ZI4z9pSgT/view?usp=sharing)
* [Watch the robot in action - Video 2 (Google Drive)](https://drive.google.com/file/d/1imyjXtySzG7IEu7ZLUgXDeHx-lYytnAa/view?usp=sharing)

## 🛠️ Key Features & Hardware
* **Microcontroller:** AVR family (programmed in pure C)
* **Drive System:** DC motors configured with a motor driver
* **Remote Control:** Bluetooth module (UART communication) receiving gamepad inputs
* **Environment Scanning:** Ultrasonic sensor (measuring distance) mounted on a Servo Motor (PWM control)
* **Display:** SSD1306 OLED screen communicating via SPI

## 💻 Development Environment
* **IDE:** Atmel Studio / Microchip Studio
* **Language:** C
* **Structure:** Custom libraries for hardware peripherals (SPI, UART, Timers, OLED, Sensors)

## 📸 Hardware Setup / Gallery
![Hardware Details](https://github.com/user-attachments/assets/ef3c2fba-9013-46dd-9daa-9a610da920f0)
![Hardware Details](https://github.com/user-attachments/assets/7f799017-3698-4648-968d-99949ac42cad)
![Hardware Details](https://github.com/user-attachments/assets/cfd4e249-74aa-453f-9f35-108d6338c506)
![Hardware Details](https://github.com/user-attachments/assets/fbcbeef4-f4e3-4a3a-81fd-a374ec21f3bc)

## 📜 License
This project is open-source and available under the **MIT License**.
