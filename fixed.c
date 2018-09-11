// ******** fixed.h ************** 
// Authors: Ryan Mitchell and Ben Richards
// Initial Creation Date: 9/3/2018
// Description: File to handle fixed point numbers
// and their applications with the ST7735
// Lab Number: Lab01
// TA: Zee Lv
// Date of last revision: 9/10/2018
// Hardware Configuration: N/A

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fixed.h"
#include "ST7735.h"

int32_t xMin, xMax, yMin, yMax = 0;

static inline __attribute__((always_inline)) char digitToASCII(uint8_t digit) 
{
	return digit + 0x30;
}

/* NAME:
 * DESCRIPTION:	
 * INPUT:
 * OUTPUT:
 */
void PutError (uint8_t points)
{
	if(points == 5) printf("***.**");
	else printf("**.**");
}

/* NAME:
 * DESCRIPTION:	
 * INPUT:
 * OUTPUT:
 */
void ST7735_sDecOut2(int32_t value)
{
	char buf[6];
	buf[5] = NULL;
	if( value <= -10000 ){
		printf("-");
		PutError(4);
		return;
	}
	if( value >= 10000 ){
		printf(" ");
		PutError(4);
		return;
	}
	
	int32_t originalValue = value;
	if (value < 0) value *= -1;
	float decimal = (float)value / 100;
	decimal = (decimal - value)*100;
	
	if( originalValue < 0 && originalValue > -1000 ) printf(" ");
	if( originalValue >= 0 && originalValue < 1000 ) printf(" ");
	if( originalValue <= -1000 && originalValue > -10000 ) printf("-");
	if( originalValue >= 1000 && originalValue < 10000 ) printf(" ");
	
	for( int i = 4; i >= 0; i-- ){
		if( i == 2 ) buf[i] = '.';
		else{
			buf[i] = digitToASCII(value % 10);
			value = value/10;
		}
	}
	
	if( buf[0] == '0' && originalValue >= 0) buf[0] = ' ';
	if( buf[0] == '0' && originalValue < 0) buf[0] = '-';
	printf("%s", buf);
	
}

/* NAME:
 * DESCRIPTION:	
 * INPUT:
 * OUTPUT:
 */
void ST7735_uBinOut6 (uint32_t value)
{
	uint8_t outSize = 6;
	uint8_t decimalPlaces = 2;
	
	if (value >= 64000) {
		PutError(5);
		return;
	}

	char buf[6];
	float decimalValue = (float)value / 64;
	int intPart = decimalValue;
	float decPart = decimalValue - intPart;
	sprintf(buf, "%d.", intPart);
	uint8_t len = strlen(buf);
	for (int i = 0; i < decimalPlaces; ++i) {
		decPart *= 10;
		if (i == decimalPlaces - 1)
			decPart = round(decPart);
		sprintf(&buf[len + i], "%d", (uint32_t)decPart % 10);
	}
	uint8_t padding = outSize - strlen(buf);
	for (int i = 0; i < padding; ++i)
		printf(" ");
	printf("%s", buf);
}

/* NAME:
 * DESCRIPTION:	
 * INPUT:
 * OUTPUT:
 */
void ST7735_XYplotInit(char *title, int32_t minX, int32_t maxX, int32_t minY, int32_t maxY)
{
	ST7735_FillScreen(0);
  ST7735_SetCursor(0,0);
	ST7735_OutString(title);
	xMin = minX; 
	xMax = maxX; 
	yMin = minY; 
	yMax = maxY; 
}

/* NAME:
 * DESCRIPTION:	
 * INPUT:
 * OUTPUT:
 */
void ST7735_XYplot(uint32_t num, int32_t bufX[], int32_t bufY[])
{
	for(int i = 0; i < num; i++){
		
		if(bufX[i] >= xMin && bufX[i] <= xMax && bufY[i] >= yMin && bufY[i] <= yMax)
			
			ST7735_DrawPixel((127*(bufX[i] - xMin)/ (xMax - xMin)), 
											 (32 + 127 *(yMax - bufY[i])/ (yMax - yMin)), 
												ST7735_WHITE);
	}
}
