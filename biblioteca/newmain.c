#include <proc/pic18f4520.h>
#include "config.h"
#include "timer.h"
#include "adc.h"
#include "lcd.h"
#include "serial.h"
#include "ssd.h"
#include "keypad.h"
#include "pwm.h"

#define L_ON  0x0F
#define L_OFF 0x08
#define L_CLR 0x01
#define L_L1  0x80
#define L_L2  0xC0


unsigned int Leitura = 0;

void Teclado(void){
    if(kpRead() != Leitura){
        Leitura = kpRead();
        
        switch(kpReadKey()){
            case 's':
                lcdCommand(L_CLR);
                lcdCommand(L_L1);
                lcdString("Carro: desligado");
                
                ssdDigit(0, 0);
                ssdDigit(0, 1);
                ssdDigit(20, 2);
                ssdDigit(20, 3);
                break;
            case 'S':
                lcdCommand(L_CLR);
                lcdCommand(L_L1);
                lcdString("Carro: ligado");
                lcdCommand(L_L2);
                lcdString("Marcha: N");
                
                ssdDigit(0, 0);
                ssdDigit(0, 1);
                ssdDigit(20, 2);
                ssdDigit(20, 3);
                break;    
            case 'U':
                lcdCommand(L_L2);
                lcdString("Marcha: 1");
                
                ssdDigit(1, 0);
                ssdDigit(0, 1);
                ssdDigit(18, 2);
                ssdDigit(18, 3);
                break;
            case 'L':
                lcdCommand(L_L2);
                lcdString("Marcha: 2");
                
                ssdDigit(2, 0);
                ssdDigit(0, 1);
                ssdDigit(18, 2);
                ssdDigit(18, 3);
                break;
            case 'D':
                lcdCommand(L_L2);
                lcdString("Marcha: 3");
                
                ssdDigit(3, 0);
                ssdDigit(5, 1);
                ssdDigit(18, 2);
                ssdDigit(18, 3);
                break;
            case 'R':
                lcdCommand(L_L2);
                lcdString("Marcha: 4");
                
                ssdDigit(6, 0);
                ssdDigit(0, 1);
                ssdDigit(18, 2);
                ssdDigit(18, 3);
                break;
            case 'X':
                lcdCommand(L_L2);
                lcdString("Marcha: 5");
                
                ssdDigit(8, 0);
                ssdDigit(0, 1);
                ssdDigit(18, 2);
                ssdDigit(18, 3);
                break;
            case 'B':
                lcdCommand(L_L2);
                lcdString("Marcha: R");
                
                ssdDigit(0, 0);
                ssdDigit(5, 1);
                ssdDigit(18, 2);
                ssdDigit(18, 3);
                break;
            case 'A':
                pwmSet(100);
                break;
            case 'Y':
                pwmSet(0);
                break;
            default:
                break;
        }        
    }
}

void Configura(void){    
    char Tecla;
    
    Tecla = serialRead();
    
    if(Tecla != 0){
        switch(Tecla){
            case 's':
                lcdCommand(L_CLR);
                lcdCommand(L_L1);
                lcdString("Carro: desligado");
               
                
                ssdDigit(0, 0);
                ssdDigit(0, 1);
                ssdDigit(18, 2);
                ssdDigit(18, 3);
                break;
            case 'S':
                lcdCommand(L_CLR);
                lcdCommand(L_L1);
                lcdString("Carro: ligado");
                lcdCommand(L_L2);
                lcdString("Marcha: NEUTRO");
                
                
                ssdDigit(0, 0);
                ssdDigit(0, 1);
                ssdDigit(18, 2);
                ssdDigit(18, 3);
                break;
            case 'U':
                lcdCommand(L_L2);
                lcdString("Marcha: 1");
                
                ssdDigit(1, 0);
                ssdDigit(0, 1);
                ssdDigit(18, 2);
                ssdDigit(18, 3);
                break;
            case 'L':
                lcdCommand(L_L2);
                lcdString("Marcha: 2");
                
                ssdDigit(2, 0);
                ssdDigit(0, 1);
                ssdDigit(18, 2);
                ssdDigit(18, 3);
                break;
            case 'D':
                lcdCommand(L_L2);
                lcdString("Marcha: 3");
                
                ssdDigit(3, 0);
                ssdDigit(5, 1);
                ssdDigit(18, 2);
                ssdDigit(18, 3);
                break;
            case 'R':
                lcdCommand(L_L2);
                lcdString("Marcha: 4");
                
                ssdDigit(4, 0);
                ssdDigit(0, 1);
                ssdDigit(18, 2);
                ssdDigit(18, 3);
                break;
            case 'X':
                lcdCommand(L_L2);
                lcdString("Marcha: 5");
                
                ssdDigit(8, 0);
                ssdDigit(0, 1);
                ssdDigit(18, 2);
                ssdDigit(18, 3);
                break;
            case 'B':
                lcdCommand(L_L2);
                lcdString("Marcha: R");
                ssdDigit(0, 0);
                ssdDigit(5, 1);
                ssdDigit(18, 2);
                ssdDigit(18, 3);
                break;
            case 'A':
                pwmSet(100);
                break;
            case 'Y':
                pwmSet(0);
                break;
            default:
                break;
        }
    }
}

void main(void){
    char slot;
    
    pwmInit();
    kpInit();
    adcInit();
    lcdInit();
    ssdInit();
    timerInit();
    serialInit();    
    
    ssdDigit(0, 0);
    ssdDigit(0, 1);
    ssdDigit(0, 2);
    ssdDigit(0, 3);
    
    lcdCommand(L_CLR);
    
    lcdCommand(L_L1);
    lcdString("Projeto Final");
    lcdCommand(L_L2);
    lcdString("Aluno: Felippe");
    timerReset(500000);
    
    
    
    for(;;){
        timerReset(5000);
        ssdUpdate();
        
        switch(slot){
            case 0:
                Teclado();
                slot = 1;
                break;
            case 1:
                Configura();
                slot = 2;
                break;
            case 2:
                kpDebounce();                
                slot = 3;
                break;
            default:
                slot = 0;
                break;
        }
        
        timerWait();
    }
}
