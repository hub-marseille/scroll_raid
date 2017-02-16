// 
// salut.
// 

#include "MyDisplay.h"

 static byte  heart[3][8] = {
	 { B00111000, B01000100, B01000010, B00100001, B00100001, B01000010, B01000100, B00111000 },   // empty
	/*
	00000000
	01100110
	10011001
	10000001
	01000010
	00100100
	00011000
	*/
	 { B00111000, B01000100, B01000010, B00100001, B00111111, B01111110, B01111100, B00111000 },   // half
	/*
	00000000
	01100110
	10011111
	10001111
	10001111
	01001110
	00101100
	00011000
	*/
	 { B00111000, B01111100, B01111110, B00111111, B00111111, B01111110, B01111100, B00111000 } }; // full
	/*
	00000000
	01100110
	11111111
	11111111
	11111111
	01111110
	00111100
	00011000
	*/

MyDisplay::MyDisplay()
	: mMatrix(MATRIX_DIN, MATRIX_CLK, MATRIX_CS, MATRIX_COUNT)
{
	mFillCount = true;
	for (short it = 0; it < MATRIX_COUNT; ++it) {
		mMatrix.clearDisplay(it);
		mMatrix.setIntensity(it, LED_INTENSITY);
		mMatrix.shutdown(it, false);
	}
	printByteArray(0, heart[0]);
	printByteArray(1, heart[0]);
	printByteArray(2, heart[0]);
	mLastLife = 0;
	printNumber(0);
	mLastNumber = 0;
}

MyDisplay::~MyDisplay()
{
}

void	MyDisplay::printByteArray(int matrixIt, byte data[8]) {
	if (matrixIt > MATRIX_COUNT - 1)
		return;
	mMatrix.setColumn(matrixIt, 0, data[0]);
	mMatrix.setColumn(matrixIt, 1, data[1]);
	mMatrix.setColumn(matrixIt, 2, data[2]);
	mMatrix.setColumn(matrixIt, 3, data[3]);
	mMatrix.setColumn(matrixIt, 4, data[4]);
	mMatrix.setColumn(matrixIt, 5, data[5]);
	mMatrix.setColumn(matrixIt, 6, data[6]);
	mMatrix.setColumn(matrixIt, 7, data[7]);
}

void MyDisplay::fillDigits(char value)
{
	mMatrix.setDigit(SCORE_MATRIX, 0, (byte)value, false);
	mMatrix.setDigit(SCORE_MATRIX, 1, (byte)value, false);
	mMatrix.setDigit(SCORE_MATRIX, 2, (byte)value, false);
	mMatrix.setDigit(SCORE_MATRIX, 3, (byte)value, false);
	mMatrix.setDigit(SCORE_MATRIX, 4, (byte)value, false);
	mMatrix.setDigit(SCORE_MATRIX, 5, (byte)value, false);
	mMatrix.setDigit(SCORE_MATRIX, 6, (byte)value, false);
	mMatrix.setDigit(SCORE_MATRIX, 7, (byte)value, false);
}

unsigned char	MyDisplay::countDigits(long value)
{
	unsigned char	count = 0;

	if (value < 0) {
		count += 1;
		value *= -1;
	}
	while (value > 0)
	{
		count += 1;
		value /= 10;
	}
	return (count);
}

bool	MyDisplay::printNumber(long value)
{
	bool  isNeg = false;
	unsigned char	lenght = countDigits(value);

	if (lenght >= 8)
		return (false);
	if (lenght < lastLenght)
		; // TODO clear all display
	lastLenght = lenght;
	if (value < 0) {
		value *= -1;
		isNeg = true;
	}
	printDigit(value, DIGIT_COUNT - 1, isNeg);
	mLastNumber = value;
	return (true);
}

void	MyDisplay::clearNumberArtefacts(int value)
{
	if (mFillCount) {

	}
	else {

	}
}

void MyDisplay::setFillCount(bool value)
{
	this->mFillCount = value;
	clearDigits();
}

bool MyDisplay::getFillCount() const
{
	return (mFillCount);
}

void MyDisplay::clearDigits()
{
	mMatrix.clearDisplay(SCORE_MATRIX);
}

void	MyDisplay::printDigit(long value, int offset, bool isNeg)
{
	mMatrix.setDigit(SCORE_MATRIX, offset, (byte)(value % 10), false);
	if (value / 10 > 0)
		printDigit(value / 10, offset - 1, isNeg);
	else
	{
		if (mFillCount)
			while (offset > 0 && !(offset == 1 && isNeg)) {
				mMatrix.setDigit(SCORE_MATRIX, offset - 1, 0, false);
				offset -= 1;
			}
		if (isNeg)
			mMatrix.setChar(SCORE_MATRIX, offset - 1, (byte)'-', false);
	}
}
