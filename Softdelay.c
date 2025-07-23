#include "Softdelay.h"
#include "mcc_generated_files/tmr0.h"
#include "mcc_generated_files/mcc.h"  // Assuming this provides get_TIMER0Status()

//uint32_t get_TIMER0Status;
//uint32_t g_timer0OverflowCount;
void SoftDelay_Start(uint32_t *startTime)
{
    *startTime = get_TIMER0Status();
}
   uint32_t get_TIMER0Status(void)   //start
{
    return g_timer0OverflowCount;
}  //end

//bool SoftDelay_IsOneMinuteOver(uint32_t *startTime)
//{
//    uint32_t currentTime = get_TIMER0Status();
//    uint32_t elapsedTime;
//
//    if (currentTime >= *startTime)
//    {
//        elapsedTime = currentTime - *startTime;
//    }
//    else
//    {
//        // Handle overflow of 32-bit timer
//        elapsedTime = (0xFFFFFFFFUL - *startTime) + currentTime + 1;
//    }
//
//    if (elapsedTime >= ONE_MINUTE_DELAY_MS)
//    {
//        *startTime = currentTime;  // Reset for next period if needed
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//}
bool SoftDelay_IsOneMinuteOver(uint32_t *startCount) //new 
{
    uint32_t currentCount = get_TIMER0Status();
    if ((currentCount - *startCount) >= 916)  // Assuming 65.536 ms overflow
    {
        *startCount = currentCount;  // Reset for next use
        return true;
    }
    return false;  //end
}

