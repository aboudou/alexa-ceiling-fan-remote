/*
 * Source : https://github.com/qwertzguy/Spark-Core-IRremote
 */

#include "IRremote.h"
#include "application.h"

IRsend::IRsend(int irPin) : irPin(irPin) {};

void IRsend::mark(int time) {
  // Sends an IR mark (frequency burst output) for the specified number of microseconds.
  noInterrupts();
  
  while (time > 0) {
    digitalWrite(irPin, HIGH); // this takes about 3 microseconds to happen
    delayMicroseconds(burstWait);
    digitalWrite(irPin, LOW); // this also takes about 3 microseconds
    delayMicroseconds(burstWait);
 
    time -= burstLength;
  }
  
  interrupts();
}

void IRsend::space(int time) {
  // Sends an IR space (no output) for the specified number of microseconds.
  digitalWrite(irPin, LOW); // Takes about 3 microsecondes
  if (time > 3) {
    delayMicroseconds(time - 3);
  }
}

void IRsend::enableIROut(int khz) {
  // Enables IR output.  The khz value controls the modulation frequency in kilohertz.
  // MAX frequency is 166khz.
  pinMode(irPin, OUTPUT);
  digitalWrite(irPin, LOW);

  // This is the time to wait with the IR LED on and off to make the frequency, in microseconds.
  // The - 3.0 at the end is because digitalWrite() takes about 3 microseconds. Info from:
  // https://github.com/eflynch/sparkcoreiremitter/blob/master/ir_emitter/ir_emitter.ino
  burstWait = round(1.0 / khz * 1000.0 / 2.0 - 3.0);
  // This is the total time of a period, in microseconds.
  burstLength = round(1.0 / khz * 1000.0);
}