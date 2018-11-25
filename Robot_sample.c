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
    while (TRUE) {
        user_sub_1();
        if (gV[VAR_B] >= 15) {
            while (TRUE) {
                user_sub_1();
                if (gV[VAR_B] <= 0) {
                    break;
                } else {
                    gPwm[0] = 0x19 | 0x80;
                    gPwm[1] = 0x19 | 0x80;
                    gPwm[2] = 0x19 | 0x80;
                    pwm_out();
                }
            }
        } else if (gV[VAR_B] <= -15) {
            while (TRUE) {
                user_sub_1();
                if (gV[VAR_B] >= 0) {
                    break;
                } else {
                    gPwm[0] = 0x19;
                    gPwm[1] = 0x19;
                    gPwm[2] = 0x19;
                    pwm_out();
                }
            }
        } else {
            user_sub_2();
            if (gV[VAR_G] <= 100) {
                gPwm[0] = 0x00 | 0x80;
                gPwm[1] = 0x00 | 0x80;
                gPwm[2] = 0x00 | 0x80;
                pwm_out();
            } else if (gV[VAR_G] == gV[VAR_C]) {
                gPwm[0] = 0x64 | 0x80;
                gPwm[1] = 0x00 | 0x80;
                gPwm[2] = 0x64;
                pwm_out();
            } else if (gV[VAR_G] == gV[VAR_D]) {
                gPwm[0] = 0x26;
                gPwm[1] = 0x64 | 0x80;
                gPwm[2] = 0x26;
                pwm_out();
            } else if (gV[VAR_G] == gV[VAR_E]) {
                gPwm[0] = 0x64;
                gPwm[1] = 0x00 | 0x80;
                gPwm[2] = 0x64 | 0x80;
                pwm_out();
            } else if (gV[VAR_G] == gV[VAR_F]) {
                gPwm[0] = 0x26 | 0x80;
                gPwm[1] = 0x64;
                gPwm[2] = 0x26 | 0x80;
                pwm_out();
            }
        }
    }
}
//--------------------------------------------------------------------------------
