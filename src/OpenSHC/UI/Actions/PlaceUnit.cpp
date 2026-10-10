#include "../Actions.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {

    using Commands::MappersEnum;
    using Game::GameMode2;
    using Game::Resources::ResourceType;
    using IO::Graphics::GmID;
    using Map::Units::SomeTribeBehaviorType;
    using Map::Units::UnitType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004381D0
    void Actions::PlaceUnit()
    {
        dword tribeID;
        int iVar1;
        int _tile;
        int iVar2;
        int iVar3;
        UnitType _unitType;
        GmID _gmID;
        bool bVar4;
        GmID local_1c;
        uint local_18;
        int local_10;
        GmID local_8;
        int local_4;
        if (DAT_TileMapState::instance.DAT_ClickedTileX < 400 && DAT_TileMapState::instance.DAT_ClickedTileY < 400
            && *(char*)(DAT_TileMapState::instance.DAT_ClickedTileY * 400 + 0x21aec98
                   + DAT_TileMapState::instance.DAT_ClickedTileX)
                != '\0') {
            _tile = DAT_ViewportRenderState::instance.translationMatrix[DAT_TileMapState::instance.DAT_ClickedTileY]
                        .addXgetTile
                + DAT_TileMapState::instance.DAT_ClickedTileX;
            iVar3 = -1;
            iVar2 = -1;
            _unitType = ((UnitType)0xffffffff);
            local_10 = 1;
            bVar4 = true;
            local_18 = 0x40501481;
            switch (DAT_TileMapState::instance.currentMapperCommand) {
            case Commands::M_MAPPER_PEOPLE_ARCHERS:
                _gmID = IO::Graphics::GID_BODY_ARCHER;
                iVar2 = 3;
                _unitType = Map::Units::UT_E_ARCHER;
                break;
            case Commands::M_MAPPER_PEOPLE_SPEARMEN:
                _gmID = IO::Graphics::GID_BODY_SPEARMAN;
                iVar2 = 5;
                _unitType = Map::Units::UT_E_SPEAR;
                break;
            case Commands::M_MAPPER_PEOPLE_PIKEMEN:
                _gmID = IO::Graphics::GID_BODY_PIKEMAN;
                iVar2 = 6;
                _unitType = Map::Units::UT_E_PIKE;
                break;
            case Commands::M_MAPPER_PEOPLE_MACEMEN:
                _gmID = IO::Graphics::GID_BODY_MACEMAN;
                iVar2 = 9;
                _unitType = Map::Units::UT_E_MACE;
                break;
            case Commands::M_MAPPER_PEOPLE_XBOWMEN:
                _gmID = IO::Graphics::GID_BODY_CROSSBOWMAN;
                iVar2 = 7;
                _unitType = Map::Units::UT_E_XBOW;
                break;
            case Commands::M_MAPPER_PEOPLE_SWORDSMEN:
                _gmID = IO::Graphics::GID_BODY_SWORDSMAN;
                iVar2 = 8;
                _unitType = Map::Units::UT_E_SWORD;
                break;
            case Commands::M_MAPPER_PEOPLE_KNIGHTS:
                _gmID = IO::Graphics::GID_BODY_KNIGHT;
                local_1c = IO::Graphics::GID_BODY_KNIGHT_TOP;
                iVar2 = 10;
                _unitType = Map::Units::UT_E_KNIGHT;
                iVar3 = 1;
                local_18 = 0x50501581;
                break;
            case Commands::M_MAPPER_PEOPLE_LADDERMEN:
                _gmID = IO::Graphics::GID_BODY_LADDER_BEARER;
                iVar2 = 4;
                _unitType = Map::Units::UT_E_LADDER;
                break;
            case Commands::M_MAPPER_PEOPLE_ENGINEERS:
                _gmID = IO::Graphics::GID_BODY_SIEGE_ENGINEER;
                iVar2 = 0xb;
                _unitType = Map::Units::UT_E_ENGINEER;
                break;
            case Commands::M_MAPPER_PEOPLE_ENGINEERS_POTS:
                _gmID = IO::Graphics::GID_BODY_SIEGE_ENGINEER;
                iVar2 = 0xb;
                _unitType = Map::Units::UT_E_ENGINEER;
                local_10 = 0x275;
                break;
            case Commands::M_MAPPER_PEOPLE_MONKS:
                _gmID = IO::Graphics::GID_BODY_FIGHTING_MONK;
                iVar2 = 0xc;
                _unitType = Map::Units::UT_E_MONK;
                break;
            case Commands::M_MAPPER_PEOPLE_CATAPULTS:
                _gmID = IO::Graphics::GID_BODY_CATAPULT;
                local_1c = IO::Graphics::GID_BODY_CATAPULT;
                _unitType = Map::Units::UT_S_CATAPULT;
                iVar3 = 0xe1;
                local_18 = 0x50501581;
                break;
            case Commands::M_MAPPER_PEOPLE_TREBUCHETS:
                _gmID = IO::Graphics::GID_BODY_TREBUTCHET;
                local_1c = IO::Graphics::GID_BODY_TREBUTCHET;
                _unitType = Map::Units::UT_S_TREBUCHET;
                iVar3 = 9;
                local_18 = 0x50501581;
                break;
            case Commands::M_MAPPER_PEOPLE_BATTERING_RAMS:
                _gmID = IO::Graphics::GID_BODY_BATTERING_RAM;
                local_1c = IO::Graphics::GID_BODY_BATTERING_RAM;
                iVar3 = 0x4d;
                _unitType = Map::Units::UT_S_BATTERINGRAM;
                local_18 = 0x50501581;
                break;
            case Commands::M_MAPPER_PEOPLE_SIEGE_TOWERS:
                _gmID = IO::Graphics::GID_BODY_SIEGE_TOWER;
                local_1c = IO::Graphics::GID_BODY_SIEGE_TOWER;
                iVar3 = 9;
                _unitType = Map::Units::UT_S_TOWER;
                local_18 = 0x50501581;
                break;
            case Commands::M_MAPPER_PEOPLE_PORTABLE_SHIELDS:
                _gmID = IO::Graphics::GID_BODY_SHIELD;
                _unitType = Map::Units::UT_S_SHIELD;
                local_18 = 0x50501581;
                break;
            case Commands::M_MAPPER_PEOPLE_TUNNELERS:
                _gmID = IO::Graphics::GID_BODY_TUNNELOR;
                iVar2 = 2;
                _unitType = Map::Units::UT_TUNNELER;
                break;
            default:
                _gmID = local_8;
                break;
            case Commands::M_MAPPER_PEOPLE_ARAB_BOW:
                _gmID = IO::Graphics::GID_BODY_ARAB_SHORTBOW;
                iVar2 = 0x19;
                _unitType = Map::Units::UT_A_ARCHER;
                break;
            case Commands::M_MAPPER_PEOPLE_ARAB_SLAVE:
                _gmID = IO::Graphics::GID_BODY_ARAB_SLAVE;
                iVar2 = 0x1a;
                _unitType = Map::Units::UT_A_SLAVE;
                break;
            case Commands::M_MAPPER_PEOPLE_ARAB_SLINGER:
                _gmID = IO::Graphics::GID_BODY_ARAB_SLINGER;
                iVar2 = 0x1b;
                _unitType = Map::Units::UT_A_SLINGER;
                break;
            case Commands::M_MAPPER_PEOPLE_ARAB_ASSASIN:
                _gmID = IO::Graphics::GID_BODY_ARAB_ASSASIN;
                iVar2 = 0x1c;
                _unitType = Map::Units::UT_A_ASSASSIN;
                break;
            case Commands::M_MAPPER_PEOPLE_ARAB_HORSEMAN:
                _gmID = IO::Graphics::GID_BODY_HORSE_ARCHER;
                iVar2 = 0x1d;
                local_1c = IO::Graphics::GID_BODY_HORSE_ARCHER_TOP;
                _unitType = Map::Units::UT_A_HARCHER;
                iVar3 = 1;
                break;
            case Commands::M_MAPPER_PEOPLE_ARAB_SWORDSMAN:
                _gmID = IO::Graphics::GID_BODY_ARAB_SWORDSMAN;
                iVar2 = 0x1e;
                _unitType = Map::Units::UT_A_SWORDSMAN;
                break;
            case Commands::M_MAPPER_PEOPLE_ARAB_GRENADIER:
                _gmID = IO::Graphics::GID_BODY_ARAB_GRENADIER;
                iVar2 = 0x1f;
                _unitType = Map::Units::UT_A_FIRETHROWER;
                break;
            case Commands::M_MAPPER_PEOPLE_ARAB_BALLISTA:
                _gmID = IO::Graphics::GID_BODY_ARAB_BALLISTA;
                local_1c = IO::Graphics::GID_BODY_ARAB_BALLISTA;
                iVar3 = 0xa9;
                iVar2 = 0x18;
                _unitType = Map::Units::UT_S_FBALLISTA;
                local_18 = 0x50501581;
            }
            if ((DAT_GameCore::instance.gameMode_2 == Game::GM_SIEGE_THAT)
                && (MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::getBuildingCost, DAT_BuildingsState::ptr)(
                        DAT_TileMapState::instance.currentMapperCommand, &local_4, (int*)&local_8),
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .startResources[0xf]
                        < (int)local_8)) {
                bVar4 = false;
            }
            if (!DAT_MouseState::instance.draggingStopped) {
                if (!(DAT_TileMapState::instance.LogicLayer[_tile] & local_18) && bVar4) {
                    if (_gmID == IO::Graphics::GID_BODY_SIEGE_TOWER) {
                        if (0 < iVar3) {
                            MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                                DAT_ViewportRenderState::ptr)(local_1c, iVar3, 0, 0x47, _tile, 0x1d);
                        }
                        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                            DAT_ViewportRenderState::ptr)(
                            IO::Graphics::GID_BODY_SIEGE_TOWER, local_10, 0, 0, _tile, 0x1d);
                    }
                    if (0 < iVar3) {
                        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                            DAT_ViewportRenderState::ptr)(local_1c, iVar3, 0, 0, _tile, 0xd);
                    }
                    MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                        DAT_ViewportRenderState::ptr)(_gmID, local_10, 0, 0, _tile, 0xd);
                }
                if (_gmID == IO::Graphics::GID_BODY_SIEGE_TOWER) {
                    if (0 < iVar3) {
                        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                            DAT_ViewportRenderState::ptr)(local_1c, iVar3, 0, 0x47, _tile, 0x18001d);
                    }
                    MACRO_CALL_MEMBER(
                        Rendering::ViewportRenderState_Func::createFloatingLayerElement, DAT_ViewportRenderState::ptr)(
                        IO::Graphics::GID_BODY_SIEGE_TOWER, local_10, 0, 0, _tile, 0x18001d);
                }
                if (0 < iVar3) {
                    MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                        DAT_ViewportRenderState::ptr)(local_1c, iVar3, 0, 0, _tile, 0x18000d);
                }
                MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                    DAT_ViewportRenderState::ptr)(_gmID, local_10, 0, 0, _tile, 0x18000d);
            }
            if (!(DAT_TileMapState::instance.LogicLayer[_tile] & local_18) && bVar4) {
                if (DAT_GameCore::instance.gameMode_2 == Game::GM_SIEGE_THAT) {
                    MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::getBuildingCost, DAT_BuildingsState::ptr)(
                        DAT_TileMapState::instance.currentMapperCommand, &local_4, (int*)&local_8);
                    MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processResourceLoss,
                        DAT_BuildingsState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                        Game::Resources::RT_GOLD, (int)((int)(local_8)), 0);
                }
                if (iVar2 < 0) {
                    MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                        DAT_GameSynchronyState::instance.currentPlayerSlotID,
                        (int)((int)(DAT_GameSynchronyState::instance.currentPlayerSlotID)),
                        (int)((int)(DAT_TileMapState::instance.DAT_ClickedTileX * 8)),
                        (int)((int)(DAT_TileMapState::instance.DAT_ClickedTileY * 8)),
                        (int)((int)((uint)DAT_TileMapState::instance.HeightLayer[_tile])), _unitType);
                } else {
                    tribeID
                        = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::spawnUnitsIntoNewTribe, DAT_TribesState::ptr)(
                            0xffffffff, iVar2, (int)((int)(DAT_TileMapState::instance.DAT_ClickedTileX)),
                            (int)((int)(DAT_TileMapState::instance.DAT_ClickedTileY)),
                            (int)((int)(DAT_GameSynchronyState::instance.currentPlayerSlotID)), _unitType,
                            ((UnitType)0), (int)((int)(DAT_TileMapState::instance.unitPlacementCount)), 0);
                    bVar4 = DAT_TileMapState::instance.currentMapperCommand == Commands::M_MAPPER_PEOPLE_ENGINEERS_POTS;
                    DAT_TribesState::instance.tribes[tribeID].tribeBehaviorType = Map::Units::STBT_1;
                    DAT_TribesState::instance.tribes[tribeID].initialMoveOrderGiven = 1;
                    if ((bVar4) && (iVar3 = 0, 0 < DAT_TileMapState::instance.unitPlacementCount)) {
                        do {
                            iVar1 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe,
                                DAT_TribesState::ptr)(tribeID, iVar3);
                            iVar2 = DAT_TileMapState::instance.unitPlacementCount;
                            iVar3 = iVar3 + 1;
                            DAT_UnitsState::instance.units[iVar1].resourceToDeposit = 1;
                        } while (iVar3 < iVar2);
                    }
                }
            }
        }
    }

}
}
