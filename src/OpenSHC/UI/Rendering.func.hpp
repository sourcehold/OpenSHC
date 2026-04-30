/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/UI/Rendering.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/Enums/DisplayElementIDInt.hpp"
#include "OpenSHC/UI/Rendering.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "WinDef.h"
namespace OpenSHC {
namespace UI {
    namespace Rendering_Func {

        using OpenSHC::UI::Enums::DisplayElementIDInt;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD tileType), false,
            Address::SHC_3BB0A8C1_0x00433BC0,
            &OpenSHC::UI::Rendering::RenderConnectAndPathLinkageInfoTextDisplayElement)
        RenderConnectAndPathLinkageInfoTextDisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int xPos, int yPos, int valueUnk, BOOLEnum otherImageFlagUnk), false,
            Address::SHC_3BB0A8C1_0x00433C20, &OpenSHC::UI::Rendering::TransformAndRenderPercentage)
        TransformAndRenderPercentage;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x00433D00, &OpenSHC::UI::Rendering::RenderBottomLeftDateDisplayElement)
        RenderBottomLeftDateDisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x00433DA0, &OpenSHC::UI::Rendering::RenderStartingGoodDisplayElement)
        RenderStartingGoodDisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00439440,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_WorkshopWeaponProduction)
        RenderBuildingMenu_WorkshopWeaponProduction;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0043A8D0,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_RecruitingBuilding)
        RenderBuildingMenu_RecruitingBuilding;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043A9F0,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Keep)
        RenderBuildingMenu_Keep;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043AF40,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Inn)
        RenderBuildingMenu_Inn;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0043B3B0,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Granary)
        RenderBuildingMenu_Granary;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043B910,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Fletcher)
        RenderBuildingMenu_Fletcher;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043B950,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Blacksmith)
        RenderBuildingMenu_Blacksmith;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043B990,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Poleturner)
        RenderBuildingMenu_Poleturner;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043B9D0,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Armourer)
        RenderBuildingMenu_Armourer;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043BA80,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Tanner)
        RenderBuildingMenu_Tanner;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043BB30,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Bakery)
        RenderBuildingMenu_Bakery;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043BB70,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Brewery)
        RenderBuildingMenu_Brewery;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043BBB0,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Outpost)
        RenderBuildingMenu_Outpost;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0043BD60,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_House)
        RenderBuildingMenu_House;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043BDE0,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_WoodcutterShut)
        RenderBuildingMenu_WoodcutterShut;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043BE20,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_OxThether)
        RenderBuildingMenu_OxThether;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043BEA0,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Quarry)
        RenderBuildingMenu_Quarry;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043BEE0,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Ironmine)
        RenderBuildingMenu_Ironmine;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043BF20,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_PitchRig)
        RenderBuildingMenu_PitchRig;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043BF60,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_HuntersHut)
        RenderBuildingMenu_HuntersHut;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043BFA0,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Apothecary)
        RenderBuildingMenu_Apothecary;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043C0A0,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Wheatfarm)
        RenderBuildingMenu_Wheatfarm;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043C0E0,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Hopfarm)
        RenderBuildingMenu_Hopfarm;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043C120,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Applefarm)
        RenderBuildingMenu_Applefarm;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043C160,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Diaryfarm)
        RenderBuildingMenu_Diaryfarm;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043C1A0,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Mill)
        RenderBuildingMenu_Mill;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043C1E0,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_ChapelAndChurch)
        RenderBuildingMenu_ChapelAndChurch;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043C6A0,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Stockpile)
        RenderBuildingMenu_Stockpile;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043C840,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Armory)
        RenderBuildingMenu_Armory;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043C9F0,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Quarry_Stonepile)
        RenderBuildingMenu_Quarry_Stonepile;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043CA70,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Engineersguild)
        RenderBuildingMenu_Engineersguild;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043CB00,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Tunnelersguild)
        RenderBuildingMenu_Tunnelersguild;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043CB90,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Cathedral)
        RenderBuildingMenu_Cathedral;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int unitID, int xPos, int yPos), false, Address::SHC_3BB0A8C1_0x0043CC30,
            &OpenSHC::UI::Rendering::RenderPeasantMenu_CurrentActionUnk)
        RenderPeasantMenu_CurrentActionUnk;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043CDB0,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Marketplace)
        RenderBuildingMenu_Marketplace;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043CE30,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Marketplace_Stonks)
        RenderBuildingMenu_Marketplace_Stonks;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043D070,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Marketplace_Food)
        RenderBuildingMenu_Marketplace_Food;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043D120,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Marketplace_Resource)
        RenderBuildingMenu_Marketplace_Resource;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043D1D0,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Marketplace_Weapons)
        RenderBuildingMenu_Marketplace_Weapons;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043D280,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Marketplace_Trade)
        RenderBuildingMenu_Marketplace_Trade;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043D420,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Well)
        RenderBuildingMenu_Well;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043D460,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_WaterPot)
        RenderBuildingMenu_WaterPot;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043D4A0,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Oilsmelter)
        RenderBuildingMenu_Oilsmelter;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043D520,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Stables)
        RenderBuildingMenu_Stables;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043D690,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Drawbridge)
        RenderBuildingMenu_Drawbridge;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043D6D0,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Unused_PosternGate)
        RenderBuildingMenu_Unused_PosternGate;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043D710,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_TunnelEntrance)
        RenderBuildingMenu_TunnelEntrance;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043D750,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Signpost)
        RenderBuildingMenu_Signpost;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043D790,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_KillingPit)
        RenderBuildingMenu_KillingPit;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043D7D0,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Campfire)
        RenderBuildingMenu_Campfire;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043D850,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Gallows)
        RenderBuildingMenu_Gallows;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043D890,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Stocks)
        RenderBuildingMenu_Stocks;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043D8D0,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Unused_Witchhoist)
        RenderBuildingMenu_Unused_Witchhoist;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043D910,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Maypole)
        RenderBuildingMenu_Maypole;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043D950,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Gardens)
        RenderBuildingMenu_Gardens;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043D990,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_TrainingGrounds)
        RenderBuildingMenu_TrainingGrounds;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043D9D0,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_CessPit)
        RenderBuildingMenu_CessPit;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043DA10,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_BurningStake)
        RenderBuildingMenu_BurningStake;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043DA50,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Gibbet)
        RenderBuildingMenu_Gibbet;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043DA90,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Dungeon)
        RenderBuildingMenu_Dungeon;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043DAD0,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_StretchingRack)
        RenderBuildingMenu_StretchingRack;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043DB10,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Unused_FloggingRack)
        RenderBuildingMenu_Unused_FloggingRack;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043DB50,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_ChoppingBlock)
        RenderBuildingMenu_ChoppingBlock;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043DB90,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_DunkingStool)
        RenderBuildingMenu_DunkingStool;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043DBD0,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_DogCage)
        RenderBuildingMenu_DogCage;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043DC60,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Statue)
        RenderBuildingMenu_Statue;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043DD30,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Shrine)
        RenderBuildingMenu_Shrine;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043DD70,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Unused_BeeHive)
        RenderBuildingMenu_Unused_BeeHive;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043DDB0,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_DancingBear)
        RenderBuildingMenu_DancingBear;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043DDF0,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Unused_Pond)
        RenderBuildingMenu_Unused_Pond;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043DE30,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Unused_BearCave)
        RenderBuildingMenu_Unused_BearCave;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043DE70,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Siegetent_Catapult)
        RenderBuildingMenu_Siegetent_Catapult;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043DF40,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Siegetent_Fireballista)
        RenderBuildingMenu_Siegetent_Fireballista;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043E010,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Siegetent_Trebuchet)
        RenderBuildingMenu_Siegetent_Trebuchet;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043E0E0,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Siegetent_Siegetower)
        RenderBuildingMenu_Siegetent_Siegetower;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043E1B0,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Siegetent_BatteringRam)
        RenderBuildingMenu_Siegetent_BatteringRam;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043E280,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Siegetent_Shield)
        RenderBuildingMenu_Siegetent_Shield;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043E350,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_RenderTowerAndGateHealth)
        RenderBuildingMenu_RenderTowerAndGateHealth;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043E6C0,
            &OpenSHC::UI::Rendering::RenderStatusMenu_Popularity)
        RenderStatusMenu_Popularity;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043F2F0,
            &OpenSHC::UI::Rendering::RenderStatusMenu_FearFactor)
        RenderStatusMenu_FearFactor;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043F6A0,
            &OpenSHC::UI::Rendering::RenderStatusMenu_Population)
        RenderStatusMenu_Population;

        MACRO_FUNCTION_RESOLVER(
            void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043FAC0, &OpenSHC::UI::Rendering::RenderStatusMenu_Food)
        RenderStatusMenu_Food;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043FD30,
            &OpenSHC::UI::Rendering::RenderStatusMenu_Resources)
        RenderStatusMenu_Resources;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043FE10,
            &OpenSHC::UI::Rendering::RenderStatusMenu_Religion)
        RenderStatusMenu_Religion;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004401A0,
            &OpenSHC::UI::Rendering::RenderStatusMenu_Weapons)
        RenderStatusMenu_Weapons;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00447A50,
            &OpenSHC::UI::Rendering::RenderStatusMenu_Chimp)
        RenderStatusMenu_Chimp;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00447CF0,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Gatehouse)
        RenderBuildingMenu_Gatehouse;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00447D30,
            &OpenSHC::UI::Rendering::RenderBuildingMenu_Tower)
        RenderBuildingMenu_Tower;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00447DC0,
            &OpenSHC::UI::Rendering::RenderStatusMenu_Overview)
        RenderStatusMenu_Overview;

        MACRO_FUNCTION_RESOLVER(
            void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00447FA0, &OpenSHC::UI::Rendering::RenderStatusMenu_Army)
        RenderStatusMenu_Army;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00452900,
            &OpenSHC::UI::Rendering::RenderTerrainTilesCenterPiece)
        RenderTerrainTilesCenterPiece;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004640D0,
            &OpenSHC::UI::Rendering::RenderCurrentNotActiveButtonWithPossibleAlphaTexOnCurrentSurfaceUnk)
        RenderCurrentNotActiveButtonWithPossibleAlphaTexOnCurrentSurfaceUnk;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00464300,
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

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(DisplayElementIDInt displayElementID, uint toggleValue), false,
            Address::SHC_3BB0A8C1_0x004AF6B0, &OpenSHC::UI::Rendering::TogglePlayerPingDisplayElementUnk)
        TogglePlayerPingDisplayElementUnk;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004AF700,
            &OpenSHC::UI::Rendering::RenderDisplayElementsUnk)
        RenderDisplayElementsUnk;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004AF820, &OpenSHC::UI::Rendering::RenderResourceMissing1DisplayElement)
        RenderResourceMissing1DisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004AF840, &OpenSHC::UI::Rendering::RenderResourceMissing2DisplayElement)
        RenderResourceMissing2DisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004AF860, &OpenSHC::UI::Rendering::RenderDebugNumbersDisplayElement)
        RenderDebugNumbersDisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004AFA50, &OpenSHC::UI::Rendering::RenderUnknownDisplayElement7)
        RenderUnknownDisplayElement7;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD MissionNumPlus1Unk), false,
            Address::SHC_3BB0A8C1_0x004AFA80, &OpenSHC::UI::Rendering::RenderSomeMissionNumberUnkDisplayElement9)
        RenderSomeMissionNumberUnkDisplayElement9;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004AFB00, &OpenSHC::UI::Rendering::RenderNoTreeGrowthTextDisplayElement)
        RenderNoTreeGrowthTextDisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004AFB30, &OpenSHC::UI::Rendering::RenderInGameWinDefeatWindowDisplayElement)
        RenderInGameWinDefeatWindowDisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD winDefeatState), false,
            Address::SHC_3BB0A8C1_0x004AFDA0, &OpenSHC::UI::Rendering::RenderMissionWinDefeatBannerDisplayElement)
        RenderMissionWinDefeatBannerDisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004AFE10, &OpenSHC::UI::Rendering::RenderSomeMultiplayerInfoUnkDisplayElement19)
        RenderSomeMultiplayerInfoUnkDisplayElement19;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004B0390, &OpenSHC::UI::Rendering::RenderPlayerInfoOnHoverDisplayElement)
        RenderPlayerInfoOnHoverDisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004B07C0, &OpenSHC::UI::Rendering::RenderGameSpeedTextDisplayElement)
        RenderGameSpeedTextDisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004B0820, &OpenSHC::UI::Rendering::RenderUnknownDisplayElement25)
        RenderUnknownDisplayElement25;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004B0AC0, &OpenSHC::UI::Rendering::RenderPeopleLeftToPlaceDisplayElement)
        RenderPeopleLeftToPlaceDisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD whichBuildingIsMissing), false,
            Address::SHC_3BB0A8C1_0x004B1C30,
            &OpenSHC::UI::Rendering::RenderAndPlayKeepAndGranaryPlacementInfoDisplayElement)
        RenderAndPlayKeepAndGranaryPlacementInfoDisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004B1D30, &OpenSHC::UI::Rendering::RenderPlayerPingUnkDisplayElement22)
        RenderPlayerPingUnkDisplayElement22;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004B1E60, &OpenSHC::UI::Rendering::RenderGamePausedTextDisplayElement)
        RenderGamePausedTextDisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004B1EB0, &OpenSHC::UI::Rendering::RenderTimeUntilVictoryDisplayElement)
        RenderTimeUntilVictoryDisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004B20B0, &OpenSHC::UI::Rendering::RenderNoRushDisplayElementUnk)
        RenderNoRushDisplayElementUnk;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004B2280, &OpenSHC::UI::Rendering::RenderTimeUntilDefeatDisplayElement)
        RenderTimeUntilDefeatDisplayElement;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int posX, int posY, DWORD elementState), false,
            Address::SHC_3BB0A8C1_0x004B2530, &OpenSHC::UI::Rendering::RenderSomeMultiplayerInfoUnkDisplayElement28)
        RenderSomeMultiplayerInfoUnkDisplayElement28;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int textNumInGroup), false, Address::SHC_3BB0A8C1_0x004BA910,
            &OpenSHC::UI::Rendering::RenderScenarioButtonWithText)
        RenderScenarioButtonWithText;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004D5810,
            &OpenSHC::UI::Rendering::RenderGreatestLordScreen)
        RenderGreatestLordScreen;

        MACRO_FUNCTION_RESOLVER(int(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004D76A0,
            &OpenSHC::UI::Rendering::RenderMissionObjectivesUnk)
        RenderMissionObjectivesUnk;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int loadedGfxIndex, int xPosInMenuRect, int yPosInMenuRect), false,
            Address::SHC_3BB0A8C1_0x004DA570, &OpenSHC::UI::Rendering::RenderGfxHelperUnk)
        RenderGfxHelperUnk;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int gfxIndex, int x, int y, int blendStrength), false,
            Address::SHC_3BB0A8C1_0x004DA640, &OpenSHC::UI::Rendering::RenderMenuGfxHelper)
        RenderMenuGfxHelper;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004DB490,
            &OpenSHC::UI::Rendering::RenderHistoryBookEdgeUnk)
        RenderHistoryBookEdgeUnk;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004F4070,
            &OpenSHC::UI::Rendering::RenderNoViewsFoundWarning)
        RenderNoViewsFoundWarning;

        MACRO_FUNCTION_RESOLVER(
            void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004F6210, &OpenSHC::UI::Rendering::RenderCurrentMenuView)
        RenderCurrentMenuView;

    } // namespace Rendering_Func
} // namespace UI
} // namespace OpenSHC
