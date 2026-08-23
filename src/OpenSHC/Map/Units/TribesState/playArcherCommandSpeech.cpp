#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00525090
        void TribesState::playArcherCommandSpeech(int selectionID)
        {
            int actionID = 0x1f;
            UnitType _majorityUnitType = MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::TribesState_Func::getMajorityArcherTypeEuropeanOrArabian, this)(selectionID);
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                _majorityUnitType, actionID);
        }

    }
}
}
