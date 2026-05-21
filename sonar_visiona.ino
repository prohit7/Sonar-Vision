#include <Arduino.h>
#include <ESP32Servo.h>

#define TRIG_PIN 5
#define ECHO_PIN 18
#define SERVO_PIN 27

Servo myServo;

long getDistance()
{
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);

    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH, 30000);

    long distance = duration * 0.034 / 2;

    return distance;
}

void setup()
{
    Serial.begin(115200);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    myServo.setPeriodHertz(50);
    myServo.attach(SERVO_PIN, 500, 2400);

    Serial.println("ESP32 Radar Scanner Started");
}

void loop()
{
    // Sweep from 0 to 180
    for(int angle = 0; angle <= 180; angle++)
    {
        myServo.write(angle);

        delay(20);

        long distance = getDistance();

        Serial.print(angle);
        Serial.print(",");
        Serial.println(distance);
    }

    // Sweep back from 180 to 0
    for(int angle = 180; angle >= 0; angle--)
    {
        myServo.write(angle);

        delay(20);

        long distance = getDistance();

        Serial.print(angle);
        Serial.print(",");
        Serial.println(distance);
    }
}