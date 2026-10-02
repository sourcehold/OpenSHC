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

        using OpenSHC::IO::Graphics::GmID;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00469290
        void PencilRenderCore::renderUpDownButtonUnk(int isDownButtonUnk, int blendStrengthUnk)
        {
            int _imageID;
            _imageID = 0x51;
            if (isDownButtonUnk == 0) {
                _imageID = 0x55;
            }
            if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                _imageID = _imageID + 1;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, _imageID,
                (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)),
                OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, _imageID + 2, blendStrengthUnk);
        }

    }
}
}
