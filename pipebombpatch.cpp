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
#include <cstdlib>
#include "memutils.h"
#include "pipebombpatch.h"
#include "patchexceptions.h"

struct fakeGlobals {
	float padding[4];
	float frametime;
};

fakeGlobals g_FakeGlobals = { {0.0, 0.0, 0.0, 0.0}, 0.015151515 };
fakeGlobals *gp_FakeGlobals = &g_FakeGlobals;

PipeBombFrameTimePatch::PipeBombFrameTimePatch(IServerGameDLL * gamedll)
{
	InitializeBinPatches(gamedll);
}

PipeBombFrameTimePatch::~PipeBombFrameTimePatch()
{
	m_patches.UnregisterAll();
}

void PipeBombFrameTimePatch::Patch()
{
	m_patches.PatchAll();
}

void PipeBombFrameTimePatch::Unpatch() 
{
	m_patches.UnpatchAll();
}

void PipeBombFrameTimePatch::InitializeBinPatches(IServerGameDLL * gamedll)
{
	BYTE instr_buf[MAX_MOV_INSTR_LEN];

	BYTE * pVPhysicsUpdate = FindVPhysicsUpdate(static_cast<void *>(gamedll));
	DevMsg("VPhysicsUpdate at 0x%08x\n", pVPhysicsUpdate);

	if(!pVPhysicsUpdate)
	{
		throw PatchException("Couldn't find CTFWeaponBaseGrenadeProj::VPhysicsUpdate() in server memory.");
	}

	DevMsg("Setting up patch for frametime read (offs:0x%x).\n", g_FrameTimeReadOffset);

	// Calculate offset target
	BYTE * pTarget = pVPhysicsUpdate + g_FrameTimeReadOffset;

	int offs = mov_src_operand_offset(pTarget); // Find offset of disp32 in this particular mov instruction
	if(offs == 0)
	{
		// Throw an exception if we can't identify this offset (unexpected instruction!)
		// TODO: More useful exception here.
		throw PatchException("CTFWeaponBaseGrenadeProj::VPhysicsUpdate() Patch Offset incorrect.");
	}

	memcpy(instr_buf, pTarget, MAX_MOV_INSTR_LEN);

	// make this instruction read from an immediate address
	mov_to_disp32(instr_buf);

	// Plug in our super cool immediate address.
	*(fakeGlobals ***)(instr_buf + offs) = &gp_FakeGlobals;
	
	// Generate BasicBinPatch
	m_patches.Register(new BasicStaticBinPatch<MAX_MOV_INSTR_LEN>(pTarget, instr_buf));
}

BYTE * PipeBombFrameTimePatch::FindVPhysicsUpdate(void * gamedll)
{
#if defined (_LINUX)
	return (BYTE *)g_MemUtils.SimpleResolve(gamedll, LIN_VPhysicsUpdate_SYMBOL);
#elif defined (_WIN32)
	return (BYTE*)g_MemUtils.FindLibPattern(gamedll, WIN_VPhysicsUpdate_SIG, WIN_VPhysicsUpdate_SIGLEN);
#endif
}
