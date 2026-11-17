#include "../TextEditor.func.hpp"

#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_UserHelpDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Text::TextAlignment;

        // FUNCTION: STRONGHOLDCRUSADER 0x0045DE40
        void TextEditor::MenuItemRenderFunction_TextEditor_Buttons(int param_1, ...)
        {
            char* textAddress;
            int xParam;
            int yParam;
            switch (param_1) {
            case -1:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                    DAT_PencilRenderCore::ptr)(0, 0);
                break;
            case -2:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                    DAT_PencilRenderCore::ptr)(1, 0);
                return;
            case -4:
                if (DAT_TextEditorState::instance.helpSectionHistoryStack[0] != -1) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    if (!DAT_ButtonCurrentlyInteracting::instance) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                            // "Back"
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_HELP, 1,
                            DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 7,
                            OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 4);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                            // "Back"
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_HELP, 1,
                            DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 7,
                            OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 2);
                    }
                    return;
                }
                break;
            case -5:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                        // "Exit"
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_HELP, 2,
                        DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 7,
                        OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 4);
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    // "Exit"
                    OpenSHC::DE::SHCDE::TEXT_HELP, 2, DAT_ButtonW::instance / 2 + DAT_ButtonX::instance,
                    DAT_ButtonY::instance + 7, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18,
                    FALSE, 2);
                return;
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 20:
                // fixme: the original tests -4 here and in the inner switch (-4, -5), though this arm never sees them
                if (param_1 == -4 && DAT_TextEditorState::instance.helpSectionHistoryStack[0] == -1) {
                    break;
                }
                if (DAT_ButtonCurrentlyInteracting::instance) {
                    DAT_TextManagerObject::instance.textColor = OpenSHC::Rendering::Colors::COL_0000FF;
                    DAT_PencilRenderCore::instance.otherColorUnk_0x0 = COL_BLACK::instance.shortValue;
                } else {
                    DAT_TextManagerObject::instance.textColor = 0;
                    DAT_PencilRenderCore::instance.otherColorUnk_0x0 = COL_WHITE::instance.shortValue;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                    DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonH::instance + DAT_ButtonY::instance,
                    DAT_PencilRenderCore::instance.otherColorUnk_0x0);
                switch (param_1) {
                case -4:
                    // "Back"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_HELP, 1, DAT_ButtonX::instance, DAT_ButtonY::instance + 3,
                        (TextAlignment)DAT_ButtonW::instance, DAT_TextManagerObject::instance.textColor, 18, FALSE);
                    return;
                case -5:
                    // "Exit"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_HELP, 2, DAT_ButtonX::instance, DAT_ButtonY::instance + 3,
                        (TextAlignment)DAT_ButtonW::instance, DAT_TextManagerObject::instance.textColor, 18, FALSE);
                    return;
                case 1:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2, DAT_TextManagerObject::ptr)(
                        // "Symbols"
                        (char*)s_Symbols_005a5608, DAT_ButtonX::instance, DAT_ButtonY::instance + 3,
                        (TextAlignment)DAT_ButtonW::instance, DAT_TextManagerObject::instance.textColor, 19, FALSE);
                    return;
                case 2:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2, DAT_TextManagerObject::ptr)(
                        // "New Page"
                        (char*)s_New_Page_005a55fc, DAT_ButtonX::instance, DAT_ButtonY::instance + 3,
                        (TextAlignment)DAT_ButtonW::instance, DAT_TextManagerObject::instance.textColor, 19, FALSE);
                    return;
                case 3:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2, DAT_TextManagerObject::ptr)(
                        // "Load"
                        (char*)s_Load_005a55f4, DAT_ButtonX::instance, DAT_ButtonY::instance + 3,
                        (TextAlignment)DAT_ButtonW::instance, DAT_TextManagerObject::instance.textColor, 19, FALSE);
                    return;
                case 4:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2, DAT_TextManagerObject::ptr)(
                        // "Save"
                        (char*)s_Save_005a55ec, DAT_ButtonX::instance, DAT_ButtonY::instance + 3,
                        (TextAlignment)DAT_ButtonW::instance, DAT_TextManagerObject::instance.textColor, 19, FALSE);
                    return;
                case 20:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2, DAT_TextManagerObject::ptr)(
                        // "ScrSize"
                        (char*)s_ScrSize_005a55e4, DAT_ButtonX::instance, DAT_ButtonY::instance + 3,
                        (TextAlignment)DAT_ButtonW::instance, DAT_TextManagerObject::instance.textColor, 19, FALSE);
                    return;
                case 5:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2, DAT_TextManagerObject::ptr)(
                        // "Pic"
                        (char*)s_Pic_005a55e0, DAT_ButtonX::instance, DAT_ButtonY::instance + 3,
                        (TextAlignment)DAT_ButtonW::instance, DAT_TextManagerObject::instance.textColor, 19, FALSE);
                    return;
                case 6:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2, DAT_TextManagerObject::ptr)(
                        // "Link"
                        (char*)s_Link_005a55d8, DAT_ButtonX::instance, DAT_ButtonY::instance + 3,
                        (TextAlignment)DAT_ButtonW::instance, DAT_TextManagerObject::instance.textColor, 19, FALSE);
                    return;
                case 7:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2, DAT_TextManagerObject::ptr)(
                        // "\\Link"
                        (char*)s__Link_005a55d0, DAT_ButtonX::instance, DAT_ButtonY::instance + 3,
                        (TextAlignment)DAT_ButtonW::instance, DAT_TextManagerObject::instance.textColor, 19, FALSE);
                    return;
                case 8:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2, DAT_TextManagerObject::ptr)(
                        // "Font"
                        (char*)s_Font_005a55c8, DAT_ButtonX::instance, DAT_ButtonY::instance + 3,
                        (TextAlignment)DAT_ButtonW::instance, DAT_TextManagerObject::instance.textColor, 19, FALSE);
                    return;
                case 9:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2, DAT_TextManagerObject::ptr)(
                        // "Centre"
                        (char*)s_Centre_005a55c0, DAT_ButtonX::instance, DAT_ButtonY::instance + 3,
                        (TextAlignment)DAT_ButtonW::instance, DAT_TextManagerObject::instance.textColor, 19, FALSE);
                    return;
                case 10:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2, DAT_TextManagerObject::ptr)(
                        // "\\Centre"
                        (char*)s__Centre_005a55b8, DAT_ButtonX::instance, DAT_ButtonY::instance + 3,
                        (TextAlignment)DAT_ButtonW::instance, DAT_TextManagerObject::instance.textColor, 19, FALSE);
                    return;
                case 11:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2, DAT_TextManagerObject::ptr)(
                        // "Colour"
                        (char*)s_Colour_005a55b0, DAT_ButtonX::instance, DAT_ButtonY::instance + 3,
                        (TextAlignment)DAT_ButtonW::instance, DAT_TextManagerObject::instance.textColor, 19, FALSE);
                    return;
                case 12:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2, DAT_TextManagerObject::ptr)(
                        // "LinkClr"
                        (char*)s_LinkClr_005a55a8, DAT_ButtonX::instance, DAT_ButtonY::instance + 3,
                        (TextAlignment)DAT_ButtonW::instance, DAT_TextManagerObject::instance.textColor, 19, FALSE);
                    return;
                case 13:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2, DAT_TextManagerObject::ptr)(
                        // "Sound"
                        (char*)s_Sound_005a55a0, DAT_ButtonX::instance, DAT_ButtonY::instance + 3,
                        (TextAlignment)DAT_ButtonW::instance, DAT_TextManagerObject::instance.textColor, 19, FALSE);
                    return;
                case 14:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2, DAT_TextManagerObject::ptr)(
                        // "String"
                        (char*)s_String_005a5598, DAT_ButtonX::instance, DAT_ButtonY::instance + 3,
                        (TextAlignment)DAT_ButtonW::instance, DAT_TextManagerObject::instance.textColor, 19, FALSE);
                    return;
                case 15:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2, DAT_TextManagerObject::ptr)(
                        // "Include"
                        (char*)s_Include_005a5590, DAT_ButtonX::instance, DAT_ButtonY::instance + 3,
                        (TextAlignment)DAT_ButtonW::instance, DAT_TextManagerObject::instance.textColor, 19, FALSE);
                    return;
                }
                break;
            case 31:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                    DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonH::instance + DAT_ButtonY::instance,
                    COL_BLACK::instance.shortValue);
                switch (DAT_TextEditorState::instance.field_0x23970) {
                case 1:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        // "PIC"
                        (char*)s_PIC_005a558c, DAT_ButtonX::instance + 3, DAT_ButtonY::instance + 3,
                        OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF, 19, FALSE, 0);
                    return;
                case 2:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        // "FONT"
                        (char*)s_FONT_005a5584, DAT_ButtonX::instance + 3, DAT_ButtonY::instance + 3,
                        OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF, 19, FALSE, 0);
                    return;
                case 3:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        // "COLOUR"
                        (char*)s_COLOUR_005a557c, DAT_ButtonX::instance + 3, DAT_ButtonY::instance + 3,
                        OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF, 19, FALSE, 0);
                    return;
                case 10:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        // "LINKCLR"
                        (char*)s_LINKCLR_005a5574, DAT_ButtonX::instance + 3, DAT_ButtonY::instance + 3,
                        OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF, 19, FALSE, 0);
                    return;
                case 4:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        // "LINK"
                        (char*)s_LINK_005a556c, DAT_ButtonX::instance + 3, DAT_ButtonY::instance + 3,
                        OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF, 19, FALSE, 0);
                    return;
                case 5:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        // "\\LINK"
                        (char*)s__LINK_005a5564, DAT_ButtonX::instance + 3, DAT_ButtonY::instance + 3,
                        OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF, 19, FALSE, 0);
                    return;
                case 7:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        // "CENTRE"
                        (char*)s_CENTRE_005a555c, DAT_ButtonX::instance + 3, DAT_ButtonY::instance + 3,
                        OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF, 19, FALSE, 0);
                    return;
                case 8:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        // "\\CENTRE"
                        (char*)s__CENTRE_005a5554, DAT_ButtonX::instance + 3, DAT_ButtonY::instance + 3,
                        OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF, 19, FALSE, 0);
                    return;
                case 11:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        // "SOUND"
                        (char*)s_SOUND_005a554c, DAT_ButtonX::instance + 3, DAT_ButtonY::instance + 3,
                        OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF, 19, FALSE, 0);
                    return;
                case 12:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        // "STRING"
                        (char*)s_STRING_005a5544, DAT_ButtonX::instance + 3, DAT_ButtonY::instance + 3,
                        OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF, 19, FALSE, 0);
                    return;
                case 14:
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        // "INCLUDE"
                        (char*)s_INCLUDE_005a553c, DAT_ButtonX::instance + 3, DAT_ButtonY::instance + 3,
                        OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF, 19, FALSE, 0);
                }
                break;
            case 32:
                if (DAT_ButtonCurrentlyInteracting::instance) {
                    DAT_TextManagerObject::instance.textColor = OpenSHC::Rendering::Colors::COL_0000FF;
                    DAT_PencilRenderCore::instance.otherColorUnk_0x0 = COL_WHITE::instance.shortValue;
                } else {
                    DAT_TextManagerObject::instance.textColor = OpenSHC::Rendering::Colors::COL_FFFFFF;
                    DAT_PencilRenderCore::instance.otherColorUnk_0x0 = COL_BLACK::instance.shortValue;
                }
                switch (DAT_TextEditorState::instance.field_0x23970) {
                case 1:
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                        DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonH::instance + DAT_ButtonY::instance,
                        DAT_PencilRenderCore::instance.otherColorUnk_0x0);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2, DAT_TextManagerObject::ptr)(
                        DAT_TextEditorState::instance.graphicFileNames[(ushort)DAT_TextEditorState::instance
                                .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex
                                    + 1]],
                        DAT_ButtonX::instance + 3, DAT_ButtonY::instance + 3, OpenSHC::Text::TTA_LEFT,
                        DAT_TextManagerObject::instance.textColor, 19, FALSE);
                    return;
                case 2:
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                        DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonH::instance + DAT_ButtonY::instance,
                        COL_BLACK::instance.shortValue);
                    yParam = DAT_ButtonY::instance + 3;
                    xParam = DAT_ButtonX::instance + 3;
                    textAddress = MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::getHelpSectionText,
                        DAT_TextEditorState::ptr)((uint)(ushort)DAT_TextEditorState::instance
                            .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex
                                + 1]);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        textAddress, xParam, yParam, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF,
                        19, FALSE, 0);
                    return;
                case 3:
                case 10:
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                        DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonH::instance + DAT_ButtonY::instance,
                        COL_BLACK::instance.shortValue);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        DAT_UserHelpDefinedData::instance
                            .field_0x7a16c[(ushort)DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory
                                    [DAT_TextEditorState::instance.activeHelpHotspotIndex + 1]]
                            .name_0x0,
                        DAT_ButtonX::instance + 3, DAT_ButtonY::instance + 3, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_FFFFFF, 19, FALSE, 0);
                    return;
                case 4:
                case 14:
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                        DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonH::instance + DAT_ButtonY::instance,
                        DAT_PencilRenderCore::instance.otherColorUnk_0x0);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2, DAT_TextManagerObject::ptr)(
                        DAT_UserHelpDefinedData::instance.HelpSections[(ushort)DAT_TextEditorState::instance
                                .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex
                                    + 1]],
                        DAT_ButtonX::instance + 3, DAT_ButtonY::instance + 3, OpenSHC::Text::TTA_LEFT,
                        DAT_TextManagerObject::instance.textColor, 19, FALSE);
                    return;
                default:
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                        DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonH::instance + DAT_ButtonY::instance,
                        COL_BLACK::instance.shortValue);
                    return;
                case 11:
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                        DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonH::instance + DAT_ButtonY::instance,
                        DAT_PencilRenderCore::instance.otherColorUnk_0x0);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2, DAT_TextManagerObject::ptr)(
                        DAT_TextEditorState::instance.soundFileNames[(ushort)DAT_TextEditorState::instance
                                .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex
                                    + 1]],
                        DAT_ButtonX::instance + 3, DAT_ButtonY::instance + 3, OpenSHC::Text::TTA_LEFT,
                        DAT_TextManagerObject::instance.textColor, 19, FALSE);
                    return;
                case 12:
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                        DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonH::instance + DAT_ButtonY::instance,
                        DAT_PencilRenderCore::instance.otherColorUnk_0x0);
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen, DAT_TextManagerObject::ptr)(
                        (uint)(ushort)DAT_TextEditorState::instance
                            .DAT_PointerToTemporaryTextMemory[DAT_TextEditorState::instance.activeHelpHotspotIndex + 1],
                        DAT_ButtonX::instance + 3, DAT_ButtonY::instance + 3, OpenSHC::Text::TTA_LEFT,
                        DAT_TextManagerObject::instance.textColor, 19, FALSE);
                }
                break;
            case 33:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                    DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonH::instance + DAT_ButtonY::instance,
                    COL_BLACK::instance.shortValue);
                switch (DAT_TextEditorState::instance.field_0x23970) {
                case 1:
                    DAT_TextManagerObject::instance.textColor
                        = (DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory
                                        [DAT_TextEditorState::instance.activeHelpHotspotIndex + 2]
                                    == 0
                                ? OpenSHC::Rendering::Colors::COL_0000FF
                                : OpenSHC::Rendering::Colors::COL_FFFFFF);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        // "Left"
                        (char*)s_Left_005a5534, DAT_ButtonX::instance + 3, DAT_ButtonY::instance + 3,
                        OpenSHC::Text::TTA_LEFT, DAT_TextManagerObject::instance.textColor, 19, FALSE, 0);
                    return;
                case 2:
                case 3:
                case 10:
                case 12:
                    if (DAT_ButtonCurrentlyInteracting::instance) {
                        DAT_TextManagerObject::instance.textColor = OpenSHC::Rendering::Colors::COL_0000FF;
                        DAT_PencilRenderCore::instance.otherColorUnk_0x0 = COL_WHITE::instance.shortValue;
                    } else {
                        DAT_TextManagerObject::instance.textColor = OpenSHC::Rendering::Colors::COL_FFFFFF;
                        DAT_PencilRenderCore::instance.otherColorUnk_0x0 = COL_BLACK::instance.shortValue;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                        DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonH::instance + DAT_ButtonY::instance,
                        DAT_PencilRenderCore::instance.otherColorUnk_0x0);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2, DAT_TextManagerObject::ptr)(
                        // "PREV"
                        (char*)s_PREV_005a552c, DAT_ButtonX::instance, DAT_ButtonY::instance + 3,
                        (TextAlignment)DAT_ButtonW::instance, DAT_TextManagerObject::instance.textColor, 19, FALSE);
                }
                break;
            case 34:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                    DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonH::instance + DAT_ButtonY::instance,
                    COL_BLACK::instance.shortValue);
                switch (DAT_TextEditorState::instance.field_0x23970) {
                case 1:
                    DAT_TextManagerObject::instance.textColor
                        = (DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory
                                        [DAT_TextEditorState::instance.activeHelpHotspotIndex + 2]
                                    == 1
                                ? OpenSHC::Rendering::Colors::COL_0000FF
                                : OpenSHC::Rendering::Colors::COL_FFFFFF);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        // "Centre"
                        (char*)s_Centre_005a55c0, DAT_ButtonX::instance + 3, DAT_ButtonY::instance + 3,
                        OpenSHC::Text::TTA_LEFT, DAT_TextManagerObject::instance.textColor, 19, FALSE, 0);
                    return;
                case 2:
                case 3:
                case 10:
                case 12:
                    if (DAT_ButtonCurrentlyInteracting::instance) {
                        DAT_TextManagerObject::instance.textColor = OpenSHC::Rendering::Colors::COL_0000FF;
                        DAT_PencilRenderCore::instance.otherColorUnk_0x0 = COL_WHITE::instance.shortValue;
                    } else {
                        DAT_TextManagerObject::instance.textColor = OpenSHC::Rendering::Colors::COL_FFFFFF;
                        DAT_PencilRenderCore::instance.otherColorUnk_0x0 = COL_BLACK::instance.shortValue;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                        DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonH::instance + DAT_ButtonY::instance,
                        DAT_PencilRenderCore::instance.otherColorUnk_0x0);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen2, DAT_TextManagerObject::ptr)(
                        // "NEXT"
                        (char*)s_NEXT_005a5524, DAT_ButtonX::instance, DAT_ButtonY::instance + 3,
                        (TextAlignment)DAT_ButtonW::instance, DAT_TextManagerObject::instance.textColor, 19, FALSE);
                }
                break;
            case 35:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                    DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonH::instance + DAT_ButtonY::instance,
                    COL_BLACK::instance.shortValue);
                if (DAT_TextEditorState::instance.field_0x23970 == 1) {
                    DAT_TextManagerObject::instance.textColor
                        = (DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory
                                        [DAT_TextEditorState::instance.activeHelpHotspotIndex + 2]
                                    == 2
                                ? OpenSHC::Rendering::Colors::COL_0000FF
                                : OpenSHC::Rendering::Colors::COL_FFFFFF);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        // "Right"
                        (char*)s_Right_005a551c, DAT_ButtonX::instance + 3, DAT_ButtonY::instance + 3,
                        OpenSHC::Text::TTA_LEFT, DAT_TextManagerObject::instance.textColor, 19, FALSE, 0);
                }
                break;
            case 36:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                    DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonH::instance + DAT_ButtonY::instance,
                    COL_BLACK::instance.shortValue);
                if (DAT_TextEditorState::instance.field_0x23970 == 1) {
                    DAT_TextManagerObject::instance.textColor
                        = (DAT_TextEditorState::instance.DAT_PointerToTemporaryTextMemory
                                        [DAT_TextEditorState::instance.activeHelpHotspotIndex + 2]
                                    == 3
                                ? OpenSHC::Rendering::Colors::COL_0000FF
                                : OpenSHC::Rendering::Colors::COL_FFFFFF);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        // "Here"
                        (char*)s_Here_005a5514, DAT_ButtonX::instance + 3, DAT_ButtonY::instance + 3,
                        OpenSHC::Text::TTA_LEFT, DAT_TextManagerObject::instance.textColor, 19, FALSE, 0);
                }
                break;
            }
        }

    }
}
}
