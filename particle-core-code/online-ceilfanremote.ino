/*
 * Ceiling fan remote control.
 * Official remote control is based on a SM5021BL chipset.
 * 
 * http://pdf1.alldatasheet.com/datasheet-pdf/view/124369/ANALOGICTECH/SM5021B.html
 * 
 */

#include "IRremote.h"

IRsend irsend(D1);


// Clock signal : 455Khz / 192 = 2,3697916667 kHz ( = 421,978022 µs period)
#define CLKPERIOD_US 422

/*
 * Buttons used
 * 
 * K1 : speed 3
 * K2 : n.a.
 * K3 : speed 2
 * K4 : on / off
 * K5 : speed 0
 * K6 : dimmer
 * K7 : speed 1
 * K8 : n.a.
 */

// Start bits
#define SB1 1
#define SB2 1
#define SB3 0

// Custom code bits
#define CCB1 0
#define CCB2 0

// Buttons bits sequences
boolean frameOnoff[]  = {SB1, SB2, SB3, CCB1, CCB2, 0, 0, 0, 1, 0, 0, 0}; // K4
boolean frameDimmer[] = {SB1, SB2, SB3, CCB1, CCB2, 0, 1, 0, 0, 0, 0, 0}; // K6
boolean frameSpeed0[] = {SB1, SB2, SB3, CCB1, CCB2, 0, 0, 1, 0, 0, 0, 0}; // K5
boolean frameSpeed1[] = {SB1, SB2, SB3, CCB1, CCB2, 1, 0, 0, 0, 0, 1, 1}; // K7
boolean frameSpeed2[] = {SB1, SB2, SB3, CCB1, CCB2, 0, 0, 0, 0, 1, 0, 0}; // K3
boolean frameSpeed3[] = {SB1, SB2, SB3, CCB1, CCB2, 0, 0, 0, 0, 0, 0, 1}; // K1


void setup() {
    // Cloud functions declaration
    Particle.function("cmdOnOff", cmdOnOff);
    Particle.function("cmdDimmer", cmdDimmer);
    Particle.function("cmdSpeed0", cmdSpeed0);
    Particle.function("cmdSpeed1", cmdSpeed1);
    Particle.function("cmdSpeed2", cmdSpeed2);
    Particle.function("cmdSpeed3", cmdSpeed3);
    
    // 38kHz modulation frequency
    irsend.enableIROut(38);
}

void loop() {
  // Loop forever
}


int cmdOnOff(String command) {
    sendFullMessage(frameOnoff);
    return 1;
}


int cmdDimmer(String command) {
    sendFullMessage(frameDimmer);
    return 1;
}


int cmdSpeed0(String command) {
    sendFullMessage(frameSpeed0);
    return 1;
}


int cmdSpeed1(String command) {
    sendFullMessage(frameSpeed1);
    return 1;
}


int cmdSpeed2(String command) {
    sendFullMessage(frameSpeed2);
    return 1;
}


int cmdSpeed3(String command) {
    sendFullMessage(frameSpeed3);
    return 1;
}


void sendFullMessage(boolean frame[]) {
    // A message is made with 4 identical frames.
    for (int i = 0; i < 4; i++) {
        sendSingleFrame(frame);
    }
}


void sendSingleFrame(boolean frame[]) {
    
    // Sending frame data
    for (int i = 0; i < 12; i++) {
        if (frame[i] == 0) {
            sendZero();
        } else {
            sendOne();
        }
    }
    
    // Ending frame with for empty bits
    for (int i = 0; i < 4; i++) {
        irsend.space(CLKPERIOD_US*4);
    }
    
}


// logical 0 : 1 sysclock HIGH, 3 sysclock LOW
void sendZero() {
    irsend.mark(CLKPERIOD_US);
    irsend.space(CLKPERIOD_US * 3);
}


// logical 1 : 3 sysclock HIGH, 1 sysclock LOW
void sendOne() {
    irsend.mark(CLKPERIOD_US * 3);
    irsend.space(CLKPERIOD_US);
}