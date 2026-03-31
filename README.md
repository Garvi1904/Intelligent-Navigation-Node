# 🚀 Intelligent Navigation Node

A multi-sensor fusion based navigation system using **GPS, IMU, and Hall Sensor** for accurate position, speed, and motion estimation.

## 📌 Features
- 📍 GPS-based absolute positioning (NEO-6M)
- 📊 IMU-based motion tracking (MPU6050)
- 🔄 Hall sensor for wheel rotation and speed
- 🧠 Sensor Fusion using Complementary Filter
- ⚡ Real-time data processing using Arduino UNO

## 🛠️ Hardware Used
- Arduino UNO
- NEO-6M GPS Module
- MPU6050 IMU Sensor
- A3144 Hall Effect Sensor
- Breadboard & Jumper Wires

## ⚙️ Working
- GPS provides global position
- IMU provides high-frequency motion data
- Hall sensor measures wheel speed
- Data fused using weighted averaging:
  
  Velocity = (GPS × 0.4) + (Hall × 0.4) + (IMU × 0.2)

## 🧾 Code
Arduino code is available in `/code/intelligent_node.ino`

## 📷 Output
- Real-time serial monitor data
- Sensor fusion based navigation output

## 🎯 Applications
- Autonomous Vehicles
- Robotics Navigation
- Asset Tracking Systems

## 🔮 Future Scope
- Extended Kalman Filter (EKF)
- RTK GPS for higher accuracy
- IoT-based live tracking

## 👩‍💻 Authors
- Garvita
- Drishti Singh
- Garv Makhija
