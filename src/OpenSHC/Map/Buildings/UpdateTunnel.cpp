#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00417FD0
    void Buildings::UpdateTunnel()
    {
        int const unitID = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].unitRefID;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIncrement = 1;
        // Unit states 3 and 9 have no UnitState constant.
        if (DAT_UnitsState::instance.units[unitID].state.generic == 3
            || DAT_UnitsState::instance.units[unitID].state.generic == Units::States::US_RELOAD_WEAPONUnk
            || DAT_UnitsState::instance.units[unitID].dying != 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
            return;
        }
        if (DAT_UnitsState::instance.units[unitID].state.generic != 9) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame
                = (char)DAT_BuildingDefinedData::instance.TunnelAnimationFrames
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
            return;
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
        char const frame = (char)DAT_BuildingDefinedData::instance.TunnelAnimationFrames
                               [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
        if (frame == -1) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
            DAT_UnitsState::instance.units[unitID].state.generic = 3;
            DAT_UnitsState::instance.units[unitID].tunnelerFinishedDigging = 2;
            return;
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame;
        if ((DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame == 10
                || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame == 25)
            && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y, OpenSHC::DE::SHCDE::FX_DIG2);
        }
    }

}
}
