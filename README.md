## 🚀 Pedro Project Repositories: 
Each Pedro repository serves a specific role in the ecosystem:

* 📂 [`Pedro 3D Files`](https://github.com/almtzr/Pedro3DFiles): STL files for printing Pedro robot.
* 📂 [`Pedro Board`](https://github.com/almtzr/PedroBoard): Gerber files, schematics, and PCB layouts for the Pedro controller board.
* 📂 [`Pedro Firmware`](https://github.com/almtzr/PedroFirmware): Firmware and library to program and control the Pedro robot.
* 📂 [`Pedro STEM Lessons`](https://github.com/almtzr/PedroSTEMLessons): STEM lessons, activities, and teaching material using the Pedro robot for schools.

# 📂 `Pedro Robot`

Source code and library to program and control the Pedro robot.
Available Control modes : **Manual**, **Record & Replay**, **Bluetooth**, **Radio**, **UART** and **USB Serial**.

## ⚙️ Installing and Uploading Pedro Firmware

1. **Download and install** the latest version of the [Arduino IDE](https://www.arduino.cc/en/software).
2. **Install the required libraries** from the Library Manager:
   * **PedroRobot**: Tools → Manage Libraries → search **PedroRobot** → Install
   * **U8glib**: Tools → Manage Libraries → search **U8glib** → Install
   * **RF24**: Tools → Manage Libraries → search **RF24** → Install
3. **Connect** your Pedro robot to your computer via USB.
4. **Select the correct port**:
   * Tools → Select the port that appear when you connect Pedro robot
5. **Select the board type**:
   * Tools → Board → Arduino Micro
6. **Open the example sketch**:
   * File → Examples → PedroRobot → Pedro
7. **Compile and upload** the sketch to your Pedro board.

✅ Done!
Your Pedro robot is now ready to run with the latest firmware.

> **Note:** Make sure all dependencies are installed before compiling to avoid errors.

## ✨ Get Started with Pedro Control Modes

<div align="left">
    <img src="img/1.png" width="45%">
    <img src="img/2.png" width="45%">
</div>
<div align="left">
    <img src="img/3.png" width="45%">
    <img src="img/4.png" width="45%">
</div>
<div align="left">
    <img src="img/5.png" width="45%">
</div>

## 🎮 1. Manual Mode

**What it does:** Direct control of servo motors using onboard buttons.

**How to use:**

1. Power **ON** Pedro (default mode **Manual**)
2. Use button **A0** to Select Servo.
3. Use button **A1** to Move Servo to Left.
4. Use button **A2** to Move Servo to Right.

🎓 **STEM Insight:** Learn about servo motors and direct PWM control.

## 🎥 2. Record & Replay Mode

**What it does:** Record servo movements, then replay them.

**How to use:**

1. Enter the **Select Mode** menu (hold button **A0** for 4 seconds).
2. Choose **Record Mode** from the menu.
3. Press **A0** to confirm.
4. Move Pedro manually using the buttons (as in **Manual Mode**).
5. Re-enter the **Select Mode** menu (hold **A0** for 4 seconds).
6. Select **Replay Mode**.
7. Pedro will now repeat the recorded sequence in a loop.
8. To stop or change, re-enter the **Select Mode** menu.

🎓 **STEM Insight:** Teaches concepts of timing, sequencing, and automation.

## 📶 3. Bluetooth Mode (HC-05)

**What it does:** Control Pedro via smartphone (validate on Android devices).

**How to use:**

**Configuring Pedro in Bluetooth Mode**

1. Power **OFF** Pedro.
2. Set Pedro’s switch **NRF → BT → WiFi** to: **BT**.
3. Press and hold the **BT → AT** button.
4. Power **ON** Pedro.
5. Release the **BT → AT** button after 3 seconds.
6. Enter the **Select Mode** menu by holding **A0** for 4 seconds).
7. Select **BLUETOOTH Mode**
8. Press **A0** to confirm.
9. Select **OK**, then press **A0** to confirm.
10. Pedro is now ready to communicate via Bluetooth.
    
**Smartphone Application Setup:**

1. Install the App: Download and install the **Serial Bluetooth** app on your smartphone.
2. Create the Control Buttons.

| Button | Value | Mode | Action | Newline |
| ------ | ----- | ---- | ------ | ------ |
| Servo1 | 1 | Text | Send | CR |
| Servo2 | 1 | Text | Send | CR |
| Servo3 | 1 | Text | Send | CR |
| Servo4 | 1 | Text | Send | CR |
| FwD (Forward) | 5 | Text | Send | CR |
| BwD (Backward) | 6 | Text | Send | CR |
| Stop | 7 | Text | Send | CR |

4. Pair your smartphone with Pedro’s HC-05 module (default name: HC-05, PIN: 1234).
5. Use the app buttons to send commands and control Pedro in real time.

✅ Once paired, use the buttons in the application to control Pedro in real time.

**Optional: Change the Bluetooth Name**

You can personalize Pedro's Bluetooth name.

1. Enter the **Bluetooth Update** menu.
2. Enter the new Bluetooth name (for example: **PEDROROBOTX**).
3. Save the new settings.
4. Pair your smartphone using the new Bluetooth device name.
  
🎓 **STEM Insight:** : Students learn about wireless serial communication and how to configure Bluetooth modules for embedded systems.

## 📡 4. Radio Mode (NRF24L01)

**What it does:** Enables remote communication between two Pedro robots or more using the NRF24L01 radio module.

**How to use:**

1. Insert the **NRF24L01 module** into the left slot of each Pedro board (one robot as transmitter, the other as receiver).
2. Set Pedro’s switch **NRF → BT → WiFi** to: **NRF**.
3. Enter the **Select Mode** menu (hold button **A0** for 4 seconds).
4. Choose **Radio Mode** from the menu.
5. Press **A0** to confirm.
6. Define the robot’s role (type): press **A1** to select **TRANSMITTER** or **RECEIVER**.
7. Press **A0** to confirm the role.
8. Set a communication Code Key:
* Press **A1** to increase (increment).
* Press **A2** to decrease (decrement).
* Values range from 1 to 99.
9. Press **A0** to confirm the Code Key.
10. Press **A0** again to validate (OK).

> **Note:** Both the transmitter and receiver must use the same Code Key to establish communication. 

🎓 **STEM Insight:** This mode introduces students to the basics of **radio frequency communication**, addressing concepts like **transmitter/receiver** pairing and unique channel codes.

## 🌐 5. USB Serial Mode

**What it does:** Control Pedro from your PC with Pedro-IHM.

**How to use:**

1. Enter the **Select Mode** menu (hold button **A0** for 4 seconds).
2. Choose **USB SERIAL MODE** from the menu.
3. Press **A0** to confirm.
4. Connect Pedro via USB cable.
5. Launch the [web controller](https://www.pedrobot.com/webController.html) app.
6. Send commands & test servo response.

🎓 **STEM Insight:** Embedded programming and PC-robot communication.

## 🌐 6. UART Mode
**What it does:** UART Mode allows two Pedro robots to communicate through a wired serial connection using the RX and TX pins.

**How to use: Wiring the Pedro Robots**

Connect the pins of the Pedro Robots transmitter and receiver as following:
- Transmitter → Receiver
- TX → RX
- GND → GND
- VCC → VCC (option)
  
> **Important**: Always connect TX → RX (never TX → TX).

**Configuring the Pedro Transmitter and Receiver**

|  Transmitter | Receiver |
| ------------- | ------------- |
| 1. Power ON Pedro | 1. Power ON Pedro |
| 2. Enter the **Select Mode** menu | 2. Enter the **Select Mode** menu |
| 3. Select **UART Mode** | 3. Select **UART Mode** |
| 4. Press **A0** to confirm | 5. Press **A0** to confirm |
| 5. Press **A1** to select the **TRANSMITTER** role | 5. Press **A1** to select the **RECEIVER** role |
| 6. Press **A0** to confirm | 6. Press **A0** to confirm |
| 7. Select **OK** | 7. Select **OK** |
| 8. Press **A0** to confirm | 8. Press **A0** to confirm |

**Ready to Communicate**

✅ Once both robots are configured, use the A0, A1, and A2 buttons on the Pedro Transmitter to remotely control the Pedro Receiver through the UART (RX/TX) connection.

💡 Note: UART communication requires a wired connection between the two Pedro robots. Unlike Radio or Bluetooth modes, data is transmitted through the RX and TX pins rather than wirelessly.

---

[Arduino logs library](https://downloads.arduino.cc/libraries/logs/github.com/almtzr/PedroRobot/)
