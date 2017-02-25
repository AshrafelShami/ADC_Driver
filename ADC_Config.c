#include "ADC_Config.h"

/********************************************************************************************
  Name:     ADC_Init.
  Purpose:  Initialize, all possible ADC registers for ATmega32 and Enables it.
  Entry:    (Struct_ADC) a STRUCT that setup the following.
							1) Voltage reference.
							2) Result Adjustment in ADCL and ADCH registers.
							3) Prescaler, The ADC operates at freq from 50kHz ~ 250kHz.
							4) Trigger settings if it is needed.
							5) Adjustment of the trigger source.
							6) Interrupt, if needed. 
  Exit:     no parameters
********************************************************************************************/
void ADC_Init ( Struct_ADC ADC_Config){

	ADCSRA |= (1 << ADEN);					/*	Enable the ADC	*/

	switch(ADC_Config.Vref_Reference_Select){
		case Vref_Internal_Vref_OFF : ADMUX &=~(1 << REFS1); ADMUX &=~(1 << REFS0); break;
		case Vref_VCC_With_ext_cap  : ADMUX &=~(1 << REFS1); ADMUX |= (1 << REFS0); break;
		case Vref_2_56_Volt			: ADMUX |= (1 << REFS1); ADMUX |= (1 << REFS0); break;
		default						: ADMUX &=~(1 << REFS1); ADMUX &=~(1 << REFS0); break;
	}
	
	switch(ADC_Config.Result_Adjustmment){
		case Left_Adjustment  : ADMUX |= (1 << ADLAR); break;
		case Right_Adjustment : ADMUX &=~(1 << ADLAR); break;
		default				  : ADMUX &=~(1 << ADLAR); break;
	}
	
	switch(ADC_Config.Prescaler_Select){
		case Division_Factor_2   : ADCSRA &=~ (1 << ADPS2); ADCSRA &=~ (1 << ADPS1); ADCSRA |=  (1 << ADPS0); break;
		case Division_Factor_4   : ADCSRA &=~ (1 << ADPS2); ADCSRA |=  (1 << ADPS1); ADCSRA &=~ (1 << ADPS0); break;
		case Division_Factor_8   : ADCSRA &=~ (1 << ADPS2); ADCSRA |=  (1 << ADPS1); ADCSRA |=  (1 << ADPS0); break;
		case Division_Factor_16  : ADCSRA |=  (1 << ADPS2); ADCSRA &=~ (1 << ADPS1); ADCSRA &=~ (1 << ADPS0); break;
		case Division_Factor_32  : ADCSRA |=  (1 << ADPS2); ADCSRA &=~ (1 << ADPS1); ADCSRA |=  (1 << ADPS0); break;
		case Division_Factor_64  : ADCSRA |=  (1 << ADPS2); ADCSRA |=  (1 << ADPS1); ADCSRA &=~ (1 << ADPS0); break;
		case Division_Factor_128 : ADCSRA |=  (1 << ADPS2); ADCSRA |=  (1 << ADPS1); ADCSRA |=  (1 << ADPS0); break;
		default					 : ADCSRA &=~ (1 << ADPS2); ADCSRA &=~ (1 << ADPS1); ADCSRA &=~ (1 << ADPS0); break;
	}
	
	switch(ADC_Config.Trigger_Select){
		case AutoTrigger_Enable  : ADCSRA |= (1 << ADATE); break;
		case AutoTrigger_Disable : ADCSRA &=~(1 << ADATE); break;
		default					 : ADCSRA &=~(1 << ADATE); break;
	}
	
	switch(ADC_Config.Trigger_Src_Select){
		case Free_Running_Mode		: SFIOR &=~(1 << ADTS2); SFIOR &=~(1 << ADTS1); SFIOR &=~(1 << ADTS0); break;
		case Analog_Comparator		: SFIOR &=~(1 << ADTS2); SFIOR &=~(1 << ADTS1); SFIOR |= (1 << ADTS0); break;
		case Ext_Interrupt_Req0		: SFIOR &=~(1 << ADTS2); SFIOR |= (1 << ADTS1); SFIOR &=~(1 << ADTS0); break;
		case Timer0_CMP_Match		: SFIOR &=~(1 << ADTS2); SFIOR |= (1 << ADTS1); SFIOR |= (1 << ADTS0); break;
		case Timer0_Overflow		: SFIOR |= (1 << ADTS2); SFIOR &=~(1 << ADTS1); SFIOR &=~(1 << ADTS0); break;
		case Timer1_CMP_MatchB		: SFIOR |= (1 << ADTS2); SFIOR &=~(1 << ADTS1); SFIOR |= (1 << ADTS0); break;
		case Timer1_Overflow		: SFIOR |= (1 << ADTS2); SFIOR |= (1 << ADTS1); SFIOR &=~(1 << ADTS0); break;
		case Timer1_Capture_Event	: SFIOR |= (1 << ADTS2); SFIOR |= (1 << ADTS1); SFIOR |= (1 << ADTS0); break;
		default						: SFIOR &=~(1 << ADTS2); SFIOR &=~(1 << ADTS1); SFIOR &=~(1 << ADTS0); break;
	}
	
	switch(ADC_Config.Interrupt_Select){
		case Interrupt_Disable	: ADCSRA &=~(1 << ADIE); break;
		case Interrupt_Enable	: ADCSRA |= (1 << ADIE); break;
		default					: ADCSRA &=~(1 << ADIE); break;
	}
}

/********************************************************************************************
  Name:     ADC_Scan.
  Purpose:  Setup the ADC channel and starts the conversion.
  Entry:    (Channel_Select) The Channel number that you are gonna work with (0 ~ 7).
  Exit:     (u68 ADC) Returns the value of the ADC conversion of the two registers.
********************************************************************************************/
u16 ADC_Scan ( u8 Channel_Select ){
	Channel_Select &= 0x07;
	ADMUX |= Channel_Select;				/*	Select ADC Channel					*/
	
	ADCSRA |= (1 << ADSC);					/*	Start the Convention				*/
	
	while (ADCSRA & (1 << ADSC));		/*	Wait for the conversion to complete
												And Interrupt flag will be high		*/
	ADCSRA |= (1 << ADIF);
	return ADC;
}