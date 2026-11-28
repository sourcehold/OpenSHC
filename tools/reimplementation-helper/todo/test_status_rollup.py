"""Tie-break rules of status_rollup.best_per_id, without git or network.

    python -I tools/reimplementation-helper/todo/test_status_rollup.py
"""

import os, sys, unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from status_rollup import named_for, namespace, tie_rank, CATCHALL_SPREAD

REPOS = {
    'origin': 'sourcehold/OpenSHC',
    'sourcehold-OpenSHC': 'sourcehold/OpenSHC',
    'gynt-OpenSHC': 'gynt/OpenSHC',
    'kotijekriv-OpenSHC': 'kotijekriv/OpenSHC',
    '6and8-OpenSHC': '6and8/OpenSHC',
    'Sebauxs-OpenSHC': 'Sebauxs/OpenSHC',
    'Wilps93-OpenSHC': 'Wilps93/OpenSHC',
    'Krarilotus-OpenSHC': 'Krarilotus/OpenSHC',
}
ENTITY = 'src/OpenSHC/Map/Entities/EntityState/updateEntities.cpp'
MENU = 'src/OpenSHC/UI/BuildingMenus/RenderBuildingMenu_Keep.cpp'


def winner(refs, cpp, tips=None, spread=None):
    return min(refs, key=lambda r: tie_rank(r, cpp, REPOS, tips or {}, spread or {}))


class TieRank(unittest.TestCase):
    def test_owner_order(self):
        refs = ['Wilps93-OpenSHC/reimpl/x', 'Sebauxs-OpenSHC/reimpl/x', '6and8-OpenSHC/reimpl/x',
                'kotijekriv-OpenSHC/reimpl/x', 'gynt-OpenSHC/reimpl/x', 'sourcehold-OpenSHC/reimpl/x']
        order = sorted(refs, key=lambda r: tie_rank(r, ENTITY, REPOS, {}, {}))
        self.assertEqual(order, list(reversed(refs)))

    def test_unlisted_owner_comes_last(self):
        self.assertEqual(winner(['Krarilotus-OpenSHC/reimpl/a', 'Wilps93-OpenSHC/reimpl/b'], ENTITY),
                         'Wilps93-OpenSHC/reimpl/b')

    def test_main_first(self):
        self.assertEqual(winner(['sourcehold-OpenSHC/reimpl/map-entities', 'HEAD', 'origin/main'], ENTITY),
                         'HEAD')

    def test_owner_beats_specific_name(self):
        self.assertEqual(winner(['gynt-OpenSHC/reimpl/map-entities-functions',
                                 'sourcehold-OpenSHC/reimpl/UnitsState'], ENTITY),
                         'sourcehold-OpenSHC/reimpl/UnitsState')

    def test_specific_name_within_owner(self):
        tips = {'gynt-OpenSHC/reimpl/TroopValueState': 2, 'gynt-OpenSHC/reimpl/map-entities-functions': 1}
        self.assertEqual(winner(list(tips), ENTITY, tips), 'gynt-OpenSHC/reimpl/map-entities-functions')

    def test_catchall_names(self):
        tips = {'gynt-OpenSHC/archive/a': 9, 'gynt-OpenSHC/fix/b': 8, 'gynt-OpenSHC/development': 7,
                'sourcehold-OpenSHC/reimpl/AICState-backup': 6, 'gynt-OpenSHC/reimpl/c': 1}
        self.assertEqual(winner([r for r in tips if r.startswith('gynt')], ENTITY, tips), 'gynt-OpenSHC/reimpl/c')

    def test_catchall_spread(self):
        # both named for the namespace; the one ahead of main all over the tree loses despite a newer tip
        tips = {'gynt-OpenSHC/reimpl/UI-BuildingMenus': 1, 'gynt-OpenSHC/reimpl/UI-BuildingMenus-development': 2}
        spread = {'gynt-OpenSHC/reimpl/UI-BuildingMenus': 2,
                  'gynt-OpenSHC/reimpl/UI-BuildingMenus-development': CATCHALL_SPREAD + 1}
        self.assertEqual(winner(list(tips), MENU, tips, spread), 'gynt-OpenSHC/reimpl/UI-BuildingMenus')
        spread['gynt-OpenSHC/reimpl/UI-BuildingMenus-development'] = CATCHALL_SPREAD
        self.assertEqual(winner(list(tips), MENU, tips, spread), 'gynt-OpenSHC/reimpl/UI-BuildingMenus-development')

    def test_newest_tip_then_name(self):
        self.assertEqual(winner(['gynt-OpenSHC/reimpl/a', 'gynt-OpenSHC/reimpl/b'], ENTITY,
                                {'gynt-OpenSHC/reimpl/a': 1, 'gynt-OpenSHC/reimpl/b': 2}), 'gynt-OpenSHC/reimpl/b')
        self.assertEqual(winner(['gynt-OpenSHC/reimpl/b', 'gynt-OpenSHC/reimpl/a'], ENTITY), 'gynt-OpenSHC/reimpl/a')


class Helpers(unittest.TestCase):
    def test_namespace(self):
        self.assertEqual(namespace(ENTITY), 'Map/Entities')
        self.assertEqual(namespace(''), '')

    def test_named_for(self):
        self.assertTrue(named_for('reimpl/map-entities-functions', ENTITY))
        self.assertTrue(named_for('reimpl/TileMapState-100-2', 'src/OpenSHC/Map/TileMapState/setLand.cpp'))
        self.assertFalse(named_for('reimpl/UnitsState', ENTITY))
        self.assertFalse(named_for('reimpl/batch1-development', ENTITY))


if __name__ == '__main__':
    unittest.main()
