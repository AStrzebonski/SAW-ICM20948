
extern "C" {
#include "icm20948_api.h"
}



#include "bsp.hpp"
#include "icm-20948.hpp"

#include <cstdio>

namespace swaw::sensor {

    int8_t readFn(const uint8_t addr, uint8_t* data, const uint32_t len) {
        auto r = bsp::read(bsp::SENSOR1, {reinterpret_cast<char*>(data), len}, addr);
        return (r.data() != nullptr) ? ICM20948_RET_OK : ICM20948_RET_GEN_FAIL;
    };


    int8_t writeFn(const uint8_t addr, const uint8_t* data, const uint32_t len) {
        auto w = bsp::write(bsp::SENSOR1, {reinterpret_cast<char const*>(data), len}, addr);
        return (w.data() != nullptr) ? ICM20948_RET_OK : ICM20948_RET_GEN_FAIL;
    };

    void ICM20948::doInit() {
        auto delayFn = [](uint32_t period) {};

        if (ICM20948_RET_OK != icm20948_init(readFn, writeFn, delayFn)) {
            printf("init failed\n");
            while (true) {
                // Or maybe something else?
            }
        }
        icm20948_settings_t settings{.gyro = {.en = ICM20948_MOD_ENABLED, .fs = ICM20948_GYRO_FS_SEL_2000DPS}, .accel = {.en = ICM20948_MOD_ENABLED, .fs = ICM20948_ACCEL_FS_SEL_2G}};
        if (ICM20948_RET_OK != icm20948_applySettings(&settings)) {
            printf("accelerometer enable failed\n");
            while (true) {
                // Or maybe something else?
            }
        }
    }

    Vector3 ICM20948::doGetAcceleration() const {
        icm20948_accel_t d;
        if (ICM20948_RET_OK == icm20948_getAccelData(&d)) {
            return {d.x, d.y, d.z};
        }
        return {};
    }

    Vector3 ICM20948::doGetAngularRate() const {
        icm20948_gyro_t d;
        if (ICM20948_RET_OK == icm20948_getGyroData(&d)) {
            return {d.x, d.y, d.z};
        }
        return {};
    }


} // namespace swaw::sensor