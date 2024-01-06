

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>


long pwm_1 = 0;

void PWM_settings (void)
{
	
	TCCR1A |= (1<<COM1A1) | (0<<COM1A0); // ��������������� ���
	
	TCCR1A |= (1<<WGM10); // 10 ��� ���, ������ ������.
	TCCR1A |= (1<<WGM11); // 10 ��� ���, ������ ������.
	TCCR1B |= (1<<WGM12); // 10 ��� ���, ������ ������.
	TCCR1B &= ~(1<<WGM13); // 10 ��� ���, ������ ������.
        	
	TCCR1B |= (1<<CS11); // ����� ������� �� �� 8
	TCCR1B &= ~((1<<CS10)|(1<<CS12)); // ����� ������� �� �� 8 = 125000
	                                  // timer counter control register (0 pin B-�������������, 8-������) ����� ������� �������� �� (8*1024)/1000000=0,008 ��� . ������� = 1024\0,008
	                                  // 1000000 / (8*1024)=122 ������� ������ ���
 	  
	OCR1A = 111;  // �������� ����������
 	pwm_1 = OCR1A;
}

int main(void)
  {

//������ ���
DDRB |= (1<<1);

 //������
 DDRD &= ~((1<<3) | (1<<2));
 PORTD |= (1<<3) | (1<<2);

PWM_settings ();   
 
   while (1)
{
    
    while(!(PIND&(1<<2)))
    {
        pwm_1++;
        pwm_1 = (pwm_1+20);
        _delay_ms (30);
        if (pwm_1 >=1023) pwm_1=1023;
        OCR1A = pwm_1 ;
       
//        OCR1A++;
//        _delay_ms (30);
//        if (OCR1A >=1023) OCR1A=1023;
      
        
     }
        
    while(!(PIND&(1<<3)))
    {
        pwm_1--;
        pwm_1 = (pwm_1-20);
        _delay_ms (30);
        if (pwm_1 <=0) pwm_1=0;
        OCR1A = pwm_1 ;
        
//          OCR1A--;
//          _delay_ms (30);
//          if (OCR1A<=0) OCR1A=0;
         
    }
    
}
}