#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/UI/BuildingMenus.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/UI/StatusMenus.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eInBuildingModes.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_MAGENTA.hpp"
#include "OpenSHC/Globals/DAT_00b96108.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::DE::SHCDE::eGM;
        using OpenSHC::Rendering::ScreenResolutionEnum;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004494E0
        void BuildingAndStatusMenu::MenuView_BuildingAndStatusMenu_DoEveryFrame()
        {
            int drawY;
            int imageID;
            int drawX;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_640x480) {
                drawY = DAT_MenuHandlerState::instance.y + 0x1d8;
                imageID = 3;
                drawX = 0;
            } else if (DAT_GameCore::instance.activeMenuTab.tabType
                == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(DAT_MenuHandlerState::instance.x,
                    DAT_MenuHandlerState::instance.y + 0x195, DAT_MenuHandlerState::instance.x + 799,
                    DAT_MenuHandlerState::instance.y + 0x1d7, (ushort)((int)(COL_MAGENTA::instance.shortValue)));
                drawY = DAT_MenuHandlerState::instance.y + 0x195;
                imageID = 4;
                drawX = DAT_MenuHandlerState::instance.x;
            } else if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_MERCENARYPOST) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(DAT_MenuHandlerState::instance.x,
                    DAT_MenuHandlerState::instance.y + 0x195, DAT_MenuHandlerState::instance.x + 799,
                    DAT_MenuHandlerState::instance.y + 0x1d7, (ushort)((int)(COL_MAGENTA::instance.shortValue)));
                drawY = DAT_MenuHandlerState::instance.y + 0x195;
                imageID = 6;
                drawX = DAT_MenuHandlerState::instance.x;
            } else {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(DAT_MenuHandlerState::instance.x,
                    DAT_MenuHandlerState::instance.y + 0x196, DAT_MenuHandlerState::instance.x + 799,
                    DAT_MenuHandlerState::instance.y + 0x1d7, (ushort)((int)(COL_MAGENTA::instance.shortValue)));
                drawY = DAT_MenuHandlerState::instance.y + 0x1b9;
                imageID = 2;
                drawX = DAT_MenuHandlerState::instance.x;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_PANELS, imageID, drawX, drawY);
            if (DAT_00b96108::instance != 0) {
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
                    0, DAT_MenuHandlerState::instance.x + 0xe, DAT_MenuHandlerState::instance.y + 0x1e9);
            }
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            switch (DAT_GameCore::instance.activeMenuTab.inBuildingTab) {
            case OpenSHC::DE::SHCDE::IBM_INSIDE_BARRACKS:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_RecruitingBuilding)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_KEEP:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Keep)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_INN:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Inn)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_GRANARY:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Granary)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_HOUSE:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_House)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_WOODCUTTERS_HUT:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_WoodcutterShut)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_OXEN_BASE:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_OxThether)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_IRON_MINE:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Ironmine)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_PITCH_DIGGER:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_PitchRig)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_HUNTERS_HUT:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_HuntersHut)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_GOODS_YARD:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Stockpile)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_ARMOURY:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Armory)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_FLETCHERS_WORKSHOP:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Fletcher)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_BLACKSMITHS_WORKSHOP:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Blacksmith)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_POLETURNERS_WORKSHOP:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Poleturner)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_ARMOURERS_WORKSHOP:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Armourer)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_TANNERS_WORKSHOP:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Tanner)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_BAKERS_WORKSHOP:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Bakery)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_BREWERS_WORKSHOP:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Brewery)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_QUARRY:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Quarry)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_QUARRYPILE:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Quarry_Stonepile)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_HEALERS:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Apothecary)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_ENGINEERS_GUILD:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Engineersguild)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_TUNNELLERS_GUILD:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Tunnelersguild)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_TRADEPOST:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Marketplace)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_WELL:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Well)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_OIL_SMELTER:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Oilsmelter)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_WHEATFARM:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Wheatfarm)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_HOPSFARM:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Hopfarm)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_APPLEFARM:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Applefarm)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_CATTLEFARM:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Diaryfarm)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_MILL:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Mill)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_STABLES:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Stables)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_CHURCH:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_ChapelAndChurch)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_GATEHOUSE:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Gatehouse)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_DRAWBRIDGE:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Drawbridge)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_POSTERN_GATE:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Unused_PosternGate)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_TUNNEL_ENTERANCE:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_TunnelEntrance)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_WATERPOT:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_WaterPot)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_SIGNPOST:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Signpost)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_KILLING_PIT:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_KillingPit)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_CAMPGROUND:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Campfire)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_MERCPOST:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_RecruitingBuilding)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_OUTPOST:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Outpost)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_TOWER:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Tower)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_GALLOWS:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Gallows)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_STOCKS:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Stocks)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_WITCH_HOIST:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Unused_Witchhoist)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_MAYPOLE:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Maypole)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_GARDEN:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Gardens)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_PARADEGROUND:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_TrainingGrounds)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_TRADEPOST_PRICES:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Marketplace_Stonks)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_TRADEPOST_FOOD:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Marketplace_Food)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_TRADEPOST_BULK:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Marketplace_Resource)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_TRADEPOST_ARMS:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Marketplace_Weapons)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_TRADEPOST_DO_THE_TRADE:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Marketplace_Trade)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_CATAPULT:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Siegetent_Catapult)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_TREBUCHET:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Siegetent_Trebuchet)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_SIEGE_TOWER:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Siegetent_Siegetower)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_BATTERING_RAM:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Siegetent_BatteringRam)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_PORTABLE_SHIELD:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Siegetent_Shield)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_CHIMP:
                MACRO_CALL(OpenSHC::UI::StatusMenus_Func::RenderStatusMenu_Chimp)();
                break;
            case OpenSHC::DE::SHCDE::IBM_SUB_MODE_REPORTS:
                MACRO_CALL(OpenSHC::UI::StatusMenus_Func::RenderStatusMenu_Overview)();
                break;
            case OpenSHC::DE::SHCDE::IBM_SUB_MODE_REPORTS_POPULARITY:
                MACRO_CALL(OpenSHC::UI::StatusMenus_Func::RenderStatusMenu_Popularity)();
                break;
            case OpenSHC::DE::SHCDE::IBM_SUB_MODE_REPORTS_FEARFACTOR:
                MACRO_CALL(OpenSHC::UI::StatusMenus_Func::RenderStatusMenu_FearFactor)();
                break;
            case OpenSHC::DE::SHCDE::IBM_SUB_MODE_REPORTS_POPULATION:
                MACRO_CALL(OpenSHC::UI::StatusMenus_Func::RenderStatusMenu_Population)();
                break;
            case OpenSHC::DE::SHCDE::IBM_SUB_MODE_REPORTS_FOOD:
                MACRO_CALL(OpenSHC::UI::StatusMenus_Func::RenderStatusMenu_Food)();
                break;
            case OpenSHC::DE::SHCDE::IBM_SUB_MODE_REPORTS_ARMY:
                MACRO_CALL(OpenSHC::UI::StatusMenus_Func::RenderStatusMenu_Army)();
                break;
            case OpenSHC::DE::SHCDE::IBM_SUB_MODE_REPORTS_STORES:
                MACRO_CALL(OpenSHC::UI::StatusMenus_Func::RenderStatusMenu_Resources)();
                break;
            case OpenSHC::DE::SHCDE::IBM_SUB_MODE_REPORTS_WEAPONS:
                MACRO_CALL(OpenSHC::UI::StatusMenus_Func::RenderStatusMenu_Weapons)();
                break;
            case OpenSHC::DE::SHCDE::IBM_SUB_MODE_REPORTS_RELIGION:
                MACRO_CALL(OpenSHC::UI::StatusMenus_Func::RenderStatusMenu_Religion)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_CESS_PIT:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_CessPit)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_BURNING_STAKE:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_BurningStake)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_GIBBET:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Gibbet)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_DUNGEON:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Dungeon)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_STRETCHING_RACK:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_StretchingRack)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_FLOGGING_RACK:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Unused_FloggingRack)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_CHOPPING_BLOCK:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_ChoppingBlock)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_DUNKING_STOOL:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_DunkingStool)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_DOG_CAGE:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_DogCage)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_STATUE:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Statue)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_SHRINE:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Shrine)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_BEEHIVE:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Unused_BeeHive)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_DANCING_BEAR:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_DancingBear)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_POND:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Unused_Pond)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_BEAR_CAVE:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Unused_BearCave)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_ARAB_BALLISTA:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Siegetent_Fireballista)();
                break;
            case OpenSHC::DE::SHCDE::IBM_INSIDE_CATHEDRAL:
                MACRO_CALL(OpenSHC::UI::BuildingMenus_Func::RenderBuildingMenu_Cathedral)();
            }
            DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 2;
            if (((DAT_GameCore::instance.isBinkVideoPlaying == 0)
                    && (DAT_BuildingsState::instance.DAT_IsBuildingOrPeasantBinkPlaying == FALSE))
                && (DAT_WindowAndDirectDraw::instance.currentGameResolution != OpenSHC::Rendering::SRE_640x480)) {
                DAT_MinimapViewState::instance.field0_0x0 = 1;
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapMain, DAT_MinimapViewState::ptr)();
            }
        }

    }
}
}
