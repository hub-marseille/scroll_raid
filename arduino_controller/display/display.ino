#include <LedControl.h>

#define MAX_MAX       4
#define LED_INTENSITY 0x5

byte  heart[3][8] = { {B00111000, B01000100, B01000010, B00100001, B00100001, B01000010, B01000100, B00111000},   // empty
                      {B00111000, B01000100, B01000010, B00100001, B00111111, B01111110, B01111100, B00111000},   // half
                      {B00111000, B01111100, B01111110, B00111111, B00111111, B01111110, B01111100, B00111000} }; // full

LedControl matrix(10, 14, 16, MAX_MAX);

void setup() {
  for (int it = 0; it < MAX_MAX; ++it)
  {
    matrix.shutdown(it, false);
    matrix.setIntensity(it, LED_INTENSITY);
    matrix.clearDisplay(it);
  }
}

void  printDigitOnMatrix(int matrixIt, long value, int offset, bool isNeg) {
  matrix.setDigit(matrixIt, offset, (byte)(value % 10), false);
  if (value / 10 > 0)
    printDigitOnMatrix(matrixIt, value / 10, offset - 1, isNeg);
  else if (isNeg)
    matrix.setChar(matrixIt, offset - 1, (byte)'-', false);
}

bool  printNumberOnMatrix(int matrixIt, long value) {
  bool  isNeg = false;
 
  if (matrixIt > (MAX_MAX - 1) || value < -9999999 || value > 99999999)
    return (false);
  if (value < 0) {
    value *= -1;
    isNeg = true;
  }
  printDigitOnMatrix(matrixIt, value, 7, isNeg);
  return (true);
}

void loop() {
  for (int id = 0; id < MAX_MAX - 1; ++id)
  {
    for (int column = 0; column < 8; ++column)
    {
      matrix.setColumn(id, column, heart[id][column]);
    }
    delay(100);
  }
if (!printNumberOnMatrix(MAX_MAX - 1, 1337))
  matrix.setChar(MAX_MAX - 1, 0, (byte)'H', false);
delay(1000);
}
