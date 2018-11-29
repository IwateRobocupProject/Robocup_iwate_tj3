//--------------------------------------------------------------------------------
#include "D_Main.h"
#include "D_I2C.h"
#include "D_SIO.h"
#include "D_EIO.h"
//--------------------------------------------------------------------------------
// Functions
//--------------------------------------------------------------------------------
void user_sub_1(void);
void user_sub_2(void);
void user_main(void);
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
    wait_ms(1000);
    while (TRUE) {
        user_sub_1();
        if (gV[VAR_B] >= 15) {
            gPwm[0] = 0x23 | 0x80;
            gPwm[2] = 0x23 | 0x80;
            gPwm[5] = 0x23 | 0x80;
            pwm_out();
        } else if (gV[VAR_B] <= -15) {
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
                gPwm[0] = 0x50 | 0x80;
                gPwm[2] = 0x50;
                gPwm[5] = 0x00 | 0x80;
                pwm_out();
            } else if (gV[VAR_G] == gV[VAR_D]) {
                gPwm[0] = 0x32;
                gPwm[2] = 0x1E;
                gPwm[5] = 0x50 | 0x80;
                pwm_out();
            } else if (gV[VAR_G] == gV[VAR_E]) {
                gPwm[0] = 0x32;
                gPwm[2] = 0x28;
                gPwm[5] = 0x5A | 0x80;
                pwm_out();
            } else if (gV[VAR_G] == gV[VAR_F]) {
                gPwm[0] = 0x1E | 0x80;
                gPwm[2] = 0x1E | 0x80;
                gPwm[5] = 0x50;
                pwm_out();
            }
        }
    }
}
//--------------------------------------------------------------------------------
