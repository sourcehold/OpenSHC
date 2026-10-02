#include "../../Synchrony.func.hpp"
#include "../Actions.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Game::Resources::ResourceType;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::UnitTypeShort;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00465F90
    short* Actions::SelectionReplenishAmmo(int playerID, int param_2)
    {
        short* psVar1;
        UnitTypeShort UVar2;
        int _catapultID;
        int _amount;
        int _unitSelectionIndex;
        int _missingRocks;
        short* _currStone;
        _currStone = &DAT_TribesState::instance.tribes[param_2].size;
        _unitSelectionIndex = 0;
        if (*_currStone <= 0) {
            return _currStone;
        }
        do {
            _catapultID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe,
                DAT_TribesState::ptr)(param_2, _unitSelectionIndex);
            _unitSelectionIndex = _unitSelectionIndex + 1;
            if (((DAT_UnitsState::instance.units[_catapultID].logicalState == OpenSHC::Map::Units::ULS_NORMAL)
                    && (DAT_UnitsState::instance.units[_catapultID].dying == 0))
                && ((UVar2 = DAT_UnitsState::instance.units[_catapultID].unitType,
                    UVar2 == OpenSHC::Map::Units::UT_S_CATAPULT || (UVar2 == OpenSHC::Map::Units::UT_S_TREBUCHET)))) {
                _missingRocks = 20 - (int)DAT_UnitsState::instance.units[_catapultID].stoneAmmunition;
                if (0 < _missingRocks) {
                    _amount = (_missingRocks + 1) / 2;
                    if (DAT_GameState::instance.playerDataArray[playerID].currentResources[4] < _amount) {
                        _currStone = (short*)DAT_GameState::instance.playerDataArray[playerID].currentResources[4];
                        if ((int)_currStone <= 0) {
                            return _currStone;
                        }
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss, DAT_BuildingsState::ptr)(
                            playerID, OpenSHC::Game::Resources::RT_STONE, (int)((int)(_currStone)), 0);
                        psVar1 = &DAT_UnitsState::instance.units[_catapultID].stoneAmmunition;
                        *psVar1 = *psVar1 + (short)_currStone * 2;
                        return &DAT_UnitsState::instance.units[_catapultID].stoneAmmunition;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss,
                        DAT_BuildingsState::ptr)(playerID, OpenSHC::Game::Resources::RT_STONE, _amount, 0);
                    psVar1 = &DAT_UnitsState::instance.units[_catapultID].stoneAmmunition;
                    *psVar1 = *psVar1 + (short)_missingRocks;
                }
            }
        } while (_unitSelectionIndex < *_currStone);
        return _currStone;
    }

}
}
