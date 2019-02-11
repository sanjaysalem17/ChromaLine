#include <AFMotor.h>
AF_DCMotor r(1, MOTOR12_2KHZ);
AF_DCMotor l(2, MOTOR12_2KHZ);
void setup() {
  // put your setup code here, to run once:
  r.setSpeed(400);
  l.setSpeed(400);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  r.run(FORWARD);
  l.run(FORWARD);

}
