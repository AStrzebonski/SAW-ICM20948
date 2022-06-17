#ifndef SENSOR_INTERFACE_HPP_
#define SENSOR_INTERFACE_HPP_

#include <cstdint>
#include <cstdio>
namespace swaw::sensor {
    struct Vector3 {
        std::int32_t x;
        std::int32_t y;
        std::int32_t z;
    };

    /// Interface for accelerometer sensors
    class AccelerometerI {
      public:
        void init() {
            return doInit();
        }
        Vector3 getAcceleration() const {
            return doGetAcceleration();
        }

        virtual ~AccelerometerI() {
            printf("hiya\n");
        }

      private:
        virtual void    doInit()                  = 0;
        virtual Vector3 doGetAcceleration() const = 0;
    };


    /// Interface for gyroscope
    template<typename CRTP> class GyroscopeI {
      public:
        void init() {
            return static_cast<CRTP*>(this)->doInit();
        }
        Vector3 getAngularRate() const {
            return static_cast<CRTP const*>(this)->doGetAngularRate();
        }
    };

} // namespace swaw::sensor

#endif