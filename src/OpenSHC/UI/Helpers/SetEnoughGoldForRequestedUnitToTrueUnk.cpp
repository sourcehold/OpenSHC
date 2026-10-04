#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_EnoughGoldForRequestedUnit.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00466E00
    void Helpers::SetEnoughGoldForRequestedUnitToTrueUnk() { DAT_EnoughGoldForRequestedUnit::instance = TRUE; }

}
}
