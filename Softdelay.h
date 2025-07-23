/* 
 * File:   Softdelay.h
 * Author: Sony
 *
 * Created on June 24, 2025, 1:52 PM
 */

/*#ifndef SOFTDELAY_H
#define	SOFTDELAY_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* SOFTDELAY_H */

#ifndef SOFTDELAY_H
#define SOFTDELAY_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#define ONE_MINUTE_DELAY_MS 60000UL  // 60 seconds = 60000 milliseconds

// Start the delay timer
void SoftDelay_Start(uint32_t *startTime);

// Check if 1 minute has passed
bool SoftDelay_IsOneMinuteOver(uint32_t *startTime);

#endif /* SOFTDELAY_H */


