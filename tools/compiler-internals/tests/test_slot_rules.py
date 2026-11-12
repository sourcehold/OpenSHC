"""Regression tests for the decoded stack-slot rules (msvc-backend.md, "The slot tiebreak, decoded").

    python tools/compiler-internals/tests/test_slot_rules.py        (or: python -m pytest tools/compiler-internals/tests)

No compiler, no cdb: the fixtures are recorded slot_probe.py traces (the AddStackElement call
sequence and the element list c2 built from it), so the tests pin the *rule* - if someone edits
simulate() or regime() and a recorded compile no longer replays, that is the regression.

Fixtures (tools/compiler-internals/tests/fixtures/*.json), each from one c2.dll run:
  tracePathPlanToDestinationViaUnoccupiedTiles-204   the function the rule was decoded on
  renameC-204 / declD-204 / splitB-204               its _direction->_dirn rename, declaration swap,
                                                     and split-asm variants (only the rename changes the list)
  findSuitableSpawnLocationUnk-202, findLinkageBasedPathOrWalkRadius-202, updateSeparateAreaTileMap-701
  nameRank-1                                         39 asm-written locals, a 0x9c frame: the sort DID run
"""
import glob
import io
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, '..'))
sys.path.insert(0, os.path.join(HERE, '..', '..', 'reimplementation-helper', 'batch'))
import slot_probe  # noqa: E402

FIXTURES = sorted(glob.glob(os.path.join(HERE, 'fixtures', '*.json')))


def load(path):
    return json.load(io.open(path, encoding='utf-8'))


def test_simulate_replays_every_recorded_list():
    assert FIXTURES, 'no fixtures'
    for path in FIXTURES:
        fx = load(path)
        got = [e for e, _s, _w in slot_probe.simulate(fx['adds'])]
        want = [e for e, _s, _w, _n in fx['list']]
        assert got == want, '%s: simulate() order differs from the recorded list' % os.path.basename(path)
        weights = dict((e, w) for e, _s, w in slot_probe.simulate(fx['adds']))
        for e, _s, w, _n in fx['list']:
            assert weights[e] == w, '%s: weight of %s is %d, recorded %d' % (os.path.basename(path), e, weights[e], w)


def test_list_is_weight_descending_within_size():
    for path in FIXTURES:
        fx = load(path)
        lst = fx['list']
        for a, b in zip(lst, lst[1:]):
            if a[1] == b[1]:
                assert a[2] >= b[2], '%s: %s (wt %d) before %s (wt %d)' % (os.path.basename(path), a[3], a[2], b[3], b[2])
            else:
                assert a[1] < b[1], '%s: sizes not ascending' % os.path.basename(path)


def names(fx):
    return [n for _e, _s, _w, n in fx['list']]


def test_rename_moves_the_pair_and_declaration_order_does_not():
    base = load(os.path.join(HERE, 'fixtures', 'tracePathPlanToDestinationViaUnoccupiedTiles-204.json'))
    assert names(base)[:4] == ['_ppIndex', '_direction', '_budget', '_result']
    decl = load(os.path.join(HERE, 'fixtures', 'declD-204.json'))
    assert names(decl)[:4] == names(base)[:4], 'swapping declarations must not move the pair'
    split = load(os.path.join(HERE, 'fixtures', 'splitB-204.json'))
    assert names(split)[:4] == names(base)[:4], 'splitting the __asm block must not move the pair'
    ren = load(os.path.join(HERE, 'fixtures', 'renameC-204.json'))
    assert names(ren)[:4] == ['_ppIndex', '_budget', '_dirn', '_result'], 'the rename is what flips the pair'


def test_list_order_is_the_frame_when_the_sort_is_skipped():
    # the /FA listing of the committed tracePathPlan... (before the rename): head of the list at
    # -4, every further local 4 bytes lower, parameters (kind 5) not in the frame
    fx = load(os.path.join(HERE, 'fixtures', 'tracePathPlanToDestinationViaUnoccupiedTiles-204.json'))
    assert not fx['sorted']
    params = set(['x', 'y', 'destX', 'destY'])
    locals_ = [n for n in names(fx) if n not in params]
    listing = {'_ppIndex': -4, '_direction': -8, '_budget': -12, '_result': -16, '_pPathPlan': -20,
               '_cardinal': -24, '_dirMatrix': -28, '_linkage': -32, '_occupancy': -36, '_fireCount': -40,
               '_destTile': -44, '_gen': -48, '_tile': -52, '_walkLayer': -56, 'this': -60}
    assert [listing[n] for n in locals_] == [-4 * (i + 1) for i in range(len(locals_))]


def test_regime():
    assert slot_probe.regime(0x3c, False) == 'list-order'       # the four asm functions
    assert slot_probe.regime(0x80, False) == 'list-order'       # the boundary is `jg 0x80`
    assert slot_probe.regime(0x84, False) == 'sorted'
    assert slot_probe.regime(0x9c, False) == 'sorted'           # nameRank-1 recorded SORTED
    assert slot_probe.regime(0x10, True) == 'sorted'            # a /GS buffer sorts any frame
    try:                             # slot_map's import chain opens the build directory, so only
        import slot_map              # cross-check the two copies of the rule when one is configured
    except (ImportError, OSError):
        slot_map = None
    if slot_map is not None:
        for frame, gs in ((0x3c, False), (0x80, False), (0x84, False), (0x9c, False), (0x10, True)):
            assert slot_map.regime(frame, gs) == slot_probe.regime(frame, gs)
    for path in FIXTURES:
        fx = load(path)
        if 'nameRank' in path:
            assert fx['sorted']
        else:
            assert not fx['sorted']


if __name__ == '__main__':
    failed = 0
    for name, fn in sorted(globals().items()):
        if name.startswith('test_') and callable(fn):
            try:
                fn()
                print('ok   ', name)
            except AssertionError as e:
                failed += 1
                print('FAIL ', name, '-', e)
    sys.exit(1 if failed else 0)
