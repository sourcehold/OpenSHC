#include "../BottomLeftTextDisplayState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_00ee1090.hpp"
#include "OpenSHC/Globals/DAT_00ee1094.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TroopDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {

    using namespace OpenSHC::DE::SHCDE;
    using namespace OpenSHC::Text;
    using namespace OpenSHC::Game::Resources;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F4F60
    void BottomLeftTextDisplayState::renderCurrentlyDisplayedTextConstructionCost(int param_1)
    {
        int const activeMenuTab = DAT_GameCore::instance.activeMenuTab.tabType;
        int const menuViewType = DAT_GameCore::instance.currentMenuViewType;
        if (param_1 == 0 && menuViewType == 16 && (activeMenuTab == 1 || activeMenuTab == 44)) {
            return;
        }
        if (this->currentlyDisplayedTextIsDisplayedUnk == 0) {
            return;
        }
        if (this->currentlyDisplayedTextIsDisplayedUnk != 6 && this->currentlyDisplayedTextIsDisplayedUnk != 12
            && this->currentlyDisplayedTextIsDisplayedUnk != 7 && this->currentlyDisplayedTextIsDisplayedUnk != 13) {
            DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            DAT_ButtonX::instance += DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX;
            DAT_ButtonY::instance += DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY;
        }
        if (menuViewType == 14 && activeMenuTab == 61) {
            DAT_ButtonX::instance += 130;
            DAT_ButtonY::instance -= 2;
        }
        switch (this->currentlyDisplayedTextIsDisplayedUnk) {
        case 6: {
            int const unitIndex = this->currentlyDisplayedUnktextExtraObject.unitsAndWeaponsType;
            if (unitIndex < 10) {
                if (DAT_GameState::instance.mapAndTime.euroRecruitable[unitIndex] == 0) {
                    break;
                }
                MACRO_CALL_MEMBER(TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                    (eTextSections)this->currentlyDisplayedUnkTextGroupIndex_0x4,
                    this->currentlyDisplayedUnkTextNumInGroup_0x8, DAT_ButtonX::instance + 260, DAT_ButtonY::instance,
                    TTA_CENTER, 12119803, 0, 18, FALSE);
                if (DAT_GameSynchronyState::instance.currentGameMode != 0
                    && DAT_GameSynchronyState::instance.skirmishTroopsCostGold == 0) {
                    break;
                }
                MACRO_CALL_MEMBER(TextManager_Func::renderText, DAT_TextManagerObject::ptr)((eTextSections)22, 2,
                    DAT_ButtonX::instance, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0, 18, FALSE);
                MACRO_CALL_MEMBER(TextManager_Func::renderNumber, DAT_TextManagerObject::ptr)(
                    DAT_TroopDefinedData::instance
                        .BarracksUnitCost[this->currentlyDisplayedUnktextExtraObject.unitsAndWeaponsType],
                    DAT_ButtonX::instance + 6, DAT_ButtonY::instance, 12119803, 0, 18, TRUE);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    GM_INTERFACE_ICONS2, 124,
                    DAT_TextManagerObject::instance.currentXOffset_0x0 + DAT_ButtonX::instance + 10,
                    DAT_ButtonY::instance);
            } else {
                if (DAT_GameState::instance.mapAndTime.euroRecruitable[unitIndex - 10] == 0) {
                    break;
                }
                MACRO_CALL_MEMBER(TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                    (eTextSections)this->currentlyDisplayedUnkTextGroupIndex_0x4,
                    this->currentlyDisplayedUnkTextNumInGroup_0x8, DAT_ButtonX::instance, DAT_ButtonY::instance,
                    TTA_LEFT, 12119803, 0, 18, FALSE);
            }
            break;
        }
        case 12:
            if (this->currentlyDisplayedUnktextExtraObject.unitsAndWeaponsType >= 10) {
                break;
            }
            MACRO_CALL_MEMBER(TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                (eTextSections)this->currentlyDisplayedUnkTextGroupIndex_0x4,
                this->currentlyDisplayedUnkTextNumInGroup_0x8, DAT_ButtonX::instance + 260, DAT_ButtonY::instance + 152,
                TTA_CENTER, 12119803, 0, 18, FALSE);
            if (DAT_GameSynchronyState::instance.currentGameMode != 0
                && DAT_GameSynchronyState::instance.skirmishTroopsCostGold == 0) {
                break;
            }
            MACRO_CALL_MEMBER(TextManager_Func::renderText, DAT_TextManagerObject::ptr)((eTextSections)22, 2,
                DAT_ButtonX::instance + 10, DAT_ButtonY::instance + 152, TTA_LEFT, 12119803, 0, 18, FALSE);
            MACRO_CALL_MEMBER(TextManager_Func::renderNumber, DAT_TextManagerObject::ptr)(
                DAT_TroopDefinedData::instance
                    .NonEuroUnitCost[this->currentlyDisplayedUnktextExtraObject.unitsAndWeaponsType],
                DAT_ButtonX::instance + 16, DAT_ButtonY::instance + 152, 12119803, 0, 18, TRUE);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                GM_INTERFACE_ICONS2, 124,
                DAT_TextManagerObject::instance.currentXOffset_0x0 + DAT_ButtonX::instance + 20,
                DAT_ButtonY::instance + 152);
            break;
        case 13:
            if (menuViewType == 20 && DAT_MenuModalComposition1::instance.activeModalDialogID == -1
                && DAT_TextManagerObject::instance.gameLanguage != 0
                && DAT_TextManagerObject::instance.gameLanguage != 1) {
                MACRO_CALL_MEMBER(TextManager_Func::renderMultilineText3Unk, DAT_TextManagerObject::ptr)(
                    (eTextSections)this->currentlyDisplayedUnkTextGroupIndex_0x4,
                    this->currentlyDisplayedUnkTextNumInGroup_0x8, DAT_ButtonX::instance - 50, DAT_ButtonY::instance,
                    DAT_ButtonW::instance + 100, 12119803, 0, 18, 0);
            } else {
                MACRO_CALL_MEMBER(TextManager_Func::renderMultilineText3Unk, DAT_TextManagerObject::ptr)(
                    (eTextSections)this->currentlyDisplayedUnkTextGroupIndex_0x4,
                    this->currentlyDisplayedUnkTextNumInGroup_0x8, DAT_ButtonX::instance, DAT_ButtonY::instance,
                    DAT_ButtonW::instance, 12119803, 0, 18, 0);
            }
            break;
        case 1:
            if (this->currentlyDisplayedUnkTextGroupIndex_0x4 == 8
                && this->currentlyDisplayedUnkTextNumInGroup_0x8 == 202) {
                this->currentlyDisplayedUnkTextNumInGroup_0x8 = DAT_00ee1090::instance;
            }
            if (this->currentlyDisplayedUnkTextGroupIndex_0x4 == 8
                && this->currentlyDisplayedUnkTextNumInGroup_0x8 == 291) {
                this->currentlyDisplayedUnkTextNumInGroup_0x8 = DAT_00ee1094::instance;
            }
            if (this->currentlyDisplayedUnkTextGroupIndex_0x4 == 77) {
                int const height
                    = MACRO_CALL_MEMBER(TextManager_Func::renderMultilineText2, DAT_TextManagerObject::ptr)(
                        (eTextSections)77, this->currentlyDisplayedUnkTextNumInGroup_0x8, 480, 18);
                MACRO_CALL_MEMBER(TextManager_Func::renderMultilineText3Unk, DAT_TextManagerObject::ptr)(
                    (eTextSections)this->currentlyDisplayedUnkTextGroupIndex_0x4,
                    this->currentlyDisplayedUnkTextNumInGroup_0x8, DAT_ButtonX::instance,
                    DAT_ButtonY::instance - height + 24, 480, 12119803, 0, 18, 0);
            } else {
                MACRO_CALL_MEMBER(TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                    (eTextSections)this->currentlyDisplayedUnkTextGroupIndex_0x4,
                    this->currentlyDisplayedUnkTextNumInGroup_0x8, DAT_ButtonX::instance, DAT_ButtonY::instance,
                    TTA_LEFT, 12119803, 0, 18, FALSE);
            }
            break;
        case 10:
            this->currentlyDisplayedUnkTextNumInGroup_0x8
                = DAT_RenderingDefinedData::instance.field_0x525a4[DAT_UnitsState::instance
                        .selectionSlots[this->currentlyDisplayedUnktextExtraObject.unitsAndWeaponsType]];
            if (this->currentlyDisplayedUnkTextNumInGroup_0x8 != 0) {
                MACRO_CALL_MEMBER(TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                    (eTextSections)this->currentlyDisplayedUnkTextGroupIndex_0x4,
                    this->currentlyDisplayedUnkTextNumInGroup_0x8, DAT_ButtonX::instance, DAT_ButtonY::instance,
                    TTA_LEFT, 12119803, 0, 18, FALSE);
            }
            break;
        case 7:
            if (DAT_MenuModalComposition1::instance.activeModalDialogID == -1) {
                if (this->currentlyDisplayedUnkTextNumInGroup_0x8 >= 310
                    && this->currentlyDisplayedUnkTextNumInGroup_0x8 <= 313) {
                    int const height = MACRO_CALL_MEMBER(
                        TextManager_Func::renderMultilineText2, DAT_TextManagerObject::ptr)((eTextSections)7,
                        this->currentlyDisplayedUnkTextNumInGroup_0x8 - 309, DAT_ButtonW::instance, 18);
                    DAT_TextManagerObject::instance.field_0x24 = 1;
                    MACRO_CALL_MEMBER(TextManager_Func::renderMultilineText3Unk, DAT_TextManagerObject::ptr)(
                        (eTextSections)7, this->currentlyDisplayedUnkTextNumInGroup_0x8 - 309, DAT_ButtonX::instance,
                        DAT_ButtonY::instance, DAT_ButtonW::instance, 13433599, 0, 18, 0);
                    DAT_TextManagerObject::instance.field_0x24 = 1;
                    MACRO_CALL_MEMBER(TextManager_Func::renderMultilineText3Unk, DAT_TextManagerObject::ptr)(
                        (eTextSections)250, this->currentlyDisplayedUnkTextNumInGroup_0x8 - 301, DAT_ButtonX::instance,
                        DAT_ButtonY::instance + height, DAT_ButtonW::instance, 13433599, 0, 18, 0);
                    break;
                }
                DAT_TextManagerObject::instance.field_0x24 = 1;
                if (this->currentlyDisplayedUnkTextGroupIndex_0x4 == 8
                    && this->currentlyDisplayedUnkTextNumInGroup_0x8 == 229
                    && DAT_GameCore::instance.directDrawStatus < 1792) {
                    MACRO_CALL_MEMBER(TextManager_Func::renderMultilineText3Unk, DAT_TextManagerObject::ptr)(
                        (eTextSections)this->currentlyDisplayedUnkTextGroupIndex_0x4, 344, DAT_ButtonX::instance,
                        DAT_ButtonY::instance, DAT_ButtonW::instance, 13433599, 0, 18, 0);
                } else {
                    MACRO_CALL_MEMBER(TextManager_Func::renderMultilineText3Unk, DAT_TextManagerObject::ptr)(
                        (eTextSections)this->currentlyDisplayedUnkTextGroupIndex_0x4,
                        this->currentlyDisplayedUnkTextNumInGroup_0x8, DAT_ButtonX::instance, DAT_ButtonY::instance,
                        DAT_ButtonW::instance, 13433599, 0, 17, 0);
                }
            } else {
                this->currentlyDisplayedTextIsDisplayedUnk = 0;
            }
            break;
        case 5:
            MACRO_CALL_MEMBER(TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                (eTextSections)this->currentlyDisplayedUnkTextGroupIndex_0x4,
                this->currentlyDisplayedUnkTextNumInGroup_0x8, DAT_ButtonX::instance, DAT_ButtonY::instance, TTA_LEFT,
                12119803, 0, 18, FALSE);
            break;
        case 2: {
            Map::Buildings::BuildingType const buildingType
                = MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                    DAT_BuildingsState::ptr)(this->currentlyDisplayedUnktextExtraObject.buildingType);
            int stone = DAT_BuildingsState::instance.buildingCosts[buildingType].requiredStone_0x4;
            int wood = DAT_BuildingsState::instance.buildingCosts[buildingType].requiredWood;
            int iron = DAT_BuildingsState::instance.buildingCosts[buildingType].requiredIron_0x8;
            int pitch = DAT_BuildingsState::instance.buildingCosts[buildingType].requiredPitch_0xc;
            int gold = DAT_BuildingsState::instance.buildingCosts[buildingType].requiredGold;
            int const playerID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            int stoneOwned = DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_STONE];
            int goldOwned = DAT_GameState::instance.playerDataArray[playerID].currentResources[RT_GOLD];
            if (MACRO_CALL_MEMBER(
                    Map::Buildings::BuildingsState_Func::hasLessWoodThanTheCostOfAWoodcuttersHutAndNoWoodcutters,
                    DAT_BuildingsState::ptr)(playerID, buildingType)
                != 0) {
                wood = 0;
            }
            if (DAT_GameCore::instance.gameMode_2 == 1) {
                iron = 0;
                gold = 0;
                pitch = 0;
                stone = 0;
                wood = 0;
            } else if (DAT_GameCore::instance.gameMode_2 == Game::GM_SIEGE_THAT) {
                goldOwned
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .startResources[RT_GOLD];
                stoneOwned
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .startResources[RT_STONE];
                pitch = 0;
                iron = 0;
                wood = 0;
                MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::getBuildingCost, DAT_BuildingsState::ptr)(
                    this->currentlyDisplayedUnktextExtraObject.buildingType, &stone, &gold);
            }
            MACRO_CALL_MEMBER(TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                (eTextSections)this->currentlyDisplayedUnkTextGroupIndex_0x4,
                this->currentlyDisplayedUnkTextNumInGroup_0x8, DAT_ButtonX::instance, DAT_ButtonY::instance, TTA_LEFT,
                12119803, 0, 18, FALSE);
            int offset = 30;
            if (wood != 0) {
                MACRO_CALL_MEMBER(TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    wood, DAT_ButtonX::instance + offset, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0, 18, TRUE, 0);
                offset += 2;
                MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    GM_INTERFACE_ICONS2, 126,
                    DAT_TextManagerObject::instance.currentXOffset_0x0 + DAT_ButtonX::instance + offset,
                    DAT_ButtonY::instance - 6);
                offset += 32;
                MACRO_CALL_MEMBER(TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    s_brace_close_005a2778, DAT_ButtonX::instance + offset, DAT_ButtonY::instance, TTA_LEFT, 12119803,
                    0, 18, TRUE, 0);
                MACRO_CALL_MEMBER(TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[RT_WOOD],
                    DAT_ButtonX::instance + offset, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0, 18, TRUE, 0);
                MACRO_CALL_MEMBER(TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    s_brace_open_005a2774, DAT_ButtonX::instance + offset, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0,
                    18, TRUE, 0);
                offset += 30;
            }
            if (stone != 0) {
                MACRO_CALL_MEMBER(TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    stone, DAT_ButtonX::instance + offset, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0, 18, TRUE, 0);
                offset += 2;
                MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    GM_INTERFACE_ICONS2, 123,
                    DAT_TextManagerObject::instance.currentXOffset_0x0 + DAT_ButtonX::instance + offset,
                    DAT_ButtonY::instance - 4);
                offset += 32;
                MACRO_CALL_MEMBER(TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    s_brace_close_005a2778, DAT_ButtonX::instance + offset, DAT_ButtonY::instance, TTA_LEFT, 12119803,
                    0, 18, TRUE, 0);
                MACRO_CALL_MEMBER(TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(stoneOwned,
                    DAT_ButtonX::instance + offset, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0, 18, TRUE, 0);
                MACRO_CALL_MEMBER(TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    s_brace_open_005a2774, DAT_ButtonX::instance + offset, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0,
                    18, TRUE, 0);
                offset += 30;
            }
            if (iron != 0) {
                MACRO_CALL_MEMBER(TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    iron, DAT_ButtonX::instance + offset, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0, 18, TRUE, 0);
                offset += 2;
                MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    GM_INTERFACE_ICONS2, 125,
                    DAT_TextManagerObject::instance.currentXOffset_0x0 + DAT_ButtonX::instance + offset,
                    DAT_ButtonY::instance - 4);
                offset += 32;
                MACRO_CALL_MEMBER(TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    s_brace_close_005a2778, DAT_ButtonX::instance + offset, DAT_ButtonY::instance, TTA_LEFT, 12119803,
                    0, 18, TRUE, 0);
                MACRO_CALL_MEMBER(TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[RT_IRON],
                    DAT_ButtonX::instance + offset, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0, 18, TRUE, 0);
                MACRO_CALL_MEMBER(TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    s_brace_open_005a2774, DAT_ButtonX::instance + offset, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0,
                    18, TRUE, 0);
                offset += 30;
            }
            if (pitch != 0) {
                MACRO_CALL_MEMBER(TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    pitch, DAT_ButtonX::instance + offset, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0, 18, TRUE, 0);
                offset += 2;
                MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    GM_INTERFACE_ICONS2, 155,
                    DAT_TextManagerObject::instance.currentXOffset_0x0 + DAT_ButtonX::instance + offset,
                    DAT_ButtonY::instance - 10);
                offset += 26;
                MACRO_CALL_MEMBER(TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    s_brace_close_005a2778, DAT_ButtonX::instance + offset, DAT_ButtonY::instance, TTA_LEFT, 12119803,
                    0, 18, TRUE, 0);
                MACRO_CALL_MEMBER(TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[RT_PITCH],
                    DAT_ButtonX::instance + offset, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0, 18, TRUE, 0);
                MACRO_CALL_MEMBER(TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    s_brace_open_005a2774, DAT_ButtonX::instance + offset, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0,
                    18, TRUE, 0);
                offset += 10;
            }
            if (gold != 0) {
                MACRO_CALL_MEMBER(TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    gold, DAT_ButtonX::instance + offset, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0, 18, TRUE, 0);
                offset += 2;
                MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    GM_INTERFACE_ICONS2, 124,
                    DAT_TextManagerObject::instance.currentXOffset_0x0 + DAT_ButtonX::instance + offset,
                    DAT_ButtonY::instance + 6);
                offset += 32;
                MACRO_CALL_MEMBER(TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    s_brace_close_005a2778, DAT_ButtonX::instance + offset, DAT_ButtonY::instance, TTA_LEFT, 12119803,
                    0, 18, TRUE, 0);
                MACRO_CALL_MEMBER(TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(goldOwned,
                    DAT_ButtonX::instance + offset, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0, 18, TRUE, 0);
                MACRO_CALL_MEMBER(TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    s_brace_open_005a2774, DAT_ButtonX::instance + offset, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0,
                    18, TRUE, 0);
            }
            break;
        }
        case 4:
            MACRO_CALL_MEMBER(TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                (eTextSections)this->currentlyDisplayedUnkTextGroupIndex_0x4,
                this->currentlyDisplayedUnkTextNumInGroup_0x8, DAT_ButtonX::instance, DAT_ButtonY::instance, TTA_LEFT,
                12119803, 0, 18, FALSE);
            MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                GM_INTERFACE_ICONS2, 123,
                DAT_TextManagerObject::instance.currentXOffset_0x0 + DAT_ButtonX::instance + 30,
                DAT_ButtonY::instance - 4);
            MACRO_CALL_MEMBER(TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                s_brace_close_005a2778, DAT_ButtonX::instance + 62, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0, 18,
                TRUE, 0);
            if (DAT_GameCore::instance.gameMode_2 == Game::GM_SIEGE_THAT) {
                MACRO_CALL_MEMBER(TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .startResources[RT_STONE],
                    DAT_ButtonX::instance + 62, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0, 18, TRUE, 0);
            } else {
                MACRO_CALL_MEMBER(TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[RT_STONE],
                    DAT_ButtonX::instance + 62, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0, 18, TRUE, 0);
            }
            MACRO_CALL_MEMBER(TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                s_brace_open_005a2774, DAT_ButtonX::instance + 62, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0, 18,
                TRUE, 0);
            break;
        case 9:
            MACRO_CALL_MEMBER(TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                (eTextSections)this->currentlyDisplayedUnkTextGroupIndex_0x4,
                this->currentlyDisplayedUnkTextNumInGroup_0x8, DAT_ButtonX::instance, DAT_ButtonY::instance, TTA_LEFT,
                12119803, 0, 18, FALSE);
            MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                GM_INTERFACE_ICONS2, 126,
                DAT_TextManagerObject::instance.currentXOffset_0x0 + DAT_ButtonX::instance + 30,
                DAT_ButtonY::instance - 4);
            MACRO_CALL_MEMBER(TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                s_brace_close_005a2778, DAT_ButtonX::instance + 62, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0, 18,
                TRUE, 0);
            MACRO_CALL_MEMBER(TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .currentResources[RT_WOOD],
                DAT_ButtonX::instance + 62, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0, 18, TRUE, 0);
            MACRO_CALL_MEMBER(TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                s_brace_open_005a2774, DAT_ButtonX::instance + 62, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0, 18,
                TRUE, 0);
            break;
        case 11: {
            int cost = 0;
            switch (this->currentlyDisplayedUnktextExtraObject.unitsAndWeaponsType) {
            case 0:
            case 2:
                cost = 30;
                break;
            case 1:
                cost = 4;
                break;
            case 3:
                cost = 10;
                break;
            }
            MACRO_CALL_MEMBER(TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                (eTextSections)this->currentlyDisplayedUnkTextGroupIndex_0x4,
                this->currentlyDisplayedUnkTextNumInGroup_0x8, DAT_ButtonX::instance, DAT_ButtonY::instance, TTA_LEFT,
                12119803, 0, 18, FALSE);
            MACRO_CALL_MEMBER(TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                cost, DAT_ButtonX::instance + 30, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0, 18, TRUE, 0);
            MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                GM_INTERFACE_ICONS2, 124,
                DAT_TextManagerObject::instance.currentXOffset_0x0 + DAT_ButtonX::instance + 32,
                DAT_ButtonY::instance - 4);
            MACRO_CALL_MEMBER(TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                s_brace_close_005a2778, DAT_ButtonX::instance + 64, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0, 18,
                TRUE, 0);
            MACRO_CALL_MEMBER(TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .currentResources[RT_GOLD],
                DAT_ButtonX::instance + 64, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0, 18, TRUE, 0);
            MACRO_CALL_MEMBER(TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                s_brace_open_005a2774, DAT_ButtonX::instance + 64, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0, 18,
                TRUE, 0);
            break;
        }
        case 3: {
            int const scroll = this->countdown / 15 + DAT_ButtonW::instance;
            if (this->currentlyDisplayedUnkTextNumInGroup_0x8 == 1) {
                MACRO_CALL_MEMBER(TextManager_Func::setTextClipRange, DAT_TextManagerObject::ptr)(
                    DAT_ButtonX::instance + 20, DAT_ButtonX::instance + DAT_ButtonW::instance);
                int const crowding
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .crowding;
                int textOffset;
                if (crowding <= 30) {
                    textOffset = 2;
                } else {
                    textOffset = crowding <= 70;
                }
                MACRO_CALL_MEMBER(TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                    (eTextSections)this->currentlyDisplayedUnkTextGroupIndex_0x4,
                    this->currentlyDisplayedUnkTextNumInGroup_0x8 + textOffset, DAT_ButtonX::instance + scroll,
                    DAT_ButtonY::instance, TTA_LEFT, 12119803, 0, 18, FALSE);
                int percentage;
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentPopulation
                    == 0) {
                    percentage = 0;
                } else {
                    int const crowdingNow
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .crowding;
                    if (crowdingNow <= 100) {
                        percentage = 0;
                    } else if (crowdingNow <= 120) {
                        percentage = -50;
                    } else if (crowdingNow <= 140) {
                        percentage = -100;
                    } else if (crowdingNow <= 160) {
                        percentage = -150;
                    } else if (crowdingNow <= 180) {
                        percentage = -200;
                    } else {
                        percentage = -250;
                    }
                }
                int const percentageX
                    = DAT_TextManagerObject::instance.currentXOffset_0x0 + DAT_ButtonX::instance + scroll + 28;
                if (percentageX + 20 > DAT_TextManagerObject::instance.textClipMin
                    && percentageX < DAT_TextManagerObject::instance.textClipMax) {
                    MACRO_CALL(Rendering_Func::TransformAndRenderPercentage)(
                        percentageX, DAT_ButtonY::instance, percentage, FALSE);
                }
                MACRO_CALL_MEMBER(
                    Rendering::TextureRenderCore_Func::renderGMWithAlphaMask, DAT_TextureRenderCoreObject::ptr)(
                    IO::Graphics::GID_INTERFACE_ICONS_2, 206, 124, 578, IO::Graphics::GID_INTERFACE_ICONS_2, 208, 0);
                MACRO_CALL_MEMBER(
                    Rendering::TextureRenderCore_Func::renderGMWithAlphaMask, DAT_TextureRenderCoreObject::ptr)(
                    IO::Graphics::GID_INTERFACE_ICONS_2, 207, 522, 578, IO::Graphics::GID_INTERFACE_ICONS_2, 209, 0);
                if (scroll < -300) {
                    this->countdown = 0;
                }
                MACRO_CALL_MEMBER(TextManager_Func::resetTextClipRange, DAT_TextManagerObject::ptr)();
            } else if (this->currentlyDisplayedUnkTextNumInGroup_0x8 == 4) {
                int textOffset;
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .storedPopularityPercent
                    > DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .popularity) {
                    textOffset = 0;
                } else if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                               .storedPopularityPercent
                    < DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .popularity) {
                    textOffset = 2;
                } else {
                    textOffset = 1;
                }
                MACRO_CALL_MEMBER(TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                    (eTextSections)this->currentlyDisplayedUnkTextGroupIndex_0x4, textOffset + 4, DAT_ButtonX::instance,
                    DAT_ButtonY::instance, TTA_LEFT, 12119803, 0, 18, FALSE);
            }
            break;
        }
        case 8: {
            int const woodCost = DAT_BuildingsState::instance.INT_SelectedBuildingStoneWoodCost;
            int const stoneCost = DAT_BuildingsState::instance.INT_SelectedBuildingStoneRepairCost;
            MACRO_CALL_MEMBER(TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                (eTextSections)this->currentlyDisplayedUnkTextGroupIndex_0x4,
                this->currentlyDisplayedUnkTextNumInGroup_0x8, DAT_ButtonX::instance, DAT_ButtonY::instance, TTA_LEFT,
                12119803, 0, 18, FALSE);
            int offset = 30;
            if (woodCost != 0) {
                MACRO_CALL_MEMBER(TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(woodCost,
                    DAT_ButtonX::instance + offset, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0, 18, TRUE, 0);
                offset += 2;
                MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    GM_INTERFACE_ICONS2, 126,
                    DAT_TextManagerObject::instance.currentXOffset_0x0 + DAT_ButtonX::instance + offset,
                    DAT_ButtonY::instance - 6);
                offset += 32;
                MACRO_CALL_MEMBER(TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    s_brace_close_005a2778, DAT_ButtonX::instance + offset, DAT_ButtonY::instance, TTA_LEFT, 12119803,
                    0, 18, TRUE, 0);
                MACRO_CALL_MEMBER(TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[RT_WOOD],
                    DAT_ButtonX::instance + offset, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0, 18, TRUE, 0);
                MACRO_CALL_MEMBER(TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    s_brace_open_005a2774, DAT_ButtonX::instance + offset, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0,
                    18, TRUE, 0);
                offset += 30;
            }
            if (stoneCost != 0) {
                MACRO_CALL_MEMBER(TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(stoneCost,
                    DAT_ButtonX::instance + offset, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0, 18, TRUE, 0);
                offset += 2;
                MACRO_CALL_MEMBER(Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    GM_INTERFACE_ICONS2, 123,
                    DAT_TextManagerObject::instance.currentXOffset_0x0 + DAT_ButtonX::instance + offset,
                    DAT_ButtonY::instance - 4);
                offset += 32;
                MACRO_CALL_MEMBER(TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    s_brace_close_005a2778, DAT_ButtonX::instance + offset, DAT_ButtonY::instance, TTA_LEFT, 12119803,
                    0, 18, TRUE, 0);
                MACRO_CALL_MEMBER(TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[RT_STONE],
                    DAT_ButtonX::instance + offset, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0, 18, TRUE, 0);
                MACRO_CALL_MEMBER(TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    s_brace_open_005a2774, DAT_ButtonX::instance + offset, DAT_ButtonY::instance, TTA_LEFT, 12119803, 0,
                    18, TRUE, 0);
            }
            break;
        }
        }
        DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
    }

} // namespace UI
} // namespace OpenSHC
