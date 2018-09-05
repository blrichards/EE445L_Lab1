#include <stdint.h>
#include <stdio.h>
#include "fixed.h"
#include "ST7735.h"

int xMin, xMax, yMin, yMax = 0;

void ConvertToASCII(uint8_t* value)
{
	value[0] = value[0] + 0x30;
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
	uint8_t digits[5] = {0};
	digits[4] = NULL;
	int8_t i = 3;
	int32_t origionalValue = value;
		
	if( value <= -10000 ){
		printf("-");
		PutError(4);
		return;
	}
	if( value >= 10000 ){
		PutError(4);
		return;
	}

	if( value < 0 )	value = value * -1;
	
	
	// TODO - need the decimal points for this stuff
	while( i >= 0 ){
		digits[i] = value % 10;
		value = value / 10;
		i--;
	}
	
	while( i < 4 ){
		ConvertToASCII(&digits[i]);
		i++;
	}
	
	if (origionalValue < 1000 && origionalValue >= 0) digits[0] = ' ';
	if (origionalValue < 0 && origionalValue > -1000) digits[0] = '-';
	
	for(int i = 0; i < 4; i++){
		if(i == 2) printf(".");
		printf("%c", digits[i]);
	}
	return;
}

/* NAME:
 * DESCRIPTION:	
 * INPUT:
 * OUTPUT:
 */
void ST7735_uBinOut6 (uint32_t value)
{
	if( value >= 64000 ){
		PutError(5);
		return;
	}
	uint32_t decimalValue = (value * 100000) / 64000;	//*100000 to have uint available
	value = decimalValue;
	
	uint8_t digits[5] = {0};
	int i = 4;
	
	while( i >= 0 ){
		digits[i] = decimalValue % 10;
		value = decimalValue / 10;
		i--;
	}
	
	if (value < 1000){
		//put two spaces or move the cursor over
		i = 2;
	}
	
	if (value < 10000){
		//put one spaces or move the cursor over
		i = 1;
	}
	
	while( i < 5 ){
		ConvertToASCII(&digits[i]);
		ST7735_OutChar(digits[i]);
		i++;
	}
	
}

/* NAME:
 * DESCRIPTION:	
 * INPUT:
 * OUTPUT:
 */
void ST7735_XYplotInit(char *title, int32_t minX, int32_t maxX, int32_t minY, int32_t maxY)
{
	ST7735_FillScreen(ST7735_BLACK); 
  ST7735_SetCursor(0,0);
	printf("%s", title);
	xMin = minX;
	xMax = maxX;
	yMin = minY;
	yMax = maxY;
	return;
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
			ST7735_DrawPixel(bufX[i]/1000, bufY[i]/1000, ST7735_WHITE);
	}
	
}
