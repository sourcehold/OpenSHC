#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // The dig table is a signed byte table: 0xFF (-1) ends digging (unit state 3, tunnelerFinishedDigging 2).
    // FUNCTION: STRONGHOLDCRUSADER 0x00417FD0
    void Buildings::UpdateTunnel()
    {
        int unitID = (short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].unitRefID;
        short unitState = DAT_UnitsState::instance.units[unitID].state.generic;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIncrement = 1;
        if (unitState == OpenSHC::Map::Units::States::US_STATE_3Unk
            || unitState == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk
            || DAT_UnitsState::instance.units[unitID].dying != 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
            return;
        }
        if (unitState != OpenSHC::Map::Units::States::US_STATE_9Unk) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = (char)DAT_BuildingDefinedData::instance
                .TunnelAnimationFrames[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
            return;
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
        if ((char)DAT_BuildingDefinedData::instance
                .TunnelAnimationFrames[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex]
            == -1) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
            DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_STATE_3Unk;
            DAT_UnitsState::instance.units[unitID].tunnelerFinishedDigging = 2;
            return;
        }
        int frame = (char)DAT_BuildingDefinedData::instance
                        .TunnelAnimationFrames[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame;
        if ((frame == 10 || frame == 0x19) && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x, DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                OpenSHC::DE::SHCDE::FX_DIG2);
        }
    }

}
}
