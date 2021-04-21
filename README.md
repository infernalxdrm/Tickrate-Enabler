## Tickrate Enabler for TF2

### Description

Enables the "-tickrate" switch to be used from the command line to set the game's tickrate.

TODO:
Patch Grenades/Stickybombs behavior to fix an issue where projectile bounce scaled inversely with tickrate.  
Patch Wrangler behaviour to fix an issue where player-controlled sentry fire speed scaled inversely with tickrate.

### Instructions

1. Place tickrate_enabler.dll (Windows) or tickrate_enabler.so (Linux) in your server's addons folder.
2. Place tickrate_enabler.vdf in your server's addons folder.
3. Add "-tickrate <desired_tickrate>" to your server's launch parameters. e.g. -tickrate 100
4. Make sure the following convar settings are properly set in server.cfg or otherwise:

    sv_maxupdaterate 100  
    sv_maxcmdrate 100

5. PROFIT!!!

### Credits

Parts of this project contain GPLv3 code adapted from SourceMod (Allied Modders L.L.C.), Left4Downtown2 (Igor Smirnov et. al.) and Tickrate Enabler for L4D/L4D2 (Michael "ProdigySim" Busby).
