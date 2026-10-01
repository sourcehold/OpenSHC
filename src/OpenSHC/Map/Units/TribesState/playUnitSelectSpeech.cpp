#include "../TribesState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00521EB0
        void TribesState::playUnitSelectSpeech(undefined4 selectionID)
        {
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(
                1);
            UnitType const unitType
                = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::getMajoritySelectedUnitType, this)(
                    selectionID, (int*)&selectionID);
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(unitType, 0xb);
        }

    }
}
}
