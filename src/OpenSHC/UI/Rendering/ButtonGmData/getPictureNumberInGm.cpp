#include "OpenSHC/UI/Rendering/ButtonGmData.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004630B0
        int ButtonGmData::getPictureNumberInGm(BOOLEnum buttonIsInteracting)
        {
            if (buttonIsInteracting != FALSE) {
                return this->numOfAdditionalIconStates_0x8 + this->pictureInGm_0x4;
            }
            return this->pictureInGm_0x4;
        }

    }
}
}
