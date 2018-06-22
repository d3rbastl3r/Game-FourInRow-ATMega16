#ifndef __DATA_VISUALIZER_H__
#define __DATA_VISUALIZER_H__

#include <avr/io.h>

#include "DisplayData.h"

// SER-Ports
#define PORT_LANE_0 PC7
#define PORT_LANE_1 PC6
#define PORT_LANE_2 PC5
#define PORT_LANE_3 PC4
#define PORT_LANE_4 PC3
#define PORT_LANE_5 PC2
#define PORT_LANE_6 PC1

#define PORT_STORE_CLOCK PA6 // Storage Register Clock Line. Speichert den SER-Wert
#define PORT_LATCH PA5 // RCLK = Register Clock. Schiebt die Daten von der Eingabe in die Ausgabe

#define PORT_NOT_CLEAR PA7 // Serial Clear Line. Not Clearing = HIGH
#define PORT_NOT_OE PA4 // LOW -> All outputs are enabled

class DataVisualizer {
/*******************************/
/* Properties                  */
private:

/*******************************/
/* Methods                     */
public:
	DataVisualizer();
	void visualize(DisplayData displayData);
	void enableOutputs();
	void disableOutputs();
	void clear();
	
private:
	void init();
	void shiftBits();
	void setForColumn(uint8_t column);
	void unsetForColumn(uint8_t column);
};

#endif
