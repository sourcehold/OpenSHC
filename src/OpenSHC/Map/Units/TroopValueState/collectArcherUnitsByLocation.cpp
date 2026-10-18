#include "OpenSHC/Map.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051CA50
        void TroopValueState::collectArcherUnitsByLocation()
        {
            BOOLEnum isAIPlayerWithKeep;
            Unit* _pUnit;
            uint _unitID;
            int _index;
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(DAT_TroopValueState::instance.attackInfo.unitIDArray_0x2b57c), '\0',
                (void*)((int)(DAT_TroopValueState::instance.attackInfo.unitIDArray_0x2b57c)));
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(DAT_TroopValueState::instance.attackInfo.tileArray_0x2bd50), '\0',
                (void*)((int)(DAT_TroopValueState::instance.attackInfo.tileArray_0x2bd50)));
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(DAT_TroopValueState::instance.attackInfo.unitIDArray_0x2c070), '\0',
                (void*)((int)(DAT_TroopValueState::instance.attackInfo.unitIDArray_0x2c070)));
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(DAT_TroopValueState::instance.attackInfo.uidArray_0x2c200), '\0',
                (void*)((int)(DAT_TroopValueState::instance.attackInfo.uidArray_0x2c200)));
            _unitID = 1;
            DAT_TroopValueState::instance.attackInfo.unitIDIndex_0x2bd4c = 0;
            DAT_TroopValueState::instance.attackInfo.unitIDIndex_0x2c520 = 0;
            if (1 < DAT_UnitsState::instance.maxUnitCount) {
                _pUnit = &DAT_UnitsState::instance.units[1];
                do {
                    if (_pUnit->logicalState != Map::Units::ULS_INVISIBLE
                        && (isAIPlayerWithKeep = MACRO_CALL_MEMBER(
                                Map::Units::TroopValueState_Func::getPlayerNot1AndHasKeep, this)((int)_pUnit->owner),
                            isAIPlayerWithKeep)
                        && (_pUnit->unitType == Map::Units::UT_E_ARCHER
                            || (_pUnit->unitType == Map::Units::UT_E_XBOW))) {
                        if ((DAT_TileMapState::instance.LogicLayer[_pUnit->tile] & 0x10000100U)) {
                            int const _tribeID = (int)_pUnit->tribeID;
                            _index = DAT_TroopValueState::instance.attackInfo.unitIDIndex_0x2c520;
                            if (_index < 200
                                && (!_tribeID || (DAT_TribesState::instance.tribes[_tribeID].isRallyingUnk == 0))) {
                                /*
                                  not rallying or part of tribe
                                 */
                                DAT_TroopValueState::instance.attackInfo.tileArray_0x2bd50[_index] = _pUnit->tile;
                                DAT_TroopValueState::instance.attackInfo
                                    .uidArray_0x2c200[DAT_TroopValueState::instance.attackInfo.unitIDIndex_0x2c520]
                                    = _pUnit->uid;
                                DAT_TroopValueState::instance.attackInfo
                                    .unitIDArray_0x2c070[DAT_TroopValueState::instance.attackInfo.unitIDIndex_0x2c520]
                                    = (short)_unitID;
                                DAT_TroopValueState::instance.attackInfo.unitIDIndex_0x2c520
                                    = DAT_TroopValueState::instance.attackInfo.unitIDIndex_0x2c520 + 1;
                            }
                        } else {
                            /*
                              not on the keep or gatehouse, or towers?
                             */
                            if (DAT_TroopValueState::instance.attackInfo.unitIDIndex_0x2bd4c < 1000) {
                                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::removeUnitFromTribe,
                                    DAT_TribesState::ptr)(_unitID, (int)(_pUnit->tribeID));
                                DAT_TroopValueState::instance.attackInfo
                                    .unitIDArray_0x2b57c[DAT_TroopValueState::instance.attackInfo.unitIDIndex_0x2bd4c]
                                    = (short)_unitID;
                                DAT_TroopValueState::instance.attackInfo.unitIDIndex_0x2bd4c
                                    = DAT_TroopValueState::instance.attackInfo.unitIDIndex_0x2bd4c + 1;
                            }
                        }
                    }
                    _unitID = _unitID + 1;
                    _pUnit = _pUnit + 1;
                } while ((int)_unitID < DAT_UnitsState::instance.maxUnitCount);
            }
        }

    }
}
}
