#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "INT_interface.h"
#include "PARSER_interface.h"
#include "BURNER_interface.h"


int main(void)
{   
    // Enable system clock
    RCC_initSysClock();
	INT_init();
	PARSER_init();
	BURNER_init();

	while(1)
	{
		INT_update();
		PARSER_update();
		BURNER_update();
	}
return 0;
}
