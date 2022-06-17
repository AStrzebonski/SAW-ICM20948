#include "bsp.hpp"
#include "icm-20948.hpp"
#include "sensor_interface.hpp"
#include "slutcom_packet.hpp"

#include <cstdio>
#include <memory>

int main() {
    using namespace ::swaw;
    using namespace std::literals::chrono_literals;
    bsp::init();
    {
        auto accelerometer = std::make_unique<swaw::sensor::ICM20948>();

        ::std::printf("Hello world\n");

        ::std::printf("Starting measurement using ICM20948\n");
        bsp::write(bsp::CONTROLLER, "hello\n");

        char buffer[100];
        for ( ; ; ) {
            auto acc = accelerometer->getAcceleration();
            ::std::printf("accelerometer [%d %d %d]\n", acc.x, acc.y, acc.z);

            slutcom::AccelerationPacket a{acc.x, acc.y, acc.z};
            auto                    serializedData = a.serialize(buffer);
            if (serializedData.data() != nullptr) {
                bsp::write(bsp::CONTROLLER, serializedData);
            }

            auto gyro = accelerometer->getAngularRate();
            ::std::printf("gyroscope [%d %d %d]\n", gyro.x, gyro.y, gyro.z);

            slutcom::GyroscopePacket g{gyro.x, gyro.y, gyro.z};
            serializedData = g.serialize(buffer);
            if (serializedData.data() != nullptr) {
                bsp::write(bsp::CONTROLLER, serializedData);
            }

            bsp::toggle(bsp::LED::LED1);
            bsp::delay(20ms);
        }
        ::std::printf("Measuring done. bye\n");
    }
    /*
    bsp::write(bsp::CONTROLLER, "Testing USART\n");
    while (true) {
        char c;
        if (auto receivedData = bsp::read(bsp::CONTROLLER, {&c, 1}); !receivedData.empty()) {
            bsp::write(bsp::CONTROLLER, receivedData);
        }
    };
    */
}
