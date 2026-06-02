# 🚨 Arduino Collision Awareness & Safety Alert System

A progressive embedded systems project built on Arduino Uno, 
simulated virtually on Tinkercad. Designed for industrial 
collision avoidance applications — relevant to Industrial 
Automation & Embedded Systems domains.

---

## 📁 Project Structure

| Folder | Project | Concepts |
|--------|---------|----------|
| `01-led-blink` | LED Blink | GPIO, digitalWrite, setup/loop |
| `02-collision-alert` | Collision Alert System | Ultrasonic sensor, PWM buzzer, Serial |

---

## 🔴 Project 1 — LED Blink {Click Below To See}
[![Tinkercad](https://img.shields.io/badge/Tinkercad-Simulation-blue)](https://www.tinkercad.com/things/fNqdVQRc9MS-led-blinking?sharecode=Q-_cG6lBwsmbM77yvIHMICEctSy8hUwUz1dpgYRzS2g)

### Circuit
![LED Blink Circuit](01-led-blink/circuit_diagram.png)

### Components
- Arduino Uno R3
- LED
- 220Ω Resistor

### How it works
GPIO pin 13 is configured as OUTPUT. The pin is toggled 
HIGH and LOW every 500ms to blink the LED. Foundation 
concept for all digital output control in embedded systems.

---

## 🚨 Project 2 — Collision Awareness & Safety Alert System {{Click Below To See}}
[![Tinkercad](https://img.shields.io/badge/Tinkercad-Simulation-blue)](https://www.tinkercad.com/things/kNo4UXLtI3Q-project-2-collision-awareness-amp-safety-alert-system)

### Circuit
![Collision Alert Circuit](02-collision-alert/circuit_diagram.png)

### Components
- Arduino Uno R3
- HC-SR04 Ultrasonic Distance Sensor
- Piezo Buzzer

### How it works
The ultrasonic sensor sends a sound pulse and measures 
the time taken for the echo to return. Using the speed 
of sound (343 m/s), distance is calculated. The buzzer 
beeps at increasing frequency as an object gets closer — 
mimicking an industrial collision avoidance system.

### Alert Zones
| Distance | Alert Level | Buzzer |
|----------|-------------|--------|
| > 40cm | Safe | Silent |
| 20–40cm | Warning | Slow beep |
| 10–20cm | Danger | Fast beep |
| < 10cm | Critical | Very fast beep |

### Industrial Application
This system simulates the core logic used in:
- Factory floor collision avoidance
- Automated guided vehicles (AGVs)
- Robotic arm safety systems
- Conveyor belt obstacle detection

---

## 🛠️ How to Run

1. Click the Tinkercad badge above for live simulation
2. Click **Tinker This** to get your own editable copy
3. For physical hardware — copy code from `.ino` file 
   and upload via Arduino IDE

---

## 📚 Concepts Practiced
- GPIO digital output/input control
- Ultrasonic sensor (HC-SR04) interfacing
- Sound-based distance calculation
- Serial monitor data logging
- Threshold-based alert system design

---

## 👩‍💻 Author
**Hetanjali Vaghela** — Robotics & Automation Engineering  
3rd Year | Embedded Systems Enthusiast
