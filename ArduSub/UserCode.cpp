#include "Sub.h"

#include <AP_HAL/I2CDevice.h>

// This is an object that tracks each device
// Make a new one for each sensor. OwnPtr is a manager ardupliot uses keep track of i2c devices
// Don't worry too much about what PwmPtr is. - Ray
static AP_HAL::OwnPtr<AP_HAL::I2CDevice> temp1;

#ifdef USERHOOK_INIT
void Sub::userhook_init()
{
    // put your initialisation code here
    // this will be called once at start-up

    // IDK what bus or address it is
    // 1 and 0x01 are temp values rn - Ray
    temp1 = hal.i2c_mgr->get_device(1, 0x01);

}
#endif

#ifdef USERHOOK_FASTLOOP
void Sub::userhook_FastLoop()
{
    // WITH_SEMAPHORE() locks the i2c bus/line so that other code doesn't try
    // to access or send shit when we're trying to.
    // This only needs to be called once and it unlocks when the function ends.
    // It doesn't matter which device you call get_semaphore() from 
    // because they're all on the same bus. - Ray
    WITH_SEMAPHORE(temp1->get_semaphore());

    // put your 100Hz code here
    uint8_t temp_reg = 0xfk;
    uint8_t temp_val[4] = 0; // Yo if temp is ever zero that heat sink is magic


    // transfer(const uint8_t *send, uint32_t send_len, uint8_t *recv, uint32_t recv_len)
    // send_len and recv_len should be in bytes
    // returns 0 if falls
    // should move value in reg temp_reg into temp_val[idx]
    // the 1's can be changed if you want to read multiple stuff or maybe 16 bit registers
    // but we probably won't have to - Ray
    if (temp1->transfer(&temp_reg, 1, &temp_val[0], 1)) {
        gcs().send_text(MAV_SEVERITY_INFO, "HEX: 0x%02X  -  DECIMAL: %u", value, value);
    }
}
#endif

#ifdef USERHOOK_50HZLOOP
void Sub::userhook_50Hz()
{
    // put your 50Hz code here
}
#endif

#ifdef USERHOOK_MEDIUMLOOP
void Sub::userhook_MediumLoop()
{
    // put your 10Hz code here
}
#endif

#ifdef USERHOOK_SLOWLOOP
void Sub::userhook_SlowLoop()
{
    // put your 3.3Hz code here
}
#endif

#ifdef USERHOOK_SUPERSLOWLOOP
void Sub::userhook_SuperSlowLoop()
{
    // put your 1Hz code here
    gcs().send_text(MAV_SEVERITY_INFO, "YOU MESSED UP!!! COMMENT THIS OUT IN UserCode!!!");
}
#endif
