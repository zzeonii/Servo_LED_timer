#include <PWMServo.h>
#include <TimerOne.h>

const int LED_PIN = 9;
const int SERVO_PIN = 10;

PWMServo servo;

void setup() {
  Timer1.initialize(20000);  // 20ms 주기로 타이머 인터럽트 설정
  pinMode(LED_PIN, OUTPUT);
  servo.attach(SERVO_PIN);
  Timer1.attachInterrupt(timerISR);
}

void loop() {
  // 여기서는 loop 함수에서 아무 것도 하지 않습니다.
  // LED와 서보 모터는 타이머 인터럽트에서 제어합니다.
}

void timerISR() {  // 타이머 인터럽트 핸들러 함수
  static boolean led_state = false;
  static int servo_pos = 0;
  static int servo_dir = 1;

  // LED 제어
  digitalWrite(LED_PIN, led_state);
  led_state = !led_state;

  // 서보 모터 제어
  servo.write(servo_pos);
  servo_pos += servo_dir;
  
  if (servo_pos <= 0 || servo_pos >= 180) {
    servo_dir *= -1;
  }
}