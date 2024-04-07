#include <Servo.h>

// Using: ESP32-S3-DevKitM-1

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

#define SERVO_1_PIN 3
#define SERVO_2_PIN 5
#define SERVO_3_PIN 9
#define SERVO_4_PIN 11
#define SERVO_5_PIN 10

#define INIT_SERVO_1_POS 100
#define INIT_SERVO_2_POS 180
#define INIT_SERVO_3_POS 100
#define INIT_SERVO_4_POS 180
#define INIT_SERVO_5_POS 100

#define SERVO_1_KEY_NEG '1'
#define SERVO_1_KEY_POS '2'

#define SERVO_2_KEY_NEG '3'
#define SERVO_2_KEY_POS '4'

#define SERVO_3_KEY_NEG '5'
#define SERVO_3_KEY_POS '6'

#define SERVO_4_KEY_NEG '7'
#define SERVO_4_KEY_POS '8'

#define SERVO_5_KEY_NEG '9'
#define SERVO_5_KEY_POS '0'

// #define INCREMEMT_SIZE 5

// const int INCREMENT_SIZE = 5;

int pos = 0;

int currServo1Pos = INIT_SERVO_1_POS;
int currServo2Pos = INIT_SERVO_2_POS;
int currServo3Pos = INIT_SERVO_3_POS;
int currServo4Pos = INIT_SERVO_4_POS;
int currServo5Pos = INIT_SERVO_5_POS;

void setup() {
  Serial.begin(115200);

  servo1.attach(SERVO_1_PIN);
  servo2.attach(SERVO_2_PIN);
  servo3.attach(SERVO_3_PIN);
  servo4.attach(SERVO_4_PIN);
  servo5.attach(SERVO_5_PIN);

  servo1.write(INIT_SERVO_1_POS);
  servo2.write(INIT_SERVO_2_POS);
  servo3.write(INIT_SERVO_3_POS);
  servo4.write(INIT_SERVO_4_POS);
  servo5.write(INIT_SERVO_5_POS);
}

char recvOneChar() {
    if (Serial.available() > 0) {
        return Serial.read();
    }

    return 0x00;
}

int floor_dec(int val) {
  val = val - 5;

  if (val <= 10) {
    return 11;
  }

  return val;
}

int ceiling_inc(int val) {
  val = val + 5;

  if (val >= 170) {
    return 169;
  }

  return val;
}

void loop() {
  char input = recvOneChar();

  switch (input) {
    case SERVO_1_KEY_NEG:
      Serial.print("1\n");
      currServo1Pos = floor_dec(currServo1Pos);
      servo1.write(currServo1Pos);
      break;
    case SERVO_1_KEY_POS:
      Serial.print("2\n");
      currServo1Pos = ceiling_inc(currServo1Pos);
      servo1.write(currServo1Pos);
      break;
    case SERVO_2_KEY_NEG:
      Serial.print("3\n");
      currServo2Pos = floor_dec(currServo2Pos);
      servo2.write(currServo2Pos);
      break;
    case SERVO_2_KEY_POS:
      Serial.print("4\n");
      currServo2Pos = ceiling_inc(currServo2Pos);
      servo2.write(currServo2Pos);
      break;
    case SERVO_3_KEY_NEG:
      Serial.print("5\n");
      currServo3Pos = floor_dec(currServo3Pos);
      servo3.write(currServo3Pos);
      break;
    case SERVO_3_KEY_POS:
      Serial.print("6\n");
      currServo3Pos = ceiling_inc(currServo3Pos);
      servo3.write(currServo3Pos);
      break;
    case SERVO_4_KEY_NEG:
      Serial.print("7\n");
      currServo4Pos = floor_dec(currServo4Pos);
      servo4.write(currServo4Pos);
      break;
    case SERVO_4_KEY_POS:
      Serial.print("8\n");
      currServo4Pos = ceiling_inc(currServo4Pos);
      servo4.write(currServo4Pos);
      break;
    case SERVO_5_KEY_NEG:
      Serial.print("9\n");
      currServo5Pos = floor_dec(currServo5Pos);
      servo5.write(currServo5Pos);
      break;
    case SERVO_5_KEY_POS:
      Serial.print("10\n");
      currServo5Pos = ceiling_inc(currServo5Pos);
      servo5.write(currServo5Pos);
      break;
    default:
      break;
  }
}