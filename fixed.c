#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "fixed.h"
#include "ST7735.h"

static inline __attribute__((always_inline)) char digitToASCII(uint8_t digit) 
{
	assert(digit < 10);
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
	uint8_t digits[5] = {0};
	digits[4] = NULL;
	int8_t i = 3;
	int32_t origionalValue = value;
		
	if( value <= -10000 )
	{
		printf("-");
		PutError(4);
		return;
	}
	if( value >= 10000 )
	{
		PutError(4);
		return;
	}

	if( value < 0 )	value = value * -1;
	
	
	// TODO - need the decimal points for this stuff
	while( i >= 0 )
	{
		digits[i] = value % 10;
		value = value / 10;
		i--;
	}
	
	while( i < 4 )
	{
		digits[i] = digitToASCII(digits[i]);
		i++;
	}
	
	if (origionalValue < 1000 && origionalValue >= 0) digits[0] = ' ';
	if (origionalValue < 0 && origionalValue > -1000) digits[0] = '-';
	
	for(int i = 0; i < 4; i++)
	{
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
	uint8_t decimalPlaces = 2;
	
	if (value >= 64000) {
		PutError(5);
		return;
	}

	float decimalValue = (float)value / 64;
	int intPart = decimalValue;
	float decPart = decimalValue - intPart;
	printf("%d", intPart);
	for (int i = 0; i < decimalPlaces; ++i) {
		decPart *= 10;
		printf("%d", (uint32_t)decPart % 10);
	}
}

/* NAME:
 * DESCRIPTION:	
 * INPUT:
 * OUTPUT:
 */
void ST7735_XYplotInit(char *title, int32_t minX, int32_t maxX, int32_t minY, int32_t maxY)
{
	return;
}

/* NAME:
 * DESCRIPTION:	
 * INPUT:
 * OUTPUT:
 */
void ST7735_XYplot(uint32_t num, int32_t bufX[], int32_t bufY[])
{
	return;
}
