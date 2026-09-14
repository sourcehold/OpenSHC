#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00433560
    void Helpers::SetTaxesSetting_unknown(int taxesSettingUnk)
    {
        if (DAT_GameCore::instance.taxesSettingUnk == 0) {
            DAT_GameCore::instance.taxesSettingUnk = taxesSettingUnk;
            DAT_GameCore::instance.unknownScribeRelatedFlag_0x130 = TRUE;
            DAT_GameCore::instance.taxestimeUnk = timeGetTime();
            DAT_GameCore::instance.scribeAnimationFrame2 = 0;
        }
    }

}
}
