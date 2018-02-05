/*
 * LightManager.c
 *
 * Created: 12/04/2017 5:47:05 PM
 * Author : Nicholas Hein - Paradox Computing
 */

#include "Main.h"

volatile double SystemMS = 0;

int main(void)
{
    while (1) 
    {
		SPIInitialize();
		InitializeManager();
		
		//Enable overflow interrupt
		TIMSK |= (1 << TOIE0);
		//Initialize Prescaler = F_CPU/RES
		SetTimerResolution(DefaultTimerResolution);
		
		//Initialize timer to zero
		TCNT0 = 0;
		SystemMS = 0;
		
		//Enable global interrupts
		sei();
		
		uint8_t regid = 0x00;
		unsigned char data;
		
		static double lastOriginalMS = 0;
		static double currentCycleMS = 0;

		while(1)
		{
			//Send/Receive Data
			if(SPIPseudoReceive(&data))
			{
				if(regid)
				{
					if(Enabled || (regid == REG_CONTROL))
					{
						if((regid & READWRITE_FILTER) == WRITE_FILTER_VALUE)
						{
							//Write to register
							SetRegisterValue(regid, data);
						}
						else if((regid & READWRITE_FILTER) == READ_FILTER_VALUE)
						{
							//Read and transmit value
							unsigned char regval = GetRegisterValue(regid);
							SPIPseudoTransmit(regval);
						}
					}
					regid = 0x00;
				}
				else
				{
					regid = data;
				}
			}

			//Lights
			currentCycleMS = SystemMS - lastOriginalMS;
			if(currentCycleMS > ((double)DutyCyclePeriod) / 1000.0)
			{
				currentCycleMS -= ((double)DutyCyclePeriod) / 1000.0;
				lastOriginalMS = SystemMS - currentCycleMS;
			}
			UpdateLights(currentCycleMS);
		}

		while(1);
    }
}

unsigned char GetRegisterValue(uint8_t id)
{
	for(int i = 0; i < REGISTER_COUNT; i++)
	{
		if(REGISTERS[i].Id == id)
		{
			return REGISTERS[i].Value;
		}
	}
	return 0;
}

void SetRegisterValue(uint8_t id, unsigned char value)
{
	for(int i = 0; i < REGISTER_COUNT; i++)
	{
		if(REGISTERS[i].Id == id)
		{
			REGISTERS[i].Value = value;
			REGISTERS[i].Callback(id, value);
			return;
		}
	}
}

void UpdateLights(double currentMS)
{
	int ms = (int)(currentMS * 1000.0);

	for(int i = 0; i < RENDER_EVENT_COUNT; i++)
	{
		RenderEvents[i](ms);
	}
}

ISR(TIMER0_OVF_vect)
{
	if(Enabled)
	{
		SystemMS += TimerOverflowIncrement;
	}
}

