/* Copyright 2020 by author Daniel Tierney.
 * All Rights Reserved.
 * This copyright notice must appear in all header files.
 */

// For interfacing between RPi0W and electronics in the RC truck re-creation
// Devices include: L298N (steer + drive), Distance sensors, Decorative LEDs

#define VERSION_MAJOR 1
#define VERSION_MINOR 0
#define VERSION_PATCH 0

#define EOT 4
#define ACK 6
#define NAK 21
#define ESC 27

#define FORWARD 1
#define BACKWARD -1
#define STOPPED 0

#define DEFAULT_TIMEOUT 4000


#define MOD 0
#define IN1 1
#define IN2 2
#define REQ_PINS 3

#define MAX_SERIAL_LEN 15

const PROGMEM char SYS_NAME[] = "RCRamDriver";

constexpr unsigned char MAX_DUTY_STEER = 0.42 * 255;
constexpr unsigned char MAX_DUTY_DRIVE = 0.75 * 255;
constexpr unsigned char DUTY_STEER_HOLD = 0.4 * MAX_DUTY_STEER;

struct Motor {
    char state;
    unsigned char speed;
    char pins[REQ_PINS];
};

Motor driveMotor, steerMotor;

unsigned long driveInstructionRecv = 0;
unsigned long steerInstructionRecv = 0;
unsigned int driveInstructionTimeout = 0;
unsigned int steerInstructionTimeout = 0;
unsigned char steerFader = 0;

struct Buffer {
    unsigned char *data;
    unsigned char limit;    // How many bytes in the buf
    unsigned char length;   // How many bytes used
};

Buffer inputBuf, replyBuf;

unsigned char inputBufData[MAX_SERIAL_LEN];
unsigned char replyBufData[MAX_SERIAL_LEN];

void setup() {
    Serial.begin(115200);
    inputBuf.data = inputBufData;
    replyBuf.data = replyBufData;
    inputBuf.limit = MAX_SERIAL_LEN;
    replyBuf.limit = MAX_SERIAL_LEN;
    
    setupMotor(&driveMotor, 3, 2, 4);
    setupMotor(&steerMotor, 6, 7, 8);
}

void loop() {
    updateMotorOutputs(&driveMotor);
    updateMotorOutputs(&steerMotor);

    monitorDriveMotor(&driveMotor);
}
