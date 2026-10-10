#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using IO::Graphics::GmID;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00469290
        void PencilRenderCore::renderUpDownButtonUnk(int isDownButtonUnk, int blendStrengthUnk)
        {
            int _imageID = 0x51;
            if (!isDownButtonUnk) {
                _imageID = 0x55;
            }
            if (DAT_ButtonCurrentlyInteracting::instance) {
                _imageID = _imageID + 1;
            }
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                DAT_TextureRenderCoreObject::ptr)(IO::Graphics::GID_INTERFACE_ICONS_3, _imageID,
                (int)(DAT_ButtonX::instance), (int)(DAT_ButtonY::instance), IO::Graphics::GID_INTERFACE_ICONS_3,
                _imageID + 2, blendStrengthUnk);
        }

    }
}
}
