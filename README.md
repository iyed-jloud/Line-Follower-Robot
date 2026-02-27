# Autonomous Line Follower Robot (PWM Speed Control)

## Project Overview
This project focuses on developing an **autonomous mobile robot** capable of tracking a black trajectory on a white surface in real-time. Unlike basic robots, this system implements **PWM (Pulse Width Modulation)** speed control to adjust velocity dynamically, ensuring smoother turns and better stability.

The robot uses a feedback loop based on 3 Infrared (IR) optical sensors to make navigation decisions without human intervention.

## Technical Stack
* **Language:** Embedded C++
* **Microcontroller:** Arduino Uno
* **Sensors:** 3-Channel IR Line Tracking Module (TCRT5000)
* **Actuators:** DC Motors with Gearbox
* **Driver:** L298N (Dual H-Bridge with PWM support)

## Hardware Architecture & Wiring
The wiring is designed to support variable speed control via PWM pins.

| Component | Pin Function | Arduino Pin | Description |
| :--- | :--- | :--- | :--- |
| **Left Motor Speed** | ENA | **D3 (~PWM)** | Speed Control (0-255) |
| **Left Motor Dir** | IN1 / IN2 | D5 / D6 | Direction Control |
| **Right Motor Speed** | ENB | **D11 (~PWM)** | Speed Control (0-255) |
| **Right Motor Dir** | IN3 / IN4 | D9 / D10 | Direction Control |
| **Sensors** | Left / Center / Right | D2 / D7 / D4 | Digital Input (HIGH/LOW) |

## Algorithmic Logic
The robot operates on a continuous "Sense-Think-Act" loop (`void loop`).

### 1. Sensor Fusion
The system reads digital states from the 3 sensors:
* `HIGH` = Black Line Detected
* `LOW` = White Surface

### 2. Decision Matrix
Based on the sensor array, the robot applies the following logic:

| Left Sensor | Center Sensor | Right Sensor | Action | Speed |
| :---: | :---: | :---: | :--- | :--- |
| ⚪ | ⚫ | ⚪ | **Forward** | Fast (130) |
| ⚫ | ⚪ | ⚪ | **Turn Left** | Slow (110) |
| ⚪ | ⚪ | ⚫ | **Turn Right** | Slow (110) |
| ⚫ | ⚫ | ⚫ | **Stop** | 0 |


## Key Technical Features implemented
* **PWM Speed Regulation:** Instead of full throttle (HIGH/LOW), I used `analogWrite()` to control motor power. This prevents the robot from overshooting the line during sharp turns.
* **Modular Functions:** Code is organized into `avancer()`, `tournerGauche()`, etc., making debugging easier.
* **Fail-Safe:** The robot automatically stops if the line is lost or at an intersection (Crossroad).

---
*Project developed by IYED JLOUD.*
