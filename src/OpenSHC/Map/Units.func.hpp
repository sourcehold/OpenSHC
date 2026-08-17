/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units.func.hpp'
*/

#pragma once

#include "OpenSHC/Map/Units.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace Map {
    namespace Units_Func {

        using OpenSHC::Map::Units::States::UnitState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        MACRO_FUNCTION_RESOLVER(
            int(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0051BE20, &OpenSHC::Map::Units::FindFirstOpponentWithKeep)
        FindFirstOpponentWithKeep;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(int unitID), false, Address::SHC_3BB0A8C1_0x00530760, &OpenSHC::Map::Units::DetachLadderman)
        DetachLadderman;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x005307B0, &OpenSHC::Map::Units::UpdateSiegeTent)
        UpdateSiegeTent;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x005309E0, &OpenSHC::Map::Units::UpdateBurningAnimal1)
        UpdateBurningAnimal1;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00530A90, &OpenSHC::Map::Units::UpdateBurningAnimal2)
        UpdateBurningAnimal2;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int unitID, BOOLEnum updateAV), false, Address::SHC_3BB0A8C1_0x00530B40,
            &OpenSHC::Map::Units::IncrementAndOptionalUpdateAVValueRelated)
        IncrementAndOptionalUpdateAVValueRelated;

        MACRO_FUNCTION_RESOLVER(BOOLEnum(__cdecl*)(int unitID, UnitState nextUnitState), false,
            Address::SHC_3BB0A8C1_0x00530C40, &OpenSHC::Map::Units::ConsiderHavingABreakNowUnk)
        ConsiderHavingABreakNowUnk;

        MACRO_FUNCTION_RESOLVER(undefined4(__cdecl*)(int unitID, int shouldFindNewGoodThing, int param_3), false,
            Address::SHC_3BB0A8C1_0x00530CF0, &OpenSHC::Map::Units::SetStateToFreetimeWalking)
        SetStateToFreetimeWalking;

        MACRO_FUNCTION_RESOLVER(bool(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00530D50,
            &OpenSHC::Map::Units::CheckUnitProductionPaused)
        CheckUnitProductionPaused;

        MACRO_FUNCTION_RESOLVER(int(__cdecl*)(int unitID, int goodsCount, BOOLEnum boost), false,
            Address::SHC_3BB0A8C1_0x00530D70, &OpenSHC::Map::Units::ComputeGoodsProduced)
        ComputeGoodsProduced;

        MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00530E00,
            &OpenSHC::Map::Units::WarnIfPlayersGranaryIsFull)
        WarnIfPlayersGranaryIsFull;

        MACRO_FUNCTION_RESOLVER(uint(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00530EB0,
            &OpenSHC::Map::Units::PlayStockpileIsFullWarning)
        PlayStockpileIsFullWarning;

        MACRO_FUNCTION_RESOLVER(
            void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00530F20, &OpenSHC::Map::Units::PlayArmoryIsFullWarning)
        PlayArmoryIsFullWarning;

        MACRO_FUNCTION_RESOLVER(
            BOOLEnum(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0053A020, &OpenSHC::Map::Units::CurrentUnitHasHealer)
        CurrentUnitHasHealer;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0053BC20, &OpenSHC::Map::Units::UpdateBurningMan)
        UpdateBurningMan;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0053BE00, &OpenSHC::Map::Units::UpdateCamel)
        UpdateCamel;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0053C300, &OpenSHC::Map::Units::UpdateShield)
        UpdateShield;

        MACRO_FUNCTION_RESOLVER(BOOLEnum(__cdecl*)(int unitID), false, Address::SHC_3BB0A8C1_0x0053CAC0,
            &OpenSHC::Map::Units::UpdateWorker_ConsiderTakingABreakUnk)
        UpdateWorker_ConsiderTakingABreakUnk;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0053EAA0, &OpenSHC::Map::Units::UpdatePeasant)
        UpdatePeasant;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0053F940, &OpenSHC::Map::Units::UpdateOx)
        UpdateOx;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x005401D0, &OpenSHC::Map::Units::UpdateMiner)
        UpdateMiner;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00540440, &OpenSHC::Map::Units::UpdateHealer)
        UpdateHealer;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00540EC0, &OpenSHC::Map::Units::UpdateInnkeeper)
        UpdateInnkeeper;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x005416B0, &OpenSHC::Map::Units::UpdateMerchant)
        UpdateMerchant;

        MACRO_FUNCTION_RESOLVER(
            void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00541A30, &OpenSHC::Map::Units::UpdateMerchantHorse)
        UpdateMerchantHorse;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00541DE0, &OpenSHC::Map::Units::UpdateDeer)
        UpdateDeer;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00542630, &OpenSHC::Map::Units::UpdateRabbit)
        UpdateRabbit;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00542D10, &OpenSHC::Map::Units::UpdateCow)
        UpdateCow;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00543340, &OpenSHC::Map::Units::UpdateFireWatch)
        UpdateFireWatch;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00543B80, &OpenSHC::Map::Units::UpdateGhost)
        UpdateGhost;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00543DC0, &OpenSHC::Map::Units::UpdateLady)
        UpdateLady;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00544750, &OpenSHC::Map::Units::UpdateSiegeTower)
        UpdateSiegeTower;

        MACRO_FUNCTION_RESOLVER(
            void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x005459B0, &OpenSHC::Map::Units::UpdateBatteringRam)
        UpdateBatteringRam;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x005464F0, &OpenSHC::Map::Units::UpdateChicken)
        UpdateChicken;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00546BC0, &OpenSHC::Map::Units::UpdateMother)
        UpdateMother;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x005477C0, &OpenSHC::Map::Units::UpdateChild)
        UpdateChild;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00549090, &OpenSHC::Map::Units::UpdateJuggler)
        UpdateJuggler;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00549650, &OpenSHC::Map::Units::UpdateFireEater)
        UpdateFireEater;

        MACRO_FUNCTION_RESOLVER(undefined4(__cdecl*)(int unitID), false, Address::SHC_3BB0A8C1_0x00549B30,
            &OpenSHC::Map::Units::SetRestingForUnit)
        SetRestingForUnit;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0054C710, &OpenSHC::Map::Units::UpdateWoodcutter)
        UpdateWoodcutter;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0054D8F0, &OpenSHC::Map::Units::UpdateFletcher)
        UpdateFletcher;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0054E6C0, &OpenSHC::Map::Units::UpdateTunneler)
        UpdateTunneler;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0054F860, &OpenSHC::Map::Units::UpdateHunter)
        UpdateHunter;

        MACRO_FUNCTION_RESOLVER(
            void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00550A50, &OpenSHC::Map::Units::UpdateQuarryMason)
        UpdateQuarryMason;

        MACRO_FUNCTION_RESOLVER(
            void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00550D70, &OpenSHC::Map::Units::UpdateQuarryWorker)
        UpdateQuarryWorker;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00551980, &OpenSHC::Map::Units::UpdatePitchman)
        UpdatePitchman;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x005521D0, &OpenSHC::Map::Units::UpdateWheatFarmer)
        UpdateWheatFarmer;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00552F80, &OpenSHC::Map::Units::UpdateHopsFarmer)
        UpdateHopsFarmer;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00553AE0, &OpenSHC::Map::Units::UpdateAppleFarmer)
        UpdateAppleFarmer;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00554500, &OpenSHC::Map::Units::UpdateDairyFarmer)
        UpdateDairyFarmer;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00554CC0, &OpenSHC::Map::Units::UpdateMiller)
        UpdateMiller;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00555880, &OpenSHC::Map::Units::UpdateBaker)
        UpdateBaker;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x005565D0, &OpenSHC::Map::Units::UpdateBrewer)
        UpdateBrewer;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00557230, &OpenSHC::Map::Units::UpdatePoleTurner)
        UpdatePoleTurner;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00557F70, &OpenSHC::Map::Units::UpdateBlacksmith)
        UpdateBlacksmith;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00558CB0, &OpenSHC::Map::Units::UpdateArmorer)
        UpdateArmorer;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x005598D0, &OpenSHC::Map::Units::UpdateTanner)
        UpdateTanner;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0055A800, &OpenSHC::Map::Units::UpdateCrusaderArcher)
        UpdateCrusaderArcher;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0055C7B0, &OpenSHC::Map::Units::UpdateCrossbowman)
        UpdateCrossbowman;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0055DA50, &OpenSHC::Map::Units::UpdateSpearman)
        UpdateSpearman;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0055F110, &OpenSHC::Map::Units::UpdatePikeman)
        UpdatePikeman;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00560700, &OpenSHC::Map::Units::UpdateMaceman)
        UpdateMaceman;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00561C10, &OpenSHC::Map::Units::UpdateSwordsman)
        UpdateSwordsman;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00562AA0, &OpenSHC::Map::Units::UpdateKnight)
        UpdateKnight;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00563910, &OpenSHC::Map::Units::UpdateLadderman)
        UpdateLadderman;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00564250, &OpenSHC::Map::Units::UpdateEngineer)
        UpdateEngineer;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00566010, &OpenSHC::Map::Units::UpdateMinerIronFetcher)
        UpdateMinerIronFetcher;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00566750, &OpenSHC::Map::Units::UpdatePriest)
        UpdatePriest;

        MACRO_FUNCTION_RESOLVER(
            void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00567320, &OpenSHC::Map::Units::UpdateDrunkard)
        UpdateDrunkard;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00567640, &OpenSHC::Map::Units::UpdateMonk)
        UpdateMonk;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00568320, &OpenSHC::Map::Units::UpdateCatapult)
        UpdateCatapult;

        MACRO_FUNCTION_RESOLVER(
            void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00569410, &OpenSHC::Map::Units::UpdateTrebuchet)
        UpdateTrebuchet;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0056A3F0, &OpenSHC::Map::Units::UpdateMangonel)
        UpdateMangonel;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0056B0E0, &OpenSHC::Map::Units::UpdateLion)
        UpdateLion;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0056B970, &OpenSHC::Map::Units::UpdateHunterDog)
        UpdateHunterDog;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0056C560, &OpenSHC::Map::Units::UpdateLord)
        UpdateLord;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0056E190, &OpenSHC::Map::Units::UpdateJester)
        UpdateJester;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0056ECD0, &OpenSHC::Map::Units::UpdateBallista)
        UpdateBallista;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0056F9B0, &OpenSHC::Map::Units::UpdateCageDog)
        UpdateCageDog;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00570400, &OpenSHC::Map::Units::UpdateArabianArcher)
        UpdateArabianArcher;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00571C00, &OpenSHC::Map::Units::UpdateSlave)
        UpdateSlave;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00572E80, &OpenSHC::Map::Units::UpdateSlinger)
        UpdateSlinger;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x005744D0, &OpenSHC::Map::Units::UpdateAssassin)
        UpdateAssassin;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(short* unitID), false, Address::SHC_3BB0A8C1_0x00575820,
            &OpenSHC::Map::Units::UpdateHorseArcher_DoShooting)
        UpdateHorseArcher_DoShooting;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00575C40, &OpenSHC::Map::Units::UpdateArabianSwordsman)
        UpdateArabianSwordsman;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x005769F0, &OpenSHC::Map::Units::UpdateFireThrower)
        UpdateFireThrower;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00577CC0, &OpenSHC::Map::Units::UpdateFireBallista)
        UpdateFireBallista;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0057AB50, &OpenSHC::Map::Units::UpdateHorseArcher)
        UpdateHorseArcher;

    } // namespace Units_Func
} // namespace Map
} // namespace OpenSHC
