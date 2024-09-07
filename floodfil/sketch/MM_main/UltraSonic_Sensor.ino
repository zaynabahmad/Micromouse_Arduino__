

float getDistance(char TRIGGER_PIN,char ECHO_PIN) {
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);

    long startTime = micros();
    while (digitalRead(ECHO_PIN) == LOW) {
        if (micros() - startTime > 10000) {
            return -1.0;
        }
    }
    long echoTime = micros() - startTime;

    float distance = echoTime * 0.0343 / 2;

    return distance;
}

