#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0052F010
        void UnitsState::removeUnitFromItsTribe(uint unitID, int unitUID)
        {
            if ((int)unitID < 1) {
                return;
            }
            if (this->units[unitID].uid != unitUID) {
                return;
            }
            int _tribeID = this->units[unitID].tribeID;
            this->units[unitID].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
            if (_tribeID < 1) {
                return;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::tribeCorrespondsWithUID, DAT_TribesState::ptr)(
                    _tribeID, this->units[unitID].tribeUID)
                == FALSE) {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::removeUnitFromTribe, DAT_TribesState::ptr)(
                unitID, _tribeID);
        }

    }
}
}
