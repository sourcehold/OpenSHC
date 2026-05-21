=======================
Contributing to OpenSHC
=======================

Ready to dive in? Here's how you can start contributing to OpenSHC.

Developing contributions
=========================

Contributions are done by contributing either:

* reimplemented source code for functions of the original game: we aim for 100% functionally identical reimplementations
* improving other's reimplementations (track progress `here <https://gynt.github.io/OpenSHC/progress.html>`)
* data structures
* other code


Contributing functions
+++++++++++++++++++++++

The functions of the original game are referenced by address. This is because the names of functions change over time, but the address never does (unless a different version of the game binary is targeted).

We use the 1.41 Latin version of the Stronghold Crusader.exe as the reference version. This exe has SHA256 hash digest `3BB0A8C1`.

For example, the function that checks if X and Y coordinates are valid coordinates is located at address 0x401000, which we refer to as `SHC_3BB0A8C1_0x401000`.

Diving right in
=========================

Here are the first two tutorials to get you going!

.. include:: wiki/tutorials/reimplementation-tutorial-0.md
   :parser: myst_parser.sphinx_

.. include:: wiki/tutorials/reimplementation-tutorial-1.md
   :parser: myst_parser.sphinx_