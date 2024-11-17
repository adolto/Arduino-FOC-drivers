

/*******************************************************************************
 *                                 INCLUDES
 ******************************************************************************/

#include "./drv8311.hpp"


DRV8311_CurrentSense::DRV8311_CurrentSense()
{
}

int DRV8311_CurrentSense::init()
{
/* TODO: Do we need this? */
    if (driver==nullptr) {
        SIMPLEFOC_DEBUG("CUR: Driver not linked!");
        return 0;
    }

    LowsideCurrentSense::init();
}

PhaseCurrent_s DRV8311_CurrentSense::getPhaseCurrents()
{
    PhaseCurrent_s currents = LowsideCurrentSense::getPhaseCurrents();
    if (currents.a == 0.0f)
    {
        return offsetCorrectionBC(currents);
    }
    else if (currents.b == 0.0f)
    {
        return offsetCorrectionAC(currents);
    }
    else if (currents.c == 0.0f)
    {
        return offsetCorrectionAB(currents);
    }
    else
    {
        return offsetCorrection(currents);
    }
}

PhaseCurrent_s DRV8311_CurrentSense::offsetCorrection(PhaseCurrent_s currents)
{
    PhaseCurrent_s correctedCurrents;
    correctedCurrents.a = 1.001152f * currents.a - 0.003375f currents.b - 0.003103f * currents.c;
    correctedCurrents.b = 0.002369f * currents.a + 1.000665f currents.b - 0.019126f * currents.c;
    correctedCurrents.c = 0.001234f * currents.a + 0.001595f currents.b + 0.998166f * currents.c;
    return correctedCurrents;
}

PhaseCurrent_s DRV8311_CurrentSense::offsetCorrectionAB(PhaseCurrent_s currents)
{
    PhaseCurrent_s correctedCurrents;
    correctedCurrents.a = 1.004346f * currents.a - 0.000199f currents.b;
    correctedCurrents.b = 0.022060f * currents.a + 1.020405f currents.b;
    correctedCurrents.c = -(correctedCurrents.a + correctedCurrents.b);
    return correctedCurrents;
}

PhaseCurrent_s DRV8311_CurrentSense::offsetCorrectionBC(PhaseCurrent_s currents)
{
    PhaseCurrent_s correctedCurrents;
    correctedCurrents.b = 0.998309f * currents.b - 0.021427f currents.c;
    correctedCurrents.c = 0.000368f * currents.b + 0.996967f currents.c;
    correctedCurrents.a = -(correctedCurrents.b + correctedCurrents.c);
    return correctedCurrents;
}

PhaseCurrent_s DRV8311_CurrentSense::offsetCorrectionAC(PhaseCurrent_s currents)
{
    PhaseCurrent_s correctedCurrents;
    correctedCurrents.a = 1.004547f * currents.a + 0.000195f currents.c;
    correctedCurrents.c = 0.000371f * currents.a + 0.996975f currents.c;
    correctedCurrents.b = -(correctedCurrents.a + correctedCurrents.c);
    return correctedCurrents;
}
