

/*******************************************************************************
 *                                 INCLUDES
 ******************************************************************************/

#include "./drv8311p.hpp"
#include "common/foc_utils.h"
#include "common/defaults.h"

/*******************************************************************************
 *                                 DEFINES
 ******************************************************************************/

#define DRV8311P_READ_BIT 0x8000
#define DRV8311P_ADDRESS_OFFSET 0x03
#define DRV8311P_ADDRESS_MASK 0x7F
#define DRV8311P_ADDRESS(ADDR) (((ADDR & DRV8311P_ADDRESS_MASK) << (DRV8311P_ADDRESS_OFFSET)))

#define DRV8311P_AD0_OFFSET 11
#define DRV8311P_AD1_OFFSET 12
#define DRV8311P_AD_MASK 0x01

DRV8311PDriver::DRV8311PDriver(int nCS, SPISettings spiSettings, bool AD0, bool AD1) : DRV8311Driver(nCS, spiSettings)
{
    voltage_power_supply = DEF_POWER_SUPPLY;
    voltage_limit = NOT_SET;
    pwm_frequency = NOT_SET;

    _tSpiADHeader = ((AD0 & DRV8311P_AD_MASK) << DRV8311P_AD0_OFFSET) | ((AD1 & DRV8311P_AD_MASK) << DRV8311P_AD1_OFFSET);
}

/* TODO: Combine assigning SPI with init */
int DRV8311PDriver::init()
{
    // sanity check for the voltage limit configuration
    if(!_isset(voltage_limit) || voltage_limit > voltage_power_supply) voltage_limit =  voltage_power_supply;

    initialized = true;
    return 1;
};

void DRV8311PDriver::enable()
{
    setPWMGenEnable(DRV8311_PWM_GEN_ENABLE::PWM_GEN_ENABLED);
};

void DRV8311PDriver::disable()
{
    setPWMGenEnable(DRV8311_PWM_GEN_ENABLE::PWM_GEN_DISABLED);
};


void DRV8311PDriver::setPwm(float Ua, float Ub, float Uc)
{
    float Ua2 = _constrain(Ua, 0.0f, voltage_limit);
    float Ub2 = _constrain(Ub, 0.0f, voltage_limit);
    float Uc2 = _constrain(Uc, 0.0f, voltage_limit);
    // calculate duty cycle
    // limited in [0,1]
    dc_a = _constrain(Ua2 / voltage_power_supply, 0.0f , 1.0f);
    dc_b = _constrain(Ub2 / voltage_power_supply, 0.0f , 1.0f);
    dc_c = _constrain(Uc2 / voltage_power_supply, 0.0f , 1.0f);

    float MAX_REGISTER_VALUE = 512 - 1;
    //float MAX_REGISTER_VALUE = 4096 - 1;
    uint16_t dutyCycleBuffer[4] = {0};
    dutyCycleBuffer[0] = MAX_REGISTER_VALUE;
    dutyCycleBuffer[1] = dc_a * MAX_REGISTER_VALUE;
    dutyCycleBuffer[2] = dc_b * MAX_REGISTER_VALUE;
    dutyCycleBuffer[3] = dc_c * MAX_REGISTER_VALUE;

    // char buffer[150];
    // sprintf(buffer, "setPwm %u %u %u %u\n", (unsigned int)dutyCycleBuffer[0], (unsigned int)dutyCycleBuffer[1], (unsigned int)dutyCycleBuffer[2], (unsigned int)dutyCycleBuffer[3]);
    // Serial.print(buffer);

    if (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
    {
        for (size_t i = 0; i < 4; i++)
        {
            dutyCycleBuffer[i] = __builtin_bswap16(dutyCycleBuffer[i]);
        }
    }
    writeRegisterSequence(DRV8311_PWMG_PERIOD_OFFSET, (uint8_t *)dutyCycleBuffer, sizeof(dutyCycleBuffer));
}

void DRV8311PDriver::setPhaseState(PhaseState sa, PhaseState sb, PhaseState sc)
{
    // char buffer[50];
    // sprintf(buffer, "setPhaseState %d %d %d\n", sa, sb, sc);
    // Serial.print(buffer);
    /* Lambda to convert PhaseState to PWM_STATE */
    auto ConvertState = [](PhaseState state) -> DRV8311_PhaseDriverOutputControl
    {
        switch (state)
        {
            case PHASE_OFF:
            {
                return DRV8311_PhaseDriverOutputControl::HIGH_SIDE_OFF_LOW_SIDE_OFF;
            }
            case PHASE_ON:
            {
                return DRV8311_PhaseDriverOutputControl::HIGH_SIDE_PWM_LOW_SIDE_nPWM;
            }
            case PHASE_HI:
            {
                return DRV8311_PhaseDriverOutputControl::HIGH_SIDE_PWM_LOW_SIDE_OFF;
            }
            case PHASE_LO:
            {
                return DRV8311_PhaseDriverOutputControl::HIGH_SIDE_OFF_LOW_SIDE_PWM;
            }
        };
    };

    DRV8311_PWM_STATE_Register phaseState{
        .PWMA_STATE = (uint16_t)ConvertState(sa),
        .PWMB_STATE = (uint16_t)ConvertState(sb),
        .PWMC_STATE = (uint16_t)ConvertState(sc)};

    writeRegister(DRV8311_PWM_STATE_OFFSET, phaseState.reg);
}


uint16_t DRV8311PDriver::readRegister(uint8_t addr)
{
    /* Begin transaction */
    digitalWrite(_nCS, LOW);
    _spi->beginTransaction(_spiSettings);

    /* Write address */
    _spi->transfer16(_tSpiADHeader | DRV8311P_ADDRESS(addr) | DRV8311P_READ_BIT);

    // TODO: Check for status in second byte of the response

    /* Read data */
    uint16_t data = _spi->transfer(0x0000);
    // data |= (_spi->transfer(0x00) << 8);
    // data |= (_spi->transfer(0x00) << 0);

    /* End transaction */
    _spi->endTransaction();
    digitalWrite(_nCS, HIGH);

    return data;
}

void DRV8311PDriver::writeRegister(uint8_t addr, uint16_t data)
{
    /* Begin transaction */
    digitalWrite(_nCS, LOW);
    _spi->beginTransaction(_spiSettings);

    /* Write address */
    _spi->transfer16(_tSpiADHeader | DRV8311P_ADDRESS(addr));

    // TODO: Check for status in second byte of the response

    /* Write data */
    _spi->transfer16(data);

    /* End transaction */
    _spi->endTransaction();
    digitalWrite(_nCS, HIGH);
}

void DRV8311PDriver::readRegisterSequence(uint8_t startAddr, uint8_t *buffer, size_t bufferSize)
{
    /* Begin transaction */
    digitalWrite(_nCS, LOW);
    _spi->beginTransaction(_spiSettings);

    /* Write address */
    _spi->transfer16(_tSpiADHeader | DRV8311P_ADDRESS(startAddr) | DRV8311P_READ_BIT);

    // TODO: Check for status in second byte of the response

    /* Read data sequence */
    for (size_t i = 0; i < bufferSize; i++)
    {
        buffer[i] = _spi->transfer(0x00);
    }

    /* End transaction */
    _spi->endTransaction();
    digitalWrite(_nCS, HIGH);
}

void DRV8311PDriver::writeRegisterSequence(uint8_t startAddr, uint8_t *buffer, size_t bufferSize)
{
    /* Begin transaction */
    digitalWrite(_nCS, LOW);
    _spi->beginTransaction(_spiSettings);

    /* Write address */
    _spi->transfer16(_tSpiADHeader | DRV8311P_ADDRESS(startAddr));

    // TODO: Check for status in second byte of the response

    /* Write data sequence */
    //char char_buffer[150];
    //sprintf(char_buffer, "writeRegisterSequence %u %x %x %x %x %x %x %x %x\n", bufferSize, buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7]);
    //Serial.print(char_buffer);
    
    _spi->transfer(buffer, bufferSize);

    /* End transaction */
    _spi->endTransaction();
    digitalWrite(_nCS, HIGH);
}