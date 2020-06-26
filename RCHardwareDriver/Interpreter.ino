void performInstruction(Buffer *instr, Buffer *response) {
    if (instr->length > 0) {
        switch (instr->data[0]) {
        case 0:
            // Instr 0: Ping~ No data -> ACK, Data 1 -> Version, Data 2 -> Name
            if (instr->length != 1) {
                if (instr->data[1] == 1) {
                    appendToResponse(response, VERSION_MAJOR);
                    appendToResponse(response, VERSION_MINOR);
                    appendToResponse(response, VERSION_PATCH);
                    break;
                } else if (instr->data[1] == 2) {
                    for (byte i = 0; SYS_NAME[i] != '\0'; i++) appendToResponse(response, SYS_NAME[i]);
                    break;
                }
            }
            appendToResponse(response, ACK);
            break;
        case 1:
            // Instr 1: Drive Motor / Response: None / Data: State+Speed+(Timeout(ds)|None->default)
            if (instr->length >= 3) {
                driveMotor.state = instr->data[1];
                driveMotor.speed = instr->data[2];
                if (instr->length >= 4) {
                    driveInstructionTimeout = instr->data[3] * 100; // Convert from deciseconds to milliseconds
                } else {
                    driveInstructionTimeout = DEFAULT_TIMEOUT;
                }
                driveInstructionRecv = millis();
            }
            break;
        case 2:
            // Instr 2: Steering / No response / Data: State (Default+Hold), Speed, Timeout
            if (instr->length >= 3) {
                if (instr->data[1] != 2) {
                    steerMotor.state = instr->data[1];
                    steerMotor.speed = instr->data[2];
                    steerFader = 0;
                }
                if (instr->length >= 4) {
                    steerInstructionTimeout = instr->data[3] * 100; // Convert from deciseconds to milliseconds
                } else {
                    steerInstructionTimeout = DEFAULT_TIMEOUT;
                }
                steerInstructionRecv = millis();
            }
            break;
        default:
            // No Instr / Response: NAK (ASCII 21) / Data: Ignored
            appendToResponse(response, NAK);
            break;
        }
    }
}

void serialEvent() {
    while (Serial.available()) {
        unsigned char ind = Serial.read();
        if (inputBuf.data[inputBuf.length] == ESC) {
            inputBuf.data[inputBuf.length++] = ind;
        } else if (ind == EOT) {
            performInstruction(&inputBuf, &replyBuf);
            if (replyBuf.length > 0) {
                for (byte i = 0; i < replyBuf.length; ++i) {
                    if (replyBuf.data[i] == EOT || replyBuf.data[i] == ESC) {
                        Serial.write(ESC);
                    }
                    Serial.write(replyBuf.data[i]);
                }
                Serial.write(EOT);
            }
            replyBuf.length = 0;
            inputBuf.length = 0;
        } else if (inputBuf.length < inputBuf.limit) {
            inputBuf.data[inputBuf.length] = ind;
            if (ind != ESC) {
                ++inputBuf.length;
            }
        }
    }
       
}

bool appendToResponse(Buffer *response, unsigned char a) {
    if (response->length < response->limit) {
        response->data[response->length++] = a;
        return true;
    }
    return false;
}

void clearBuffer(Buffer *buf) {
    buf->length = buf->limit;
    do {
        buf->data[--buf->limit] = 0;
    } while (buf->limit > 0);
    buf->limit = buf->length;
    buf->length = 0;
}
