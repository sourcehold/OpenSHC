/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Rendering.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        void __cdecl DrawOuterMenuBorder();

        void __cdecl RenderScribeFrame();

        void __cdecl RenderGoldValue();

        void __cdecl TransformAndRenderPercentage(int xPos, int yPos, int valueUnk, BOOLEnum otherImageFlagUnk);

        void __cdecl RenderPeasantMenu_CurrentActionUnk(int unitID, int xPos, int yPos);

        void __cdecl DisplayMapDescriptionAndAllocatePlayersToSlots();

        void __cdecl InitBlendFilterArraysUnk();

        void __cdecl RenderTerrainTilesCenterPiece();

        void __cdecl RenderCurrentNotActiveButtonWithPossibleAlphaTexOnCurrentSurfaceUnk();

        void __cdecl RenderButtonImageWithBlending();

        void __cdecl RenderCurrentButtonOnScreenMenu();

        void __cdecl RenderCurrentButtonToScreenMenuWithBlendingUnk(int blendStrengthUnk);

        uint __cdecl TransformToCurrentModeColor(int red, int green, int blue);

        void __cdecl RenderLoadAndSaveBar(int progressValueUnk);

        void __cdecl RenderScenarioButtonWithText(int textNumInGroup);

        void __cdecl RenderAnimatedTutorialFloatOverlay(int param_1, int param_2);

        void __cdecl RenderTutorialFloatForUIElement(int param_1);

        void __cdecl RenderGreatestLordScreen();

        int __cdecl RenderMissionObjectivesUnk();

        void __cdecl RenderPlayerAvatars(int imageID, int x, int y);

        void __cdecl RenderGfxHelperUnk(int loadedGfxIndex, int xPosInMenuRect, int yPosInMenuRect);

        void __cdecl RenderMenuGfxHelper(int gfxIndex, int x, int y, int blendStrength);

        void __cdecl DrawLoadedMenuStringHelper(int loadedMenuStringIndex, int xPos, int yPos, int maxWidth, uint color,
            int fontSize, BOOLEnum isSingleLine);

        void __cdecl DrawLoadedMenuStringHelperWithBlending(int loadedMenuStringIndex, int xPos, int yPos, int maxWidth,
            uint color, int fontSize, BOOLEnum isSingleLine, int blendStrength);

        void __cdecl RenderTextPageProgressBar();

        void __cdecl DisplayFullScreenTextPage(int param_1);

        void __cdecl RenderHistoryBookEdgeUnk();

        void __cdecl RenderNoViewsFoundWarning();

        void __cdecl RenderCurrentMenuView();

    } // namespace Rendering
} // namespace UI
} // namespace OpenSHC
