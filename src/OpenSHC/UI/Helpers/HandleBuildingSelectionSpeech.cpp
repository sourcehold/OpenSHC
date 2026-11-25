#include "../Helpers.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EnoughGoldForRequestedUnit.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace UI {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00439730
    void Helpers::HandleBuildingSelectionSpeech(int buildingID)
    {
        if (DAT_BuildingsState::instance.buildings[buildingID].owner
            != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
            return;
        }
        // At most one warning is spoken when the player selects one of their buildings.
        int const buildingType = DAT_BuildingsState::instance.buildings[buildingID].buildingType;
        if (buildingType == Map::Buildings::BT_ENGINEERSGUILD) {
            MACRO_CALL(UI::Helpers_Func::CheckIfEnoughGoldForLadderman)();
            if (!DAT_EnoughGoldForRequestedUnit::instance) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                    SFX_NotEnoughGoldForApprentices);
                return;
            }
        } else if (buildingType == Map::Buildings::BT_TUNNELERSGUILD) {
            MACRO_CALL(UI::Helpers_Func::CheckIfEnoughGoldForTunneler)();
            if (!DAT_EnoughGoldForRequestedUnit::instance) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                    SFX_NotEnoughGoldForTunneler);
                return;
            }
        } else if (buildingType >= Map::Buildings::BT_MANORHOUSE) {
            return;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].sleeping) {
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(SFX_WorkHaltedMyLord);
            return;
        }
        short const employees = DAT_BuildingsState::instance.buildings[buildingID].currentEmployeeCount;
        if (employees == 0 && DAT_BuildingsState::instance.buildings[buildingID].currentlyNeededEmployeeCount == 0) {
            return;
        }
        short const needed = DAT_BuildingsState::instance.buildings[buildingID].currentlyNeededEmployeeCount;
        if (needed > 0) {
            if (employees == 0) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                    SFX_ThisBuildingHasNoLaborSire);
                return;
            }
            if (needed == 1) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(SFX_NeedsOneMorePerson);
                return;
            }
            // Always true here, but the original tests it again.
            if (needed > 1) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(SFX_NeedsTwoMorePeople);
                return;
            }
        }
        BOOLEnum noPeasantOnTheWay = TRUE;
        for (int worker = 0; worker < employees && worker < 4; ++worker) {
            if (DAT_UnitsState::instance.units[DAT_BuildingsState::instance.buildings[buildingID].workerID[worker]]
                    .unitType
                == Map::Units::UT_PEASANT) {
                noPeasantOnTheWay = FALSE;
            }
        }
        if (noPeasantOnTheWay) {
            return;
        }
        if (buildingType != Map::Buildings::BT_OILSMELTER) {
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(SFX_APeasantIsOnHisWay);
        }
    }

}
}
