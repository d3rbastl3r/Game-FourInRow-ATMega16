#include "DataVisualizer.h"

#include "DisplayData.h"

DataVisualizer::DataVisualizer() {
	this->init();
}

void DataVisualizer::visualize(DisplayData displayData) {
	PORTA &= ~(1<<PORT_LATCH);
	
	for (uint8_t row=0; row<8; ++row) {
		uint8_t bit = 1<<row;

		for (uint8_t color=0; color<3; ++color) { // 0=blue, 1=green, 2=red
			for (uint8_t column=0; column<7; ++column) {
				
				// RED
				if (color == 0) {
					if (displayData.getBlueData(column) & bit) setForColumn(column);
					else unsetForColumn(column);
				}
				
				// GREEN
				else if (color == 1) {
					if (displayData.getGreenData(column) & bit) setForColumn(column);
					else unsetForColumn(column);
				}
				
				// BLUE
				else {
					if (displayData.getRedData(column) & bit) setForColumn(column);
					else unsetForColumn(column);
				}
			}
			shiftBits();
		}
	}
	
	PORTA |= (1<<PORT_LATCH);
}

void DataVisualizer::enableOutputs() {
	PORTA &= ~(1<<PORT_NOT_OE);
}

void DataVisualizer::disableOutputs() {
	PORTA |= (1<<PORT_NOT_OE);
}

void DataVisualizer::clear() {
	PORTA &= ~(1<<PORT_NOT_CLEAR);
	PORTA |= (1<<PORT_NOT_CLEAR);
}

/*
 * ______     _            _
 * | ___ \   (_)          | |
 * | |_/ / __ ___   ____ _| |_ ___
 * |  __/ '__| \ \ / / _` | __/ _ \
 * | |  | |  | |\ V / (_| | ||  __/
 * \_|  |_|  |_| \_/ \__,_|\__\___|
*/

void DataVisualizer::shiftBits() {
	PORTA |= (1<<PORT_STORE_CLOCK);
	PORTA &= ~(1<<PORT_STORE_CLOCK);
}

void DataVisualizer::setForColumn(uint8_t column) {
	switch(column) {
		case 0:
			PORTC |= (1<<PORT_LANE_0);
			break;
			
		case 1:
			PORTC |= (1<<PORT_LANE_1);
			break;
			
		case 2:
			PORTC |= (1<<PORT_LANE_2);
			break;
			
		case 3:
			PORTC |= (1<<PORT_LANE_3);
			break;
			
		case 4:
			PORTC |= (1<<PORT_LANE_4);
			break;
			
		case 5:
			PORTC |= (1<<PORT_LANE_5);
			break;
			
		case 6:
			PORTC |= (1<<PORT_LANE_6);
			break;
	}
}

void DataVisualizer::unsetForColumn(uint8_t column) {
	switch(column) {
		case 0:
		PORTC &= ~(1<<PORT_LANE_0);
		break;
		
		case 1:
		PORTC &= ~(1<<PORT_LANE_1);
		break;
		
		case 2:
		PORTC &= ~(1<<PORT_LANE_2);
		break;
		
		case 3:
		PORTC &= ~(1<<PORT_LANE_3);
		break;
		
		case 4:
		PORTC &= ~(1<<PORT_LANE_4);
		break;
		
		case 5:
		PORTC &= ~(1<<PORT_LANE_5);
		break;
		
		case 6:
		PORTC &= ~(1<<PORT_LANE_6);
		break;
	}
}

void DataVisualizer::init() {
	// Initialisiert die Ports
	DDRC |= (1<<PORT_LANE_0);
	DDRC |= (1<<PORT_LANE_1);
	DDRC |= (1<<PORT_LANE_2);
	DDRC |= (1<<PORT_LANE_3);
	DDRC |= (1<<PORT_LANE_4);
	DDRC |= (1<<PORT_LANE_5);
	DDRC |= (1<<PORT_LANE_6);
	
	DDRA |= (1<<PORT_NOT_CLEAR);
	DDRA |= (1<<PORT_STORE_CLOCK);
	DDRA |= (1<<PORT_LATCH);
	DDRA |= (1<<PORT_NOT_OE);
	
	// Setzt den Shift- und Latch-Bit auf LOW
	PORTA &= ~(1<<PORT_STORE_CLOCK);
	PORTA &= ~(1<<PORT_LATCH);
}

