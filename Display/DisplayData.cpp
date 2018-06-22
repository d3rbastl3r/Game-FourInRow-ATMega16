#include "DisplayData.h"

DisplayData::DisplayData() {
	// Initialize all values with zero
	for (uint8_t column=0; column<8; ++column) {
		this->red[column] = 0;
		this->green[column] = 0;
		this->blue[column] = 0;
	}
}
	
uint8_t DisplayData::getRedData(uint8_t column) {
	return this->red[column];
}

uint8_t DisplayData::getGreenData(uint8_t column) {
	return this->green[column];
}

uint8_t DisplayData::getBlueData(uint8_t column) {
	return this->blue[column];
}

void DisplayData::setRedPixel(uint8_t column, uint8_t row) {
	this->red[column] |= (1<<row);
}
	
void DisplayData::setGreenPixel(uint8_t column, uint8_t row) {
	this->green[column] |= (1<<row);
}
	
void DisplayData::setBluePixel(uint8_t column, uint8_t row) {
	this->blue[column] |= (1<<row);
}
	
void DisplayData::unsetRedPixel(uint8_t column, uint8_t row) {
	this->red[column] &= ~(1<<row);
}
	
void DisplayData::unsetGreenPixel(uint8_t column, uint8_t row) {
	this->green[column] &= ~(1<<row);
}
	
void DisplayData::unsetBluePixel(uint8_t column, uint8_t row) {
	this->blue[column] &= ~(1<<row);
}

void DisplayData::setPixel(uint8_t column, uint8_t row, uint8_t color) {
	if (color & 0b00000001) { // Set Red
		this->setRedPixel(column, row);
	}
	
	if (color & 0b00000010) { // Set Green
		this->setGreenPixel(column, row);
	}
	
	if (color & 0b00000100) { // Set Blue
		this->setBluePixel(column, row);
	}
}

void DisplayData::unsetPixel(uint8_t column, uint8_t row, uint8_t color) {
	if (color & 0b00000001) { // Set Red
		this->unsetRedPixel(column, row);
	}
	
	if (color & 0b00000010) { // Set Green
		this->unsetGreenPixel(column, row);
	}
	
	if (color & 0b00000100) { // Set Blue
		this->unsetBluePixel(column, row);
	}
}