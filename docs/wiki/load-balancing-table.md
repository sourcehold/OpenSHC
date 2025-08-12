| Game tick (0 - 199) | Function called (and key args)                                                                       |
| -------------------------------: | ---------------------------------------------------------------------------------------------------- |
|                            10–18 | `recomputeTroopValuesForPlayer(&DAT_UnitsState, gTLB - 10)` → players 0–8    |
|                               25 | `setTreeSpreadInterval(&DAT_LandscapeState)`                                    |
|                               31 | `createStatsPopUpEntities(&DAT_GameState)`                                                           |
|                               34 | `recountTotalTroopValue(&DAT_TroopValueState)`                          |
|                               40 | `moatRelatedUpdateFunction(&DAT_TileMapState)`                                    |
|                            60–68 | `recomputeTroopValuesForPlayer(&DAT_UnitsState, gTLB - 60)` → players 0–8    |
|                            71–78 | `updateEnemyBuildings(&DAT_BuildingsState, gTLB - 70)` → indices 1–8 |
|                               80 | `spawnMotherOrChild(&DAT_GameState)`                                                                 |
|                               93 | `recomputeTotalTroopValueOfTroopsNearKeep(&DAT_TroopValueState)`        |
|                               95 | `processPeasantsForBuildings(&DAT_GameState)`                                                        |
|                               99 | `showPopAndGoldPopup(&DAT_GameState)`                                                                |
|                          101–108 | `recomputeTroopValuesForPlayer(&DAT_UnitsState, gTLB - 100)` → players 1–8   |
|                          110–149 | `updateWildlifeGrid(&DAT_WildlifeState, gTLB - 110)` → grid slice 0–39           |
|                              150 | `updateWildlife(&DAT_WildlifeState)`                                             |
|                              151 | `updateSection1034Info(&DAT_WildlifeState)`                                      |
|                              152 | `updateNofFpoints(&DAT_WildlifeState)`                                           |
|                          160–168 | `recomputeTroopValuesForPlayer(&DAT_UnitsState, gTLB - 160)` → players 0–8   |
|                              180 | `spawnChicken(&DAT_GameState)`                                                                       |
|                              190 | `recountStablesAndHorses(&DAT_GameState)`                                                            |
