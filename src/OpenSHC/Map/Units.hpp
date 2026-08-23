/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Units.hpp'
*/

#pragma once

#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::States::UnitState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        int __cdecl FindFirstOpponentWithKeep();

        void __cdecl DetachLadderman(int unitID);

        void __cdecl UpdateSiegeTent();

        void __cdecl UpdateBurningAnimal1();

        void __cdecl UpdateBurningAnimal2();

        void __cdecl IncrementAndOptionalUpdateAVValueRelated(int unitID, BOOLEnum updateAV);

        BOOLEnum __cdecl ConsiderHavingABreakNowUnk(int unitID, UnitState nextUnitState);

        undefined4 __cdecl SetStateToFreetimeWalking(int unitID, int shouldFindNewGoodThing, int param_3);

        BOOLEnum __cdecl CheckUnitProductionPaused(int param_1);

        int __cdecl ComputeGoodsProduced(int unitID, int goodsCount, BOOLEnum boost);

        void __cdecl WarnIfPlayersGranaryIsFull();

        uint __cdecl PlayStockpileIsFullWarning();

        void __cdecl PlayArmoryIsFullWarning();

        BOOLEnum __cdecl CurrentUnitHasHealer();

        void __cdecl UpdateBurningMan();

        void __cdecl UpdateCamel();

        void __cdecl UpdateShield();

        BOOLEnum __cdecl UpdateWorker_ConsiderTakingABreakUnk(int unitID);

        void __cdecl UpdatePeasant();

        void __cdecl UpdateOx();

        void __cdecl UpdateMiner();

        void __cdecl UpdateHealer();

        void __cdecl UpdateInnkeeper();

        void __cdecl UpdateMerchant();

        void __cdecl UpdateMerchantHorse();

        void __cdecl UpdateDeer();

        void __cdecl UpdateRabbit();

        void __cdecl UpdateCow();

        void __cdecl UpdateFireWatch();

        void __cdecl UpdateGhost();

        void __cdecl UpdateLady();

        void __cdecl UpdateSiegeTower();

        void __cdecl UpdateBatteringRam();

        void __cdecl UpdateChicken();

        void __cdecl UpdateMother();

        void __cdecl UpdateChild();

        void __cdecl UpdateJuggler();

        void __cdecl UpdateFireEater();

        BOOLEnum __cdecl SetRestingForUnit(int unitID);

        void __cdecl UpdateWoodcutter();

        void __cdecl UpdateFletcher();

        void __cdecl UpdateTunneler();

        void __cdecl UpdateHunter();

        void __cdecl UpdateQuarryMason();

        void __cdecl UpdateQuarryWorker();

        void __cdecl UpdatePitchman();

        void __cdecl UpdateWheatFarmer();

        void __cdecl UpdateHopsFarmer();

        void __cdecl UpdateAppleFarmer();

        void __cdecl UpdateDairyFarmer();

        void __cdecl UpdateMiller();

        void __cdecl UpdateBaker();

        void __cdecl UpdateBrewer();

        void __cdecl UpdatePoleTurner();

        void __cdecl UpdateBlacksmith();

        void __cdecl UpdateArmorer();

        void __cdecl UpdateTanner();

        void __cdecl UpdateCrusaderArcher();

        void __cdecl UpdateCrossbowman();

        void __cdecl UpdateSpearman();

        void __cdecl UpdatePikeman();

        void __cdecl UpdateMaceman();

        void __cdecl UpdateSwordsman();

        void __cdecl UpdateKnight();

        void __cdecl UpdateLadderman();

        void __cdecl UpdateEngineer();

        void __cdecl UpdateMinerIronFetcher();

        void __cdecl UpdatePriest();

        void __cdecl UpdateDrunkard();

        void __cdecl UpdateMonk();

        void __cdecl UpdateCatapult();

        void __cdecl UpdateTrebuchet();

        void __cdecl UpdateMangonel();

        void __cdecl UpdateLion();

        void __cdecl UpdateHunterDog();

        void __cdecl UpdateLord();

        void __cdecl UpdateJester();

        void __cdecl UpdateBallista();

        void __cdecl UpdateCageDog();

        void __cdecl UpdateArabianArcher();

        void __cdecl UpdateSlave();

        void __cdecl UpdateSlinger();

        void __cdecl UpdateAssassin();

        void __cdecl UpdateHorseArcher_DoShooting(short* unitID);

        void __cdecl UpdateArabianSwordsman();

        void __cdecl UpdateFireThrower();

        void __cdecl UpdateFireBallista();

        void __cdecl UpdateHorseArcher();

    } // namespace Units
} // namespace Map
} // namespace OpenSHC
