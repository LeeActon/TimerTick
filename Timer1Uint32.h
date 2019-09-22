/*
 * Timer1Uint32.h
 *
 * Created: 9/14/2019 9:14:16 PM
 *  Author: Lee
 */ 
#include <avr/io.h>
#include <util/atomic.h>

#ifndef TIMER1UINT32_H_
#define TIMER1UINT32_H_

#define CLOCK_SELECT_MASK		(_BV(CS02) | _BV(CS01) | _BV(CS00))
#define NO_CLOCK				0
#define CLOCK_NO_PRESCALE		1
#define CLOCK_PRESCALE_DIV_8	2
#define CLOCK_PRESCALE_DIV_64	3
#define CLOCK_PRESCALE_DIV_256	4
#define CLOCK_PRESCALE_DIV_1024 5
#define FALLING_EXTERNAL_CLOCK	6
#define RISING_EXTERNAL_CLOCK	7

class Timer1Uint32
{
    public:
    static volatile uint16_t ticksHigh;
    static volatile uint16_t overflowCount;
    static uint32_t ticksPerSecond;
    
    static void Start(uint8_t prescale);
    
    static uint32_t Now();
    
    static uint32_t Future(uint32_t delta)
    {
        return Now() + delta;
    }

    static bool IsPast(uint32_t futureTicks)
    {
        return (Now() >= futureTicks) ? true : false;
    }
};

#endif /* TIMER1UINT32_H_ */