/*
 * Timer1Uint32.cpp
 *
 * Created: 9/14/2019 9:13:32 PM
 * Author : Lee
 */ 

#include "Timer1Uint32.h"

volatile uint16_t Timer1Uint32::ticksHigh = 0;
volatile uint16_t Timer1Uint32::overflowCount = 0;
uint32_t Timer1Uint32::ticksPerSecond = 0;

void Timer1Uint32::Start(uint8_t prescale)
{
    ticksHigh = 0;
    overflowCount = 0;
    
    switch (prescale)
    {
    case CLOCK_NO_PRESCALE:
        ticksPerSecond = F_CPU;
        break;
    case CLOCK_PRESCALE_DIV_8:
        ticksPerSecond = F_CPU/8;
        break;
    case CLOCK_PRESCALE_DIV_64:
        ticksPerSecond = F_CPU/64;
        break;
    case CLOCK_PRESCALE_DIV_256:
        ticksPerSecond = F_CPU/256;
        break;
    case CLOCK_PRESCALE_DIV_1024:
        ticksPerSecond = F_CPU/1024;
        break;
    }    

    // Run timer1 full blast.
    TCCR1A = 0;
    TCCR1B = prescale;
    TIFR1 |= _BV(TOV1);     // Clear overflow
    TIMSK1 = _BV(TOIE1);    // Enable overflow interrupts
}    
uint32_t Timer1Uint32::Now()
{
    int32_t now = 0;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        if ((TIFR1 & _BV(TOV1)) != 0)
        {
            TIFR1 |= _BV(TOV1);  // Clear the overflow
            ticksHigh++;
            overflowCount++;
        }

        now = (((int32_t) ticksHigh) << 16) + TCNT1;
    }
        
    return now;
}

// Extend TIMER1 to 32-bits by keeping track of 16-bit overflow
ISR(TIM1_OVF_vect)
{
    Timer1Uint32::ticksHigh++;
}
