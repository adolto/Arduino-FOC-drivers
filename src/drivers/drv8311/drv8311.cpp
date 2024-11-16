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
    return (DRV8311_OverTemperatureFaultMode)((DRV8311_FLT_MODE_Register)readRegister(DRV8311_FLT_MODE_OFFSET)).OTSD_MODE;
};

void DRV8311Driver::setOverTemperatureFaultMode(DRV8311_OverTemperatureFaultMode mode)
{
    DRV8311_FLT_MODE_Register fltMode = { .reg = readRegister(DRV8311_FLT_MODE_OFFSET) };
    fltMode.OTSD_MODE = (uint16_t)mode;
    writeRegister(DRV8311_FLT_MODE_OFFSET, fltMode.reg);
};

DRV8311_UnderVoltageProtectionFaultMode DRV8311Driver::getUnderVoltageProtectionFaultMode()
{
    return (DRV8311_UnderVoltageProtectionFaultMode)((DRV8311_FLT_MODE_Register)readRegister(DRV8311_FLT_MODE_OFFSET)).UVP_MODE;
};

void DRV8311Driver::setUnderVoltageProtectionFaultMode(DRV8311_UnderVoltageProtectionFaultMode mode)
{
    DRV8311_FLT_MODE_Register fltMode = { .reg = readRegister(DRV8311_FLT_MODE_OFFSET) };
    fltMode.UVP_MODE = (uint16_t)mode;
    writeRegister(DRV8311_FLT_MODE_OFFSET, fltMode.reg);
};

DRV8311_OverCurrentProtectionFaultMode DRV8311Driver::getOverCurrentProtectionFaultMode()
{
    return (DRV8311_OverCurrentProtectionFaultMode)((DRV8311_FLT_MODE_Register)readRegister(DRV8311_FLT_MODE_OFFSET)).OCP_MODE;
};

void DRV8311Driver::setOverCurrentProtectionFaultMode(DRV8311_OverCurrentProtectionFaultMode mode)
{
    DRV8311_FLT_MODE_Register fltMode = { .reg = readRegister(DRV8311_FLT_MODE_OFFSET) };
    fltMode.OCP_MODE = (uint16_t)mode;
    writeRegister(DRV8311_FLT_MODE_OFFSET, fltMode.reg);
};

DRV8311_SPIFaultMode DRV8311Driver::getSPIFaultMode()
{
    return (DRV8311_SPIFaultMode)((DRV8311_FLT_MODE_Register)readRegister(DRV8311_FLT_MODE_OFFSET)).SPIFLT_MODE;
};

void DRV8311Driver::setSPIFaultMode(DRV8311_SPIFaultMode mode)
{
    DRV8311_FLT_MODE_Register fltMode = { .reg = readRegister(DRV8311_FLT_MODE_OFFSET) };
    fltMode.SPIFLT_MODE = (uint16_t)mode;
    writeRegister(DRV8311_FLT_MODE_OFFSET, fltMode.reg);
};

DRV8311_SystemFaultMode DRV8311Driver::getSystemFaultMode()
{
    return (DRV8311_SystemFaultMode)((DRV8311_FLT_MODE_Register)readRegister(DRV8311_FLT_MODE_OFFSET)).OTPFLT_MODE;
};

void DRV8311Driver::setSystemFaultMode(DRV8311_SystemFaultMode mode)
{
    DRV8311_FLT_MODE_Register fltMode = { .reg = readRegister(DRV8311_FLT_MODE_OFFSET) };
    fltMode.OTPFLT_MODE = (uint16_t)mode;
    writeRegister(DRV8311_FLT_MODE_OFFSET, fltMode.reg);
};

DRV8311_CSAREFUnderVoltageFaultEnable DRV8311Driver::getCSAREFUnderVoltageFaultEnable()
{
    return (DRV8311_CSAREFUnderVoltageFaultEnable)((DRV8311_SYSF_CTRL_Register)readRegister(DRV8311_SYSF_CTRL_OFFSET)).CSAREFUV_EN;
};

void DRV8311Driver::setCSAREFUnderVoltageFaultEnable(DRV8311_CSAREFUnderVoltageFaultEnable enable)
{
    DRV8311_SYSF_CTRL_Register sysfCtrl = { .reg = readRegister(DRV8311_SYSF_CTRL_OFFSET) };
    sysfCtrl.CSAREFUV_EN = (uint16_t)enable;
    writeRegister(DRV8311_SYSF_CTRL_OFFSET, sysfCtrl.reg);
};

DRV8311_OverTemperatureWaringFaultEnable DRV8311Driver::getOverTemperatureWaringFaultEnable()
{
    return (DRV8311_OverTemperatureWaringFaultEnable)((DRV8311_SYSF_CTRL_Register)readRegister(DRV8311_SYSF_CTRL_OFFSET)).OTW_EN;
};

void DRV8311Driver::setOverTemperatureWaringFaultEnable(DRV8311_OverTemperatureWaringFaultEnable enable)
{
    DRV8311_SYSF_CTRL_Register sysfCtrl = { .reg = readRegister(DRV8311_SYSF_CTRL_OFFSET) };
    sysfCtrl.OTW_EN = (uint16_t)enable;
    writeRegister(DRV8311_SYSF_CTRL_OFFSET, sysfCtrl.reg);
};

DRV8311_AVDDOverTemperatureFaultEnable DRV8311Driver::getAVDDOverTemperatureFaultEnable()
{
    return (DRV8311_AVDDOverTemperatureFaultEnable)((DRV8311_SYSF_CTRL_Register)readRegister(DRV8311_SYSF_CTRL_OFFSET)).OTAVDD_EN;
};

void DRV8311Driver::setAVDDOverTemperatureFaultEnable(DRV8311_AVDDOverTemperatureFaultEnable enable)
{
    DRV8311_SYSF_CTRL_Register sysfCtrl = { .reg = readRegister(DRV8311_SYSF_CTRL_OFFSET) };
    sysfCtrl.OTAVDD_EN = (uint16_t)enable;
    writeRegister(DRV8311_SYSF_CTRL_OFFSET, sysfCtrl.reg);
};

DRV8311_OCPLevel DRV8311Driver::getOCPLevel()
{
    return (DRV8311_OCPLevel)((DRV8311_DRVF_CTRL_Register)readRegister(DRV8311_DRVF_CTRL_OFFSET)).OCP_LVL;
};

void DRV8311Driver::setOCPLevel(DRV8311_OCPLevel level)
{
    DRV8311_DRVF_CTRL_Register drvFltCtrl = { .reg = readRegister(DRV8311_DRVF_CTRL_OFFSET) };
    drvFltCtrl.OCP_LVL = (uint16_t)level;
    writeRegister(DRV8311_DRVF_CTRL_OFFSET, drvFltCtrl.reg);
};

DRV8311_OCPBlankingTime DRV8311Driver::getOCPBlankingTime()
{
    return (DRV8311_OCPBlankingTime)((DRV8311_DRVF_CTRL_Register)readRegister(DRV8311_DRVF_CTRL_OFFSET)).OCP_TBLANK;
};

void DRV8311Driver::setOCPBlankingTime(DRV8311_OCPBlankingTime time)
{
    DRV8311_DRVF_CTRL_Register drvFltCtrl = { .reg = readRegister(DRV8311_DRVF_CTRL_OFFSET) };
    drvFltCtrl.OCP_TBLANK = (uint16_t)time;
    writeRegister(DRV8311_DRVF_CTRL_OFFSET, drvFltCtrl.reg);
};

DRV8311_OCPDeglitchTime DRV8311Driver::getOCPDeglitchTime()
{
    return (DRV8311_OCPDeglitchTime)((DRV8311_DRVF_CTRL_Register)readRegister(DRV8311_DRVF_CTRL_OFFSET)).OCP_DEG;
};

void DRV8311Driver::setOCPDeglitchTime(DRV8311_OCPDeglitchTime time)
{
    DRV8311_DRVF_CTRL_Register drvFltCtrl = { .reg = readRegister(DRV8311_DRVF_CTRL_OFFSET) };
    drvFltCtrl.OCP_DEG = (uint16_t)time;
    writeRegister(DRV8311_DRVF_CTRL_OFFSET, drvFltCtrl.reg);
};

DRV8311_FastRecoveryRetryTime DRV8311Driver::getFastRecoveryRetryTime()
{
    return (DRV8311_FastRecoveryRetryTime)((DRV8311_FLT_TCTRL_Register)readRegister(DRV8311_FLT_TCTRL_OFFSET)).FAST_TRETRY;
};

void DRV8311Driver::setFastRecoveryRetryTime(DRV8311_FastRecoveryRetryTime time)
{
    DRV8311_FLT_TCTRL_Register fltTCtrl = { .reg = readRegister(DRV8311_FLT_TCTRL_OFFSET) };
    fltTCtrl.FAST_TRETRY = (uint16_t)time;
    writeRegister(DRV8311_FLT_TCTRL_OFFSET, fltTCtrl.reg);
};

DRV8311_SlowRecoveryRetryTime DRV8311Driver::getSlowRecoveryRetryTime()
{
    return (DRV8311_SlowRecoveryRetryTime)((DRV8311_FLT_TCTRL_Register)readRegister(DRV8311_FLT_TCTRL_OFFSET)).SLOW_TRETRY;
};

void DRV8311Driver::setSlowRecoveryRetryTime(DRV8311_SlowRecoveryRetryTime time)
{
    DRV8311_FLT_TCTRL_Register fltTCtrl = { .reg = readRegister(DRV8311_FLT_TCTRL_OFFSET) };
    fltTCtrl.SLOW_TRETRY = (uint16_t)time;
    writeRegister(DRV8311_FLT_TCTRL_OFFSET, fltTCtrl.reg);
};

void DRV8311Driver::clearFaults()
{
    DRV8311_FLT_CLR_Register fltClr = { .FLT_CLR = 0x01 };
    writeRegister(DRV8311_FLT_CLR_OFFSET, fltClr.reg);
};

// ----------------------------------------------------------------------------

DRV8311_SPISyncClockCycles DRV8311Driver::getSPISyncClockCycles()
{
    return (DRV8311_SPISyncClockCycles)((DRV8311_PWMG_CTRL_Register)readRegister(DRV8311_PWMG_CTRL_OFFSET)).SPISYNC_ACRCY;
};

void DRV8311Driver::setSPISyncClockCycles(DRV8311_SPISyncClockCycles cycles)
{
    DRV8311_PWMG_CTRL_Register pwmCtrl = { .reg = readRegister(DRV8311_PWMG_CTRL_OFFSET) };
    pwmCtrl.SPISYNC_ACRCY = (uint16_t)cycles;
    writeRegister(DRV8311_PWMG_CTRL_OFFSET, pwmCtrl.reg);
};

DRV8311_SPISyncFrequency DRV8311Driver::getSPISyncFrequency()
{
    return (DRV8311_SPISyncFrequency)((DRV8311_PWMG_CTRL_Register)readRegister(DRV8311_PWMG_CTRL_OFFSET)).SPICLK_FREQ_SYNC;
};

void DRV8311Driver::setSPISyncFrequency(DRV8311_SPISyncFrequency frequency)
{
    DRV8311_PWMG_CTRL_Register pwmCtrl = { .reg = readRegister(DRV8311_PWMG_CTRL_OFFSET) };
    pwmCtrl.SPICLK_FREQ_SYNC = (uint16_t)frequency;
    writeRegister(DRV8311_PWMG_CTRL_OFFSET, pwmCtrl.reg);
};

DRV8311_OscillatorSyncControl DRV8311Driver::getOscillatorSyncControl()
{
    return (DRV8311_OscillatorSyncControl)((DRV8311_PWMG_CTRL_Register)readRegister(DRV8311_PWMG_CTRL_OFFSET)).PWM_OSC_SYNC;
};

void DRV8311Driver::setOscillatorSyncControl(DRV8311_OscillatorSyncControl control)
{
    DRV8311_PWMG_CTRL_Register pwmCtrl = { .reg = readRegister(DRV8311_PWMG_CTRL_OFFSET) };
    pwmCtrl.PWM_OSC_SYNC = (uint16_t)control;
    writeRegister(DRV8311_PWMG_CTRL_OFFSET, pwmCtrl.reg);
};

DRV8311_PWMGenCounterMode DRV8311Driver::getPWMGenCounterMode()
{
    return (DRV8311_PWMGenCounterMode)((DRV8311_PWMG_CTRL_Register)readRegister(DRV8311_PWMG_CTRL_OFFSET)).PWMCNTR_MODE;
};

void DRV8311Driver::setPWMGenCounterMode(DRV8311_PWMGenCounterMode mode)
{
    DRV8311_PWMG_CTRL_Register pwmCtrl = { .reg = readRegister(DRV8311_PWMG_CTRL_OFFSET) };
    pwmCtrl.PWMCNTR_MODE = (uint16_t)mode;
    writeRegister(DRV8311_PWMG_CTRL_OFFSET, pwmCtrl.reg);
};

DRV8311_PWM_GEN_ENABLE DRV8311Driver::getPWMGenEnable()
{
    return (DRV8311_PWM_GEN_ENABLE)((DRV8311_PWMG_CTRL_Register)readRegister(DRV8311_PWMG_CTRL_OFFSET)).PWM_EN;
};

void DRV8311Driver::setPWMGenEnable(DRV8311_PWM_GEN_ENABLE enable)
{
    DRV8311_PWMG_CTRL_Register pwmCtrl = { .reg = readRegister(DRV8311_PWMG_CTRL_OFFSET) };
    pwmCtrl.PWM_EN = (uint16_t)enable;
    writeRegister(DRV8311_PWMG_CTRL_OFFSET, pwmCtrl.reg);
};

DRV8311_PWMMode DRV8311Driver::getPWMMode()
{
    return (DRV8311_PWMMode)((DRV8311_PWM_CTRL1_Register)readRegister(DRV8311_PWM_CTRL1_OFFSET)).PWM_MODE;
};

void DRV8311Driver::setPWMMode(DRV8311_PWMMode mode)
{
    DRV8311_PWM_CTRL1_Register pwmCtrl1 = { .reg = readRegister(DRV8311_PWM_CTRL1_OFFSET) };
    pwmCtrl1.PWM_MODE = (uint16_t)mode;
    writeRegister(DRV8311_PWM_CTRL1_OFFSET, pwmCtrl1.reg);
};

DRV8311_SpreadSpectrumModulation DRV8311Driver::getSpreadSpectrumModulation()
{
    return (DRV8311_SpreadSpectrumModulation)((DRV8311_PWM_CTRL1_Register)readRegister(DRV8311_PWM_CTRL1_OFFSET)).SSC_DIS;
};

void DRV8311Driver::setSpreadSpectrumModulation(DRV8311_SpreadSpectrumModulation modulation)
{
    DRV8311_PWM_CTRL1_Register pwmCtrl1 = { .reg = readRegister(DRV8311_PWM_CTRL1_OFFSET) };
    pwmCtrl1.SSC_DIS = (uint16_t)modulation;
    writeRegister(DRV8311_PWM_CTRL1_OFFSET, pwmCtrl1.reg);
};

DRV8311_SlewRate DRV8311Driver::getSlewRate()
{
    return (DRV8311_SlewRate)((DRV8311_DRV_CTRL_Register)readRegister(DRV8311_DRV_CTRL_OFFSET)).SLEW_RATE;
};

void DRV8311Driver::setSlewRate(DRV8311_SlewRate rate)
{
    DRV8311_DRV_CTRL_Register drvCtrl = { .reg = readRegister(DRV8311_DRV_CTRL_OFFSET) };
    drvCtrl.SLEW_RATE = (uint16_t)rate;
    writeRegister(DRV8311_DRV_CTRL_OFFSET, drvCtrl.reg);
};

DRV8311_DeadtimeInsertion DRV8311Driver::getDeadtimeInsertion()
{
    return (DRV8311_DeadtimeInsertion)((DRV8311_DRV_CTRL_Register)readRegister(DRV8311_DRV_CTRL_OFFSET)).TDEAD_CTRL;
};

void DRV8311Driver::setDeadtimeInsertion(DRV8311_DeadtimeInsertion insertion)
{
    DRV8311_DRV_CTRL_Register drvCtrl = { .reg = readRegister(DRV8311_DRV_CTRL_OFFSET) };
    drvCtrl.TDEAD_CTRL = (uint16_t)insertion;
    writeRegister(DRV8311_DRV_CTRL_OFFSET, drvCtrl.reg);
};

DRV8311_DriverDelayCompensation DRV8311Driver::getDriverDelayCompensation()
{
    return (DRV8311_DriverDelayCompensation)((DRV8311_DRV_CTRL_Register)readRegister(DRV8311_DRV_CTRL_OFFSET)).DLYCMP_EN;
};

void DRV8311Driver::setDriverDelayCompensation(DRV8311_DriverDelayCompensation enable)
{
    DRV8311_DRV_CTRL_Register drvCtrl = { .reg = readRegister(DRV8311_DRV_CTRL_OFFSET) };
    drvCtrl.DLYCMP_EN = (uint16_t)enable;
    writeRegister(DRV8311_DRV_CTRL_OFFSET, drvCtrl.reg);
};

DRV8311_CurrentSenseAmplifierGain DRV8311Driver::getCSAGain()
{
    return (DRV8311_CurrentSenseAmplifierGain)((DRV8311_CSA_CTRL_Register)readRegister(DRV8311_CSA_CTRL_OFFSET)).CSA_GAIN;
};

void DRV8311Driver::setCSAGain(DRV8311_CurrentSenseAmplifierGain gain)
{
    DRV8311_CSA_CTRL_Register csaCtrl = { .reg = readRegister(DRV8311_CSA_CTRL_OFFSET) };
    csaCtrl.CSA_GAIN = (uint16_t)gain;
    writeRegister(DRV8311_CSA_CTRL_OFFSET, csaCtrl.reg);
};

DRV8311_CurrentSenseAmplifierState DRV8311Driver::getCSAEnable()
{
    return (DRV8311_CurrentSenseAmplifierState)((DRV8311_CSA_CTRL_Register)readRegister(DRV8311_CSA_CTRL_OFFSET)).CSA_EN;
};

void DRV8311Driver::setCSAEnable(DRV8311_CurrentSenseAmplifierState enable)
{
    DRV8311_CSA_CTRL_Register csaCtrl = { .reg = readRegister(DRV8311_CSA_CTRL_OFFSET) };
    csaCtrl.CSA_EN = (uint16_t)enable;
    writeRegister(DRV8311_CSA_CTRL_OFFSET, csaCtrl.reg);
};

DRV8311_ParityEnable DRV8311Driver::getParityEnable()
{
    return (DRV8311_ParityEnable)((DRV8311_SYS_CTRL_Register)readRegister(DRV8311_SYS_CTRL_OFFSET)).SPI_PEN;
}; 

DRV8311_RegisterLock DRV8311Driver::getRegisterLock()
{
    return (DRV8311_RegisterLock)((DRV8311_SYS_CTRL_Register)readRegister(DRV8311_SYS_CTRL_OFFSET)).REG_LOCK;
};

void DRV8311Driver::setRegisterLock(DRV8311_RegisterLock lock)
{
    DRV8311_SYS_CTRL_Register sysCtrl = { .reg = readRegister(DRV8311_SYS_CTRL_OFFSET) };
    sysCtrl.REG_LOCK = (uint16_t)lock;
    writeRegister(DRV8311_SYS_CTRL_OFFSET, sysCtrl.reg);
};
