==================================
Frequently Asked Questions (FAQ)
==================================

Why?
====

The original game is a masterpiece, seeing new reignited popularity since the release of the Definitive Edition.
However, the Definitive Edition does not address various `shortcomings` in the original game.
Furthermore, the new Definitive Edition requires modern hardware to run, which isn't something all fans can afford.

This reimplementation seeks to cater to the wishes of the dedicated community by providing an
open source reimplementation that permits modding.


An open source Stronghold Crusader has been tried before, why will it work this time?
===========================================================================================
The current project has several key strategies that will more likely make it a success.

#. The current project focuses on fidelity to the original game. This means the goals are clear: reimplement the original engine. Stronghold Crusader is a game where many players have different experiences playing the same game. Some play it as a simulation, others as a Real Time Strategy, and others watch AI battle each other. Focusing on a reimplementation focuses our energy on the same goal, rather than trying to recreate different games.

#. The current project builds on the knowledge in the Sourcehold network of people. The sourcehold project has more than half a decade of working with the details of the game and therefore there is a lot of knowledge that can be transferred to a reimplementation to pull off a reimplementation.

#. A reimplementation sets clear expectations for the outcome and the usefulness of the end-product. Everyone knows what to expect because everyone can be made familiar with the original game. Original creations such as maps, ais, and save games should be compatible.

Will the end-product be free of charge?
===========================================================================================
Yes.


Am I free to make a spin-off of the current reimplementation?
===========================================================================================
Yes and no. The spin-off needs to give credit to this project and the spin-off needs to be open source and free of charge. This is to protect the effort invested by contributors: contributors may be less inclined to contribute to a private project than a common-good.


What Software and programming language is the reimplementation using?
======================================================================
In order to be a true reimplementation it should work on machines on which the original game also works. Preferably, the same kind of performance level is retained. Thus, for performance-sensitive code, we will be mostly using C and C++. For other parts of the project (mods), we could rely on another software paradigm such lua or python.

What skills do I need, in order to contribute?
============================================================================
You need to be able to read (basic) C and C++ code. You need to understand, or have the willingness to understand, the original game. The main programs we use to understand the original game are Ghidra (static analysis), and x64dbg and CheatEngine (dynamic analysis).

Why not use a framework such as Unity, Löve2D, or X?
===========================================================
The main reason is that each framework comes with downsides that typically either hurt performance, compatibility, development (being bloated), or stability. As C and C++ are close to machine code (especially C), writing in these languages comes with the benefit of comparability with the bytecode of the original game.