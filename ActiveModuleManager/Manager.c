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
}