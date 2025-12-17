#include "../include/Camera.h"
#include "../include/SecuritySystem.h" // SecuritySystem ile konuştuğu için lazım
#include <iostream>

using namespace std;

// --- CONSTRUCTOR (Eksikti, eklendi) ---
Camera::Camera(int id, string n)
    : Device(id, n), isRecording(false), nightVisionMode(false) {}

// --- DEVICE OVERRIDES ---
void Camera::togglePower() {
  if (isPowered && isRecording) {
    stopRecording();
  }
  isPowered = !isPowered;
  cout << ">> Camera [" << name << "] is now " << (isPowered ? "ON" : "OFF") << endl;
}

Device *Camera::clone() const { return new Camera(deviceID, name); }

string Camera::getType() const { return "Camera"; }

// --- ÖZEL METODLAR ---
void Camera::startRecording() {
  if (!isPowered) {
    cout << "!! Camera is OFF. Cannot start recording." << endl;
    return;
  }
  if (!isRecording) {
    isRecording = true;
    cout << "[REC] Camera started recording..." << endl;
  }
}

void Camera::stopRecording() {
  if (isRecording) {
    isRecording = false;
    cout << "[STOP] Recording saved to server." << endl;
  }
}

void Camera::toggleNightVision() {
  if (!isPowered) {
    cout << "!! Camera is OFF. Cannot toggle night vision." << endl;
    return;
  }
  nightVisionMode = !nightVisionMode;
  cout << "[MODE] Night Vision is now " << (nightVisionMode ? "ON" : "OFF")
       << endl;
}

void Camera::detectMotion(SecuritySystem *sys) {
  if (!isPowered) {
    cout << "!! Camera is OFF. Motion detection inactive." << endl;
    return;
  }
  cout << ">> MOTION DETECTED by " << name << "!" << endl;
  startRecording();
  if (sys) {
    sys->notifyBreach(name, "MOTION");
  }
}

// --- ACTION HANDLING ---
vector<string> Camera::getActions() {
  return {"Toggle Power", "Start Rec", "Stop Rec", "Night Vision",
          "SIMULATE MOTION"};
}

void Camera::performAction(string actionName) {
  if (actionName == "Toggle Power")
    togglePower();
  else if (actionName == "Start Rec")
    startRecording();
  else if (actionName == "Stop Rec")
    stopRecording();
  else if (actionName == "Night Vision")
    toggleNightVision();
  else if (actionName == "SIMULATE MOTION")
    detectMotion(nullptr);
}