

#ifndef SIMPLEFOC_DRV8311_CURRENT_SENSE
#define SIMPLEFOC_DRV8311_CURRENT_SENSE

/*******************************************************************************
 *                                 INCLUDES
 ******************************************************************************/

#include <SimpleFOC.h>

class DRV8311_CurrentSense : public LowsideCurrentSense
{

    /* TODO: 
     - Add input pins as parameters
     - How do we get the set gain? 
       - Do we need to set the gain manaually?
       - Can we link it with the driver?
    */

    DRV8311_CurrentSense();

    // CurrentSense interface implementing functions
    int init() override;
    PhaseCurrent_s getPhaseCurrents() override;

private:
    static PhaseCurrent_s offsetCorrection(PhaseCurrent_s currents);
    static PhaseCurrent_s offsetCorrectionAB(PhaseCurrent_s currents);
    static PhaseCurrent_s offsetCorrectionBC(PhaseCurrent_s currents);
    static PhaseCurrent_s offsetCorrectionAC(PhaseCurrent_s currents);
}

#endif /* SIMPLEFOC_DRV8311_CURRENT_SENSE */