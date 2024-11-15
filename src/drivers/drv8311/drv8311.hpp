#ifndef SIMPLEFOC_DRV8311
#define SIMPLEFOC_DRV8311

/*******************************************************************************
 *                                 INCLUDES
 ******************************************************************************/

#include "Arduino.h"
#include <SPI.h>
#include "./drv8311_registers.hpp"

// TODO: Improve
static SPISettings DRV8311_DEFAULT_SPISettings(1000000, MSBFIRST, SPI_MODE1);

/* Configuration enum classs for Fault Mode Register */

/**
 * @brief Overtemperature Fault mode
 */
enum class DRV8311_OverTemperatureFaultMode
{
    REPORT_nFAULT_SLOW_RETRY = 0x00, /* Report on nFault, predriver HiZ, auto recovery with Slow Retry time (in s) */
    REPORT_nFAULT_FAST_RETRY = 0x01  /* Report on nFault, predriver HiZ, auto recovery with Fast Retry time (in ms) */
};

/**
 * @brief Undervoltage Protection Fault mode
 */
enum class DRV8311_UnderVoltageProtectionFaultMode
{
    REPORT_nFAULT_SLOW_RETRY = 0x00, /* Report on nFault, predriver HiZ, auto recovery with Slow Retry time (in s) */
    REPORT_nFAULT_FAST_RETRY = 0x01  /* Report on nFault, predriver HiZ, auto recovery with Fast Retry time (in ms) */
};

/**
 * @brief Overcurrent Protection Fault mode
 */
enum class DRV8311_OverCurrentProtectionFaultMode
{
    REPORT_nFAULT_SLOW_RETRY = 0x00,    /* Report on nFault, predriver HiZ, auto recovery with Slow Retry time (in s) */
    REPORT_nFAULT_FAST_RETRY = 0x01,    /* Report on nFault, predriver HiZ, auto recovery with Fast Retry time (in ms) */
    REPORT_nFAULT_LATCHED_FAULT = 0x02, /* Report on nFault, predriver HiZ, Latched Fault */
    REPORT_nFAULT_NO_ACTION = 0x03,     /* Report on nFault, No action on predriver */
    Disabled = 0x07                     /* Disabled */
};

/**
 * @brief SPI Fault mode
 */
enum class DRV8311_SPIFaultMode
{
    SPI_FAULT_ENABLED = 0x00, /* SPI Fault is enabled */
    SPI_FAULT_DISABLED = 0x01 /* SPI Fault is disabled */
};

/**
 * @brief System Fault mode
 */
enum class DRV8311_SystemFaultMode
{
    SYSTEM_FAULT_ENABLED = 0x00, /* OTP read fault is enabled */
    SYSTEM_FAULT_DISABLED = 0x01 /* OTP read fault is disabled */
};

/* Configuration enum classs for System Fault Control Register */

/**
 * @brief CSAREF Undervoltage Fault Enable
 */
enum class DRV8311_CSAREFUnderVoltageFaultEnable
{
    CSAREF_UNDER_VOLTAGEFAULT_DISABLED = 0x00, /* CSAREF undervoltage lockout is disabled */
    CSAREF_UNDER_VOLTAGEFAULT_ENABLED = 0x01   /* CSAREF undervoltage lockout is enabled */
};

/**
 * @brief Overtemperature Warning Fault Enable
 */
enum class DRV8311_OverTemperatureWaringFaultEnable
{
    OVER_TEMPERATUR_WARNING_FAULT_DISABLED = 0x00, /* Overtemperature fault is disabled */
    OVER_TEMPERATUR_WARNING_FAULT_ENABLED = 0x01   /* Overtemperature fault is enabled */
};

/**
 * @brief AVDD Overtemperature Fault Enable
 */
enum class DRV8311_AVDDOverTemperatureFaultEnable
{
    AVDD_OVER_TEMPERATUR_FAULT_DISABLED = 0x00, /* Overtemperature protection near AVDD is disabled */
    AVDD_OVER_TEMPERATUR_FAULT_ENABLED = 0x01   /* Overtemperature protection near AVDD is enabled */
};

/* Configuration enum classs for Driver Fault Control Register */

/**
 * @brief OCP Level Settings
 */
enum class DRV8311_OCPLevel
{
    OCP_LEVEL_9A = 0x00, /* OCP level is 9 A (TYP) */
    OCP_LEVEL_4A = 0x01  /* OCP level is 5 A (TYP) */
};

/**
 * @brief OCP Blanking Time
 */
enum class DRV8311_OCPBlankingTime
{
    OCP_BLANKING_TIME_0_2us = 0x00, /* OCP blanking time is 0.2 µs */
    OCP_BLANKING_TIME_0_5us = 0x01, /* OCP blanking time is 0.5 µs */
    OCP_BLANKING_TIME_0_8us = 0x02, /* OCP blanking time is 0.8 µs */
    OCP_BLANKING_TIME_1us = 0x03    /* OCP blanking time is 1 µs */
};

/**
 * @brief OCP Deglitch Time
 */
enum class DRV8311_OCPDeglitchTime
{
    OCP_DEGLITCH_TIME_0_2us = 0x00, /* OCP deglitch time is 0.2 µs */
    OCP_DEGLITCH_TIME_0_5us = 0x01, /* OCP deglitch time is 0.5 µs */
    OCP_DEGLITCH_TIME_0_8us = 0x02, /* OCP deglitch time is 0.8 µs */
    OCP_DEGLITCH_TIME_1us = 0x03    /* OCP deglitch time is 1 µs */
};

/* Configuration enum classs for Fault Timing Control Register */

/**
 * @brief Fast Recovery Retry Time from Fault Condition
 */
enum class DRV8311_FastRecoveryRetryTime
{
    FAST_RECOVERY_RETRY_0_5ms = 0x00, /* Fast recovery retry time from Fault condition is 0.5 ms */
    FAST_RECOVERY_RETRY_1ms = 0x01,   /* Fast recovery retry time from Fault condition is 1 ms */
    FAST_RECOVERY_RETRY_2ms = 0x02,   /* Fast recovery retry time from Fault condition is 2 ms */
    FAST_RECOVERY_RETRY_5ms = 0x03    /* Fast recovery retry time from Fault condition is 5 ms */
};

/**
 * @brief Slow Recovery Retry Time from Fault Condition
 */
enum class DRV8311_SlowRecoveryRetryTime
{
    SLOW_RECOVERY_RETRY_TIME_0_5s = 0x00, /* Slow recovery retry time from Fault condition is 0.5 s */
    SLOW_RECOVERY_RETRY_TIME_1s = 0x01,   /* Slow recovery retry time from Fault condition is 1 s */
    SLOW_RECOVERY_RETRY_TIME_2s = 0x02,   /* Slow recovery retry time from Fault condition is 2 s */
    SLOW_RECOVERY_RETRY_TIME_5s = 0x03    /* Slow recovery retry time from Fault condition is 5 s */
};

/* Configuration enum classs for PWM State Register */

/**
 * @brief Phase Driver Output control
 */
enum class DRV8311_PhaseDriverOutputControl
{
    HIGH_SIDE_OFF_LOW_SIDE_OFF = 0x00, /* High Side is OFF, Low Side is OFF */
    HIGH_SIDE_OFF_LOW_SIDE_ON = 0x01,  /* High Side is OFF, Low Side is forced ON */
    HIGH_SIDE_ON_LOW_SIDE_OFF = 0x02,  /* High Side is forced ON, Low Side is OFF */
    HIGH_SIDE_OFF_LOW_SIDE_PWM = 0x05, /* High Side is OFF, Low Side is PWM */
    HIGH_SIDE_PWM_LOW_SIDE_OFF = 0x06, /* High Side is PWM, Low Side is OFF */
    HIGH_SIDE_PWM_LOW_SIDE_nPWM = 0x07 /* High Side is PWM, Low Side is !PWM */
};

/* Configuration enum classs for PWM_GEN Control Register */

/**
 * @brief Number of SPI Clock Cycle require for synchronizing the Oscillator
 */
enum class DRV8311_SPISyncClockCycles
{
    SPI_SYNC_CLOCK_CYCLES_512 = 0x00, /* 512 Clock Cycles (1%) */
    SPI_SYNC_CLOCK_CYCLES_256 = 0x01, /* 256 Clock Cycles (1%) */
    SPI_SYNC_CLOCK_CYCLES_128 = 0x02, /* 128 Clock Cycles (1%) */
    SPI_SYNC_CLOCK_CYCLES_64 = 0x03   /* 64 Clock Cycles (2%) */
};

/**
 * @brief SPI Clock Frequency for synchronizing the Oscillator
 */
enum class DRV8311_SPISyncFrequency
{
    SPI_SYNC_FREQUENCY_1MHz = 0x00,    /* 1 MHz */
    SPI_SYNC_FREQUENCY_1_25MHz = 0x01, /* 1.25 MHz */
    SPI_SYNC_FREQUENCY_2MHz = 0x02,    /* 2 MHz */
    SPI_SYNC_FREQUENCY_2_5MHz = 0x03,  /* 2.5 MHz */
    SPI_SYNC_FREQUENCY_4MHz = 0x04,    /* 4 MHz */
    SPI_SYNC_FREQUENCY_5MHz = 0x05,    /* 5 MHz */
    SPI_SYNC_FREQUENCY_8MHz = 0x06,    /* 8 MHz */
    SPI_SYNC_FREQUENCY_10MHz = 0x07    /* 10 MHz */
};

/**
 * @brief Oscillator synchronization and PWM_SYNC control
 */
enum class DRV8311_OscillatorSyncControl
{
    PWM_SYNC_DISABLED = 0x00,              /* Oscillator synchronization is disable */
    PWM_SYNC_WITH_CALIBRATION = 0x01,      /* PWM_SYNC_PRD indicates period of PWM_SYNC signal and can be used to calibrate PWM period */
    PWM_SYNC = 0x02,                       /* PWM_SYNC used to set PWM period */
    PWM_SYNC_20KHZ = 0x05,                 /* PWM_SYNC used for oscillator synchronization (only 20 kHz frequency supported) */
    PWM_SYNC_20HZ_WITH_CALIBRATION = 0x06, /* PWM_SYNC used for oscillator synchronization and setting PWM period (only 20 kHz frequency supported) */
    PWM_SYNC_SPI_CLK = 0x07                /* PI Clock pin SCLK used for oscillator synchronization (Configure SPICLK_FREQ_SYNC) */
};

/**
 * @brief PWM Gen counter mode
 */
enum class DRV8311_PWMGenCounterMode
{
    PWM_GEN_COUNT_MODE_UP_DOWN = 0x00, /* Up and Down */
    PWM_GEN_COUNT_MODE_UP = 0x01,      /* Up */
    PWM_GEN_COUNT_MODE_DOWN = 0x02     /* Down */
};

/**
 * @brief Enable 3X Internal mode PWM Generation
 */
enum class DRV8311_PWM_GEN_ENABLE
{
    PWM_GEN_DISABLED = 0x00, /* PWM_GEN disabled */
    PWM_GEN_ENABLED = 0x01   /* PWM_GEN enabled */
};

/* Configuration enum classs for PWM Control Register 1 */

/**
 * @brief PWM mode selection
 * The reset setting in DRV8311S is 00b and in DRV8311 is 11b
 */
enum class DRV8311_PWMMode
{
    PWM_6X_MODE = 0x00,  /* 6x mode */
    PWM_3X_MODE = 0x02,  /* 3x mode */
    PWM_GEN_MODE = 0x03, /* PWM generation mode */
};

/**
 * @brief Spread Spectrum Modulation for internal Oscillator
 */
enum class DRV8311_SpreadSpectrumModulation
{
    SPREA_SPECTRUM_MODULATATION_ENABLED = 0x00, /* Spread spectrum modulation is enabled */
    SPREA_SPECTRUM_MODULATATION_DISABLED = 0x01 /* Spread spectrum modulation is disable */
};

/* Configuration enum classs for Predriver control Register */

/**
 * @brief Slew rate settings
 */
enum class DRV8311_SlewRate
{
    SLEW_RATE_35_V_uS = 0x00,  /* Slew rate is 35 V/µs */
    SLEW_RATE_70_V_uS = 0x01,  /* Slew rate is 70 V/µs */
    SLEW_RATE_180_V_uS = 0x02, /* Slew rate is 180 V/µs */
    SLEW_RATE_230_V_uS = 0x03  /* Slew rate is 230 V/µs */
};

/**
 * @brief Deadtime insertion control
 */
enum class DRV8311_DeadtimeInsertion
{
    DEADTIME_NONE = 0x00,   /* No deadtime (Handshake Only) */
    DEADTIME_200_nS = 0x01, /* Deadtime is 200 ns */
    DEADTIME_400_nS = 0x02, /* Deadtime is 400 ns */
    DEADTIME_600_nS = 0x03,  /* Deadtime is 600 ns */
    DEADTIME_800_nS = 0x04, /* Deadtime is 800 ns */
    DEADTIME_1_uS = 0x05,   /* Deadtime is 1 µs */
    DEADTIME_1_2_uS = 0x06, /* Deadtime is 1.2 µs */
    DEADTIME_1_4_uS = 0x07  /* Deadtime is 1.4 µs */
};

/**
 * @brief Driver Delay Compensation
 */
enum class DRV8311_DriverDelayCompensation
{
    DRIVER_DELAY_COMPENSATION_DISABLED = 0x00, /* Driver delay compensation is disabled */
    DRIVER_DELAY_COMPENSATION_ENABLED = 0x01   /* Driver delay compensation is enabled */
};

/** Configuration enum classs for CSA Control Register */

/**
 * @brief Current Sense Amplifier Gain
 */
enum class DRV8311_CurrentSenseAmplifierGain
{
    CSA_GAIN_0_25_V_A = 0x00,   /* CSA gain is 0.25 V/A */
    CSA_GAIN_0_5_V_A = 0x01,    /* CSA gain is 0.5 V/A */
    CSA_GAIN_1_V_A = 0x02,      /* CSA gain is 1 V/A */
    CSA_GAIN_2_V_A = 0x03       /* CSA gain is 2 V/A */
};

/**
 * @brief Current Sense Amplifier State
 */
enum class DRV8311_CurrentSenseAmplifierState
{
    CSA_DISABLED = 0x00, /* Current Sense Amplifier is disabled */
    CSA_ENABLED = 0x01   /* Current Sense Amplifier is enabled */
};

/* Configuration enum classs for System Control Register */

/**
 * @brief Parity Enable for both SPI and tSPI
 */
enum class DRV8311_ParityEnable
{
    PARITY_DISABLED = 0x00, /* Parity is disabled */
    PARITY_ENABLED = 0x01   /* Parity is enabled */
};

/**
 * @brief Register Lock
 */
enum class DRV8311_RegisterLock
{
    REGISTER_LOCK_DISABLED = 0x00, /* Registers unlocked */
    REGISTER_LOCK_ENABLED = 0x01   /* Registers locked */
};

/*******************************************************************************
 *                                 CLASSES
 ******************************************************************************/

/**
 * @brief Holds the DRV8311 device status
 */
class DRV8311_DeviceStatus
{
public:
    DRV8311_DeviceStatus(DRV8311_DEV_STS1 status) : _status(status){};
    DRV8311_DeviceStatus(uint16_t status) : _status(status){};


    bool faultDetected() { return _status.FAULT == 0x01; };
    bool overTemperatureDetected() { return _status.OT == 0x01; };
    bool supplyUnderVoltageDetected() { return _status.UVP == 0x01; };
    bool driverOverCurrentDetected() { return _status.OCP == 0x01; };
    bool spiCommuncationErrorDetected() { return _status.SPI_FLT == 0x01; };
    bool powerOnResetDetected() { return _status.RESET == 0x01; };
    bool otpReadErrorDetected() { return _status.OTP_FLT == 0x01; };

    DRV8311_DEV_STS1 getRegister() { return _status; };

private:
    DRV8311_DEV_STS1 _status;
};

/**
 * @brief Holds the DRV8311 over temperature status
 */
class DRV8311_OverTemperatureStatus
{
public:
    DRV8311_OverTemperatureStatus(DRV8311_OT_STS status) : _status(status){};
    DRV8311_OverTemperatureStatus(uint16_t status) : _status(status){};

    bool overTemperatureShutdownDetected() { return _status.OTSD == 0x01; };
    bool overTemperatureWarningDetected() { return _status.OTW == 0x01; };
    bool overTemperaturAVDDShutdownDetected() { return _status.OTS_AVDD == 0x01; };

    DRV8311_OT_STS getRegister() { return _status; };

private:
    DRV8311_OT_STS _status;
};

/**
 * @brief Holds the DRV8311 supply status
 */
class DRV8311_SupplyStatus
{
public:
    DRV8311_SupplyStatus(DRV8311_SUP_STS status) : _status(status){};
    DRV8311_SupplyStatus(uint16_t status) : _status(status){};

    bool underVoltageVinAvddDetected() { return _status.VINAVDD_UV == 0x01; };
    bool underVoltageAvddDetected() { return _status.AVDD_UV == 0x01; };
    bool underVoltageChargePumpDetected() { return _status.CP_UV == 0x01; };
    bool underVoltageCsaRefDetected() { return _status.CSAREF_UV == 0x01; };

    DRV8311_SUP_STS getRegister() { return _status; };

private:
    DRV8311_SUP_STS _status;
};

/**
 * @brief Holds the DRV8311 driver status
 */
class DRV8311_DriverStatus
{
public:
    DRV8311_DriverStatus(DRV8311_DRV_STS status) : _status(status){};
    DRV8311_DriverStatus(uint16_t status) : _status(status){};

    bool overCurrentALowSideDetected() { return _status.OCPA_LS == 0x01; };
    bool overCurrentBLowSideDetected() { return _status.OCPB_LS == 0x01; };
    bool overCurrentCLowSideDetected() { return _status.OCPC_LS == 0x01; };
    bool overCurrentAHighSideDetected() { return _status.OCPA_HS == 0x01; };
    bool overCurrentBHighSideDetected() { return _status.OCPB_HS == 0x01; };
    bool overCurrentCHighSideDetected() { return _status.OCPC_HS == 0x01; };

    DRV8311_DRV_STS getRegister() { return _status; };

private:
    DRV8311_DRV_STS _status;
};

/**
 * @brief Holds the DRV8311 system status
 */
class DRV8311_SystemStatus
{
public:
    DRV8311_SystemStatus(DRV8311_SYS_STS status) : _status(status){};
    DRV8311_SystemStatus(uint16_t status) : _status(status){};

    bool spiFrameErrorDetected() { return _status.FRM_ERR == 0x01; };
    bool spiBusContentionErrorDetected() { return _status.BUS_CNT == 0x01; };
    bool spiParityErrorDetected() { return _status.SPI_PARITY == 0x01; };
    bool otpReadErrorDetected() { return _status.OTPLD_ERR == 0x01; };

    DRV8311_SYS_STS getRegister() { return _status; };

private:
    DRV8311_SYS_STS _status;
};

class DRV8311Driver
{
public:
    DRV8311Driver(int nCS = -1, SPISettings spiSettings = DRV8311_DEFAULT_SPISettings) : _nCS(nCS), _spiSettings(spiSettings) {};

    /**
     * @brief Initialize the driver
     */
    void assignSpi(SPIClass *spi);
    
    /* Read status from device */

    /**
     * @brief Read and returns the device status
     */
    DRV8311_DeviceStatus getDeviceStatus();

    /**
     * @brief Read and returns the over temperature status
     */
    DRV8311_OverTemperatureStatus getOverTemperatureStatus();

    /**
     * @brief Read and returns the supply status
     */
    DRV8311_SupplyStatus getSupplyStatus();

    /**
     * @brief Read and returns the driver status
     */
    DRV8311_DriverStatus getDriverStatus();

    /**
     * @brief Read and returns the system status
     */
    DRV8311_SystemStatus getSystemStatus();

    /* Read and write configurations from and to device */

    /**
     * @brief Set the over temperature fault mode
     */
    void setOverTemperatureFaultMode(DRV8311_OverTemperatureFaultMode mode);

    /**
     * @brief Get the over temperature fault mode
     */
    DRV8311_OverTemperatureFaultMode getOverTemperatureFaultMode();

    /**
     * @brief Set the under voltage protection fault mode
     */
    void setUnderVoltageProtectionFaultMode(DRV8311_UnderVoltageProtectionFaultMode mode);

    /**
     * @brief Get the under voltage protection fault mode
     */
    DRV8311_UnderVoltageProtectionFaultMode getUnderVoltageProtectionFaultMode();

    /**
     * @brief Set the over current protection fault mode
     */
    void setOverCurrentProtectionFaultMode(DRV8311_OverCurrentProtectionFaultMode mode);

    /**
     * @brief Get the over current protection fault mode
     */
    DRV8311_OverCurrentProtectionFaultMode getOverCurrentProtectionFaultMode();

    /**
     * @brief Set the SPI fault mode
     */
    void setSPIFaultMode(DRV8311_SPIFaultMode mode);

    /**
     * @brief Get the SPI fault mode
     */
    DRV8311_SPIFaultMode getSPIFaultMode();

    /**
     * @brief Set the system fault mode
     */
    void setSystemFaultMode(DRV8311_SystemFaultMode mode);

    /**
     * @brief Get the system fault mode
     */
    DRV8311_SystemFaultMode getSystemFaultMode();

    /**
     * @brief Set the CSAREF undervoltage fault enable
     */
    void setCSAREFUnderVoltageFaultEnable(DRV8311_CSAREFUnderVoltageFaultEnable enable);

    /**
     * @brief Get the CSAREF undervoltage fault enable
     */
    DRV8311_CSAREFUnderVoltageFaultEnable getCSAREFUnderVoltageFaultEnable();

    /**
     * @brief Set the over temperature warning fault enable
     */
    void setOverTemperatureWaringFaultEnable(DRV8311_OverTemperatureWaringFaultEnable enable);

    /**
     * @brief Get the over temperature warning fault enable
     */
    DRV8311_OverTemperatureWaringFaultEnable getOverTemperatureWaringFaultEnable();

    /**
     * @brief Set the AVDD over temperature fault enable
     */
    void setAVDDOverTemperatureFaultEnable(DRV8311_AVDDOverTemperatureFaultEnable enable);

    /**
     * @brief Get the AVDD over temperature fault enable
     */
    DRV8311_AVDDOverTemperatureFaultEnable getAVDDOverTemperatureFaultEnable();

    /**
     * @brief Set the OCP level
     */
    void setOCPLevel(DRV8311_OCPLevel level);

    /**
     * @brief Get the OCP level
     */
    DRV8311_OCPLevel getOCPLevel();

    /**
     * @brief Set the OCP blanking time
     */
    void setOCPBlankingTime(DRV8311_OCPBlankingTime time);

    /**
     * @brief Get the OCP blanking time
     */
    DRV8311_OCPBlankingTime getOCPBlankingTime();

    /**
     * @brief Set the OCP deglitch time
     */
    void setOCPDeglitchTime(DRV8311_OCPDeglitchTime time);

    /**
     * @brief Get the OCP deglitch time
     */
    DRV8311_OCPDeglitchTime getOCPDeglitchTime();

    /**
     * @brief Set the fast recovery retry time
     */
    void setFastRecoveryRetryTime(DRV8311_FastRecoveryRetryTime time);

    /**
     * @brief Get the fast recovery retry time
     */
    DRV8311_FastRecoveryRetryTime getFastRecoveryRetryTime();

    /**
     * @brief Set the slow recovery retry time
     */
    void setSlowRecoveryRetryTime(DRV8311_SlowRecoveryRetryTime time);

    /**
     * @brief Get the slow recovery retry time
     */
    DRV8311_SlowRecoveryRetryTime getSlowRecoveryRetryTime();

    /**
     * @brief Set the Phase A Driver Output control
     */
    void setPhaseADriverOutputControl(DRV8311_PhaseDriverOutputControl control);

    /**
     * @brief Get the Phase A Driver Output control
     */
    DRV8311_PhaseDriverOutputControl getPhaseADriverOutputControl();

    /**
     * @brief Set the Phase B Driver Output control
     */
    void setPhaseBDriverOutputControl(DRV8311_PhaseDriverOutputControl control);

    /**
     * @brief Get the Phase B Driver Output control
     */
    DRV8311_PhaseDriverOutputControl getPhaseBDriverOutputControl();

    /**
     * @brief Set the Phase C Driver Output control
     */
    void setPhaseCDriverOutputControl(DRV8311_PhaseDriverOutputControl control);

    /**
     * @brief Get the Phase C Driver Output control
     */
    DRV8311_PhaseDriverOutputControl getPhaseCDriverOutputControl();

    /**
     * @brief Set the number of SPI Clock Cycle require for synchronizing the Oscillator
     */
    void setSPISyncClockCycles(DRV8311_SPISyncClockCycles cycles);

    /**
     * @brief Number of SPI Clock Cycle require for synchronizing the Oscillator
     */
    DRV8311_SPISyncClockCycles getSPISyncClockCycles();

    /**
     * @brief Set the SPI Clock Frequency for synchronizing the Oscillator
     */
    void setSPISyncFrequency(DRV8311_SPISyncFrequency frequency);

    /**
     * @brief get SPI Clock Frequency for synchronizing the Oscillator
     */
    DRV8311_SPISyncFrequency getSPISyncFrequency();

    /**
     * @brief Set the Oscillator synchronization and PWM_SYNC control
     */
    void setOscillatorSyncControl(DRV8311_OscillatorSyncControl control);

    /**
     * @brief get Oscillator synchronization and PWM_SYNC control
     */
    DRV8311_OscillatorSyncControl getOscillatorSyncControl();

    /**
     * @brief Set the PWM Gen counter mode
     */
    void setPWMGenCounterMode(DRV8311_PWMGenCounterMode mode);

    /**
     * @brief get PWM Gen counter mode
     */
    DRV8311_PWMGenCounterMode getPWMGenCounterMode();

    /**
     * @brief Set the Enable 3X Internal mode PWM Generation
     */
    void setPWMGenEnable(DRV8311_PWM_GEN_ENABLE enable);

    /**
     * @brief get Enable 3X Internal mode PWM Generation
     */
    DRV8311_PWM_GEN_ENABLE getPWMGenEnable();

    /**
     * @brief Set the PWM mode selection
     */
    void setPWMMode(DRV8311_PWMMode mode);

    /**
     * @brief get PWM mode selection
     */
    DRV8311_PWMMode getPWMMode();

    /**
     * @brief Set the Spread Spectrum Modulation for internal Oscillator
     */
    void setSpreadSpectrumModulation(DRV8311_SpreadSpectrumModulation modulation);

    /**
     * @brief get Spread Spectrum Modulation for internal Oscillator
     */
    DRV8311_SpreadSpectrumModulation getSpreadSpectrumModulation();

    /**
     * @brief Set the Slew rate settings
     */
    void setSlewRate(DRV8311_SlewRate rate);

    /**
     * @brief get Slew rate settings
     */
    DRV8311_SlewRate getSlewRate();

    /**
     * @brief Set the Deadtime insertion control
     */
    void setDeadtimeInsertion(DRV8311_DeadtimeInsertion insertion);

    /**
     * @brief get Deadtime insertion control
     */
    DRV8311_DeadtimeInsertion getDeadtimeInsertion();

    /**
     * @brief Set the Driver Delay Compensation
     */
    void setDriverDelayCompensation(DRV8311_DriverDelayCompensation compensation);

    /**
     * @brief get Driver Delay Compensation
     */
    DRV8311_DriverDelayCompensation getDriverDelayCompensation();

    /**
     * @brief Set the Current Sense Amplifier Gain settings
     */
    void setCurrentSenseAmplifierGain(DRV8311_CurrentSenseAmplifierGain gain);

    /**
     * @brief get Current Sense Amplifier Gain settings
     */
    DRV8311_CurrentSenseAmplifierGain getCSAGain();

    /**
     * @brief Set the Current Sense Amplifier Enable
     */
    void setCurrentSenseAmplifierEnable(DRV8311_CurrentSenseAmplifierState enable);

    /**
     * @brief get Current Sense Amplifier Enable
     */
    DRV8311_CurrentSenseAmplifierState getCSAEnable();

    /**
     * @brief Set the Parity Enable for both SPI and tSPI
     */
    /* Parity handling is not supported for now
       Disabled method so it can't be enabled by mistake
    void setParityEnable(DRV8311_ParityEnable enable); */
    /**
     * @brief get Parity Enable for both SPI and tSPI
     */
    DRV8311_ParityEnable getParityEnable();

    /**
     * @brief Set the Register Lock
     */
    void setRegisterLock(DRV8311_RegisterLock lock);

    /**
     * @brief get Register Lock
     */
    DRV8311_RegisterLock getRegisterLock();

    /* Varius other functionalities */

    /** 
     * @brief Clear all faults
     */
    void clearFaults();

    /**
     * @brief Get PWM Sync Period
     */
    uint16_t getPWMSyncPeriod();

protected:

    /**
     * @brief Read from a register
     */
    virtual uint16_t readRegister(uint8_t addr) = 0;

    /**
     * @brief Write to a register
     */
    virtual void writeRegister(uint8_t addr, uint16_t data) = 0;

    /**
     * @brief Read from a sequence of registers
     */
    virtual void readRegisterSequence(uint8_t startAddr, uint8_t *buffer, size_t bufferSize) = 0;

    /**
     * @brief Write to a sequence of register
     */
    
    virtual void writeRegisterSequence(uint8_t startAddr, uint8_t *buffer, size_t bufferSize) = 0;

    int _nCS;
    SPISettings _spiSettings;
    SPIClass *_spi;

    /* TODO: Variables that saves states like parity enabled and so on */
};

#endif /* SIMPLEFOC_DRV8311 */
