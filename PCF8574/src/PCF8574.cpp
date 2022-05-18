/**
 * serial-readline.cpp - Library for buffered serial line reading
 * Created by MSZ, May 18, 2022.
 * Released into the public domain.
*/

#include "PCF8574.h"

void digitalWrite(PCF8574 &expander, int pin, int value) {
	int reg = expander.getReg();
	expander.write(value ? reg | (1 << pin) : reg &~ (1 << pin));
}

/** PCF8574 does not support different pin modes. Input mode is just a HIGH state (high state is always pull-up). It also does not support pull-down. */
void pinMode(PCF8574 &expander, int pin, int mode) {
	if(mode != OUTPUT) digitalWrite(expander, pin, HIGH);
}

int digitalRead(PCF8574 &expander, int pin) {
	return (expander.read() & (1 << pin)) ? HIGH : LOW;
}

void digitalToggle(PCF8574 &expander, int pin) {
	int reg = expander.getReg();
	expander.write(reg ^ (1 << pin));
}

int PCF8574::combinationToAddress(int A2_A1_A0, bool version_A) {
	if(A2_A1_A0 < 0 || A2_A1_A0 > 7) return -1;
	if(version_A) return 0x38 + A2_A1_A0;
	return 0x20 + A2_A1_A0;
}
