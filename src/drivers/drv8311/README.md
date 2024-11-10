
# DRV8311 SimpleFOC Driver

by [@adolto](https://github.com/adolto)

The DRV8311 provides three integrated MOSFET half-H-bridges for driving a three-phase brushless DC (BLDC) motor for 5-V, 9-V, 12-V, or 18-V DC rails or 1S to 4S battery powered applications.
The device integrates three current-sense amplifiers (CSA) with integrated current sense for sensing the three phase currents of BLDC motors to achieve optimum FOC and current-control system implementation.

See https://www.ti.com/lit/ds/symlink/drv8311.pdf for more information.


## Driver limitations

- Only DRV8311P variant is supported (tSPI interface)
- Parity handing is not supported



## Hardware setup

TODO

## Usage

Usage is quite easy, especially if you already know SimpleFOC. See also the [examples](https://github.com/simplefoc/Arduino-FOC-drivers/examples/drivers/drv8316/)

```c++
#include "Arduino.h"
#include <SimpleFOC.h>
#include "SimpleFOCDrivers.h"
#include "drivers/drv8311/drv8311.hpp"

TODO: Add example

BLDCMotor motor = BLDCMotor(15);
TMC6200Driver6PWM driver = DRV8316Driver6PWM(UH, UL, VH, VL, WH, WL, nCS, DRV_EN);

//... normal simpleFOC init code...
```

### Current Sensing

The gain of the internal current amplifiers can be set to 5, 10 or 20 through `setCurrentSenseGain()`

```c++
    driver.setCurrentSenseGain(TMC6200_AmplificationGain::_5);
    //driver.setCurrentSenseGain(TMC6200_AmplificationGain::_10);
    //driver.setCurrentSenseGain(TMC6200_AmplificationGain::_20);
```
The sense amplifiers can also be turned off ( they are on by default ), through `setCurrentSenseAmplifierState()`

```c++
    driver.setCurrentSenseAmplifierState(false);
```
### Driver Strength
The strength of the mosfet drivers can be controlled through `setDriverStrength()`

```c++
    driver.setDriverStrength(TMC6200_DRVStrength::Weak);
    //driver.setDriverStrength(TMC6200_DRVStrength::WeakTC); // (medium above OTPW level)
    //driver.setDriverStrength(TMC6200_DRVStrength::Medium);
    //driver.setDriverStrength(TMC6200_DRVStrength::Strong);
```

### Handling Faults
The fault line will go high if a fault occurs such as a short, an interrupt can be used to handle it.
Note that some faults will disable the driver and will require the DRV_EN to be cycled to clear the fault.
    
```c++
    // somewhere in setup
    attachInterrupt(digitalPinToInterrupt(FAULT), handleFault, RISING);
```

```c++
    void handleFault()
    {
        // you can read the status register to see what happened
        TMC6200GStatus status = driver.getStatus();
        Serial.print("hasUShorted: "); Serial.println(status.hasUShorted());
        Serial.print("hasVShorted: "); Serial.println(status.hasVShorted());
        Serial.print("hasWShorted: "); Serial.println(status.hasWShorted());
        Serial.print("isUShortedToGround: "); Serial.println(status.isUShortedToGround());
        Serial.print("isUShortedToSupply: "); Serial.println(status.isUShortedToSupply());
        Serial.print("isVShortedToGround: "); Serial.println(status.isVShortedToGround());
        Serial.print("isVShortedToSupply: "); Serial.println(status.isVShortedToSupply());
        Serial.print("isWShortedToGround: "); Serial.println(status.isWShortedToGround());
        Serial.print("isWShortedToSupply: "); Serial.println(status.isWShortedToSupply());
        Serial.print("isOverTemperaturePreWarning: "); Serial.println(status.isOverTemperaturePreWarning());
        Serial.print("isChargePumpUnderVoltage: "); Serial.println(status.isChargePumpUnderVoltage());
        
        // the driver must be cycled to clear the fault
        digitalWrite(DRV_EN, LOW);
        delayMicrosockets(someSmallDelay);
        digitalWrite(DRV_EN, HIGH);
    }
```

The driver provides other features such as controlling the tolerences of short detection and the BBM cycle time and so on, setting the options can be conveniently done via the provided setter methods. All documented registers and options are available via the driver, and the option values can be accessed via enums.
