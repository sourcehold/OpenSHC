#include "../../../Map.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
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
            BOOLEnum BVar1;
            Unit* _pUnit;
            uint _unitID;
            int _index;
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                2000, '\0', (void*)((int)(this->attackInfo.unitIDArray_0x2b57c)));
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                800, '\0', (void*)((int)(this->attackInfo.tileArray_0x2bd50)));
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                400, '\0', (void*)((int)(this->attackInfo.unitIDArray_0x2c070)));
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                800, '\0', (void*)((int)(this->attackInfo.uidArray_0x2c200)));
            _unitID = 1;
            this->attackInfo.unitIDIndex_0x2bd4c = 0;
            this->attackInfo.unitIDIndex_0x2c520 = 0;
            if (1 < DAT_UnitsState::instance.maxUnitCount) {
                _pUnit = &DAT_UnitsState::instance.units[1];
                do {
                    _index = this->attackInfo.unitIDIndex_0x2c520;
                    if (((_pUnit->logicalState != Map::Units::ULS_INVISIBLE)
                            && (BVar1 = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getPlayerNot1AndHasKeep,
                                    this)((int)_pUnit->owner),
                                BVar1))
                        && ((_pUnit->unitType == Map::Units::UT_E_ARCHER
                            || (_pUnit->unitType == Map::Units::UT_E_XBOW)))) {
                        if (!(DAT_TileMapState::instance.LogicLayer[_pUnit->tile] & 0x10000100U)) {
                            /*
                              not on the keep or gatehouse, or towers?
                             */
                            if (this->attackInfo.unitIDIndex_0x2bd4c < 1000) {
                                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::removeUnitFromTribe,
                                    DAT_TribesState::ptr)(_unitID, (int)((int)(_pUnit->tribeID)));
                                this->attackInfo.unitIDArray_0x2b57c[this->attackInfo.unitIDIndex_0x2bd4c]
                                    = (short)_unitID;
                                this->attackInfo.unitIDIndex_0x2bd4c = this->attackInfo.unitIDIndex_0x2bd4c + 1;
                            }
                        } else if ((_index < 200)
                            && ((!_pUnit->tribeID
                                || (DAT_TribesState::instance.tribes[_pUnit->tribeID].isRallyingUnk == 0)))) {
                            /*
                              not rallying or part of tribe
                             */
                            this->attackInfo.tileArray_0x2bd50[_index] = _pUnit->tile;
                            this->attackInfo.uidArray_0x2c200[this->attackInfo.unitIDIndex_0x2c520] = _pUnit->uid;
                            this->attackInfo.unitIDArray_0x2c070[this->attackInfo.unitIDIndex_0x2c520] = (short)_unitID;
                            this->attackInfo.unitIDIndex_0x2c520 = this->attackInfo.unitIDIndex_0x2c520 + 1;
                        }
                    }
                    _unitID = _unitID + 1;
                    _pUnit = _pUnit + 0x248;
                } while ((int)_unitID < DAT_UnitsState::instance.maxUnitCount);
            }
        }

    }
}
}
