#include "../Helpers.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EnoughGoldForRequestedUnit.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace UI {

    using Map::Buildings::BuildingType;
    using Map::Buildings::BuildingTypeShort;
    using Map::Units::UnitType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00439730
    void Helpers::HandleBuildingSelectionSpeech(int buildingIndexUnk)
    {
        int _requiredEmployeeCount;
        if (DAT_BuildingsState::instance.buildings[buildingIndexUnk].owner
            == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
            BuildingTypeShort _buildingType = DAT_BuildingsState::instance.buildings[buildingIndexUnk].buildingType;
            if (_buildingType == Map::Buildings::BT_ENGINEERSGUILD) {
                MACRO_CALL(UI::Helpers_Func::CheckIfEnoughGoldForLadderman)();
                if (!DAT_EnoughGoldForRequestedUnit::instance) {
                    /*
                      "You do not have enough gold for apprentices"
                     */
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                        "units_warning1.wav");
                }
            } else if (_buildingType == Map::Buildings::BT_TUNNELERSGUILD) {
                MACRO_CALL(UI::Helpers_Func::CheckIfEnoughGoldForTunneler)();
                if (!DAT_EnoughGoldForRequestedUnit::instance) {
                    /*
                      "You do not have enough gold to train a tunneler"
                     */
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                        "units_warning2.wav");
                }
            } else if (0x27 < (short)_buildingType) {
            }
            if (DAT_BuildingsState::instance.buildings[buildingIndexUnk].sleeping != false) {
                /*
                  "Work halted my lord"
                 */
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                    "other_warning12.wav");
            }
            short _currentEmployeeCount = DAT_BuildingsState::instance.buildings[buildingIndexUnk].currentEmployeeCount;
            if ((_currentEmployeeCount)
                || (DAT_BuildingsState::instance.buildings[buildingIndexUnk].currentlyNeededEmployeeCount != 0)) {
                _requiredEmployeeCount
                    = DAT_BuildingsState::instance.buildings[buildingIndexUnk].currentlyNeededEmployeeCount;
                if (0 < _requiredEmployeeCount) {
                    if (!_currentEmployeeCount) {
                        /*
                          "This building has no labor sire"
                         */
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            "other_warning8.wav");
                    }
                    if (_requiredEmployeeCount == 1) {
                        /*
                          "Needs one more person"
                         */
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            "other_warning10.wav");
                    }
                    if (1 < _requiredEmployeeCount) {
                        /*
                          "Needs two more people"
                         */
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            "other_warning11.wav");
                    }
                }
                int _workerIndex = 0;
                bool _noPeasantOnTheWay = true;
                if (0 < _currentEmployeeCount) {
                    do {
                        if (3 < _workerIndex)
                            break;
                        if (DAT_UnitsState::instance
                                .units[DAT_BuildingsState::instance.buildings[buildingIndexUnk].workerID[_workerIndex]]
                                .unitType
                            == Map::Units::UT_PEASANT) {
                            _noPeasantOnTheWay = false;
                        }
                        _workerIndex = _workerIndex + 1;
                    } while (_workerIndex < _currentEmployeeCount);
                    if ((!_noPeasantOnTheWay) && (_buildingType != Map::Buildings::BT_OILSMELTER)) {
                        /*
                          "A peasant is on its way"
                         */
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            "other_warning9.wav");
                    }
                }
            }
        }
    }

}
}
