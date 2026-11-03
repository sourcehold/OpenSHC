#include "../MenuModalComposition.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/UI/Menu.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/UI/Enums/MenuItemHandleState.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/RoundedBoxEdgeRoundingLevel.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/COL_BLUE.hpp"
#include "OpenSHC/Globals/COL_DARK_CYAN_GREY.hpp"
#include "OpenSHC/Globals/COL_LIME.hpp"
#include "OpenSHC/Globals/COL_MAGENTA.hpp"
#include "OpenSHC/Globals/COL_RED.hpp"
#include "OpenSHC/Globals/COL_VERY_DARK_GREY.hpp"
#include "OpenSHC/Globals/COL_VIVID_BLUE.hpp"
#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B0B30
    void MenuModalComposition::renderMenuModal()
    {
        if (this->activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE
            || this->activeModalDialogID == OpenSHC::UI::Enums::MMT_NO_MENU) {
            return;
        }
        if (this->mbr_0x6c != 0) {
            this->disappearAfter -= (timeGetTime() - this->timeItIsSet) / 75;
            if (this->disappearAfter <= 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog, this)(
                    OpenSHC::UI::Enums::MMT_NONE, FALSE);
                this->disappearAfter = 0;
                this->mbr_0x6c = 0;
                return;
            }
        }
        int left;
        int top;
        if (MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()) {
            left = this->modalMenu.x + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX;
            top = this->modalMenu.y + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY;
            DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        } else {
            left = this->modalMenu.x;
            top = this->modalMenu.y;
        }
        int width = this->modalMenu.width;
        if (this->modalMenu.x + width > DAT_WindowAndDirectDraw::instance.resolutionX) {
            width = DAT_WindowAndDirectDraw::instance.resolutionX - this->modalMenu.x;
        }
        int height = this->modalMenu.height;
        int color = this->modalMenu.backgroundColourIndex;
        switch (color) {
        case 1:
            color = COL_RED::instance.shortValue;
            break;
        case 2:
            color = COL_LIME::instance.shortValue;
            break;
        case 3:
            color = COL_BLUE::instance.shortValue;
            break;
        case 4:
            color = COL_WHITE::instance.shortValue;
            break;
        case 5:
            color = COL_BLACK::instance.shortValue;
            break;
        case 6:
            color = COL_DARK_CYAN_GREY::instance.shortValue;
            break;
        case 7:
            color = COL_VERY_DARK_GREY::instance.shortValue;
            break;
        case 8:
            color = COL_MAGENTA::instance.shortValue;
            break;
        case 9:
            color = COL_VIVID_BLUE::instance.shortValue;
            break;
        }
        if (MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()) {
            DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        } else {
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        }
        if ((this->modalMenu.borderStyle & 0x400) != 0 && this->disappearAfter < 32 && this->mbr_0x6c == 0) {
            // fixme: this adds the whole time since timeItIsSet on every frame, so disappearAfter grows faster
            // than linearly and can pass 32 on its last step
            this->disappearAfter += (timeGetTime() - this->timeItIsSet) / 75;
        }
        if ((this->modalMenu.borderStyle & 2) != 0) {
            // title bar
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                left, top, left + width, top + 12, COL_DARK_CYAN_GREY::instance.shortValue);
            top += 12;
            height -= 12;
        }
        if ((this->modalMenu.borderStyle & 1) != 0) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                left, top, left + width, top + height, (ushort)this->modalMenu.backgroundColourIndex);
        }
        if ((this->modalMenu.borderStyle & 8) != 0) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                left, top, left + width, top + height);
        }
        if ((this->modalMenu.borderStyle & 0x10) != 0) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges,
                DAT_PencilRenderCore::ptr)(left, top, left + width, top + height, OpenSHC::UI::Enums::RBERL_STRONG);
        }
        if ((this->modalMenu.borderStyle & 0x20) != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::drawBorderStyle0x20, DAT_TextEditorState::ptr)(
                left, top, width, height);
        }
        if ((this->modalMenu.borderStyle & 0x80) != 0) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdgesAndColor,
                DAT_PencilRenderCore::ptr)(
                left, top, left + width, top + height, (ushort)color, OpenSHC::UI::Enums::RBERL_STRONG);
        }
        if ((this->modalMenu.borderStyle & 0x100) != 0) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdgesAndColor,
                DAT_PencilRenderCore::ptr)(left, top, left + width, top + height, COL_BLACK::instance.shortValue,
                OpenSHC::UI::Enums::RBERL_STRONG);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdgesAndColor,
                DAT_PencilRenderCore::ptr)(
                left + 3, top + 3, left + width - 3, top + height - 3, (ushort)color, OpenSHC::UI::Enums::RBERL_STRONG);
        }
        if ((this->modalMenu.borderStyle & 0x200) != 0 || (this->modalMenu.borderStyle & 0x20) != 0) {
            // a frame of 24x24 tiles: corners and edges, the inside is left empty
            for (int y = 0; y < this->modalMenu.height; y += 24) {
                int rowImage;
                if (y == 0) {
                    rowImage = 1;
                } else if (y == this->modalMenu.height - 24) {
                    rowImage = 13;
                } else {
                    rowImage = 7;
                }
                for (int x = 0; x < this->modalMenu.width; x += 24) {
                    int imageID = rowImage;
                    if (x != 0) {
                        if (x == this->modalMenu.width - 24) {
                            imageID = rowImage + 2;
                        } else {
                            if (rowImage == 7) {
                                continue;
                            }
                            imageID = rowImage + 1;
                        }
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, imageID,
                        x + left, y + top, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, imageID + 3,
                        32 - this->disappearAfter);
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                DAT_PencilRenderCore::ptr)(left + 24, top + 24, left + this->modalMenu.width - 25,
                top + this->modalMenu.height - 25, 32 - this->disappearAfter * 16 / 32);
        }
        if (MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()) {
            DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        }
        this->modalMenu.menuModalRenderFunction(left, top, this->modalMenu.width, this->modalMenu.height);
        if (MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()) {
            DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        } else {
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        }
        Menu* menu = this->modalMenu.pointerToMenu;
        if (menu != NULL) {
            menu->xPosition = left;
            menu->yPosition = top;
            // read again after the two stores, as the original does
            menu = this->modalMenu.pointerToMenu;
            MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::handleMenuItems, menu)(
                OpenSHC::UI::Enums::MIHS_PREPARE_AND_RENDER);
            MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::renderConstructionMenu, menu)();
        }
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
    }

}
}
