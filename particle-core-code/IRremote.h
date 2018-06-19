/*
 * Source : https://github.com/qwertzguy/Spark-Core-IRremote
 */

#ifndef IRremote_h
#define IRremote_h

class IRsend
{
  const int irPin;
  int burstWait;
  int burstLength;

public:
  IRsend(int irPin);

  void enableIROut(int khz);
  void mark(int usec);
  void space(int usec);
}
;

#endif