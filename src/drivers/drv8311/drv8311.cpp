

/*******************************************************************************
 *                                 INCLUDES
 ******************************************************************************/

#include "./drv8311.hpp"

/*******************************************************************************
 *                                 IMPLEMENTATION
 ******************************************************************************/

void DRV8311Driver::assignSpi(SPIClass *spi)
{
    _spi = spi;
    if (_nCS >= 0) {
        pinMode(_nCS, OUTPUT);
        digitalWrite(_nCS, HIGH);
    }
};

DRV8311_DeviceStatus DRV8311Driver::getDeviceStatus()
{
    return DRV8311_DeviceStatus(readRegister(DRV8311_DEV_STS1_OFFSET));
};

DRV8311_OverTemperatureStatus DRV8311Driver::getOverTemperatureStatus()
{
    return DRV8311_OverTemperatureStatus(readRegister(DRV8311_OT_STS_OFFSET));
};

DRV8311_SupplyStatus DRV8311Driver::getSupplyStatus()
{
    return DRV8311_SupplyStatus(readRegister(DRV8311_SUP_STS_OFFSET));
};

DRV8311_DriverStatus DRV8311Driver::getDriverStatus()
{
    return DRV8311_DriverStatus(readRegister(DRV8311_DRV_STS_OFFSET));
};

DRV8311_SystemStatus DRV8311Driver::getSystemStatus()
{
    return DRV8311_SystemStatus(readRegister(DRV8311_SYS_STS_OFFSET));
};


DRV8311_OverTemperatureFaultMode DRV8311Driver::getOverTemperatureFaultMode()
{
    return (DRV8311_OverTemperatureFaultMode)((DRV8311_FLT_MODE)readRegister(DRV8311_FLT_MODE_OFFSET)).OTSD_MODE;
};


void DRV8311Driver::setPWMGenEnable(DRV8311_PWM_GEN_ENABLE enable)
{
    DRV8311_PWMG_CTRL pwmg_ctrl = {0};
    pwmg_ctrl.PWM_EN = (uint16_t)enable;
    writeRegister(DRV8311_PWMG_CTRL_OFFSET, pwmg_ctrl.reg);
};