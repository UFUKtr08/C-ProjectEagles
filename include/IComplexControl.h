#ifndef ICOMPLEXCONTROL_H
#define ICOMPLEXCONTROL_H

#include <string>

// Bu bir "Interface" (Soyut Sınıf).
// Sadece kuralları belirler, işi yapan sınıflar (Stove gibi) içini doldurur.
class IComplexControl {
public:
  virtual ~IComplexControl() {}

  // Alt parçaların (gözlerin) listesini ve durumunu gösterir
  virtual void showSubComponents() = 0;

  // Belirli bir parçayı açar veya kapatır (index: parça no, turnOn: aç/kapa)
  virtual void operateSubComponent(int index, bool turnOn) = 0;

  // Tüm parçaları aynı anda açar veya kapatır
  virtual void toggleAll(bool turnOn) = 0;

  // Kaç tane alt parça olduğunu döndürür (Input kontrolü için)
  virtual int getSubComponentCount() = 0;
};

#endif