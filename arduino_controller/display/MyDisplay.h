// display.h

#ifndef _DISPLAY_h
#define _DISPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <LedControl.h>

#define		MATRIX_DIN	10
#define		MATRIX_CS	16
#define		MATRIX_CLK	14
#define		MATRIX_COUNT	4
#define		SCORE_MATRIX	3
#define		DIGIT_COUNT		8

#define MAX_MAX         0x4
#define LED_INTENSITY   0x5
#define NB_HEARTS       0x3
#define NB_HEART_CELLS  0x8

class MyDisplay
{
public:
	MyDisplay();
	~MyDisplay();
	bool	printNumber(long value);
	void clearNumberArtefacts(int value);
	void	setFillCount(bool);
	bool	getFillCount() const;
	void	clearDigits();

private:
	LedControl	mMatrix;
	bool		mFillCount;
	long		mLastNumber;
	unsigned short	mLastLife;

	void	printDigit(long value, int offset, bool isNeg);
	void	printByteArray(int matrixIt, byte array[8]);
	void	fillDigits(char value);
};

#endif

