* **Note:** The firmware is still being optimized to reduce flash memory usage on the Pedro Board (ATmega32U4). Currently (release 1.0.3
), it occupies about 98% of the available 32 KB, with the goal of reducing it closer to 90% for better efficiency. Optimization work is ongoing for the upcoming release 1.0.4.

# PedroRobot – Firmware

Firmware for **Pedro Robot**.
This repository contains the firmware to directly control the Pedro Robot in the following modes: Normal, Radio, Bluetooth, Replay, Record, and [Web Controller](https://www.pedrobot.com/webController.html)

## ✨ Pedro Modes

* 🎮 **Direct Control** – Control Pedro directly from the board
* 📶 **Bluetooth HC-05** – Connect Pedro to a smartphone
* 📡 **Radio NRF24L01** – Enable remote communication between two or more Pedro Robots (one as Transmitter, the other as Receiver)
* 🌐 **Web Interface** – Control Pedro through the [web controller](https://www.pedrobot.com/webController.html) interface via serial communication
* 🔄 **Record & Replay** – Record and replay Pedro’s movements

## 🛠️ Installation

1. Install a recent version of the Arduino IDE (any up-to-date version will work).
2. From the Arduino IDE, download and install the U8glib library.
3. Copy the folder PedroRobot/src into your Arduino/libraries directory.
4. In the Arduino IDE, select the board: Arduino Micro.
5. Open the sketch located at: src/examples/PedroRobot/PedroRobot.ino.
6. Compile and upload the sketch to the board.

## 📑 Documentation & Resources

👉 Find the complete documentation, as well as the STL files for 3D printing Pedro, in the main repository: [Pedro – Documentation & STL](https://github.com/almtzr/Pedro)

## 🤝 Contribution

Contributions are welcome!
Feel free to open an issue or submit a pull request to improve the firmware.

---

