#include "ADC_Config.h"

int main(void){
	u16 ADC_Read;
	DDRC |= 0xFF;
	Struct_ADC ADC_Init_Struct;
	ADC_Init_Struct.Vref_Reference_Select	=	Vref_VCC_With_ext_cap;
	ADC_Init_Struct.Result_Adjustmment		=	Right_Adjustment;
	ADC_Init_Struct.Prescaler_Select		=	Division_Factor_128;
	ADC_Init_Struct.Trigger_Select			=	AutoTrigger_Disable;
	ADC_Init(ADC_Init_Struct);
	
    while (1){
		ADC_Read = ADC_Scan(1)/4;
		PORTC = ADC_Read;
    }
}