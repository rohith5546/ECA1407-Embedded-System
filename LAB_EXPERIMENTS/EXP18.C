#include <reg51.h>

/* Global PWM counter */
unsigned int count = 0;

/* PWM duty cycle */
unsigned int duty = 50;

/* Timer 0 Interrupt Service Routine */
void timer0_ISR(void) interrupt 1
{
    /* Reload Timer 0 for approximately 1 ms */
    TH0 = 0xFC;
    TL0 = 0x66;

    /* Increment PWM counter */
    count++;

    /*
     * Generate PWM signal on Port 1
     * Duty cycle is controlled by 'duty'
     */
    if (count < duty)
    {
        P1 = 0xFF;       // Output HIGH
    }
    else
    {
        P1 = 0x00;       // Output LOW
    }

    /*
     * Total PWM period = 200 ms
     * Reset counter after 200 timer interrupts
     */
    if (count >= 200)
    {
        count = 0;
    }
}

/* Main Function */
void main()
{
    /* Timer 0 Mode 1 - 16-bit timer */
    TMOD = 0x01;

    /* Initial Timer 0 reload value */
    TH0 = 0xFC;
    TL0 = 0x66;

    /* Enable Timer 0 interrupt and global interrupt */
    IE = 0x82;

    /* Start Timer 0 */
    TR0 = 1;

    /* Infinite loop */
    while (1)
    {
        /* PWM is generated inside Timer 0 ISR */
    }
}