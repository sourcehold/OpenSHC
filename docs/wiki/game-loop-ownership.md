# Game-loop ownership

This describes the original Crusader 1.41 executable with SHA-256
`3bb0a8c1e72331b3a30a5aa93ed94beca0081b476b04c1960e26d5b45387ac5a`.
Addresses identify original instructions, not replacement DLL addresses.
Extreme must be inspected separately.

## The outer iteration

`WinMain` (`57BE10`) owns the Windows message pump and the budget of calls into
the game. A pending Windows message takes the dispatch path instead of the
ordinary update/render path. An unfocused solitary/single-player game takes a
waiting path; multiplayer can continue without focus.

The ordinary path has this order:

1. Time-based message/video selection, modifier keys, menu transitions, ambient
   music, network receive, and focused mouse/cursor updates.
2. Synchrony chooses `gameTicksThisLoop` (`487A30`). Synchronized autosave and
   viewport bookkeeping run before the inner loop.
3. For each budgeted iteration: execute waiting commands (`4892F0`), call
   `processGameTick` (`45CD10`), receive network traffic (`490690`), process Bink
   frames (`409200`), and update tactical help (`4D9D90`). `DAT_GameHalted` can
   break the loop before `performedGameTicksThisLoop` increments.
4. Lag checks, focused menu/input handling, world rendering, another Bink
   processing call, menu rendering, audio and display presentation.

Consequently, a rendered frame, a command batch, a call to `processGameTick`, and
a match-clock increment are distinct events. A zero budget omits step 3 but not
all menu, input, audio or receive activity. Multiple budgeted iterations occur
before the next ordinary render/input pass.

The existing [WinMain reconstruction (PR #202)](https://github.com/sourcehold/OpenSHC/pull/202)
contains this outer call order. The implementation here complements that work
by reconstructing the tick coordinator it calls.

## The tick orchestrator

[processGameTick.cpp](../../src/OpenSHC/Game/GameStateStructures/processGameTick.cpp)
preserves the original order and delegates subsystem work through existing
resolvers. It does not implement those subsystems again.

| Phase | Native evidence | Owner and behavior |
| --- | --- | --- |
| Save/synchronization | `45CD10`–`45CDE3` | Synchrony may service a host state machine, advance a client handshake and queue its reply, or return without world work. |
| Timed external decision | `45CDE4`–`45CE15` | An expired quit-vote request queues a command using Windows time. This precedes the clock gate. |
| Clock advancement | `45CE16`–`45CE68` | In-game/menu/pause checks guard RNG2, RNG1, match-clock increment, then `processSingleTimeTick` (`45CA20`). |
| Map maintenance | `45CE69`–`45CEF7` | Orientation, height/view layers, navigation, building linkage, siege starting costs and minimap markers. This phase does not require a clock increment. |
| World admission | `45CEF8`–`45CF55` | Rotation/refresh can bypass the later logical/menu pause test. Editor halt and in-game checks follow. |
| World update | `45CF56`–`45D055` | Reset statistics; wind/navigation; buildings; terrain/events; defeat/AI; units/entities; food/population; tribes/wildlife; remaining map/UI bookkeeping. |

The two pause gates are not interchangeable. A height/view refresh can set
`DAT_RotateMapOrPullDownTerrain`, permitting world updates without a clock
increment. A negative logical-pause value also has explicit behavior at the
later gate: it is reset to zero. A replacement must preserve these branches
even if their ownership would be different in a redesigned engine.

`processSingleTimeTick` is itself an owner of scheduled game work, rather than
just an integer increment: it dispatches work from `gameTicksLoadBalancer`,
advances its [200-step cycle](load-balancing-table.md) and handles
calendar/network timing. The subsequent
world phase must not be mistaken for the only simulation owner.

The native calendar call uses the global game-state receiver. The statistics,
food/population and final army-limit calls use the incoming `this` receiver.
That distinction is preserved in the C++ implementation.

## Cross-boundary dependencies

- Navigation maintenance has its own schedule. `updateSeparateAreaTileMap`
  (`4995E0`) decrements `MapAndTimeState::counterForUpdatingSeparateAreaTileMaps`
  (`117CAD8`) per invocation. It returns while the count is positive, otherwise
  resets it to 200 and checks `PathFindingState + 6C`. A dirty map increments
  the revision at `+74`, clears that flag and rebuilds connectivity regions,
  zone sizes and building linkage. The countdown is serialized in section 1023;
  it is not derived solely from the match clock.
  `canUnitReachAdjacentTile` (`4105F0`) reads the unit's and neighboring tiles'
  connectivity regions and passes them to the navigation query (`4A5320`).
  That adjacent-tile query is called by the unit-controls UI (`4348D0`). There
  is also a simulation consumer: `UpdateLord` calls
  `canNavigateToDefensiveBuilding` (`40AC80`) at `56C8A1` and `56D0E9`; its
  returned building ID controls the lord's state and target writes. Thus the
  maintenance phase owns inputs to gameplay decisions, even on a paused call.
  This establishes a dependency, not a reproduced desynchronization cause.
  The tick passes `forceUpdate = 0`; nonzero callers force the count to zero
  and mark the map dirty before the decrement. Preparation and
  `traceAndCommitPathPlan` also call this owner. Equal countdown samples alone
  therefore cannot establish equal call history.
- Commands are constructed/received before they are selected and executed.
  Their handlers run before the tick call in `WinMain`; the selector's limit
  of 100 applies to one selection invocation, not to a unique match-clock value.
- `updateBuildings` reads `performedGameTicksThisLoop` to derive
  `isFirstTickInLoop`. This is an explicit dependency on outer-loop grouping.
  The direct readers found are armory/granary visual activity and
  `updateVisuallyActiveState` (`410290`); the mill temporarily forces this flag
  while updating its visual activity. These writes identify the next ownership
  boundary, not proof that every downstream reader is presentation-only.
- The field `BuildingsState::unknownCountdown01` is not a time counter in its
  observed writers. `setupBuildingData` (`420D20`) decrements it;
  `updateBuildings` (`422E20`, store at `423333`) rebuilds it as
  `2000 - structCount`. AI placement compares it with remaining-capacity
  thresholds. Its reset to 2000 during preparation is distinct from restoring
  serialized scheduling fields.
- Crusader's `TacticalPowersFill` (`4D9D90`) decrements a help-display timeout
  and clears the display flag when it reaches zero. This function does not
  replenish an army or execute a tactical action.
- `processBinkFrames` operates on two Bink slots and their sound/end-of-video
  flags. `stopBinkPlayback` (`408E30`) calls `BinkClose` and clears the slot's
  handle. Closing slot 1 also clears `GameCore::isBinkVideoPlaying` and sets
  `GameCore::countdown` to 1. The latter is consumed by viewport/menu refresh
  bookkeeping (`46BB20`, `WinMain`), rather than the match clock.

The Bink library owns its internal allocations; clearing a game-side handle is
not proof of leak-free library behavior. Likewise, classifying these direct
writes does not certify every downstream menu handler as simulation-neutral.

## Navigation maintenance and worker population

The connectivity map also participates in ordinary workers' movement recovery.
In `UnitsState::processUnitMove` (`578C40`), a failed tile move or an outstanding
retry enters the recovery path. After the retry delay expires, it validates the
destination and reads the source and destination `PathConnectionLayer` regions.
A zero destination region rejects the route immediately. Otherwise the movement
owner calls `calculateCanPlayerUnitsNavigateToAreaFromArea` (`4A5320`), whose
initial checks reject a route between different regions if either region is zero.

An invalid or unreachable destination does not have the same result for every
unit. Lords and selectable units return without being marked for removal; a
caged dog has its walking state cleared. An ordinary nonselectable worker is
assigned `US_DISAPPEAR` and its update tracker is cleared (`579211`). This is a
state transition, not an immediate free of the unit slot. The unit lifecycle
subsequently removes it, and the population census observes the changed counts.

This connects two phases of the coordinator: navigation maintenance supplies a
movement decision, and `computePopulationStatistics` runs after the unit update.
The next clocked `processPeasantSpawnAndDespawnCycle` can admit a peasant when
that census has freed population capacity. A ready population clock alone is
therefore insufficient to explain when a peasant spawns.

Buildings own tile occupancy and linkage changes; navigation owns connectivity
rebuilding; movement owns recovery and disappearance; the census owns population
accounting. The refresh countdown schedules a rebuild rather than directly
spawning or deleting a unit. Its per-call scheduling matters because maintenance
can run while the match clock is stationary.

## Scheduling is distinct from network agreement

`determineGameTicksToPerform` (`487A30`) owns how much work the outer loop
attempts before rendering. It returns zero outside a match or when
`DAT_GameHalted` is set. Otherwise it uses elapsed milliseconds, carry and game
speed to choose the budget. Its single-player path updates synchrony's local
clock from the match clock; its multiplayer path first calls the peer-time
adjustment routine (`47E5B0`). The logical pause field checked inside
`processGameTick` is a different gate. A zero work budget, a network halt and
a paused tick must therefore be distinguished when tracing a stalled game.

The budget does not itself certify agreement between peers. Timed-command
selection owns due/order decisions; immediate receive handlers can mutate state
outside that selection; synchronization checks and replacement transfers have
their own owners. The [command/network reconstruction (PR #220)](https://github.com/sourcehold/OpenSHC/pull/220)
describes those paths. Following the chain requires comparing the first differing
decision and its inputs, not inferring a transport defect from a later checksum.

One concrete question is whether a clock-only trace has omitted intervening
maintenance calls. Another is whether recovery has restored the state consumed
by the next command or tick. The navigation dependency above explains why these
are separate proof obligations. Neither observation establishes that the
original multiplayer synchronization algorithm is faulty.

## Scope of the reconstruction

The tick also has callers outside `WinMain`, including map preparation
(`512778`) and UI/editor paths (`42FA04`, `4ABFA4`). Entering or returning from it
alone does not establish an ordinary match step, a complete load, or a safe
point to replace the world beneath an outer caller.

This orchestration map establishes where to inspect a state difference: the
responsible subsystem, the phase in which it runs, its input fields, and their
writers. It does not attribute a particular desynchronization to an unmeasured
counter, frame grouping, resource leak or callback.
