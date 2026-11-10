#include "../AiLordSelect.func.hpp"

#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"

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

        // FUNCTION: STRONGHOLDCRUSADER 0x004AE950
        void AiLordSelect::MenuItemRenderFunction_AiLordSelect_Main(int buttonID, ...)
        {
            if (buttonID == 100) {
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                return;
            }
            if (buttonID == 1) {
                DAT_LobbyAddAICurrentlyHoveredAI::instance = 0;
            }
            if (buttonID > DAT_GameCore::instance.numOfAIsWithCastleUnk) {
                DAT_ButtonUnknownZero::instance = 1;
                return;
            }
            int const lordID = DAT_GameCore::instance.arrayOfLordIdsWithAIVsUnk[buttonID - 1];
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 555, DAT_ButtonX::instance, DAT_ButtonY::instance);
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, lordID + 522, DAT_ButtonX::instance, DAT_ButtonY::instance);
            if (!DAT_ButtonCurrentlyInteracting::instance) {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 514,
                DAT_ButtonX::instance - 6, DAT_ButtonY::instance - 6, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 513,
                0);
            DAT_LobbyAddAICurrentlyHoveredAI::instance = lordID;
        }

    }
}
}
