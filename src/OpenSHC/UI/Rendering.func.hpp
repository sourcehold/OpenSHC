/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Rendering.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/Rendering.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace Rendering_Func {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00424BE0, &OpenSHC::UI::Rendering::DrawOuterMenuBorder)
        DrawOuterMenuBorder;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00433260, &OpenSHC::UI::Rendering::RenderScribeFrame)
        RenderScribeFrame;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00433780, &OpenSHC::UI::Rendering::RenderGoldValue)
        RenderGoldValue;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int xPos, int yPos, int valueUnk, BOOLEnum otherImageFlagUnk), false,
            Address::SHC_3BB0A8C1_0x00433C20, &OpenSHC::UI::Rendering::TransformAndRenderPercentage)
        TransformAndRenderPercentage;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int unitID, int xPos, int yPos), false, Address::SHC_3BB0A8C1_0x0043CC30,
            &OpenSHC::UI::Rendering::RenderPeasantMenu_CurrentActionUnk)
        RenderPeasantMenu_CurrentActionUnk;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004410D0,
            &OpenSHC::UI::Rendering::DisplayMapDescriptionAndAllocatePlayersToSlots)
        DisplayMapDescriptionAndAllocatePlayersToSlots;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0044E510,
            &OpenSHC::UI::Rendering::InitBlendFilterArraysUnk)
        InitBlendFilterArraysUnk;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00452900,
            &OpenSHC::UI::Rendering::RenderTerrainTilesCenterPiece)
        RenderTerrainTilesCenterPiece;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004640D0,
            &OpenSHC::UI::Rendering::RenderCurrentNotActiveButtonWithPossibleAlphaTexOnCurrentSurfaceUnk)
        RenderCurrentNotActiveButtonWithPossibleAlphaTexOnCurrentSurfaceUnk;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004641A0,
            &OpenSHC::UI::Rendering::RenderButtonImageWithBlending)
        RenderButtonImageWithBlending;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00464300,
            &OpenSHC::UI::Rendering::RenderCurrentButtonOnScreenMenu)
        RenderCurrentButtonOnScreenMenu;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int blendStrengthUnk), false, Address::SHC_3BB0A8C1_0x00464370,
            &OpenSHC::UI::Rendering::RenderCurrentButtonToScreenMenuWithBlendingUnk)
        RenderCurrentButtonToScreenMenuWithBlendingUnk;

        MACRO_FUNCTION_RESOLVER(uint(__cdecl*)(int red, int green, int blue), false, Address::SHC_3BB0A8C1_0x00467850,
            &OpenSHC::UI::Rendering::TransformToCurrentModeColor)
        TransformToCurrentModeColor;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int progressValueUnk), false, Address::SHC_3BB0A8C1_0x00493690,
            &OpenSHC::UI::Rendering::RenderLoadAndSaveBar)
        RenderLoadAndSaveBar;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int textNumInGroup), false, Address::SHC_3BB0A8C1_0x004BA910,
            &OpenSHC::UI::Rendering::RenderScenarioButtonWithText)
        RenderScenarioButtonWithText;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2), false, Address::SHC_3BB0A8C1_0x004BC790,
            &OpenSHC::UI::Rendering::RenderAnimatedTutorialFloatOverlay)
        RenderAnimatedTutorialFloatOverlay;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004BC910,
            &OpenSHC::UI::Rendering::RenderTutorialFloatForUIElement)
        RenderTutorialFloatForUIElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004D5810,
            &OpenSHC::UI::Rendering::RenderGreatestLordScreen)
        RenderGreatestLordScreen;

        MACRO_FUNCTION_RESOLVER(int(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004D76A0,
            &OpenSHC::UI::Rendering::RenderMissionObjectivesUnk)
        RenderMissionObjectivesUnk;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int imageID, int x, int y), false, Address::SHC_3BB0A8C1_0x004D8AE0,
            &OpenSHC::UI::Rendering::RenderPlayerAvatars)
        RenderPlayerAvatars;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int loadedGfxIndex, int xPosInMenuRect, int yPosInMenuRect), false,
            Address::SHC_3BB0A8C1_0x004DA570, &OpenSHC::UI::Rendering::RenderGfxHelperUnk)
        RenderGfxHelperUnk;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int gfxIndex, int x, int y, int blendStrength), false,
            Address::SHC_3BB0A8C1_0x004DA640, &OpenSHC::UI::Rendering::RenderMenuGfxHelper)
        RenderMenuGfxHelper;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int loadedMenuStringIndex, int xPos, int yPos, int maxWidth, uint color,
                                    int fontSize, BOOLEnum isSingleLine),
            false, Address::SHC_3BB0A8C1_0x004DA670, &OpenSHC::UI::Rendering::DrawLoadedMenuStringHelper)
        DrawLoadedMenuStringHelper;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int loadedMenuStringIndex, int xPos, int yPos, int maxWidth, uint color,
                                    int fontSize, BOOLEnum isSingleLine, int blendStrength),
            false, Address::SHC_3BB0A8C1_0x004DA6E0, &OpenSHC::UI::Rendering::DrawLoadedMenuStringHelperWithBlending)
        DrawLoadedMenuStringHelperWithBlending;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004DAFB0,
            &OpenSHC::UI::Rendering::RenderTextPageProgressBar)
        RenderTextPageProgressBar;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004DB0D0,
            &OpenSHC::UI::Rendering::DisplayFullScreenTextPage)
        DisplayFullScreenTextPage;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004DB490,
            &OpenSHC::UI::Rendering::RenderHistoryBookEdgeUnk)
        RenderHistoryBookEdgeUnk;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004F4070,
            &OpenSHC::UI::Rendering::RenderNoViewsFoundWarning)
        RenderNoViewsFoundWarning;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004F6210, &OpenSHC::UI::Rendering::RenderCurrentMenuView)
        RenderCurrentMenuView;

    } // namespace Rendering_Func
} // namespace UI
} // namespace OpenSHC
