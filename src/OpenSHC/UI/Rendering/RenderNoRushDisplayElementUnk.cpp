#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"



#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/COL_DARK_LIME.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace UI {

using OpenSHC::Text::TextAlignment;
using OpenSHC::WindowsHelper::Enums::BOOLEnum;
using OpenSHC::UI::Enums::DisplayElementID;
using OpenSHC::DE::SHCDE::eTextSections;
using OpenSHC::Rendering::Enums::RenderTarget;
using OpenSHC::Rendering::ScreenResolutionEnum;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004B20B0
void Rendering::RenderNoRushDisplayElementUnk(int posX,int posY,DWORD elementState)

{
char *pcVar1;
int left;
int iVar2;
int iVar3;
int xParam;
int yParam;
TextAlignment alignment;
uint foregroundColor;
uint backgroundColor;
int fontSize;
BOOLEnum keepOffsetX;
int iVar4;
int blendStrength;

if (DAT_GameState::instance.mapAndTime.skirmishNoRushTicks == 0) {
/* 
  Plays pa paam pa pa pa paam
 */

MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)("battlehorn.wav");
MACRO_CALL(OpenSHC::UI::Helpers_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(OpenSHC::UI::Enums::DEID_NO_RUSH, 0);
return;
}
iVar4 = 0x12;
pcVar1 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_MISC, 7);
iVar4 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(pcVar1, iVar4);
iVar2 = posX + 800;
DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
iVar2 = posX + 0x390;
goto LAB_004b21ab;
}
if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
LAB_004b212c:
iVar2 = posX + 0x230;
}
else {
if (DAT_WindowAndDirectDraw::instance.currentGameResolution != OpenSHC::Rendering::SRE_1600x1200) {
if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x720) goto LAB_004b212c;
if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1440x900) {
iVar2 = posX + 0x1e0;
goto LAB_004b21ab;
}
if ((DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1080) ||
(DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1200)) {
iVar2 = posX + 0xf0;
goto LAB_004b21ab;
}
if ((DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) ||
(DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1600)) {
iVar2 = posX + -0x50;
goto LAB_004b21ab;
}
if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1366x768) {
iVar2 = posX + 0x205;
goto LAB_004b21ab;
}
if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1680x1050) {
iVar2 = posX + 0x168;
goto LAB_004b21ab;
}
if (DAT_WindowAndDirectDraw::instance.currentGameResolution != OpenSHC::Rendering::SRE_1600x900) {
if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x600) {
iVar2 = posX + 0x2b0;
}
else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1360x768) {
iVar2 = posX + 0x208;
}
goto LAB_004b21ab;
}
}
iVar2 = posX + 400;
}
LAB_004b21ab:
iVar3 = (iVar4 + 0x32) / 2;
iVar2 = iVar2 + (-0x12 - iVar3);
left = iVar2 - iVar3;
MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox, DAT_PencilRenderCore::ptr)(left + -7, posY + -5, iVar3 + 5 + iVar2, posY + 0x1e, 0x10);
blendStrength = 0;
keepOffsetX = FALSE;
fontSize = 0x12;
backgroundColor = 0;
foregroundColor = 0xc2f0eb;
alignment = OpenSHC::Text::TTA_CENTER;
xParam = iVar2;
yParam = posY;
pcVar1 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_MISC, 7);
MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(pcVar1, xParam, yParam, alignment, foregroundColor, backgroundColor, 
fontSize, keepOffsetX, blendStrength);
MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(left + -1, posY + 0x12, iVar3 + 1 + iVar2, posY + 0x18, (ushort)((int)(
COL_BLACK::instance.shortValue)));
MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(left, posY + 0x13, 
((DAT_GameState::instance.mapAndTime.skirmishNoRushTicks * (iVar4 + 0x32)) /
DAT_GameState::instance.mapAndTime.skirmishNoRushTicksLeft - iVar3) + iVar2, posY + 0x17, (ushort)((int)(
COL_DARK_LIME::instance.shortValue)));
DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
return;
}


}
}