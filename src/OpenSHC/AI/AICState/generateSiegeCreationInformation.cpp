#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::Game::GameMode;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::UnitTypeShort;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names */

    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names */

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CC420
    void AICState ::generateSiegeCreationInformation(int playerID, int buildingID, int unitID)

    {

        UnitTypeShort UVar1;

        int iVar2;

        int _siegeIndex;

        int _engineIndexUnk;

        int _nextIndex;

        int _goal;

        if ((DAT_GameState::instance.playerDataArray[playerID].aiType != OpenSHC::AI::AIT_NULL)
            && (DAT_GameSynchronyState::instance.DAT_CurrentGameMode != OpenSHC::Game::GM_SOLITARY)) {

            UVar1 = DAT_UnitsState::instance.units[unitID].unitType;

            if (UVar1 == OpenSHC::Map::Units::UT_S_TREBUCHET) {

                _siegeIndex = 2;

            }

            else {

                if (UVar1 != OpenSHC::Map::Units::UT_S_FBALLISTA) {

                    return;
                }

                _siegeIndex = 3;
            }

            iVar2 = DAT_SkirmishDefinedData::instance.DAT_SiegeEngineMetaInfoArray[_siegeIndex].slot;

            _goal = DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlotLocationCount[iVar2];

            if (0 < _goal) {

                _engineIndexUnk = 0;

                while ((_nextIndex = _engineIndexUnk + 1,
                    *(int*)(playerID * 0x39f4 + iVar2 * 40 + 0x115eb14 + _engineIndexUnk * 4) < 1
                        || (buildingID
                            != *(int*)(playerID * 0x39f4 + 0x115f494 + (_engineIndexUnk + _siegeIndex * 5) * 0x14)))) {

                    _engineIndexUnk = _nextIndex;

                    if (_goal <= _nextIndex) {

                        return;
                    }
                }

                DAT_GameState::instance.playerDataArray[playerID]
                    .aiSiegeCreationInformation[_siegeIndex][_engineIndexUnk]
                    .unitID = unitID;

                DAT_GameState::instance.playerDataArray[playerID]
                    .aiSiegeCreationInformation[_siegeIndex][_engineIndexUnk]
                    .uid = DAT_UnitsState::instance.units[unitID].uid;

                DAT_GameState::instance.playerDataArray[playerID]
                    .aiSiegeCreationInformation[_siegeIndex][_engineIndexUnk]
                    .buildingID = 0;
            }
        }

        return;
    }

}
}
