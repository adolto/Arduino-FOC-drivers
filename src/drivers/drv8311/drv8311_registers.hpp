

#ifndef SIMPLEFOC_DRV8311_REGISTERS
#define SIMPLEFOC_DRV8311_REGISTERS

/*******************************************************************************
 *                                 INCLUDES
 ******************************************************************************/

#include <stdint.h>

/*******************************************************************************
 *                                 DEFINES
 ******************************************************************************/

constexpr uint8_t DRV8311_DEV_STS1_OFFSET = 0x00;       /* Device Status 1 Register */
constexpr uint8_t DRV8311_OT_STS_OFFSET = 0x04;         /* Over Temperature Status Register */
constexpr uint8_t DRV8311_SUP_STS_OFFSET = 0x05;        /* Supply Status Register */
constexpr uint8_t DRV8311_DRV_STS_OFFSET = 0x06;        /* Driver Status Register */
constexpr uint8_t DRV8311_SYS_STS_OFFSET = 0x07;        /* System Status Register */
constexpr uint8_t DRV8311_PWM_SYNC_PRD_OFFSET = 0x0C;   /* PWM Sync Period Register */
constexpr uint8_t DRV8311_FLT_MODE_OFFSET = 0x10;       /* Fault Mode Register */
constexpr uint8_t DRV8311_SYSF_CTRL_OFFSET = 0x12;      /* System Fault Control Register */
constexpr uint8_t DRV8311_DRVF_CTRL_OFFSET = 0x13;      /* Driver Fault Control Register */
constexpr uint8_t DRV8311_FLT_TCTRL_OFFSET = 0x16;      /* Fault Timing Control Register */
constexpr uint8_t DRV8311_FLT_CLR_OFFSET = 0x17;        /* Fault Clear Register */
constexpr uint8_t DRV8311_PWMG_PERIOD_OFFSET = 0x18;    /* PWM_GEN Period Register */
constexpr uint8_t DRV8311_PWMG_A_DUTY_OFFSET = 0x19;    /* PWM_GEN A Duty Register */
constexpr uint8_t DRV8311_PWMG_B_DUTY_OFFSET = 0x1A;    /* PWM_GEN B Duty Register */
constexpr uint8_t DRV8311_PWMG_C_DUTY_OFFSET = 0x1B;    /* PWM_GEN C Duty Register */
constexpr uint8_t DRV8311_PWM_STATE_OFFSET = 0x1C;      /* PWM State Register */
constexpr uint8_t DRV8311_PWMG_CTRL_OFFSET = 0x1D;      /* PWM_GEN Control Register */
constexpr uint8_t DRV8311_PWM_CTRL1_OFFSET = 0x20;      /* PWM Control Register 1 */
constexpr uint8_t DRV8311_DRV_CTRL_OFFSET = 0x22;       /* Predriver control Register */
constexpr uint8_t DRV8311_CSA_CTRL_OFFSET = 0x23;       /* CSA Control Register */
constexpr uint8_t DRV8311_SYS_CTRL_OFFSET = 0x3F;       /* System Control Register */

/*******************************************************************************
 *                                 TYPEDEFS
 ******************************************************************************/

/**
 * @brief Device Status 1 Register
 */
typedef union
{
    struct
    {
        uint16_t FAULT : 1;      /* Bit 0: Device Fault Status.
                                    0h = No fault condition is detected,
                                    1h = Fault condition is detected */
        uint16_t OT : 1;         /* Bit 1: Overtemperature Fault Status.
                                    0h = No overtemperature warning / shutdown is detected,
                                    1h = Overtemperature warning / shutdown is detected */
        uint16_t UVP : 1;        /* Bit 2: Supply Undervoltage Status.
                                    0h = No undervoltage voltage condition is detected on CP, AVDD or VIN_AVDD,
                                    1h = Undervoltage voltage condition is detected on CP, AVDD or VIN_AVDD */
        uint16_t RESERVED1 : 2;  /* Bits 3-4: Reserved */
        uint16_t OCP : 1;        /* Bit 5: Driver Overcurrent Protection Status.
                                    0h = No overcurrent condition is detected,
                                    1h = Overcurrent condition is detected */
        uint16_t SPI_FLT : 1;    /* Bit 6: SPI Fault Status.
                                    0h = No SPI communication fault is detected,
                                    1h = SPI communication fault is detected */
        uint16_t RESET : 1;      /* Bit 7: Supply Power On Reset Status.
                                    0h = No power on reset condition is detected,
                                    1h = Power-on-reset condition is detected */
        uint16_t OTP_FLT : 1;    /* Bit 8: OTP read fault.
                                    0h = No OTP read fault is detected,
                                    1h = OTP read fault detected */
        uint16_t RESERVED2 : 6;  /* Bits 9-14: Reserved */
        uint16_t PARITY_BIT : 1; /* Bit 15: Parity Bit if SPI_PEN is set to '1' otherwise reserved */
    };
    uint16_t reg;
} DRV8311_DEV_STS1_Register;

/**
 * @brief Over Temperature Status Register
 */
typedef union
{
    struct
    {
        uint16_t OTSD : 1;       /* Bit 0: Overtemperature Shutdown Fault Status.
                                    0h = No overtemperature shutdown is detected,
                                    1h = Overtemperature shutdown is detected */
        uint16_t OTW : 1;        /* Bit 1: Overtemperature Warning Status.
                                    0h = No overtemperature warning is detected,
                                    1h = Overtemperature warning is detected */
        uint16_t OTS_AVDD : 1;   /* Bit 2: AVDD LDO Overtemperature Fault Status.
                                    0h = No overtemperature shutdown near AVDD is detected,
                                    1h = Overtemperature shutdown near AVDD is detected */
        uint16_t RESERVED : 11;  /* Bits 3-14: Reserved */
        uint16_t PARITY_BIT : 1; /* Bit 15: Parity Bit if SPI_PEN is set to '1' otherwise reserved */
    };
    uint16_t reg;
} DRV8311_OT_STS_Register;

/**
 * @brief Supply Status Register
 */
typedef union
{
    struct
    {
        uint16_t VINAVDD_UV : 1; /* Bit 0: VIN_AVDD Undervoltage Fault Status.
                                    0h = No AVDD supply input undervoltage is detected,
                                    1h = AVDD supply input undervoltage is detected */
        uint16_t RESERVED1 : 1;  /* Bit 1: Reserved */
        uint16_t AVDD_UV : 1;    /* Bit 2: AVDD LDO Undervoltage Fault Status.
                                    0h = No AVDD output undervoltage is detected,
                                    1h = AVDD output undervoltage is detected */
        uint16_t RESERVED2 : 1;  /* Bit 3: Reserved */
        uint16_t CP_UV : 1;      /* Bit 4: Charge Pump Undervoltage Fault Status.
                                    0h = No charge pump undervoltage is detected,
                                    1h = Charge pump undervoltage is detected */
        uint16_t CSAREF_UV : 1;  /* Bit 5: CSA REF Undervoltage Fault Status.
                                    0h = No CSAREF undervoltage is detected,
                                    1h = CSAREF undervoltage is detected */
        uint16_t RESERVED3 : 8;  /* Bits 6-14: Reserved */
        uint16_t PARITY_BIT : 1; /* Bit 15: Parity Bit if SPI_PEN is set to '1' otherwise reserved */
    };
    uint16_t reg;
} DRV8311_SUP_STS_Register;

/**
 * @brief Driver Status Register
 */
typedef union
{
    struct
    {
        uint16_t OCPA_LS : 1;    /* Bit 0: Overcurrent Status on Low-side MOSFET of OUTA.
                                    0h = No overcurrent detected on low-side MOSFET of OUTA,
                                    1h = Overcurrent detected on low-side MOSFET of OUTA */
        uint16_t OCPB_LS : 1;    /* Bit 1: Overcurrent Status on Low-side MOSFET of OUTB.
                                    0h = No overcurrent detected on low-side MOSFET of OUTB,
                                    1h = Overcurrent detected on low-side MOSFET of OUTB */
        uint16_t OCPC_LS : 1;    /* Bit 2: Overcurrent Status on Low-side MOSFET of OUTC.
                                    0h = No overcurrent detected on low-side MOSFET of OUTC,
                                    1h = Overcurrent detected on low-side MOSFET of OUTC */
        uint16_t RESERVED1 : 1;  /* Bit 3: Reserved */
        uint16_t OCPA_HS : 1;    /* Bit 4: Overcurrent Status on High-side MOSFET of OUTA.
                                    0h = No overcurrent detected on high-side MOSFET of OUTA,
                                    1h = Overcurrent detected on high-side MOSFET of OUTA */
        uint16_t OCPB_HS : 1;    /* Bit 5: Overcurrent Status on High-side MOSFET of OUTB.
                                    0h = No overcurrent detected on high-side MOSFET of OUTB,
                                    1h = Overcurrent detected on high-side MOSFET of OUTB */
        uint16_t OCPC_HS : 1;    /* Bit 6: Overcurrent Status on High-side MOSFET of OUTC.
                                    0h = No overcurrent detected on high-side MOSFET of OUTC,
                                    1h = Overcurrent detected on high-side MOSFET of OUTC */
        uint16_t RESERVED2 : 7;  /* Bits 7-14: Reserved */
        uint16_t PARITY_BIT : 1; /* Bit 15: Parity Bit if SPI_PEN is set to '1' otherwise reserved */
    };
    uint16_t reg;
} DRV8311_DRV_STS_Register;

/**
 * @brief System Status Register
 */
typedef union
{
    struct
    {
        uint16_t FRM_ERR : 1;    /* Bit 0: SPI Frame Error.
                                    0h = No SPI Frame Error is detected,
                                    1h = SPI Frame Error is detected */
        uint16_t BUS_CNT : 1;    /* Bit 1: SPI Bus Contention Error.
                                    0h = No SPI Bus Contention Error is detected,
                                    1h = SPI Bus Contention Error is detected */
        uint16_t SPI_PARITY : 1; /* Bit 2: SPI Parity Error.
                                    0h = No SPI Parity Error is detected,
                                    1h = SPI Parity Error is detected */
        uint16_t RESERVED1 : 1;  /* Bit 3: Reserved */
        uint16_t OTPLD_ERR : 1;  /* Bit 4: OTP Read Error.
                                    0h = No OTP read error is detected,
                                    1h = OTP read error is detected */
        uint16_t RESERVED2 : 9;  /* Bits 5-14: Reserved */
        uint16_t PARITY_BIT : 1; /* Bit 15: Parity Bit if SPI_PEN is set to '1' otherwise reserved */
    };
    uint16_t reg;
} DRV8311_SYS_STS_Register;

/**
 * @brief PWM Sync Period Register
 */
typedef union
{
    struct
    {
        uint16_t PWM_SYNC_PRD : 12; /* Bits 0-11: 12-bit output indicating period of PWM_SYNC signal */
        uint16_t RESERVED : 3;      /* Bits 12-14: Reserved */
        uint16_t PARITY_BIT : 1;    /* Bit 15: Parity Bit if SPI_PEN is set to '1' otherwise reserved */
    };
    uint16_t reg;
} DRV8311_PWM_SYNC_PRD_Register;

/**
 * @brief Fault Mode Register
 */
typedef union
{
    struct
    {
        uint16_t OTSD_MODE : 2;   /* Bits 0-1: Overtemperature Fault mode.
                                     0h = Report on nFault, predriver HiZ, auto recovery with Slow Retry time (in ms),
                                     1h = Report on nFault, predriver HiZ, auto recovery with Fast Retry time (in ms),
                                     2h = Reserved,
                                     3h = Reserved */
        uint16_t UVP_MODE : 2;    /* Bits 2-3: Undervoltage Protection Fault mode.
                                     0h = Report on nFault, predriver HiZ, auto recovery with Slow Retry time (in ms),
                                     1h = Report on nFault, predriver HiZ, auto recovery with Fast Retry time (in ms),
                                     2h = Reserved,
                                     3h = Reserved */
        uint16_t OCP_MODE : 3;    /* Bits 4-6: Overcurrent Protection Fault mode.
                                     0h = Report on nFault, predriver HiZ, auto recovery with Slow Retry time (in ms),
                                     1h = Report on nFault, predriver HiZ, auto recovery with Fast Retry time (in ms),
                                     2h = Report on nFault, predriver HiZ, Latched Fault,
                                     3h = Report on nFault, No action on predriver,
                                     4h = Reserved,
                                     5h = Reserved,
                                     6h = Reserved,
                                     7h = Disabled */
        uint16_t SPIFLT_MODE : 1; /* Bit 7: SPI Fault mode.
                                     0h = SPI Fault is enabled,
                                     1h = SPI Fault is disabled */
        uint16_t OTPFLT_MODE : 1; /* Bit 8: System Fault Mode.
                                     0h = OTP read fault is enabled,
                                     1h = OTP read fault is disabled */
        uint16_t RESERVED : 6;    /* Bits 9-14: Reserved */
        uint16_t PARITY_BIT : 1;  /* Bit 15: Parity Bit if SPI_PEN is set to '1' otherwise reserved */
    };
    uint16_t reg;
} DRV8311_FLT_MODE_Register;

/**
 * @brief System Fault Control Register
 */
typedef union
{
    struct
    {
        uint16_t RESERVED1 : 1;   /* Bit 0: Reserved */
        uint16_t RESERVED2 : 1;   /* Bit 1: Reserved */
        uint16_t RESERVED3 : 1;   /* Bit 2: Reserved */
        uint16_t RESERVED4 : 1;   /* Bit 3: Reserved */
        uint16_t RESERVED5 : 1;   /* Bit 4: Reserved */
        uint16_t CSAREFUV_EN : 1; /* Bit 5: CSAREF Undervoltage Fault Enable.
                                     0h = CSAREF undervoltage lockout is disabled,
                                     1h = CSAREF undervoltage lockout is enabled */
        uint16_t RESERVED6 : 3;   /* Bits 6-8: Reserved */
        uint16_t OTW_EN : 1;      /* Bit 9: Overtemperature Warning Fault Enable.
                                     0h = Over temperature warning reporting on nFAULT is disabled,
                                     1h = Over temperature warning reporting on nFAULT is enabled */
        uint16_t OTAVDD_EN : 1;   /* Bit 10: AVDD Overtemperature Fault Enable.
                                     0h = Overtemperature protection near AVDD is disabled,
                                     1h = Overtemperature protection near AVDD is enabled */
        uint16_t RESERVED7 : 4;   /* Bits 11-14: Reserved */
        uint16_t PARITY_BIT : 1;  /* Bit 15: Parity Bit if SPI_PEN is set to '1' otherwise reserved */
    };
    uint16_t reg;
} DRV8311_SYSF_CTRL_Register;

/**
 * @brief Driver Fault Control Register
 */
typedef union
{
    struct
    {
        uint16_t OCP_LVL : 1;    /* Bit 0: OCP Level Settings.
                                    0h = OCP level is 9 A (TYP),
                                    1h = OCP level is 5 A (TYP) */
        uint16_t RESERVED : 1;   /* Bit 1: Reserved */
        uint16_t OCP_TBLANK : 2; /* Bits 2-3: OCP Blanking time.
                                    0h = OCP blanking time is 0.2 µs,
                                    1h = OCP blanking time is 0.5 µs,
                                    2h = OCP blanking time is 0.8 µs,
                                    3h = OCP blanking time is 1 µs */
        uint16_t OCP_DEG : 2;    /* Bits 4-5: OCP Deglitch time.
                                    0h = OCP deglitch time is 0.2 µs,
                                    1h = OCP deglitch time is 0.5 µs,
                                    2h = OCP deglitch time is 0.8 µs,
                                    3h = OCP deglitch time is 1 µs */
        uint16_t RESERVED2 : 8;  /* Bits 6-14: Reserved */
        uint16_t PARITY_BIT : 1; /* Bit 15: Parity Bit if SPI_PEN is set to '1' otherwise reserved */
    };
    uint16_t reg;
} DRV8311_DRVF_CTRL_Register;

/**
 * @brief Fault Timing Control Register
 */
typedef union
{
    struct
    {
        uint16_t FAST_TRETRY : 2; /* Bits 0-1: Fast Recovery Retry Time from Fault Condition.
                                     0h = 0.5ms,
                                     1h = 1ms,
                                     2h = 2ms,
                                     3h = 5ms */
        uint16_t SLOW_TRETRY : 2; /* Bits 2-3: Slow Recovery Retry Time from Fault Condition.
                                     0h = 0.5s,
                                     1h = 1s,
                                     2h = 2s,
                                     3h = 5s */
        uint16_t RESERVED : 10;   /* Bits 4-14: Reserved */
        uint16_t PARITY_BIT : 1;  /* Bit 15: Parity Bit if SPI_PEN is set to '1' otherwise reserved */
    };
    uint16_t reg;
} DRV8311_FLT_TCTRL_Register;

/**
 * @brief Fault Clear Register
 */
typedef union
{
    struct
    {
        uint16_t FLT_CLR : 1;    /* Bit 0: Clear Fault.
                                    0h = No clear fault command is issued,
                                    1h = To clear the latched fault bits. This bit automatically resets after being written. */
        uint16_t RESERVED : 14;  /* Bits 1-14: Reserved */
        uint16_t PARITY_BIT : 1; /* Bit 15: Parity Bit if SPI_PEN is set to '1' otherwise reserved */
    };
    uint16_t reg;
} DRV8311_FLT_CLR_Register;

/**
 * @brief PWM_GEN Period Register
 */
typedef union
{
    struct
    {
        uint16_t PWM_PRD_OUT : 12; /* Bits 0-11: 12-bit Period for output PWM signals in PWM Generation Mode */
        uint16_t RESERVED : 3;     /* Bits 12-14: Reserved */
        uint16_t PARITY_BIT : 1;   /* Bit 15: Parity Bit if SPI_PEN is set to '1' otherwise reserved */
    };
    uint16_t reg;
} DRV8311_PWMG_PERIOD_Register;

/**
 * @brief PWM_GEN A Duty Register
 */
typedef union
{
    struct
    {
        uint16_t PWM_DUTY_OUTA : 12; /* Bits 0-11: 12-bit Duty Cycle for Phase A output in PWM Generation Mode */
        uint16_t RESERVED : 3;       /* Bits 12-14: Reserved */
        uint16_t PARITY_BIT : 1;     /* Bit 15: Parity Bit if SPI_PEN is set to '1' otherwise reserved */
    };
    uint16_t reg;
} DRV8311_PWMG_A_DUTY_Register;

/**
 * @brief PWM_GEN B Duty Register
 */
typedef union
{
    struct
    {
        uint16_t PWM_DUTY_OUTB : 12; /* Bits 0-11: 12-bit Duty Cycle for Phase B output in PWM Generation Mode */
        uint16_t RESERVED : 3;       /* Bits 12-14: Reserved */
        uint16_t PARITY_BIT : 1;     /* Bit 15: Parity Bit if SPI_PEN is set to '1' otherwise reserved */
    };
    uint16_t reg;
} DRV8311_PWMG_B_DUTY_Register;

/**
 * @brief PWM_GEN C Duty Register
 */
typedef union
{
    struct
    {
        uint16_t PWM_DUTY_OUTC : 12; /* Bits 0-11: 12-bit Duty Cycle for Phase C output in PWM Generation Mode */
        uint16_t RESERVED : 3;       /* Bits 12-14: Reserved */
        uint16_t PARITY_BIT : 1;     /* Bit 15: Parity Bit if SPI_PEN is set to '1' otherwise reserved */
    };
    uint16_t reg;
} DRV8311_PWMG_C_DUTY_Register;

/**
 * @brief PWM State Register
 */
typedef union
{
    struct
    {
        uint16_t PWMA_STATE : 3; /* Bits 0-2: Phase A Driver Output control.
                                    0h = High Side is OFF, Low Side is OFF,
                                    1h = High Side is OFF, Low Side is forced ON,
                                    2h = High Side is forced ON, Low Side is OFF,
                                    3h = Reserved,
                                    4h = Reserved,
                                    5h = High Side is OFF, Low Side PWM,
                                    6h = High Side PWM, Low Side is OFF,
                                    7h = High Side PWM, Low Side !PWM */
        uint16_t RESERVED : 1;   /* Bit 3: Reserved */
        uint16_t PWMB_STATE : 3; /* Bits 4-6: Phase B Driver Output control.
                                    0h = High Side is OFF, Low Side is OFF,
                                    1h = High Side is OFF, Low Side is forced ON,
                                    2h = High Side is forced ON, Low Side is OFF,
                                    3h = Reserved,
                                    4h = Reserved,
                                    5h = High Side is OFF, Low Side PWM,
                                    6h = High Side PWM, Low Side is OFF,
                                    7h = High Side PWM, Low Side !PWM */
        uint16_t RESERVED2 : 1;  /* Bit 7: Reserved */
        uint16_t PWMC_STATE : 3; /* Bits 8-10: Phase C Driver Output control.
                                    0h = High Side is OFF, Low Side is OFF,
                                    1h = High Side is OFF, Low Side is forced ON,
                                    2h = High Side is forced ON, Low Side is OFF,
                                    3h = Reserved,
                                    4h = Reserved,
                                    5h = High Side is OFF, Low Side PWM,
                                    6h = High Side PWM, Low Side is OFF,
                                    7h = High Side PWM, Low Side !PWM */
        uint16_t RESERVED3 : 4;  /* Bits 11-14: Reserved */
        uint16_t PARITY_BIT : 1; /* Bit 15: Parity Bit if SPI_PEN is set to '1' otherwise reserved */
    };
    uint16_t reg;
} DRV8311_PWM_STATE_Register;

/**
 * @brief PWM_GEN Control Register
 */
typedef union
{
    struct
    {
        uint16_t SPISYNC_ACRCY : 2;    /* Bits 0-1: Number of SPI Clock Cycle require for synchronizing the Oscillator
                                          0h = 512 Clock Cycles (1%)
                                          1h = 256 Clock Cycles (1%)
                                          2h = 128 Clock Cycles (1%)
                                          3h = 64 Clock Cycles (2%) */
        uint16_t SPICLK_FREQ_SYNC : 3; /* Bits 2-4: SPI Clock Frequency for synchronizing the Oscillator
                                          0h = 1 MHz
                                          1h = 1.25 MHz
                                          2h = 2 MHz
                                          3h = 2.5 MHz
                                          4h = 4 MHz
                                          5h = 5 MHz
                                          6h = 8 MHz
                                          7h = 10 MHz */
        uint16_t PWM_OSC_SYNC : 3;     /* Bits 5-7: Oscillator synchronization and PWM_SYNC control
                                          0h = Oscillator synchronization is disable
                                          1h = PWM_SYNC_PRD indicates period of PWM_SYNC signal and
                                               can be used to calibrate PWM period
                                          2h = PWM_SYNC used to set PWM period
                                          3h = Oscillator synchronization is disable
                                          4h = Oscillator synchronization is disable
                                          5h = PWM_SYNC used for oscillator synchronization (only 20 kHz
                                               frequency supported)
                                          6h = PWM_SYNC used for oscillator synchronization and setting
                                               PWM period (only 20 kHz frequency supported)
                                          7h = SPI Clock pin SCLK used for oscillator synchronization
                                               (Configure SPICLK_FREQ_SYNC) */
        uint16_t PWMCNTR_MODE : 2;     /* Bits 8-9: PWM Gen counter mode
                                          0h = Up and Down
                                          1h = Up
                                          2h = Down
                                          3h = No action */
        uint16_t PWM_EN : 1;           /* Bit 10: Enable 3X Internal mode PWM Generation
                                          0h = PWM_GEN disabled
                                          1h = PWM_GEN enabled */
        uint16_t RESERVED : 2;         /* Bits 11-12: Reserved */
        uint16_t PARITY_BIT : 1;       /* Bit 13: Parity Bit if SPI_PEN is set to '1' otherwise reserved */
    };
    uint16_t reg;
} DRV8311_PWMG_CTRL_Register;

/**
 * @brief PWM Control Register 1
 */
typedef union
{
    struct
    {
        uint16_t PWM_MODE : 2;   /* Bits 0-1: PWM mode selection (The reset setting in DRV8311S is 00b and in
                                   DRV8311 is 11b)
                                    0h = 6x mode
                                    1h = 6x mode
                                    2h = 3x mode
                                    3h = PWM Generation mode */
        uint16_t SSC_DIS : 1;    /* Bit 2: Disable Spread Spectrum Modulation for internal Oscillator
                                    0h = Spread spectrum modulation is enabled
                                    1h = Spread spectrum modulation is disabled */
        uint16_t RESERVED : 11;  /* Bits 3-13: Reserved */
        uint16_t PARITY_BIT : 1; /* Bit 14: Parity Bit if SPI_PEN is set to '1' otherwise reserved */
    };
    uint16_t reg;
} DRV8311_PWM_CTRL1_Register;

/**
 * @brief Predriver control Register
 */
typedef union
{
    struct
    {
        uint16_t SLEW_RATE : 2;  /* Bits 0-1: Slew rate settings
                                    0h = Slew rate is 35 V/µs
                                    1h = Slew rate is 75 V/µs
                                    2h = Slew rate is 180 V/µs
                                    3h = Slew rate is 230 V/µs */
        uint16_t RESERVED1 : 2;  /* Bits 2-3: Reserved */
        uint16_t TDEAD_CTRL : 3; /* Bits 4-6: Deadtime insertion control
                                    0h = No deadtime (Handshake Only)
                                    1h = 200ns
                                    2h = 400ns
                                    3h = 600ns
                                    4h = 800ns
                                    5h = 1us
                                    6h = 1.2us
                                    7h = 1.4us */
        uint16_t DLYCMP_EN : 1;  /* Bit 7: Driver Delay Compensation enable
                                    0h = Driver Delay Compensation is disabled
                                    1h = Driver Delay Compensation is enabled */
        uint16_t RESERVED2 : 4;  /* Bits 8-11: Reserved */
        uint16_t RESERVED3 : 3;  /* Bits 12-14: Reserved */
        uint16_t PARITY_BIT : 1; /* Bit 15: Parity Bit if SPI_PEN is set to '1' otherwise reserved */
    };
    uint16_t reg;
} DRV8311_DRV_CTRL_Register;

/**
 * @brief CSA Control Register
 */
typedef union
{
    struct
    {
        uint16_t CSA_GAIN : 2;   /* Bits 0-1: Current Sense Amplifier Gain settings
                                    0h = CSA gain is 0.25 V/A
                                    1h = CSA gain is 0.5 V/A
                                    2h = CSA gain is 1 V/A
                                    3h = CSA gain is 2 V/A */
        uint16_t RESERVED1 : 1;  /* Bit 2: Reserved */
        uint16_t CSA_EN : 1;     /* Bit 3: Current Sense Amplifier Enable
                                    0h = Current Sense Amplifier is disabled
                                    1h = Current Sense Amplifier is enabled */
        uint16_t RESERVED2 : 10; /* Bits 4-13: Reserved */
        uint16_t PARITY_BIT : 1; /* Bit 14: Parity Bit if SPI_PEN is set to '1' otherwise reserved */
    };
    uint16_t reg;
} DRV8311_CSA_CTRL_Register;

/**
 * @brief System Control Register
 */
typedef union
{
    struct
    {
        uint16_t RESERVED1 : 3;  /* Bits 0-2: Reserved */
        uint16_t RESERVED2 : 1;  /* Bit 3: Reserved */
        uint16_t RESERVED3 : 2;  /* Bits 4-5: Reserved */
        uint16_t SPI_PEN : 1;    /* Bit 6: Parity Enable for both SPI and tSPI
                                    0h = Parity Disabled
                                    1h = Parity Enabled */
        uint16_t REG_LOCK : 1;   /* Bit 7: Register Lock Bit
                                    0h = Registers Unlocked
                                    1h = Registers Locked */
        uint16_t RESERVED4 : 1;  /* Bit 8: Reserved */
        uint16_t RESERVED5 : 3;  /* Bits 9-11: Reserved */
        uint16_t WRITE_KEY : 3;  /* Bits 12-14: 0x5 Write Key Specific to this register. */
        uint16_t PARITY_BIT : 1; /* Bit 15: Parity Bit if SPI_PEN is set to '1' otherwise reserved */
    };
    uint16_t reg;
} DRV8311_SYS_CTRL_Register;

/**
 * @brief Template Register just with Parity Bit
 */
typedef union
{
    struct
    {
        uint16_t RESERVED : 15;  /* Bits 0-14: Reserved */
        uint16_t PARITY_BIT : 1; /* Bit 15: Parity Bit if SPI_PEN is set to '1' otherwise reserved */
    };
    uint16_t reg;

} DRV8311_TEMPLATE_Register;

#endif /* SIMPLEFOC_DRV8311_REGISTERS */
