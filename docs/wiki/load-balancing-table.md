
### Load balancing in the core game engine
In an ideal world, the game computes everything at every tick, however, this will slow the game down over time (e.g. when unit count becomes large). The game solves this by load-balancing ticks: not all actions are performed each tick, but actions are distributed across ticks.

In this article, a table is presented with a summarized form of what occurs at every tick.

One load-balance cycle is 200 ticks (0 - 199), after which count starts from 0 again.

#### Table of always load-balanced stuff
(source: `processSingleTimeTick`)

| Tick (0 - 199) | Function called (and key args)                                                                       |
| -------------------------------: | ---------------------------------------------------------------------------------------------------- |
|0|In multiplayer, check resync by computing hashes of game data|
|0|Update greatest lord, but not in the first cycle of load-balancing of a match|
|0|Recompute sync hashes|
|                            10–18 | `recomputeTroopValuesForPlayer` → players 0–8    |
|                               25 | `setTreeSpreadInterval`                                    |
|                               31 | `createStatsPopUpEntities`                                                           |
|                               34 | `recountTotalTroopValue`                          |
|                               40 | `moatRelatedUpdateFunction`                                    |
|                            60–68 | `recomputeTroopValuesForPlayer` → players 0–8    |
|                            71–78 | `updateEnemyBuildings` → indices 1–8 |
|                               80 | `spawnMotherOrChild`                                                                 |
|                               93 | `recomputeTotalTroopValueOfTroopsNearKeep`        |
|                               95 | `processPeasantsForBuildings`                                                        |
|                               99 | `showPopAndGoldPopup`                                                                |
|                          101–108 | `recomputeTroopValuesForPlayer` → players 1–8   |
|                          110–149 | `updateWildlifeGrid` → grid slice 0–39           |
|                              150 | `updateWildlife`                                             |
|                              151 | `updateSection1034Info`                                      |
|                              152 | `updateNofFpoints`                                           |
|                          160–168 | `recomputeTroopValuesForPlayer` → players 0–8   |
|                              180 | `spawnChicken`                                                                       |
|                              190 | `recountStablesAndHorses`                                                            |

##### Things that are not load-balanced:
- Checking game sync status as this is performed by the host at the game time we know hashes for


#### Load-balancing in calendar modes

##### Time in the game
One load-balance cycle corresponds to a week in game time. After 200 ticks (0 - 199), the cycle is started from 0 again.

|What|Ticks|Day|Week|Month|Year|
|----|-----|-----|-----|-----|-----|
|Day|50|1|1/4|1/16|1/192|
|Week|200|4|1|1/4|1/48|
|Month|800|16|1/4|1|1/12|
|Year|9600|192|48|12|1|
|**Load-balance cycle**|200|4|1|1/4|1/48|

Note: In EDITOR mode and SIEGE THAT mode, there is no concept of time. In the other game modes, time works like in the table.

Note 2: While the on-screen instruction to place keep and/or granary is showing, then weeks, months, and years are not counted yet.

##### Table of calendar-based balancing

| Tick (0 - 199) | Function called (and key args)                                                                       |
|--:|:--|
|0|updateCrowding|
|0|updateTrader|
|0|updateTaxing|
|0|updateAleRate|
|0|recomputeAllFearFactors|
|0|updateFearFactorProductivity|
|0|updateReligionBonuses|
|0|updatePopularity|
|0-199|(de)spawn peasants (tick the campfire clock)|
|||

### More game ticks
source: `processGameTick`

With the calendar-based ticks out of the way, the game also balances several other computations.

|Tick|What|
|--:|:--|
|0-199|updateWind (a wind cycle is 32 ticks)|
|0-199|updateClimbData (a wind cycle is 32 ticks)|
|0-199|updateBuildings (a wind cycle is 32 ticks)|
|(tick % 10) == 5|recount amount of buildings|
|0-199|updateBuildings|
|(tick % 20) == 5|apply damage to burning buildings|
|(tick % 20) == 3|recount amount of pitch ditches|
|0-199|updatePitchDitches|
|(tick % 10) == 8|recount amount of trees|
|(tick % 8) == 4|random tree (growth?)|
|0-199|update trees|
|0-199|single player events|
|every day|"Once more unto the breach"|
|every month|recompute resources in stock|
|every day's 10th tick|make Outpost tribes attack|
|day tick == ai player id|recruit units, buy and sell goods, raid|
|week tick == ai player id|recruit oil duty, update tribe locations, update AI state, update taxes and rations, set food buy plan|
|week tick == ai player and month tick != ai player|reconsider strength/weak in Extreme trail|
|month tick == ai player|moat instructions, sortie units, reconsider strength/weak, destroy buildings, recruit raiding units preferably, select attack target, update recruit gold threshold status |
|every week| update path linkage layer, update heatmap, disappear units that can't reach the keep |
|day tick == ai player|decide on new ai buildings, snooze buildings, buying plan for low resources|
|day tick == 8|propagate building sleep to all buildings of that type|
|month tick == 10|recompute heat maps|
|every 64 ticks|set troop value of player to 0 and recompute it|
|every tick| update units |
|every 64 ticks|assign citizen name to unit|
|unit dependent notice frequency|notice enemy units|
|every tick|update entities|
|every tick|remove unit chaining on same tiles|
|every tick|update food|
|every month|give food warning|
|every day|update population growth|
|every month|moving average of population|
|every tick|update tribe unit assignments|
|(tick % 32) == (tribe id % 32)|compute tribe percentage|
|every tick|update tribe behavior|
|every tick|recompute army size limit based on alive player count|