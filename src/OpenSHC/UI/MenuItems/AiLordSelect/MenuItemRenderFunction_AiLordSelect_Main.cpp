#include "../AiLordSelect.func.hpp"

#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_LobbyAddAICurrentlyHoveredAI.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using DE::SHCDE::eGM;
        using IO::Graphics::GmID;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004AE950
        void AiLordSelect::MenuItemRenderFunction_AiLordSelect_Main(int param_1, ...)
        {
            if (param_1 == 100) {
                MACRO_CALL(UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
            }
            if (param_1 == 1) {
                DAT_LobbyAddAICurrentlyHoveredAI::instance = 0;
            }
            if (DAT_GameCore::instance.numOfAIsWithCastleUnk < param_1) {
                DAT_ButtonUnknownZero::instance = 1;
            }
            int iVar1 = DAT_GameCore::instance.arrayOfLordIdsWithAIVsUnk[param_1 + -1];
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                DE::SHCDE::GM_INTERFACE_ICONS2, 0x22b, (int)(DAT_ButtonX::instance), (int)(DAT_ButtonY::instance));
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                DE::SHCDE::GM_INTERFACE_ICONS2, iVar1 + 0x20a, (int)(DAT_ButtonX::instance),
                (int)(DAT_ButtonY::instance));
            if (DAT_ButtonCurrentlyInteracting::instance) {
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(IO::Graphics::GID_INTERFACE_ICONS_2, 0x202,
                    (int)(DAT_ButtonX::instance + -6), (int)(DAT_ButtonY::instance + -6),
                    IO::Graphics::GID_INTERFACE_ICONS_2, 0x201, 0);
                DAT_LobbyAddAICurrentlyHoveredAI::instance = iVar1;
            }
        }

    }
}
}
