#ifndef SIMPLEFOC_DRV8311P
#define SIMPLEFOC_DRV8311P

/*******************************************************************************
 *                                 INCLUDES
 ******************************************************************************/

#include "./drv8311.hpp"
#include "common/base_classes/BLDCDriver.h"

class DRV8311PDriver : public BLDCDriver, public DRV8311Driver
{
public:
    DRV8311PDriver(int nCS = -1, SPISettings spiSettings = DRV8311_DEFAULT_SPISettings, bool AD0 = false, bool AD1 = false);

    /* override from FOCDriver inherited from BLDCDriver */
    virtual int init() override;
    virtual void enable() override;
    virtual void disable() override;

    /* override from BLDCDriver */
    virtual void setPwm(float Ua, float Ub, float Uc) override;
    virtual void setPhaseState(PhaseState sa, PhaseState sb, PhaseState sc) override;

protected:
    /* override from DRV8311Driver */
    virtual uint16_t readRegister(uint8_t addr) override;
    virtual void writeRegister(uint8_t addr, uint16_t data) override;
    virtual void readRegisterSequence(uint8_t startAddr, uint8_t *buffer, size_t bufferSize) override;
    virtual void writeRegisterSequence(uint8_t startAddr, uint8_t *buffer, size_t bufferSize) override;
  
    uint16_t _tSpiADHeader; /** tSPI header with AD0/AD1 at the desired position */

    /* TODO: Variables that saves states like parity enabled and so on */
};

#endif /* SIMPLEFOC_DRV8311P */
