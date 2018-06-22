#include "DisplayController.h"

DisplayController::DisplayController() : data(DisplayData()),
										 visualizer(DataVisualizer()),
										 animationSelector(0),
										 selectAnimationData(SelectAnimationData()),
										 dropAnimationData(DropAnimationData()),
										 animationCounter(0) {
	
	this->visualizer.enableOutputs();
	this->visualizer.clear();
}

void DisplayController::startSelectAnimation(uint8_t column, uint8_t color) {
	this->animationSelector = SELECT_ANIMATION_CODE;
	
	this->selectAnimationData.column = column;
	this->selectAnimationData.color = color;
	this->selectAnimationData.isActive = false;
	
	this->animationCounter = 0;
}

void DisplayController::stopSelectAnimation() {
	this->animationSelector = NO_ANIMATION_CODE;
}

void DisplayController::startDropAnimation(uint8_t column, uint8_t color, uint8_t destinationRow) {
	this->animationSelector = DROP_ANIMATION_CODE;
	
	this->dropAnimationData.column = column;
	this->dropAnimationData.color = color;
	this->dropAnimationData.currentRow = 0;
	this->dropAnimationData.destinationRow = destinationRow;
	
	this->animationCounter = 0;
}

void DisplayController::update() {
	switch (this->animationSelector) {
		case SELECT_ANIMATION_CODE:
			this->updateSelectAnimation();
			break;
			
		case DROP_ANIMATION_CODE:
			this->updateDropAnimation();
			break;
	}
}

/*
 * ______     _            _
 * | ___ \   (_)          | |
 * | |_/ / __ ___   ____ _| |_ ___
 * |  __/ '__| \ \ / / _` | __/ _ \
 * | |  | |  | |\ V / (_| | ||  __/
 * \_|  |_|  |_| \_/ \__,_|\__\___|
*/

void DisplayController::updateSelectAnimation() {
	if (this->animationCounter >= SELECT_ANIMATION_SWITCH_VALUE) {
		this->animationCounter = 0;
		
		if (this->selectAnimationData.isActive) {
			this->data.setPixel(
				this->selectAnimationData.column,
				0,
				this->selectAnimationData.color
			);
			
		} else {
			this->data.unsetPixel(
				this->selectAnimationData.column,
				0,
				this->selectAnimationData.color
			);
		}
		
		this->selectAnimationData.isActive = !this->selectAnimationData.isActive;
		this->visualizer.visualize(this->data);
	}
}

void DisplayController::updateDropAnimation() {
	if (this->animationCounter >= DROP_ANIMATION_SWITCH_VALUE) {
		this->animationCounter = 0;
		
		if (this->dropAnimationData.currentRow == this->dropAnimationData.destinationRow) {
			this->stopDropAnimation();
			
		} else {
			if (this->dropAnimationData.currentRow > 0) {
				this->data.unsetPixel(
					this->dropAnimationData.column,
					this->dropAnimationData.currentRow-1,
					this->dropAnimationData.color
				);
			}
			
			this->data.setPixel(
				this->dropAnimationData.column,
				this->dropAnimationData.currentRow,
				this->dropAnimationData.color
			);
			
			++this->dropAnimationData.currentRow;
		}
		
		this->visualizer.visualize(this->data);
	}
}

void DisplayController::stopDropAnimation() {
	this->animationSelector = NO_ANIMATION_CODE;
}