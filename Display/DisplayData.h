/************************************************************************/
/* Klasse zum Speichern von visuellen Daten für die Anzeige             */
/*                                                                      */
/* Gespeichert wird jede Farbe in einem 8 x 7 Bit Array.                */
/* Jedes Feld representiert eine LED-Leiste, wobei unter dem Index 0    */
/* die Daten für die linke Leiste und unter dem Index 6 die Daten für   */
/* die rechte Leiste gespeichert werden.                                */
/* Das höherwertige Bit spricht eine LED weiter unten an, 0b00000001    */
/* würde aomit die LED ganz oben in der Anzeige aktivieren              */
/************************************************************************/

#ifndef __DISPLAY_DATA_H__
#define __DISPLAY_DATA_H__

#include <stdint.h>

class DisplayData {
/*******************************/
/* Properties                  */
private:
	// Array position represents a column
	uint8_t red[7];
	uint8_t green[7];
	uint8_t blue[7];

/*******************************/
/* Methods                     */
public:
	DisplayData();
	
	uint8_t getRedData(uint8_t column);
	uint8_t getGreenData(uint8_t column);
	uint8_t getBlueData(uint8_t column);
	
	void setRedPixel(uint8_t column, uint8_t row);
	void setGreenPixel(uint8_t column, uint8_t row);
	void setBluePixel(uint8_t column, uint8_t row);
	
	void unsetRedPixel(uint8_t column, uint8_t row);
	void unsetGreenPixel(uint8_t column, uint8_t row);
	void unsetBluePixel(uint8_t column, uint8_t row);
	
	/**
	 * Setzt ein bestimmtes Pixel einer bestimmten Farbe
	 * @param column Spalte in der das Pixel gesetzt werden soll
	 * @param row Zeile in der das Pixel gesetzt werden soll
	 * @param color Farbe des Pixels
	 *			0b00000001 = Red, 0b00000010 = Green, 0b00000100 = Blue und alle Kombinationen
	 */
	void setPixel(uint8_t column, uint8_t row, uint8_t color);
	
	/**
	 * Entfernt ein bestimmtes Pixel einer bestimmten Farbe
	 * @param column Spalte in der das Pixel entfernt werden soll
	 * @param row Zeile in der das Pixel entfernt werden soll
	 * @param color Farbe an der angegebenen Position die entfernt werden soll
	 *			0b00000001 = Red, 0b00000010 = Green, 0b00000100 = Blue und alle Kombinationen
	 */
	void unsetPixel(uint8_t column, uint8_t row, uint8_t color);
};

#endif
