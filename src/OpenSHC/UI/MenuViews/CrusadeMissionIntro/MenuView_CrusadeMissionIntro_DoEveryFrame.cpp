#include "../CrusadeMissionIntro.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/Text/TextAlignmentInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/CHAR_ARRAY_00eb0ab0.hpp"
#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00eb9ae8.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::DE::SHCDE::eGM;
        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Game::TrailType;
        using OpenSHC::IO::Graphics::GmID;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::Text::TextAlignmentInt;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004DD7B0
        void CrusadeMissionIntro::MenuView_CrusadeMissionIntro_DoEveryFrame()
        {
            int iVar1;
            char* pcVar2;
            char* _pExtremeTrailName;
            int _extremeTrailNameWidth;
            char* _pTitle;
            dword dVar3;
            int iVar4;
            int _offset;
            int* piVar5;
            int iVar6;
            int _goldMultiplier;
            int iVar7;
            bool bVar8;
            uint uVar9;
            TextAlignment TVar10;
            uint uVar11;
            BGR24 BVar12;
            int iVar13;
            BOOLEnum BVar14;
            int* local_10c;
            int* local_108;
            int local_104;
            int _textY_01;
            int local_f4[33];
            int local_70[4];
            undefined4 local_60;
            undefined4 local_54;
            undefined4 local_48;
            undefined4 local_3c;
            undefined4 local_30;
            undefined4 local_24;
            undefined4 local_18;
            undefined4 local_c;
            int _titleX;
            int _titleY;
            TextAlignmentInt _titleAlignment;
            uint _titleFG;
            uint _titleBG;
            int _titleFontSize;
            BOOLEnum _titleRetainX;
            int _textX_01;
            int _fontSize;
            int _blendStrength;
            if (!DAT_MissionDefinedData::instance.field26_0xaf8) {}
            MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderGfxHelperUnk)(0, 0, 0);
            iVar1 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            _textX_01 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                if (0x13 < DAT_GameCore::instance.extremeTrailProgress) {
                    _offset = 0;
                    BVar14 = FALSE;
                    iVar13 = 0x10;
                    BVar12 = 0xccfaff;
                    TVar10 = OpenSHC::Text::TTA_CENTER;
                    iVar1 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x32;
                    iVar4 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400;
                    /*
                      added by script: "Crusader Trail Completed!"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE, 6), iVar4, iVar1, TVar10, BVar12, iVar13, BVar14, _offset);
                }
            } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST) {
                if (0x1d < (int)DAT_GameCore::instance.warchestTrailProgress) {
                    _offset = 0;
                    BVar14 = FALSE;
                    iVar13 = 0x10;
                    BVar12 = 0xccfaff;
                    TVar10 = OpenSHC::Text::TTA_CENTER;
                    iVar1 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x32;
                    iVar4 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400;
                    /*
                      added by script: "Crusader Trail Completed!"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE, 6), iVar4, iVar1, TVar10, BVar12, iVar13, BVar14, _offset);
                }
            } else if ((DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_FIRST_EDITION)
                && (0x31 < (int)DAT_GameCore::instance.skirmishTrailProgress)) {
                _offset = 0;
                BVar14 = FALSE;
                iVar13 = 0x10;
                BVar12 = 0xccfaff;
                TVar10 = OpenSHC::Text::TTA_CENTER;
                iVar1 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x32;
                iVar4 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400;
                /*
                  added by script: "Crusader Trail Completed!"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE, 6), iVar4, iVar1, TVar10, BVar12, iVar13, BVar14, _offset);
            }
            iVar4 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x20;
            _textY_01 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x156;
            iVar13 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0xfe;
            local_f4[0x15] = 0;
            local_f4[0x16] = 0;
            local_f4[0x17] = 0;
            local_f4[0x18] = 0;
            local_f4[0x19] = 0;
            local_f4[0x1a] = 0;
            local_f4[0x1b] = 0;
            local_f4[0x1c] = 0;
            local_f4[0x1d] = 0;
            local_f4[0x1e] = 0;
            local_f4[0xb] = 0;
            local_f4[0xc] = 0;
            local_f4[0xd] = 0;
            local_f4[0xe] = 0;
            local_f4[0xf] = 0;
            local_f4[0x10] = 0;
            local_f4[0x11] = 0;
            local_f4[0x12] = 0;
            local_f4[0x13] = 0;
            local_f4[0x14] = 0;
            local_f4[1] = 0;
            local_f4[2] = 0;
            local_f4[3] = 0;
            local_f4[4] = 0;
            local_f4[5] = 0;
            local_f4[6] = 0;
            local_f4[7] = 0;
            local_f4[8] = 0;
            local_f4[9] = 0;
            local_f4[10] = 0;
            if (DAT_GameCore::instance.field22_0x64 == 0) {
                dVar3 = DAT_GameCore::instance.extremeTrailProgress;
                if ((DAT_GameCore::instance.currentTrailType != OpenSHC::Game::TT_EXTREME)
                    && (dVar3 = DAT_GameCore::instance.skirmishTrailProgress,
                        DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST)) {
                    dVar3 = DAT_GameCore::instance.warchestTrailProgress;
                }
                MACRO_CALL(OpenSHC::Synchrony_Func::LoadSkirmishCampaignData)(dVar3);
            }
            _blendStrength = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            _offset = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            iVar7 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x238;
            iVar6 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 10;
            if (INT_00eb9ae8::instance == 0) {
                MACRO_CALL(OpenSHC::UI::Helpers_Func::ReadMapHeaderFromFile)(CHAR_ARRAY_00eb0ab0::instance);
            }
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderedBoxWithBlendedBackground,
                DAT_PencilRenderCore::ptr)(iVar7, iVar6, 0xd8, 0xd8);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapPreview, DAT_MinimapViewState::ptr)(
                _offset + 0x240, _blendStrength + 0x12);
            _offset = 0;
            do {
                _blendStrength = DAT_GameCore::instance.keepPositions[_offset].x;
                if (-1 < _blendStrength) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    if (DAT_GameSynchronyState::instance.playerPositionsArray[_offset] != -10) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                            (int)((int)(DAT_GameSynchronyState::instance.playerPositionsArray[_offset] + 0x1d6)),
                            _blendStrength + 5 + iVar7, DAT_GameCore::instance.keepPositions[_offset].y + 1 + iVar6);
                    }
                }
                _offset = _offset + 1;
            } while (_offset < 8);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderedBoxWithBlendedBackground,
                DAT_PencilRenderCore::ptr)(DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x10,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 10, 0x210, 0xd8);
            iVar7 = 0;
            BVar14 = FALSE;
            iVar6 = 0x11;
            uVar11 = 0;
            uVar9 = 0xccfaff;
            TVar10 = OpenSHC::Text::TTA_LEFT;
            _offset = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 100;
            _blendStrength = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x20;
            /*
              added by script: "Human Lord"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE, 7), _blendStrength, _offset, TVar10, uVar9, uVar11, iVar6, BVar14, iVar7);
            iVar7 = 0;
            BVar14 = FALSE;
            iVar6 = 0x11;
            uVar11 = 0;
            uVar9 = 0xccfaff;
            TVar10 = OpenSHC::Text::TTA_LEFT;
            _offset = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x8c;
            _blendStrength = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x20;
            /*
              added by script: "Computer Lords"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE, 8), _blendStrength, _offset, TVar10, uVar9, uVar11, iVar6, BVar14, iVar7);
            _goldMultiplier = 1;
            if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                _goldMultiplier = 3;
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                DAT_RenderingDefinedData::instance
                        .field451_0x53bb4[(DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance
                                              + DAT_GameSynchronyState::instance.skirmishGameIntensityType * 5)
                                * 2
                            + 0xc]
                    * _goldMultiplier,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x118,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 100, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0,
                0x11, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                DAT_RenderingDefinedData::instance
                        .field451_0x53bb4[(DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance
                                              + DAT_GameSynchronyState::instance.skirmishGameIntensityType * 5)
                                * 2
                            + 0xd]
                    * _goldMultiplier,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x118,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x8c, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0,
                0x11, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x2da,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x15e,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x5c);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x2da,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x15e,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x84);
            if (DAT_GameSynchronyState::instance.skirmishGameIntensityType == 2) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x25c,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 500,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0xb4);
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderedBoxWithBlendedBackground,
                DAT_PencilRenderCore::ptr)(DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x10,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0xee, 0x300, 0x120);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            _fontSize = 0xf;
            if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                _extremeTrailNameWidth = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER( OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)( OpenSHC::DE::SHCDE::TEXT_TRAIL_NAMES_CRU, DAT_GameCore::instance.extremeTrailProgress + 0x51), _fontSize);
                if (445 < _extremeTrailNameWidth) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                        DAT_GameCore::instance.extremeTrailProgress + 1,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1e,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x1e, OpenSHC::Text::TTA_LEFT,
                        0xccfaff, 0, 0x10, FALSE, 0);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                        DAT_TextManagerObject::ptr)(".", DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1f,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x1e, OpenSHC::Text::TTA_LEFT,
                        0xccfaff, 0, 0x10, TRUE, 0);
                    _offset = DAT_GameCore::instance.extremeTrailProgress + 0x51;
                    _titleFontSize = 0x10;
                    goto LAB_004ddfa0;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameCore::instance.extremeTrailProgress + 1,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1e,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x1e, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0,
                    0xf, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)(".", DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1f,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x1e, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0,
                    0xf, TRUE, 0);
                _offset = DAT_GameCore::instance.extremeTrailProgress + 0x51;
            } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST) {
                _offset = MACRO_CALL_MEMBER( OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_TRAIL_NAMES_CRU, (int)((int)(DAT_GameCore::instance.warchestTrailProgress + 0x33))), _fontSize);
                if (0x1bd < _offset) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                        DAT_GameCore::instance.warchestTrailProgress + 0x33,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1e,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x1e, OpenSHC::Text::TTA_LEFT,
                        0xccfaff, 0, 0x10, FALSE, 0);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                        DAT_TextManagerObject::ptr)(".", DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1f,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x1e, OpenSHC::Text::TTA_LEFT,
                        0xccfaff, 0, 0x10, TRUE, 0);
                    _offset = DAT_GameCore::instance.warchestTrailProgress + 0x33;
                    _titleFontSize = 0x10;
                    goto LAB_004ddfa0;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameCore::instance.warchestTrailProgress + 0x33,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1e,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x1e, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0,
                    0xf, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)(".", DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1f,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x1e, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0,
                    0xf, TRUE, 0);
                _offset = DAT_GameCore::instance.warchestTrailProgress + 0x33;
            } else {
                _offset = MACRO_CALL_MEMBER( OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_TRAIL_NAMES_CRU, (int)((int)(DAT_GameCore::instance.skirmishTrailProgress + 1))), _fontSize);
                if (0x1bd < _offset) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                        DAT_GameCore::instance.skirmishTrailProgress + 1,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1e,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x1e, OpenSHC::Text::TTA_LEFT,
                        0xccfaff, 0, 0x10, FALSE, 0);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                        DAT_TextManagerObject::ptr)(".", DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1f,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x1e, OpenSHC::Text::TTA_LEFT,
                        0xccfaff, 0, 0x10, TRUE, 0);
                    _offset = DAT_GameCore::instance.skirmishTrailProgress + 1;
                    _titleFontSize = 0x10;
                    goto LAB_004ddfa0;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameCore::instance.skirmishTrailProgress + 1,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1e,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x1e, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0,
                    0xf, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)(".", DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1f,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x1e, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0,
                    0xf, TRUE, 0);
                _offset = DAT_GameCore::instance.skirmishTrailProgress + 1;
            }
            _titleFontSize = 0xf;
        LAB_004ddfa0:
            _blendStrength = 0;
            _titleRetainX = TRUE;
            _titleBG = 0;
            _titleFG = 0xccfaff;
            _titleAlignment = OpenSHC::Text::TTA_LEFT;
            _titleY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x1e;
            _titleX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x23;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_TRAIL_NAMES_CRU, _offset), _titleX, _titleY, (TextAlignment)((int)(_titleAlignment)), _titleFG, _titleBG, _titleFontSize, _titleRetainX, _blendStrength);
            local_108 = local_f4 + 0x21;
            _blendStrength = 0;
            local_10c = local_f4 + 0x1f;
            local_f4[0x1f] = 0;
            local_70[1] = 0;
            local_60 = 0;
            local_54 = 0;
            local_48 = 0;
            local_3c = 0;
            local_30 = 0;
            local_24 = 0;
            local_18 = 0;
            local_c = 0;
            _offset = 1;
            piVar5 = local_f4 + 0x20;
            dVar3 = DAT_GameCore::instance.field22_0x64;
            do {
                if (dVar3 == 1) {
                    bVar8 = DAT_GameSynchronyState::instance.finalResults.active[_offset] == 0;
                LAB_004de064:
                    if (!bVar8)
                        goto LAB_004de066;
                } else {
                    if ((dVar3 == 0) && (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_offset] == -1)) {
                        bVar8 = DAT_GameSynchronyState::instance.currentAIArray[_offset] == 0;
                        goto LAB_004de064;
                    }
                LAB_004de066:
                    *local_10c = _offset;
                    if (dVar3 == 1) {
                        local_f4[_blendStrength + 1] = DAT_GameState::instance.mapAndTime.playerTeams[_offset];
                        iVar6 = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(_offset);
                        dVar3 = DAT_GameCore::instance.field22_0x64;
                        if (iVar6 == 0) {
                            local_10c = local_10c + 3;
                            *piVar5 = 0;
                            *local_108 = 0;
                            _blendStrength = _blendStrength + 1;
                            piVar5 = piVar5 + 3;
                            local_108 = local_108 + 3;
                            local_f4[_offset + 0xb] = 1;
                            goto LAB_004de0d9;
                        }
                    } else {
                        local_f4[_blendStrength + 1] = DAT_GameState::instance.mapAndTime.playerTeams[_offset];
                    }
                    local_10c = local_10c + 3;
                    _blendStrength = _blendStrength + 1;
                    piVar5 = piVar5 + 3;
                    local_108 = local_108 + 3;
                }
            LAB_004de0d9:
                _offset = _offset + 1;
            } while (_offset < 9);
            _offset = 0;
            if (0 < _blendStrength) {
                do {
                    iVar6 = -1;
                    iVar7 = 0;
                    piVar5 = local_f4 + 0x1f;
                    do {
                        if ((*piVar5 != 0) && ((iVar6 == -1 || (local_f4[iVar7 + 1] < local_f4[0])))) {
                            local_f4[0] = local_f4[iVar7 + 1];
                            iVar6 = iVar7;
                        }
                        iVar7 = iVar7 + 1;
                        piVar5 = piVar5 + 3;
                    } while (iVar7 < _blendStrength);
                    if (iVar6 < 0)
                        break;
                    local_f4[_offset + 0x16] = local_f4[iVar6 * 3 + 0x1f];
                    _offset = _offset + 1;
                    local_f4[iVar6 * 3 + 0x1f] = 0;
                } while (_offset < _blendStrength);
            }
            local_108 = (int*)(iVar1 + 0x152);
            _offset = 1;
            local_10c = (int*)(_textX_01 + 0x22);
            local_f4[0] = 1;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            local_104 = iVar4;
            do {
                if (1 < _offset) {
                    _textY_01 = _textY_01 + 0x16;
                    local_108 = (int*)((int)local_108 + 0x16);
                    local_104 = local_104 + 0x50;
                    local_10c = (int*)((int)local_10c + 0x50);
                }
                _blendStrength = local_f4[_offset + 0x15];
                if (_blendStrength < 1) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    return;
                }
                if (local_f4[0] < local_f4[_blendStrength]) {
                    local_f4[0] = local_f4[_blendStrength];
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x240, local_104, iVar1 + 0x117);
                    local_104 = local_104 + 0x24;
                    local_10c = (int*)((int)local_10c + 0x24);
                }
                if ((local_f4[_blendStrength + 0xb] != 0)
                    && ((int)(DAT_GameCore::instance.section1127 + 200) < (int)DAT_GameCore::instance.mapTimeInTicks)) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x299, iVar4, (int)((int)(local_108)));
                }
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderPlayerAvatars)(_blendStrength, local_104, iVar13);
                if ((local_f4[_blendStrength + 0xb] != 0)
                    && ((int)(DAT_GameCore::instance.section1127 + 200) < (int)DAT_GameCore::instance.mapTimeInTicks)) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                        (int)local_10c, iVar1 + 0x100, local_104 + 0x45, iVar1 + 0x143);
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x299, (int)((int)(local_10c)), iVar1 + 0x100);
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)(DAT_GameSynchronyState::instance.DAT_PlayerNames[_blendStrength],
                    _textX_01 + 0x4c, _textY_01, OpenSHC::Text::TTA_LEFT,
                    (uint)((int)(DAT_RenderingDefinedData::instance
                            .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[_blendStrength]])),
                    0, 0x12, FALSE, 0);
                iVar6 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2,
                    _blendStrength + 0x1d5, _textX_01 + 0x34, (int)((int)(local_108)),
                    ((int)(iVar6 + (iVar6 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                _offset = _offset + 1;
            } while (_offset < 9);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            return;
        }

    }
}
}
