/* Copyright 2020 by author Daniel Tierney.
 * All Rights Reserved.
 * This copyright notice must appear in all header files.
 */

void updateMotorOutputs(Motor *m) {
    switch (m->state) {
        case STOPPED:
            digitalWrite(m->pins[IN1], LOW);
            digitalWrite(m->pins[IN2], LOW);
            break;
        case FORWARD:
            digitalWrite(m->pins[IN1], HIGH);
            digitalWrite(m->pins[IN2], LOW);
            break;
        case BACKWARD:
            digitalWrite(m->pins[IN1], LOW);
            digitalWrite(m->pins[IN2], HIGH);
            break;
    }
    analogWrite(m->pins[MOD], min(m->speed, MAX_DUTY_DRIVE));
}

void setupMotor(Motor *m, unsigned char mod, unsigned char in1, unsigned char in2) {
    m->state = STOPPED;
    m->speed = 0;
    m->pins[MOD] = mod;
    m->pins[IN1] = in1;
    m->pins[IN2] = in2;
    pinMode(mod, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
}

void monitorDriveMotor(Motor *m) {
    if (millis() - driveInstructionRecv > driveInstructionTimeout) {
        driveMotor.state = STOPPED;
        driveMotor.speed = 0;
    }
}

void monitorSteerMotor(Motor *m) {
    if (millis() - steerInstructionRecv > steerInstructionTimeout) {
        steerMotor.state = STOPPED;
        steerMotor.speed = 0;
        steerFader = 0;
        return;
    }
    static unsigned long lastCycle;
    if (steerMotor.state != STOPPED && steerMotor.speed > DUTY_STEER_HOLD && millis() - lastCycle > 50) {
        lastCycle = millis();
        steerMotor.speed -= min(++steerFader, steerMotor.speed - DUTY_STEER_HOLD);
    }
}
