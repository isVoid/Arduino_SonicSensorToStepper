#include <Stepper.h>

Stepper stepper(300,4,5,6,7);

void setup() {
  // put your setup code here, to run once:

  stepper.setSpeed(25);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  stepper.step(20);

  delay(2000);
}
