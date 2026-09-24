#include "../BuildingsState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/Player/PlayerDataBuildingCategoryEnum.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Commands::MappersEnum;
        using OpenSHC::DE::SHCDE::eSFX;
        using OpenSHC::Game::GameMode;
        using OpenSHC::Game::GameMode2;
        using OpenSHC::Game::Player::PlayerDataBuildingCategoryEnum;
        using OpenSHC::Game::Resources::ResourceType;
        using OpenSHC::Map::MapType2;
        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Map::Entities::EntityType;
        using OpenSHC::Map::Units::UnitInstructionType;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
        using OpenSHC::UI::Enums::MenuViewType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00420D20
        int BuildingsState::setupBuildingData(int playerID, uint x, uint y, undefined4 averageHeight,
            BuildingType buildingType, uint width, int playerID_dup, int variationIndex)
        {
            // Matching note: The remaining differences are mostly register and stack slot allocation in the
            // large initialisation block and the building type switch.
            // Places a new building of the type at (x, y) and returns its ID
            if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                playerID_dup = 0;
            }
            if (x > 399 || y > 399 || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
                return 0;
            }

            // Find a free building slot
            int buildingID;
            for (buildingID = 1; buildingID < 2000; ++buildingID) {
                if (this->buildings[buildingID].logicalState == 0) {
                    break;
                }
                if (buildingID >= 1999) {
                    return 0;
                }
            }
            if (buildingID >= this->maxBuildingsCount) {
                this->maxBuildingsCount = buildingID + 1;
            }
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(Building), 0, &this->buildings[buildingID]);

            // New buildings are snoozed if the other buildings of the type are
            int sameTypeID
                = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findFirstBuildingIDForPlayerAndType,
                    this)(playerID, buildingType);
            if (sameTypeID != 0 && this->buildings[sameTypeID].sleeping) {
                this->buildings[buildingID].sleeping = true;
            }
            --this->unknownCountdown01;
            this->buildings[buildingID].uid = DAT_GameCore::instance.uniqueGameObjectTracker;
            ++DAT_GameCore::instance.uniqueGameObjectTracker;
            this->buildings[buildingID].owner = playerID;
            this->buildings[buildingID].logicalState = BLS_INITIAL;
            this->buildings[buildingID].widthOrHeight = width;
            this->buildings[buildingID].x = x;
            this->buildings[buildingID].y = y;
            this->buildings[buildingID].buildingType = buildingType;
            this->buildings[buildingID].currentTilePositionAdjusted
                = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            this->buildings[buildingID].microX = x * 8;
            this->buildings[buildingID].microY = y * 8;
            this->buildings[buildingID].terrainHeightUnk = averageHeight;

            // Decorations use their own sprite variations
            short variation;
            if (buildingType == BT_GARDEN) {
                this->buildings[buildingID].ffBuildingVariation
                    = DAT_BuildingDefinedData::instance.GardenVariations[variationIndex];
                variation = 15;
            } else if (buildingType == BT_UNKNOWN1) {
                this->buildings[buildingID].ffBuildingVariation
                    = DAT_BuildingDefinedData::instance.UnknownVariations[variationIndex];
                variation = 15;
            } else if (buildingType == BT_CESSPIT) {
                this->buildings[buildingID].ffBuildingVariation
                    = DAT_BuildingDefinedData::instance.CesspitVariations[variationIndex];
                variation = 15;
            } else if (buildingType == BT_STATUE) {
                this->buildings[buildingID].ffBuildingVariation
                    = DAT_BuildingDefinedData::instance.StatueVariations[variationIndex];
                variation = 15;
            } else if (buildingType == BT_SHRINE) {
                this->buildings[buildingID].ffBuildingVariation
                    = DAT_BuildingDefinedData::instance.ShrineVariations[variationIndex];
                variation = 15;
            } else if (buildingType == BT_POND) {
                this->buildings[buildingID].ffBuildingVariation
                    = DAT_BuildingDefinedData::instance.PondVariations[variationIndex];
                variation = 15;
            } else {
                variation = variationIndex;
                this->buildings[buildingID].ffBuildingVariation = 0;
            }
            this->buildings[buildingID].playerColorUnk = playerID_dup;
            this->buildings[buildingID].buildingVariation = variation;
            this->buildings[buildingID].oldVisualActiveState = -1;
            this->buildings[buildingID].fireRelatedRNG1 = SEC_RNG::instance.currentNumber2;
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();

            // Rendering data. Only the lower half of spriteSheetID is written.
            *(short*)&this->buildings[buildingID].spriteSheetID
                = DAT_BuildingDefinedData::instance.Building_SpriteSheet_ID_Array_1[buildingType].shortValue;
            this->buildings[buildingID].spriteID
                = DAT_BuildingDefinedData::instance.Building_Sprite_ID_Array_1[buildingType]
                + this->buildings[buildingID].ffBuildingVariation;
            this->buildings[buildingID].visuallyActiveSpriteID
                = DAT_BuildingDefinedData::instance.VisuallyActiveSpriteIDOffsets[buildingType];
            this->buildings[buildingID].gfxOffset = DAT_BuildingDefinedData::instance.GFXOffsets[buildingType];
            this->buildings[buildingID].gfxOffset2
                = DAT_BuildingDefinedData::instance.Building_Sprite_ID_Array_2[buildingType];
            this->buildings[buildingID].gfxOffset3 = DAT_BuildingDefinedData::instance.GFXOffsets3[buildingType];
            this->buildings[buildingID].spriteOffetX
                = DAT_BuildingDefinedData::instance.SpriteOffsets1[buildingType][0][0];
            this->buildings[buildingID].spriteOffetY
                = DAT_BuildingDefinedData::instance.SpriteOffsets1[buildingType][1][0];
            this->buildings[buildingID].animAdvanceThrottle
                = DAT_BuildingDefinedData::instance.AnimAdvanceThrottles[buildingType];
            this->buildings[buildingID].animationFrame = 0;
            this->buildings[buildingID].campgroundVclock = 0;
            this->buildings[buildingID].field25_0x4c = 0;
            this->buildings[buildingID].field26_0x50 = 0;
            this->buildings[buildingID].field27_0x54 = 0;
            this->buildings[buildingID].spriteID2
                = DAT_BuildingDefinedData::instance.SpriteIDs2[buildingType].shortValue;
            this->buildings[buildingID].animStateCounterTracker = 0;
            this->buildings[buildingID].animStateCounter = 0;

            // Buildings of AI players in multiplayer cannot be set on fire for a longer time
            if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY
                || DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1
                || DAT_GameSynchronyState::instance.currentAIArray[playerID] == 0) {
                this->buildings[buildingID].cooldownTimer = 400;
            } else {
                this->buildings[buildingID].cooldownTimer = 2000;
            }
            this->buildings[buildingID].currentlyNeededEmployeeCount = 0;
            this->buildings[buildingID].renderAnimation = 0;
            this->buildings[buildingID].unknownStockpileOrSignpostRelated = 1;
            this->buildings[buildingID].numberOfPopulationProvided
                = DAT_BuildingDefinedData::instance.BuildingNumberOfPopulationProvided[buildingType].shortValue;
            this->buildings[buildingID].buildingTypeBasedEmployeeCount
                = DAT_BuildingDefinedData::instance.EmployeeCountPerBuildingType[buildingType].shortValue;
            this->buildings[buildingID].unknownFlag3
                = DAT_BuildingDefinedData::instance.field15_0x1404[buildingType].shortValue;
            this->buildings[buildingID].flag1
                = DAT_BuildingDefinedData::instance.field16_0x15bc[buildingType].shortValue;
            this->buildings[buildingID].unknownFlag4
                = DAT_BuildingDefinedData::instance.field18_0x192c[buildingType].byteValue;
            this->buildings[buildingID].flag2
                = DAT_BuildingDefinedData::instance.field24_0x237c[buildingType].shortValue;
            this->buildings[buildingID].maxHealth
                = DAT_BuildingDefinedData::instance.BuildingHP[buildingType].shortValue;
            this->buildings[buildingID].currentHealth
                = DAT_BuildingDefinedData::instance.BuildingHP[buildingType].shortValue;
            this->buildings[buildingID].buildMonthOrBuildOrder
                = DAT_GameState::instance.mapAndTime.month + DAT_GameState::instance.mapAndTime.year * 12;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setBuildingInitialEntryTileTry, this)(
                buildingID, 0);
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::determineBuildingEntranceFromKeepArea,
                this)(buildingID, 1, FALSE);

            // Building type specific setup
            switch (buildingType) {
            case BT_DAIRYFARM:
                this->field4_0x10 = 3;
                // fallthrough
            case BT_WHEATFARM:
            case BT_HOPFARM:
            case BT_APPLEFARM:
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setBuildingInitialEntryTileTry, this)(
                    buildingID, 0);
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::determineBuildingEntranceFromKeepArea,
                    this)(buildingID, 1, FALSE);
                break;
            case BT_OXTETHER:
                this->buildings[buildingID].field28_0x58 = 50;
                break;
            case BT_SIGNPOST:
                this->buildings[buildingID].unknownStockpileOrSignpostRelated = 0;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addSignpostToBuildingEntryData,
                    DAT_GameState::ptr)(buildingID);
                break;
            case BT_MANORHOUSE:
            case BT_STONEKEEP:
            case BT_STRONGHOLD:
            case BT_KEEPFOUR:
            case BT_KEEPFIVE:
                MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding,
                    DAT_GameState::ptr)(buildingID, playerID, OpenSHC::Game::Player::PDBCE_KEEP);
                if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR
                    && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT) {
                    DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType = OpenSHC::UI::Enums::BASMTT_HUNTERSHUT;
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
                    DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_NULL;
                }
                break;
            case BT_CAMPGROUND:
                MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding,
                    DAT_GameState::ptr)(buildingID, playerID, OpenSHC::Game::Player::PDBCE_CAMPGROUND);
                break;
            case BT_STOCKPILE:
                this->buildings[buildingID].unknownStockpileOrSignpostRelated = 0;
                MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding,
                    DAT_GameState::ptr)(buildingID, playerID, OpenSHC::Game::Player::PDBCE_STOCKPILE);
                break;
            case BT_GRANARY:
                MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding,
                    DAT_GameState::ptr)(buildingID, playerID, OpenSHC::Game::Player::PDBCE_GRANARY);
                break;
            case BT_ARMORY:
                MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding,
                    DAT_GameState::ptr)(buildingID, playerID, OpenSHC::Game::Player::PDBCE_ARMORY);
                break;
            case BT_MARKETPLACE:
                MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding,
                    DAT_GameState::ptr)(buildingID, playerID, OpenSHC::Game::Player::PDBCE_MARKETPLACE);
                break;
            case BT_ENGINEERSGUILD:
                MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding,
                    DAT_GameState::ptr)(buildingID, playerID, OpenSHC::Game::Player::PDBCE_ENGINEERSGUILD);
                break;
            case BT_TUNNELERSGUILD:
                MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding,
                    DAT_GameState::ptr)(buildingID, playerID, OpenSHC::Game::Player::PDBCE_TUNNELERSGUILD);
                break;
            case BT_MERCENARYPOST:
                MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding,
                    DAT_GameState::ptr)(buildingID, playerID, OpenSHC::Game::Player::PDBCE_MERCENARYPOST);
                break;
            case BT_BARRACKS:
                MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding,
                    DAT_GameState::ptr)(buildingID, playerID, OpenSHC::Game::Player::PDBCE_BARRACKS);
                break;
            case BT_BLACKSMITH:
                if (DAT_GameCore::instance.swordProducible_logic != 0) {
                    this->buildings[buildingID].producedItemTypeNext = OpenSHC::Game::Resources::RT_SWORD;
                    this->buildings[buildingID].producedItemType = OpenSHC::Game::Resources::RT_SWORD;
                } else {
                    this->buildings[buildingID].producedItemTypeNext = OpenSHC::Game::Resources::RT_MACE;
                    this->buildings[buildingID].producedItemType = OpenSHC::Game::Resources::RT_MACE;
                }
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_ECONOMIC_CAMPAIGN_SH1
                    && DAT_GameCore::instance.missionNumber1to20 == 36) {
                    this->buildings[buildingID].producedItemTypeNext = OpenSHC::Game::Resources::RT_MACE;
                    this->buildings[buildingID].producedItemType = OpenSHC::Game::Resources::RT_MACE;
                }
                break;
            case BT_POLETURNER:
                this->buildings[buildingID].producedItemTypeNext = OpenSHC::Game::Resources::RT_SPEAR;
                this->buildings[buildingID].producedItemType = OpenSHC::Game::Resources::RT_SPEAR;
                break;
            case BT_FLETCHER:
                this->buildings[buildingID].producedItemTypeNext = OpenSHC::Game::Resources::RT_BOW;
                this->buildings[buildingID].producedItemType = OpenSHC::Game::Resources::RT_BOW;
                break;
            case BT_FIREBALLISTA:
            case BT_CATAPULT:
            case BT_TREBUCHET:
            case BT_BATTERINGRAM:
            case BT_SIEGETOWER:
            case BT_SHIELD:
                this->buildings[buildingID].playerColorUnk = playerID;
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::relayTribeInstruction, DAT_UnitsState::ptr)(
                        this->DAT_DraggedTileCountVerified,
                        OpenSHC::Map::Units::UIT_CONSTRUCT_SIEGE_EQUIPMENTOIL_DUTYENGINEERRELATED, buildingID,
                        this->buildings[buildingID].uid, 0);
                }
                break;
            case BT_UNKNOWN4:
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::relayTribeInstruction, DAT_UnitsState::ptr)(
                        this->DAT_DraggedTileCountVerified, (UnitInstructionType)0x15, buildingID,
                        this->buildings[buildingID].uid, 0);
                }
                break;
            case BT_HOVEL:
            case BT_HOUSE:
                this->buildings[buildingID].padding_0x2a5[0]
                    = (this->buildings[buildingID].fireRelatedRNG1 >> 5) % 3 + 1;
                break;
            case BT_OILSMELTER:
                MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::computeBuildingCategoryEntryPointAndDestroyEarlierBuilding,
                    DAT_GameState::ptr)(buildingID, playerID, OpenSHC::Game::Player::PDBCE_OILSMELTER);
                // The oil smelters of siege maps start full
                if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                        || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT)
                    && DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE) {
                    this->buildings[buildingID].resources[OpenSHC::Game::Resources::RT_PITCH]
                        = DAT_BuildingDefinedData::instance
                              .StorageLimitResourceTypeArray[OpenSHC::Game::Resources::RT_PITCH];
                }
                break;
            case BT_KILLINGPIT:
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                    this->buildings[buildingID].state = -1;
                }
                break;
            case BT_CESSPIT: {
                // Flies and a poison cloud in the middle of the cesspit
                int halfSize = (int)width / 2;
                int middleY = (short)this->buildings[buildingID].y + halfSize;
                int buildingX = (short)this->buildings[buildingID].x;
                MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity,
                    DAT_EntityState::ptr)(0, 0, 0, (buildingX + halfSize) * 8, middleY * 8,
                    DAT_TileMapState::instance
                        .HeightLayer[DAT_ViewportRenderState::instance.translationMatrix[middleY].addXgetTile
                            + buildingX + halfSize],
                    0, 0, 0, OpenSHC::Map::Entities::ET_COW_POISON_CLOUD, 0);
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    (short)this->buildings[buildingID].x + halfSize, (short)this->buildings[buildingID].y + halfSize,
                    OpenSHC::DE::SHCDE::FX_FLIES);
                break;
            }
            case BT_DOGCAGE:
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setBuildingInitialEntryTileTry, this)(
                    buildingID, 0);
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::determineBuildingEntranceFromKeepArea,
                    this)(buildingID, 1, FALSE);
                for (int i = 0; i < 4; ++i) {
                    (&this->buildings[buildingID].insideUnitID1)[i] = 0;
                    (&this->buildings[buildingID].insideUnitUID1)[i] = 0;
                }
                // Every cage holds four dogs
                {
                    int dogID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                        0, playerID, this->buildings[buildingID].buildingEntryX * 8,
                        this->buildings[buildingID].buildingEntryY * 8, this->buildings[buildingID].terrainHeightUnk,
                        OpenSHC::Map::Units::UT_CAGEDOG);
                    if (dogID != 0) {
                        DAT_UnitsState::instance.units[dogID].workplaceBuildingID_1 = buildingID;
                        DAT_UnitsState::instance.units[dogID].workplaceBuildingUID = this->buildings[buildingID].uid;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::commitUnitLocation, DAT_UnitsState::ptr)(dogID);
                        DAT_UnitsState::instance.units[dogID].state.generic = (UnitState)0xd2;
                        DAT_UnitsState::instance.units[dogID].cagedogReleaseCheckMoment = 0;
                        this->buildings[buildingID].insideUnitID1 = dogID;
                        this->buildings[buildingID].insideUnitUID1 = DAT_UnitsState::instance.units[dogID].uid;
                    }
                }
                {
                    int dogID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                        0, playerID, this->buildings[buildingID].buildingEntryX * 8,
                        this->buildings[buildingID].buildingEntryY * 8,
                        DAT_BuildingsState::instance.buildings[buildingID].terrainHeightUnk,
                        OpenSHC::Map::Units::UT_CAGEDOG);
                    if (dogID != 0) {
                        DAT_UnitsState::instance.units[dogID].workplaceBuildingID_1 = buildingID;
                        DAT_UnitsState::instance.units[dogID].workplaceBuildingUID = this->buildings[buildingID].uid;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::commitUnitLocation, DAT_UnitsState::ptr)(dogID);
                        DAT_UnitsState::instance.units[dogID].state.generic = (UnitState)0xd2;
                        DAT_UnitsState::instance.units[dogID].cagedogReleaseCheckMoment = 1;
                        this->buildings[buildingID].insideUnitID2 = dogID;
                        this->buildings[buildingID].insideUnitUID2 = DAT_UnitsState::instance.units[dogID].uid;
                    }
                }
                {
                    int dogID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                        0, playerID, this->buildings[buildingID].buildingEntryX * 8,
                        this->buildings[buildingID].buildingEntryY * 8,
                        DAT_BuildingsState::instance.buildings[buildingID].terrainHeightUnk,
                        OpenSHC::Map::Units::UT_CAGEDOG);
                    if (dogID != 0) {
                        DAT_UnitsState::instance.units[dogID].workplaceBuildingID_1 = buildingID;
                        DAT_UnitsState::instance.units[dogID].workplaceBuildingUID = this->buildings[buildingID].uid;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::commitUnitLocation, DAT_UnitsState::ptr)(dogID);
                        DAT_UnitsState::instance.units[dogID].state.generic = (UnitState)0xd2;
                        DAT_UnitsState::instance.units[dogID].cagedogReleaseCheckMoment = 2;
                        this->buildings[buildingID].insideUnitID3 = dogID;
                        this->buildings[buildingID].insideUnitUID3 = DAT_UnitsState::instance.units[dogID].uid;
                    }
                }
                {
                    int dogID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                        0, playerID, this->buildings[buildingID].buildingEntryX * 8,
                        this->buildings[buildingID].buildingEntryY * 8, this->buildings[buildingID].terrainHeightUnk,
                        OpenSHC::Map::Units::UT_CAGEDOG);
                    if (dogID != 0) {
                        DAT_UnitsState::instance.units[dogID].workplaceBuildingID_1 = buildingID;
                        DAT_UnitsState::instance.units[dogID].workplaceBuildingUID = this->buildings[buildingID].uid;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::commitUnitLocation, DAT_UnitsState::ptr)(dogID);
                        DAT_UnitsState::instance.units[dogID].state.generic = (UnitState)0xd2;
                        DAT_UnitsState::instance.units[dogID].cagedogReleaseCheckMoment = 3;
                        this->buildings[buildingID].insideUnitID4 = dogID;
                        this->buildings[buildingID].insideUnitUID4 = DAT_UnitsState::instance.units[dogID].uid;
                        this->buildings[buildingID].unitRefID = dogID;
                        this->buildings[buildingID].unitRefUID = DAT_UnitsState::instance.units[dogID].uid;
                    }
                }
                break;
            case BT_OUTPOST_EUROPEAN:
            case BT_OUTPOST_ARABIAN:
                this->buildings[buildingID].outpostRelatedUnk1 = 0xff;
                this->buildings[buildingID].outpostRelatedUnk2 = 1;
                this->buildings[buildingID].outpostRelatedUnk3 = 0;
                this->buildings[buildingID].randomOutpostField = SEC_RNG::instance.currentNumber2 % 2 + 6;
                MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                this->buildings[buildingID].outpostRelatedUnk4 = 1200;
                break;
            }

            this->field34_0x18e074 = 1;
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::isFearFactorBuilding, this)(buildingID)
                != 0) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::recomputeAllFearFactors, DAT_BuildingsState::ptr)();
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::isReligiousBuilding, this)(buildingID)
                != 0) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::recomputeReligionBonuses, DAT_GameState::ptr)();
            }
            return buildingID;
        }

    }
}
}
