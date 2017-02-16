#include <LedControl.h>
#include "MyDisplay.h"

MyDisplay		g_display;

void setup() {
	//g_display.setFillCount(false);
}

void loop() {
	for (int i = 100; i > -101; --i)
	{
		g_display.printNumber(i);
		delay(100);
	}
	for (int i = -100; i < 101; ++i)
	{
		g_display.printNumber(i);
		delay(100);
	}
}
