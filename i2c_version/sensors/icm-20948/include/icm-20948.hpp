#ifndef ICM__20948_HPP_
#define ICM__20948_HPP_

#include "sensor_interface.hpp"

namespace swaw::sensor {

    class ICM20948 : public AccelerometerI, public GyroscopeI<ICM20948> {
      public:
      ICM20948() {
        init();
      }
      
        void init() {
          return doInit();
        }
        void doInit() override;

        Vector3 doGetAcceleration() const override;
        Vector3 doGetAngularRate() const;
    };

} // namespace swaw::sensor

#endif