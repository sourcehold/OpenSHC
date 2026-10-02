#include "../MenuModalComposition.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/UI/Menu.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/UI/Enums/MenuItemHandleState.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/RoundedBoxEdgeRoundingLevel.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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

    using OpenSHC::IO::Graphics::GmID;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::UI::Enums::MenuItemHandleState;
    using OpenSHC::UI::Enums::MenuModalType;
    using OpenSHC::UI::Enums::RoundedBoxEdgeRoundingLevel;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004B0B30
    void MenuModalComposition::renderMenuModal()
    {
        uint uVar1;
        BOOLEnum _areWeInAnInGameMenu;
        int _width;
        DWORD _currentTime;
        int imageID;
        int _top;
        int _left;
        int _color;
        int _height;
        int _top2;
        Menu* _menu;
        int _x;
        if ((this->activeModalDialogID != OpenSHC::UI::Enums::MMT_NONE)
            && (this->activeModalDialogID != OpenSHC::UI::Enums::MMT_NO_MENU)) {
            if (this->mbr_0x6c != 0) {
                _currentTime = timeGetTime();
                this->disappearAfter = this->disappearAfter - (_currentTime - this->timeItIsSet) / 75;
                if ((int)this->disappearAfter < 1) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog, this)(
                        OpenSHC::UI::Enums::MMT_NONE, FALSE);
                    this->disappearAfter = 0;
                    this->mbr_0x6c = 0;
                }
            }
            _areWeInAnInGameMenu
                = MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
            _top = (this->modalMenu).y;
            if (_areWeInAnInGameMenu == FALSE) {
                _left = (this->modalMenu).x;
            } else {
                _left = (this->modalMenu).x + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX;
                _top = _top + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY;
                DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            _width = (this->modalMenu).width;
            _x = (this->modalMenu).x;
            if (DAT_WindowAndDirectDraw::instance.resolutionX < _x + _width) {
                _width = DAT_WindowAndDirectDraw::instance.resolutionX - _x;
            }
            _height = (this->modalMenu).height;
            _color = (this->modalMenu).backgroundColourIndex;
            switch (_color) {
            case 1:
                _color = (int)COL_RED::instance.shortValue;
                break;
            case 2:
                _color = (int)COL_LIME::instance.shortValue;
                break;
            case 3:
                _color = (int)COL_BLUE::instance.shortValue;
                break;
            case 4:
                _color = (int)COL_WHITE::instance.shortValue;
                break;
            case 5:
                _color = (int)COL_BLACK::instance.shortValue;
                break;
            case 6:
                _color = (int)COL_DARK_CYAN_GREY::instance.shortValue;
                break;
            case 7:
                _color = (int)COL_VERY_DARK_GREY::instance.shortValue;
                break;
            case 8:
                _color = (int)COL_MAGENTA::instance.shortValue;
                break;
            case 9:
                _color = (int)COL_VIVID_BLUE::instance.shortValue;
            }
            _areWeInAnInGameMenu
                = MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
            if (_areWeInAnInGameMenu == FALSE) {
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            } else {
                DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (((((this->modalMenu).borderStyle & 0x400U) != 0) && ((int)this->disappearAfter < 32))
                && (this->mbr_0x6c == 0)) {
                _currentTime = timeGetTime();
                /*
                  fixme
                 */
                this->disappearAfter = this->disappearAfter + (_currentTime - this->timeItIsSet) / 75;
            }
            _top2 = _top;
            if (((this->modalMenu).borderStyle & 2) != 0) {
                _top2 = _top + 0xc;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                    _left, _top, _width + _left, _top2, (ushort)((int)(COL_DARK_CYAN_GREY::instance.shortValue)));
                _height = _height + -0xc;
            }
            if (((this->modalMenu).borderStyle & 1) != 0) {
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(_left,
                    _top2, _width + _left, _height + _top2, (ushort)((int)((this->modalMenu).backgroundColourIndex)));
            }
            if (((this->modalMenu).borderStyle & 8) != 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                    _left, _top2, _width + _left, _height + _top2);
            }
            if (((this->modalMenu).borderStyle & 0x10) != 0) {
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges, DAT_PencilRenderCore::ptr)(
                    _left, _top2, _width + _left, _height + _top2, OpenSHC::UI::Enums::RBERL_STRONG);
            }
            if (((this->modalMenu).borderStyle & 0x20) != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::drawBorderStyle0x20, DAT_TextEditorState::ptr)(
                    _left, _top2, _width, _height);
            }
            if (((this->modalMenu).borderStyle & 0x80) != 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdgesAndColor,
                    DAT_PencilRenderCore::ptr)(_left, _top2, _width + _left, _height + _top2, (ushort)((int)(_color)),
                    OpenSHC::UI::Enums::RBERL_STRONG);
            }
            if (((this->modalMenu).borderStyle & 0x100U) != 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdgesAndColor,
                    DAT_PencilRenderCore::ptr)(_left, _top2, _width + _left, _height + _top2,
                    (ushort)((int)(COL_BLACK::instance.shortValue)), OpenSHC::UI::Enums::RBERL_STRONG);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdgesAndColor,
                    DAT_PencilRenderCore::ptr)(_left + 3, _top2 + 3, _width + _left + -3, _height + _top2 + -3,
                    (ushort)((int)(_color)), OpenSHC::UI::Enums::RBERL_STRONG);
            }
            uVar1 = (this->modalMenu).borderStyle;
            if (((uVar1 & 0x200) != 0) || ((uVar1 & 0x20) != 0)) {
                _height = 0;
                if (0 < (this->modalMenu).height) {
                    do {
                        if (_height == 0) {
                            _width = 1;
                        } else {
                            _width = (-(uint)(_height != (this->modalMenu).height + -0x18) & 0xfffffffa) + 0xd;
                        }
                        _x = 0;
                        if (0 < (this->modalMenu).width) {
                            do {
                                imageID = _width;
                                if (_x == 0) {
                                LAB_004b0e31:
                                    MACRO_CALL_MEMBER(
                                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                                        imageID, _x + _left, _height + _top2,
                                        OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, imageID + 3,
                                        (int)((int)(0x20 - this->disappearAfter)));
                                } else {
                                    if (_x == (this->modalMenu).width + -0x18) {
                                        imageID = _width + 2;
                                        goto LAB_004b0e31;
                                    }
                                    if (_width != 7) {
                                        imageID = _width + 1;
                                        goto LAB_004b0e31;
                                    }
                                }
                                _x = _x + 0x18;
                            } while (_x < (this->modalMenu).width);
                        }
                        _height = _height + 0x18;
                    } while (_height < (this->modalMenu).height);
                }
                _width = this->disappearAfter * 0x10;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(_left + 0x18, _top2 + 0x18, _left + -0x19 + (this->modalMenu).width,
                    (this->modalMenu).height + -0x19 + _top2, 0x20 - ((int)(_width + (_width >> 0x1f & 0x1fU)) >> 5));
            }
            _areWeInAnInGameMenu
                = MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
            if (_areWeInAnInGameMenu != FALSE) {
                DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            (*(this->modalMenu).menuModalRenderFunction)(
                _left, _top2, (this->modalMenu).width, (this->modalMenu).height);
            _areWeInAnInGameMenu
                = MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
            if (_areWeInAnInGameMenu == FALSE) {
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            } else {
                DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            _menu = (this->modalMenu).pointerToMenu;
            if (_menu != (Menu*)0x0) {
                _menu->xPosition = _left;
                _menu->yPosition = _top2;
                _menu = (this->modalMenu).pointerToMenu;
                MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::handleMenuItems, _menu)(
                    OpenSHC::UI::Enums::MIHS_PREPARE_AND_RENDER);
                MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::renderConstructionMenu, _menu)();
            }
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        }
    }

}
}
