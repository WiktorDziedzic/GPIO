#include <LPC21xx.H>

/*
20. Napisac funkcje „StepLeft”, której pojedyncze 
wywolanie bedzie powodowac przesuniecie punktu swietlnego
w lewo (np. 0->1, 1->2, 2->3, 3->0).
UWAGI:
? Uzyc funkcji „LedOn”,
? Uzyc zmiennej globalnej unsigned int i operatora „modulo”,
? Docelowo funkcja powinna skladac sie z dwóch linii kodu,
? Inkrementacje / dekrementacje zmiennej dac przed wywolaniem LedOn.
? W programie testowym nie uzywac LedOn – zauwazyc, ze LedInit zapala diode zerowa.
Test z punktu 12 na symulatorze i mikrokontrolerze.
*/
// zmiana dla testu

#define LED0_bm 1<<16
#define LED1_bm 1<<17
#define LED2_bm 1<<18
#define LED3_bm 1<<19

#define BUTTON0_bm 1<<4
#define	BUTTON1_bm 1<<6
#define	BUTTON2_bm 1<<5
#define	BUTTON3_bm 1<<7



unsigned int iRealDealayTimeMs = 250;

void Delay (unsigned int uiWaitTime)
{
	unsigned int uiLoopClock;
	for(uiLoopClock=0; uiLoopClock < uiWaitTime*1175; uiLoopClock++){
	}
}



void LedInit(void){
	IO1DIR = LED0_bm | LED1_bm | LED2_bm | LED3_bm;
	IO1SET= LED0_bm;
}

void LedOn(unsigned int ucLedIndeks){
	
	IO1CLR = LED0_bm | LED1_bm | LED2_bm | LED3_bm;
	
	switch ( ucLedIndeks ){
		
		case 0:
			IO1SET = LED0_bm;
		break;
		
		case 1:
			IO1SET = LED1_bm;
		break;
		
		case 2:
			IO1SET = LED2_bm;
		break;
		
		case 3:
			IO1SET = LED3_bm;
		break;
		
		default:
		break;
	}
}


enum Step{LEFT, RIGHT};

void LedStep (enum Step Direction){
	
	static unsigned int uiLedIndeksForStep = 0;
	
	if (Direction == LEFT){
		uiLedIndeksForStep++;
		}
	else if(Direction == RIGHT){
		uiLedIndeksForStep--;
		}
	LedOn(uiLedIndeksForStep%4);
	
}


void LedStepLeft(void){
	LedStep(LEFT);
}

void LedStepRight(void){
	LedStep(RIGHT);
}


void KeyboardInit(){
	IO0DIR =IO0DIR & (~(BUTTON0_bm | BUTTON1_bm | BUTTON2_bm | BUTTON3_bm));
}


enum ButtonState {RELASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};

enum ButtonState eKeyboardRead(){

	if((IO0PIN & BUTTON0_bm) == 0){
		return(BUTTON_0);
	}
	else if((IO0PIN & BUTTON1_bm) == 0){
		return(BUTTON_1);
	}
	else if((IO0PIN & BUTTON2_bm) == 0){
		return(BUTTON_2);
	}
	else if((IO0PIN & BUTTON3_bm) == 0){
		return(BUTTON_3);
	}
	else{
		return(RELASED);
	}
}



int main()
{
	
	LedInit();
	KeyboardInit();
	
	while(1)
	{
	
		switch(eKeyboardRead()){
			
			case BUTTON_0:
			break;
			
			case BUTTON_1:
				LedStepRight();
				Delay(250);
			break;
			
			case BUTTON_2:
				LedStepLeft();
				Delay(250);
			
			break;
			
			case BUTTON_3:
			break;
			
			case RELASED:
				IO1CLR = LED0_bm | LED1_bm | LED2_bm | LED3_bm;
			break;
		}
	}
}
	
