//--------------------------------------------------------------------------------
#include "D_Main.h"
#include "D_I2C.h"
#include "D_SIO.h"
#include "D_EIO.h"
//--------------------------------------------------------------------------------
// Functions
//--------------------------------------------------------------------------------
void user_sub_3(void);
void user_sub_1(void);
void user_sub_2(void);
void user_main(void);
//--------------------------------------------------------------------------------
// Program Name : line.C
//--------------------------------------------------------------------------------
void user_sub_3(void)
{
    if (gAD[CN5] > 593) {
        clr_timer(0);
        while (get_timer(T1) < 200L) {
            gPwm[0] = 0x50;
            gPwm[2] = 0x50 | 0x80;
            gPwm[5] = 0x00 | 0x80;
            pwm_out();
        }
    } else if (gAD[CN6] > 593) {
        clr_timer(0);
        while (get_timer(T1) < 200L) {
            gPwm[0] = 0x1E | 0x80;
            gPwm[2] = 0x1E | 0x80;
            gPwm[5] = 0x50;
            pwm_out();
        }
    } else if (gAD[CN7] > 593) {
        clr_timer(0);
        while (get_timer(T1) < 200L) {
            gPwm[0] = 0x50 | 0x80;
            gPwm[2] = 0x50;
            gPwm[5] = 0x00 | 0x80;
            pwm_out();
        }
    } else if (gAD[CN8] > 593) {
        clr_timer(0);
        while (get_timer(T1) < 200L) {
            gPwm[0] = 0x1E;
            gPwm[2] = 0x1E;
            gPwm[5] = 0x50 | 0x80;
            pwm_out();
        }
    }
}
//--------------------------------------------------------------------------------
// Program Name : get_dir.C
//--------------------------------------------------------------------------------
void user_sub_1(void)
{
    gV[VAR_B] = get_dir(0) - gV[VAR_A];
    if (gV[VAR_B] <= -180) {
        gV[VAR_B] = gV[VAR_B] + 360;
    } else if (gV[VAR_B] >= 180) {
        gV[VAR_B] = gV[VAR_B] - 360;
    }
    return;
}
//--------------------------------------------------------------------------------
// Program Name : ball_get_max.C
//--------------------------------------------------------------------------------
void user_sub_2(void)
{
    gV[VAR_C] = gAD[CN1];
    gV[VAR_D] = gAD[CN2];
    gV[VAR_E] = gAD[CN3];
    gV[VAR_F] = gAD[CN4];
    if (gV[VAR_C] >= gV[VAR_D]) {
        gV[VAR_G] = gV[VAR_C];
    } else {
        gV[VAR_G] = gV[VAR_D];
    }
    if (gV[VAR_E] >= gV[VAR_G]) {
        gV[VAR_G] = gV[VAR_E];
    }
    if (gV[VAR_F] >= gV[VAR_G]) {
        gV[VAR_G] = gV[VAR_F];
    }
    return;
}
//--------------------------------------------------------------------------------
// Program Name : Robot_sample.C
//--------------------------------------------------------------------------------
void user_main(void)
{
    gV[VAR_A] = get_dir(0);
    gPwm[0] = 0x64 | 0x80;
    gPwm[2] = 0x64;
    pwm_out();
    wait_ms(200);
    while (TRUE) {
        user_sub_3();
        user_sub_1();
        if (gV[VAR_B] >= 18) {
            gPwm[0] = 0x26 | 0x80;
            gPwm[2] = 0x26 | 0x80;
            gPwm[5] = 0x26 | 0x80;
            pwm_out();
        } else if (gV[VAR_B] <= -18) {
            gPwm[0] = 0x23;
            gPwm[2] = 0x23;
            gPwm[5] = 0x23;
            pwm_out();
        } else {
            user_sub_2();
            if (gV[VAR_G] <= 100) {
                gPwm[0] = 0x00 | 0x80;
                gPwm[2] = 0x00 | 0x80;
                gPwm[5] = 0x00 | 0x80;
                pwm_out();
            } else if (gV[VAR_G] == gV[VAR_C]) {
                if (gAD[CN1] > 849) {
                    gPwm[0] = 0x50 | 0x80;
                    gPwm[2] = 0x50;
                    gPwm[5] = 0x00 | 0x80;
                    pwm_out();
                } else {
                    if (gAD[CN2] > gAD[CN4]) {
                        gPwm[0] = 0x1E;
                        gPwm[2] = 0x1E;
                        gPwm[5] = 0x50 | 0x80;
                        pwm_out();
                    } else {
                        gPwm[0] = 0x1E | 0x80;
                        gPwm[2] = 0x1E | 0x80;
                        gPwm[5] = 0x50;
                        pwm_out();
                    }
                }
            } else if (gV[VAR_G] == gV[VAR_D]) {
                if (gAD[CN1] > gAD[CN3]) {
                    gPwm[0] = 0x50;
                    gPwm[2] = 0x00 | 0x80;
                    gPwm[5] = 0x53 | 0x80;
                    pwm_out();
                } else {
                    gPwm[0] = 0x50;
                    gPwm[2] = 0x50 | 0x80;
                    gPwm[5] = 0x00 | 0x80;
                    pwm_out();
                    user_sub_3();
                }
            } else if (gV[VAR_G] == gV[VAR_E]) {
                if (gAD[CN2] > gAD[CN4]) {
                    gPwm[0] = 0x1E | 0x80;
                    gPwm[2] = 0x1E | 0x80;
                    gPwm[5] = 0x50;
                    pwm_out();
                } else {
                    gPwm[0] = 0x1E | 0x80;
                    gPwm[2] = 0x1E | 0x80;
                    gPwm[5] = 0x50;
                    pwm_out();
                }
            } else if (gV[VAR_G] == gV[VAR_F]) {
                if (gAD[CN1] > gAD[CN3]) {
                    gPwm[0] = 0x00 | 0x80;
                    gPwm[2] = 0x50 | 0x80;
                    gPwm[5] = 0x53;
                    pwm_out();
                } else {
                    gPwm[0] = 0x50;
                    gPwm[2] = 0x50 | 0x80;
                    gPwm[5] = 0x00 | 0x80;
                    pwm_out();
                    user_sub_3();
                }
            }
        }
    }
}
//--------------------------------------------------------------------------------
