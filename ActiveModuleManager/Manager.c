/*
 * Manager.c
 *
 * Created: 02/08/2018 9:13:29 PM
 *  Author: nichh
 */ 


void InitializeManager(void)
{
	uint8_t servos = (1 << GIMBALX) | (1 << GIMBALY) | (1 << GIMBALZ) | (1 << LANDINGGEAR) | (1 << THERMSWIVELX) | (1 << THERMSWIVELY);
	//Enable servos pins for output
	SERVOREG |= servos;
	//Turn off all servo pins
	SERVOPORT &= ~servos;
	
	uint8_t winch = (1 << WINCHPOS) | (1 << WINCHNEG);
	//Enable winch pins for output
	WINCHREG |= winch;
	//Turn off winch pins
	WINCHPORT &= ~winch;
	
	winch = (1 << WINCHINT);
	//Enable winch interrupt for input
	WINCHREG &= ~winch;
	
	uint8_t notify = (1 << PROJLAUNCHNOTIFY) | (1 << WINCHACTIVENOTIFY) | (1 << LANDINGGEARACTIVENOTIFY) | (1 << PIEZOBUZZER);
	//Enable notify pins for output
	NOTIFYREG |= notify;
	//Turn off all notify pins
	NOTIFYPORT &= ~notify;
	
	uint8_t shiftregset = (1 << PROJSHIFTREGSET) | (1 << ACCESSORYSHIFTREGSET);
	//Enable shift register set pins for output
	SHIFTREGSETREG |= shiftregset;
	//Turn off all shift register set pins
	SHIFTREGSETPORT &= ~shiftregset;
	
	uint8_t shiftregdata = (1 << SHIFTREGDATA);
	//Enable shift register data pins for output
	SHIFTREGDATAREG |= shiftregdata;
	//Turn off all shift register data pins
	SHIFTREGDATAPORT &= ~shiftregdata;
	
	//Set initial duty cycle period
	DutyCyclePeriod = (unsigned int)(1.0f / ((float)DEFAULTDUTYFREQUENCY) * 1000.0f);
}

struct PulseRegister *FindPulseModule(enum RegisterId rid, unsigned char num)
{
	for(uint8_t i = 0; i < PULSE_MODULE_COUNT; i++)
	{
		if(PulseModules[i].RID == rid && PulseModules[i].RegisterNumber == num)
		{
			return &PulseModules[i];
		}
	}
};

unsigned char ConvertAlphaToDuty(unsigned char alpha)
{
	return (unsigned char)(((float)alpha / 255.0f) * (float)DutyCyclePeriod);
}

void ToggleGimbal(unsigned char x, unsigned char y, unsigned char z)
{
	struct PulseRegister *gimbalxreg = FindPulseModule(RIDC, GIMBALX);
	(*gimbalxreg).Save.Alpha = (*gimbalxreg).Alpha;
	(*gimbalxreg).Save.DutyCycle = (*gimbalxreg).DutyCycle;
	(*gimbalxreg).Alpha = x;
	(*gimbalxreg).DutyCycle = ConvertAlphaToDuty(x);
	
	//... Change to functions?
}

enum RegisterId
{
	RIDB,
	RIDC,
	RIDD
};

struct PulseRegister
{
	enum RegisterId RID;
	unsigned char RegisterNumber;
	unsigned char Alpha;
	unsigned char DutyCycle;
	
	struct PulseRegisterSave Save;
};
struct PulseRegisterSave
{
	unsigned char Alpha;
	unsigned char DutyCycle;	
};


#define PULSE_MODULE_COUNT 3
#define DEFAULTDUTYFREQUENCY 60
#define MINDUTYFREQUENCY 4
#define MAXDUTYFREQUENCY 500
unsigned int DutyCyclePeriod = 0; //Must be more than 4Hz and less than 500Hz.  Default is 60Hz


struct PulseRegister PulseModules[3] = {
	{RIDC, GIMBALX, 0x00, 0, {0x00, 0}},
	{RIDC, GIMBALY, 0x00, 0, {0x00, 0}},
	{RIDC, GIMBALZ, 0x00, 0, {0x00, 0}}
};