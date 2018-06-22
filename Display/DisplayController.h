#ifndef __DISPLAY_CONTROLLER_H__
#define __DISPLAY_CONTROLLER_H__

#define NO_ANIMATION_CODE 0
#define SELECT_ANIMATION_CODE 1
#define DROP_ANIMATION_CODE 2
#define WON_ANIMATION_CODE 3

#define SELECT_ANIMATION_SWITCH_VALUE 125
#define DROP_ANIMATION_SWITCH_VALUE 10

#include <stdint.h>

#include "DisplayData.h"
#include "DataVisualizer.h"

struct SelectAnimationData {
	uint8_t column;
	uint8_t color; // 0b00000001 = Red, 0b00000010 = Green, 0b00000100 = Blue and all combinations
	bool isActive;
	SelectAnimationData() : column(0), color(0), isActive(false) {}
};

struct DropAnimationData {
	uint8_t column;
	uint8_t color;  // 0b00000001 = Red, 0b00000010 = Green, 0b00000100 = Blue and all combinations
	uint8_t currentRow;
	uint8_t destinationRow;
	DropAnimationData() : column(0), color(0), currentRow(0), destinationRow(0) {}
};

class DisplayController {
/*******************************/
/* Properties                  */
private:
	DisplayData data;
	DataVisualizer visualizer;
	
	/*
	 * Save which animation is currently active
	 * 0: no animation
	 * 1: select animation
	 * 2: drop animation
	 * 3: won animation
	 */
	uint8_t animationSelector;
	
	SelectAnimationData selectAnimationData;
	DropAnimationData dropAnimationData;
	
public:
	// Timer counter for select and drop animation
	volatile uint32_t animationCounter;
	
/*******************************/
/* Methods                     */
private:
	/**
	 * Update the select animation
	 */
	void updateSelectAnimation();
	
	/**
	 * Updates the drop animation
	 */	
	void updateDropAnimation();
	
	/**
	 * Stops the drop animation
	 */
	void stopDropAnimation();

public:
	DisplayController();
	
	/**
	 * Zeigt ein Blinken einer LED oben in einer bestimmten Spalte an
	 * @param column Spalte in der die Animation angezeigt werden soll
	 * @param color Farbe in der die Animation angezeigt werden soll
	 *		0b00000001 = Red, 0b00000010 = Green, 0b00000100 = Blue und alle Kombinationen
	 */
	void startSelectAnimation(uint8_t column, uint8_t color);
	
	/**
	 * Stop the animation of column selection
	 */
	void stopSelectAnimation();
	
	/**
	 * Zeigt eine Animation wie ein Coin entlang einer Spalte runter f‰llt. Die animation wird gestoppt sobald der
	 * Coin sein Ziel erreicht hat
	 * @param column Spalte in der die Animation angezeigt werden soll
	 * @param destinationRow Reihe bzw. LED bis zu (einschlieﬂlich) der die Animation angezeigt werden soll 
	 * @param color Farbe in der die Animation angezeigt werden soll
	 *		0b00000001 = Red, 0b00000010 = Green, 0b00000100 = Blue und alle Kombinationen
	 */
	void startDropAnimation(uint8_t column, uint8_t color, uint8_t destinationRow);
	
	/**
	 * Updates the visual data
	 */
	void update();
};

#endif
