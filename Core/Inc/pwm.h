#ifndef PWM_H
#define PWM_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

void pwm_init(void);
void set_pwm(uint8_t pwm);

#ifdef __cplusplus
}
#endif

#endif