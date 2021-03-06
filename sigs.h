/**
 * vim: set ts=4 :
 * =============================================================================
 * BoomerVomitPatch
 * Copyright (C) 2012 Michael "ProdigySim" Busby
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, the author(s) give you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, the author(s) grant
 * this exception to all derivative works.  The author(s) define further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.sourcemod.net/license.php>.
 *
 * Version: $Id$
 */
#ifndef _SIGS_H_
#define _SIGS_H_

/* Platform specific offset+sig data */

/* CTFWeaponBaseGrenadeProj::VPhysicsUpdate() function finding */
#define LIN_VPhysicsUpdate_SYMBOL "_ZN24CTFWeaponBaseGrenadeProj14VPhysicsUpdateEP14IPhysicsObject"
/* CTFWeaponBaseGrenadeProj::ResolveFlyCollisionCustom() function finding */
#define LIN_ResolveFlyCollisionCustom_SYMBOL "_ZN24CTFWeaponBaseGrenadeProj25ResolveFlyCollisionCustomER10CGameTraceR6Vector"

/* TODO: Find sigs for Windows */
#define WIN_VPhysicsUpdate_SIG "\x55\x8B\xEC\x81\xEC\x2A\x2A\x2A\x2A\xA1\x2A\x2A\x2A\x2A\x33\xC5\x89\x45\xFC\x53\x56\x57\x8B\xF9\x8B\x87\x2A\x2A\x2A\x2A\x83"
#define WIN_VPhysicsUpdate_SIGLEN 31

#define WIN_ResolveFlyCollisionCustom_SIG "\x55\x8B\xEC\x81\xEC\x2A\x2A\x2A\x2A\xA1\x2A\x2A\x2A\x2A\x33\xC5\x89\x45\xFC\x53\x56\x57\x8B\xF9\x8B\x87\x2A\x2A\x2A\x2A\x83"
#define WIN_ResolveFlyCollisionCustom_SIGLEN 31

/* gpGlobals read offsets into CTFWeaponBaseGrenadeProj::VPhysicsUpdate() and CTFWeaponBaseGrenadeProj::ResolveFlyCollisionCustom()*/
const int g_FrameTimeReadOffsets[] =
#if defined (_LINUX)
	{0x11E, 0x290, 0x339};
#elif defined (_WIN32)
	{0x11E, 0x290, 0x339}; // TODO: Change offset
#endif
#endif // _SIGS_H_