#ifndef CAMERA_H
#define CAMERA_H

#include "Device.h"
#include <string>
#include <vector>

// Forward Declaration
class SecuritySystem;

class Camera : public Device {
private:
  bool isRecording;
  bool nightVisionMode;

public:
  Camera(int id, std::string n);

  void togglePower() override;
  Device *clone() const override;
  std::string getType() const override;
  std::vector<std::string> getActions() override;
  void performAction(std::string actionName) override;

  // Özel Metodlar
  void startRecording();
  void stopRecording();
  void toggleNightVision();
  void detectMotion(SecuritySystem *sys);
};

#endif