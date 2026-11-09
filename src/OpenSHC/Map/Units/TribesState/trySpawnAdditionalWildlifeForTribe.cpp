#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x005260B0
        BOOLEnum TribesState::trySpawnAdditionalWildlifeForTribe(
            int tribeID, int spawnIntervalTicks, int maxUnitsOfType, int unitType)
        {
            if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
                return FALSE;
            }
            if (tribeID <= 0) {
                return FALSE;
            }
            if (this->tribes[tribeID].predatorNearby) {
                return FALSE;
            }
            if (DAT_GameCore::instance.missionNumber1to20 == 38 && unitType == Map::Units::UT_CAMELSHBEAR) {
                return FALSE;
            }
            int const _targetUnitID = this->tribes[tribeID].selectionTargetUnitID;
            int _unitID = _targetUnitID;
            if (unitType == Map::Units::UT_ANTELOPESHDEER) {
                _unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getNonDyingUnit, this)(tribeID);
                if (!_unitID) {
                    _unitID = _targetUnitID;
                }
            }
            int const _spawnRoll = SEC_RNG::instance.currentNumber2 & 127;
            int const _spawnX = DAT_UnitsState::instance.units[_unitID].x;
            int const _spawnY = DAT_UnitsState::instance.units[_unitID].y;
            int const _spawnHeight = DAT_UnitsState::instance.units[_unitID].terrainOrClimbHeight;
            this->tribes[tribeID].field_0x288 = this->tribes[tribeID].field_0x288 + 1;
            if (this->tribes[tribeID].field_0x288 < spawnIntervalTicks) {
                return FALSE;
            }
            this->tribes[tribeID].field_0x288 = 0;
            if (_spawnRoll < 100) {
                return FALSE;
            }
            _unitID = MACRO_CALL_MEMBER(
                Map::Units::UnitsState_Func::countLivingNondyingUnitsForPlayer, DAT_UnitsState::ptr)(unitType);
            if (_unitID >= maxUnitsOfType) {
                return FALSE;
            }
            if (unitType == Map::Units::UT_CAMELSHBEAR) {
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createAnimal, this)(
                    Commands::M_MAPPER_CAMEL, _spawnX, _spawnY, _spawnHeight);
            }
            return TRUE;
        }

    }
}
}
