/*
 * File:   main.c
 * Author: Juan De Dios De Luna Ponce
 *
 * Created on 17 de abril de 2019, 06:44 PM
*/  //Pointers//USer interface improved
#include <xc.h>
#define _XTAL_FREQ 40000000
#include "flex_lcd.h"
#include <stdio.h>

// PIC16F1938 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF        // Watchdog Timer Enable (WDT enabled)
#pragma config PWRTE = ON      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor Enable (All VCAP pin functionality is disabled)
#pragma config PLLEN = OFF       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF         // Low-Voltage Programming Enable (Low-voltage programming enabled)

int a=-1,b=1,c=0,d=1,e=0,f=0,g=0,h=0,i=24,adc=0,v=0,w=25,z=1,j=1,k=0,l=0,m=0;
int numberT[20];
int *pointer1; int *pointer2;
*pointer1 = &numberT[0];
*pointer2 = &w;
float temp = 0.0, volt = 0.0;
int Secuence1() ,Secuence2(),Secuence3(),Secuence4(),PWM(float a),Temperature(),SecuenceB();

void interrupt interrupcion(){
     a++;
       *(pointer1+a) = 11;
        __delay_ms(100);  //para evitar rebotes
        INTCONbits.INTF=0;  //Limpiamos la bandera
        
}
    

int main() {
            //Para generar una variable loop for
   
    unsigned char buffer1[16]; //La usaremos para usarlo on una libreria de hasta 20 caracteres
    //**//*OSCilador  32 MHZ
    OSCCONbits.IRCF=0b1110; // Tenemos una frequencia de 8 MHZ pero resulta 32 porque tenemos activada la funcion PLLEN..
    OSCCONbits.SCS=0b00; // Esta es la fuente del oscilador //cONFIG intocS
    //Acomodo de bits que vamos a usar
    ANSELA=0b00100000;  //Este bit nos dice que es analogico
    ANSELD=0b00100000;//Todo el puerto como digital
    ANSELB=0b00000000;
    TRISB=0b00000000;
    TRISA=0b00000000;
    //TRISB=0b00000000;
    
   // ANSELC=0x00000000;
    TRISD0 = 1; //RD0 as Input PIN
    TRISD1 = 1;
    TRISD2 = 1;
    TRISD3 = 1;
    TRISD4 = 0;
    TRISC4 = 0;
    RD0=0;RD1=0;RD2=0;RD3=0,RD4=0;
    RC4=0;
    TRISC=1;
    //ADC
    ADCON0bits.CHS=4;
    ADCON1bits.ADNREF=0;//VOltage de referencia + y -
    ADCON1bits.ADPREF=0;   //Vdd
    ADCON1bits.ADCS=0b111;
    ADCON1bits.ADFM=1;  //justificamos a la derecha
    ADCON0bits.ADON = 1; //ADC encendido
    // TRISB0 = 0; TRISB1=0; TRISB2=0; TRISB3=0;
    //LCD 
    
    Lcd_Init();         //Inicializamos la LCD
    Lcd_Cmd(LCD_CLEAR);     // Limpiamos la LCD
    Lcd_Cmd(LCD_CURSOR_OFF);        //Apagamos la LCD
    __delay_ms(100);        //Esperamos 1000ms
    while(1){
    while(j!=0){
   
     while(k!=11){
         //COnfigiracion de la interrupcion
         PORTB=0;
         RB2=1;
            //cONFIGURACION DEL PULL-UP resistor
         OPTION_REGbits.nWPUEN=0;
         WPUBbits.WPUB0=1;     //Resistencia en RB0
         //COnfigurar la interrupcion
         INTCONbits.GIE=1;   //Habilitamos la interrupcion global
         INTCONbits.INTE=1;
         INTCONbits.INTF=0;
         OPTION_REGbits.INTEDG=0;     //Interrupcion de flanco de bajada
         //while(1);
           // RC2=0;
            temp = 0;
            ADCON0bits.GO_nDONE=1; //LANZA LA CONERSION
        while(ADCON0bits.GO_nDONE);
            adc=ADRESH;   //
            adc=adc<<8; //CON UN corrimiento hacia la izquierda
            adc=adc+ADRESL;
            volt=adc*5.0/1024.0;
            sprintf(buffer1,"TEMP SETUP= %d",*(pointer2));
            Lcd_Out2(1, 1, buffer1); 
            temp = (volt*100)-380;
            sprintf(buffer1,"TEMP %04.2f",temp);
             Lcd_Out2(2, 1, buffer1); 
              __delay_ms(200);  //Este delay ayuda para el capacitor este cargado y hagamos la conversion
               k=*(pointer1+a);
        RB2=0;
        if(temp>=w){ 
            RD4=1;
            PWM(temp);
            RD4=0;
           }
        else {
            RD4=0;
            CCP1CONbits.CCP1M=0b0000;
            T2CONbits.TMR2ON=0;
             }
            TRISC=1;
            PORTC=1;
            temp = 0;
       }
    //Si presiona B entonces...
     Lcd_Cmd(LCD_CLEAR);
    sprintf(buffer1,"Type password:"); //Guardamos en el string buffer la palabra 
    Lcd_Out2(2, 1, buffer1);        // Escribimos en el renglon un espacio 1 la que 
    d=1;
     while(d!=0){
         a = -1;
          *(pointer1+0) = 0;
          *(pointer1+1) = 0;
          *(pointer1+2) = 0;
    // while(a!=0 && g<=100){ //Cuando culquiera de las dos sea falsa, nos salimos de ciclo
          for(a=-1; a!=0 && g<=100; g++ ){
         sprintf(buffer1, "Password: "); //Guardamos en el string buffer la palabra
         Lcd_Cmd(LCD_BLINK_CURSOR_ON);
         Lcd_Out2(1, 1, buffer1);
         Secuence1();
         Secuence2();
         Secuence3();
         Secuence4();
        Lcd_Cmd(LCD_BLINK_CURSOR_ON);
        g++;
        }
         g=0;
         d=0;
        
        while(a<=1 && g<=100 ){
            Secuence1();
            Secuence2();
            Secuence3();
            Secuence4();
            sprintf(buffer1, "Password: %d",*(pointer1+a)); //Guardamos en el string buffer la palabra 
            Lcd_Out2(1, 1, buffer1);        // Escribimos en el renglon un espacio 1 la que 
            Lcd_Cmd(LCD_BLINK_CURSOR_ON);
            g++;
            }
         g=0;
         a=-1;
         
           sprintf(buffer1, "U typed: %d,%d,%d",*(pointer1+0),*(pointer1+1),*(pointer1+2)); //Guardamos en el string buffer la palabra 
            Lcd_Out2(1, 1, buffer1);        // Escribimos en el renglon un espacio 1 la que 
            Lcd_Cmd(LCD_BLINK_CURSOR_ON);
            __delay_ms(700);
        if(*(pointer1+0)==1 &&*(pointer1+1) == 2 && *(pointer1+2) == 3){
            Lcd_Cmd(LCD_CLEAR);
            sprintf(buffer1, "Acess grounted"); //Guardamos en el string buffer la palabra 
            Lcd_Out2(1, 1, buffer1);        // Escribimos en el renglon un espacio 1 la que 
             __delay_ms(600);
            d=0;
            j=0;
            a=-1;
           
        }
        else{
            Lcd_Cmd(LCD_CLEAR);
            sprintf(buffer1, "No access"); //Guardamos en el string buffer la palabra 
            Lcd_Out2(1, 1, buffer1);        // Escribimos en el renglon un espacio 1 la que
            __delay_ms(600);
             k=0;
             d=0;
              j=1;
          }
           
        }
    
    }
    //Si accede al menu entonces...
        // a = -1;
         Lcd_Cmd(LCD_CLEAR);
         sprintf(buffer1,"Max 3 digits..."); //Guardamos en el string buffer la palabra 
         Lcd_Out2(2, 1, buffer1);
         __delay_ms(900);
         Lcd_Cmd(LCD_CLEAR);
         sprintf(buffer1,"A to enter value"); //Guardamos en el string buffer la palabra 
         Lcd_Out2(2, 1, buffer1);
         g=0;
        while(a<2 && *(pointer1+a) != 10 && g<=60 ){
            Secuence1();
            Secuence2();
            Secuence3();
            Secuence4();
            sprintf(buffer1,"ENTER TEMPE: %d",*(pointer1+a)); //Guardamos en el string buffer la palabra 
            Lcd_Out2(1, 1, buffer1);
            Lcd_Cmd(LCD_BLINK_CURSOR_ON);
            g++;
            
         }
         h=1+a;//Como saber cuantos digitos presiono el usuario?.... //if a=0 then 1 digit was pressed a=1 then 2 digits were press
//si el usuario presiono algo then
         if(*(pointer1+a) != 10){
         if(h==1){
         w = (*(pointer1+0) * 1);
            Lcd_Cmd(LCD_CLEAR);
            sprintf(buffer1, "Tem set: %d °C",*(pointer2)); //Guardamos en el string buffer la palabra 
            Lcd_Out2(1, 1, buffer1);
            __delay_ms(900);
            Lcd_Cmd(LCD_CLEAR);
         }
         else if(h==2){
              w =((*(pointer1+0) * 10) + (*(pointer1+1) * 1)) ;
            Lcd_Cmd(LCD_CLEAR);
            sprintf(buffer1, "Tem set: %d °C",*(pointer2)); //Guardamos en el string buffer la palabra 
            Lcd_Out2(1, 1, buffer1);
            __delay_ms(900);
            Lcd_Cmd(LCD_CLEAR);
             
         }
         else if(h==3){
              w =((*(pointer1+0) * 100) + (*(pointer1+1) * 10) + (*(pointer1+2) * 1));
            Lcd_Cmd(LCD_CLEAR);
            sprintf(buffer1, "Tem set:%03d °C",*(pointer2)); //Guardamos en el string buffer la palabra 
            Lcd_Out2(1, 1, buffer1);
            __delay_ms(900);
            Lcd_Cmd(LCD_CLEAR);
             
         }
         else{
             Lcd_Cmd(LCD_CLEAR);
            sprintf(buffer1, "Something's wrong"); //Guardamos en el string buffer la palabra 
            Lcd_Out2(1, 1, buffer1);
             Lcd_Cmd(LCD_CLEAR);
         }
             
         }
         else if(*(pointer1+a) == 10){  //Para este tenemos un simbolo de mas entonces..
             if(a==1){
                  w = (*(pointer1+0) * 1);
            Lcd_Cmd(LCD_CLEAR);
            sprintf(buffer1, "Tem set: %d °C",*(pointer2)); //Guardamos en el string buffer la palabra 
            Lcd_Out2(1, 1, buffer1);
            __delay_ms(900);
            Lcd_Cmd(LCD_CLEAR);
                 
             }
             else if(a==2){
                  w = ((*(pointer1+0) * 10) + (*(pointer1+1)) * 1) ;
            Lcd_Cmd(LCD_CLEAR);
            sprintf(buffer1, "Tem set: %d °C",*(pointer2)); //Guardamos en el string buffer la palabra 
            Lcd_Out2(1, 1, buffer1);
            __delay_ms(900);
            Lcd_Cmd(LCD_CLEAR);
                 
             }
              else if(a==3){
                  w =( (*(pointer1+0) * 100) + (*(pointer1+1) * 10)  + (*(pointer1+1)) * 10);
            Lcd_Cmd(LCD_CLEAR);
            sprintf(buffer1, "Tem set: %d °C",*(pointer2)); //Guardamos en el string buffer la palabra 
            Lcd_Out2(1, 1, buffer1);
            __delay_ms(900);
            Lcd_Cmd(LCD_CLEAR);
                 
             }
              else;      
         }
         else{
              Lcd_Cmd(LCD_CLEAR);
            sprintf(buffer1, "No value entered"); //Guardamos en el string buffer la palabra 
            Lcd_Out2(1, 1, buffer1);
            __delay_ms(900);
            Lcd_Cmd(LCD_CLEAR);
         }
         j=1;
         d=1;
         a=-1;
         k=0;
         h=0;
         
         
    }
    return 0;
}
   /*     while(1){
            z=0;
            TRISC=1;
           // RC2=0;
            temp = 0;
            ADCON0bits.GO_nDONE=1; //LANZA LA CONERSION
        while(ADCON0bits.GO_nDONE);
            adc=ADRESH;   //
            adc=adc<<8; //CON UN corrimiento hacia la izquierda
            adc=adc+ADRESL;
            volt=adc*5.0/1024.0;
            sprintf(buffer1,"ADC %04d",adc);
            Lcd_Out2(1, 1, buffer1); 
            temp = (volt*100);
            sprintf(buffer1,"TEMP %04.2f",temp);
             Lcd_Out2(2, 1, buffer1); 
              __delay_ms(300);  //Este delay ayuda para el capacitor este cargado y hagamos la conversion
        if(temp>=w){ 
            RD4=1;
            PWM(temp);
            RD4=0;
           }
        else {
            RD4=0;
            CCP1CONbits.CCP1M=0b0000;
            T2CONbits.TMR2ON=0;
             }
            TRISC=1;
            PORTC=1;
            temp = 0;
       }
    return ;
    }
    */
int Secuence1(){
    TRISB1= 0;  RB1=1;
    if(RD0==1){
        RB1=0; a++; m=1;
         *(pointer1+a) = 10;
       // numberT[a] = 10;
        Lcd_Cmd(LCD_MOVE_CURSOR_RIGHT);
        RD0=0;
        __delay_us(1); 
    }
    else if(RD1==1){
        RB1=0; a++; 
         *(pointer1+a) = 3;
        Lcd_Cmd(LCD_MOVE_CURSOR_RIGHT);
        __delay_us(1); 
        RD1=1;
    }
    else if(RD2==1){
        RB1=0; 
        a++;
          *(pointer1+a) = 2;
         Lcd_Cmd(LCD_MOVE_CURSOR_RIGHT);
         __delay_us(1);
         RD2=0;
    }
    else if(RD3==1){
          RB1=0;
          a++;
          *(pointer1+a) = 1;
          Lcd_Cmd(LCD_MOVE_CURSOR_RIGHT);
          __delay_us(1);
          RD3=0;
    }
    else RB1=0;
}
int Secuence2(){
    TRISB2= 0;
    RB2=1;
    if(RD0==1){
        RB2=0;
         a++;
       *(pointer1+a) = 11;
        Lcd_Cmd(LCD_MOVE_CURSOR_RIGHT);
        __delay_us(1);RD0=0;}
    else if(RD1==1){
         RB2=0;
          a++;
        *(pointer1+a) = 6;
        Lcd_Cmd(LCD_MOVE_CURSOR_RIGHT);
        __delay_us(1);
        RD1=0;
    }
    else if(RD2==1){
        RB2=0;
        a++;
         *(pointer1+a) = 5;
         Lcd_Cmd(LCD_MOVE_CURSOR_RIGHT);
        __delay_us(1);
         RD2=0;
    }
    else if(RD3==1){
        RB2=0;
          a++;
         *(pointer1+a) = 4;
      Lcd_Cmd(LCD_MOVE_CURSOR_RIGHT);
      __delay_us(1);
      RD3=0;
    }
    else  RB2=0; 
         
}
int Secuence3(){
    TRISB3= 0;
    RB3=1;
    if(RD0==1){
        RB3=0;
         a++;
        *(pointer1+a) = 12;
        Lcd_Cmd(LCD_MOVE_CURSOR_RIGHT);
        __delay_us(1);
          RD0=0;
    }
    else if(RD1==1){
         RB3=0;
          a++;
        *(pointer1+a) = 9;
        Lcd_Cmd(LCD_MOVE_CURSOR_RIGHT);
        __delay_us(1);
          RD1=0;
    }
    else if(RD2==1){
        RB3=0;
        a++;
         *(pointer1+a) = 8;
         Lcd_Cmd(LCD_MOVE_CURSOR_RIGHT);
         __delay_us(1);
           RD2=0;
    }
    else if(RD3==1){
        RB3=0;
          a++;
         *(pointer1+a) = 7;
      Lcd_Cmd(LCD_MOVE_CURSOR_RIGHT);
      __delay_us(1);
        RD3=0;
    }
    else RB3=0;
         
    
}
int Secuence4(){
    TRISB5= 0;
    RB5=1;
    if(RD0==1){
        RB5=0;
         a++;
       *(pointer1+a) = 16;
        Lcd_Cmd(LCD_MOVE_CURSOR_RIGHT);     
        __delay_us(1);
          RD0=0;
    }
    else if(RD1==1){
         RB5=0;
          a++;
        *(pointer1+a) = 13;
        Lcd_Cmd(LCD_MOVE_CURSOR_RIGHT);
        __delay_us(1);
          RD1=0;
    }
    else if(RD2==1){
        RB5=0;
        a++;
         *(pointer1+a) =0;
         Lcd_Cmd(LCD_MOVE_CURSOR_RIGHT);
         __delay_us(1);
           RD2=0;
    }
    else if(RD3==1){
        RB5=0;
          a++;
        *(pointer1+a) = 15;
      Lcd_Cmd(LCD_MOVE_CURSOR_RIGHT);
      __delay_us(1);
      RD3=0;
    }
    else  RB5=0;
        
}

int PWM(float temp){
    while(h<=50){
    TRISC=255;
    PORTC=0;
    
    //COnfiguracion del CCP1
    CCP1CONbits.CCP1M=0b1100;
    CCP1CONbits.P1M=0b00; //Slaida simple, no analogica
    
    //Configiracion del timer 2
    T2CONbits.T2CKPS=0b10; //Configuracion del bit 1:16
    T2CONbits.T2OUTPS=0b0; // Postacaler 1:1
    
    //Cicclo de trabajo
    CCPR1L=800>>2;
    CCP1CONbits.DC1B=512;
    
    
    //Seleccion del timer
    CCPTMRS0bits.C1TSEL=0b00; // Timer2
    //
    TRISC=0;
    T2CONbits.TMR2ON=1;
    //Added
    
    h++;
   // while(1);
    }
   // CCP1CONbits.CCP1M=0b0000;
    //T2CONbits.TMR2ON=0;
    TRISC=1;
    temp=0;
    h=0;
    
}
int Temperature(){
    {
            TRISC=1;
           // RC2=0;
            temp = 0;
            ADCON0bits.GO_nDONE=1; //LANZA LA CONERSION
        while(ADCON0bits.GO_nDONE);
            adc=ADRESH;   //
            adc=adc<<8; //CON UN corrimiento hacia la izquierda
            adc=adc+ADRESL;
            volt=adc*5.0/1024.0;
            temp = (volt*100);
              __delay_ms(100);  //Este delay ayuda para el capacitor este cargado y hagamos la conversion
        if(temp>=w){ 
            RD4=1;
            PWM(temp);
            RD4=0;
           }
        else {
            RD4=0;
            CCP1CONbits.CCP1M=0b0000;
            T2CONbits.TMR2ON=0;
             }
            TRISC=1;
            PORTC=1;
            temp = 0;
       }
    
    
}
int SecuenceB(){
    
    TRISB2= 0;
    RB2=1;
    
    if(RD0==1){
        RB2=0;
         a++;
       *(pointer1+a) = 11;
        Lcd_Cmd(LCD_MOVE_CURSOR_RIGHT);
        __delay_ms(5);}
    else{
         RB2=0;
    }
     
}
