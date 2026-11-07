#include "../RankingGames.func.hpp"

#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_00ed27a0.hpp"
#include "OpenSHC/Globals/DAT_00ed3124.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonPictureInGm.hpp"
#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004D99F0
        void RankingGames::MenuItemRenderFunction_RankingGames_Main(int button, ...)
        {
            // buttons -10 and -11 scroll the list up and down: pictures 85 and 81, the next one when hovered
            if (button == -10 || button == -11) {
                int picture = 81;
                if (button == -10) {
                    picture = 85;
                }
                if (DAT_ButtonCurrentlyInteracting::instance) {
                    ++picture;
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, picture, DAT_ButtonX::instance, DAT_ButtonY::instance);
                // a frame from one pixel above and left of the arrow to 20 pixels below and right of it
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance - 1, DAT_ButtonY::instance - 1,
                    DAT_ButtonX::instance + 20, DAT_ButtonY::instance + 20, COL_VERY_SOFT_YELLOW::instance.shortValue);
                return;
            }
            // buttons 0 to 7 are the rows, which draw nothing here
            if (button < 8) {
                return;
            }
            // the column headers are 20 to 31; any other button draws its own picture
            if (button >= 20 && button <= 31) {
                // button 20 clears the hovered header, and the hovered one stores itself
                if (button == 20) {
                    DAT_00ed27a0::instance = 0;
                }
                if (DAT_ButtonCurrentlyInteracting::instance) {
                    DAT_00ed27a0::instance = button;
                }
                // headers 20 to 29 sort by columns 1 to 10; 30 and 31 toggle DAT_00ed3124 to 1 and 2 and back to 0: the
                // header in use draws the picture two after its own
                if ((button < 30 && button - 19 == DAT_MissionDefinedData::instance.sortColumn)
                    || (button == 30 && DAT_00ed3124::instance == 1) || (button == 31 && DAT_00ed3124::instance == 2)) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    int const picture
                        = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                              .pictureInGm_0x4
                        + 2;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)((OpenSHC::DE::SHCDE::eGM)DAT_UIButtonDefinedData::instance
                                                              .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                                              .gmId_0x0,
                        picture, DAT_ButtonX::instance, DAT_ButtonY::instance);
                    DAT_CurrentButtonPictureInGm::instance = picture;
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    return;
                }
            }
            MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                    MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
        }

    }
}
}
