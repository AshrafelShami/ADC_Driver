
#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

#include <avr/io.h>
#include "DataTypes.h"
#include "Function_Prototypes.h"

typedef enum{
	Vref_Internal_Vref_OFF,
	Vref_VCC_With_ext_cap ,
	Vref_2_56_Volt
	}Vref;
	
typedef enum{
	Right_Adjustment,
	Left_Adjustment	,
	}Adjust;
	
typedef enum{
	Division_Factor_2  ,
	Division_Factor_4  ,
	Division_Factor_8  ,
	Division_Factor_16 ,
	Division_Factor_32 ,
	Division_Factor_64 ,
	Division_Factor_128
	}Prescaler;
	
typedef enum{
	AutoTrigger_Disable,
	AutoTrigger_Enable
	}Trigger;
	
typedef enum{
	Free_Running_Mode	,
	Analog_Comparator	,
	Ext_Interrupt_Req0	,
	Timer0_CMP_Match	,
	Timer0_Overflow		,
	Timer1_CMP_MatchB	,
	Timer1_Overflow		,
	Timer1_Capture_Event
	}Trigger_Src;
	
typedef enum{
	Interrupt_Disable,
	Interrupt_Enable
	}Interrupt;

typedef struct{
		Vref		Vref_Reference_Select;
		Adjust		Result_Adjustmment	 ;
		Prescaler	Prescaler_Select	 ;
		Trigger		Trigger_Select		 ;
		Trigger_Src	Trigger_Src_Select	 ;
		Interrupt	Interrupt_Select	 ;
	}Struct_ADC;
	
void ADC_Init ( Struct_ADC );

#endif /* ADC_CONFIG_H_ */
