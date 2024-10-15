//Copyright Paul Reiche, Fred Ford. 1992-2002

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "genall.h"
#include "../planets.h"
#include "../../build.h"
#include "../../gendef.h"
#include "../../grpinfo.h"
#include "../../starmap.h"
#include "../../state.h"
#include "../../globdata.h"
#include "libs/mathlib.h"

static bool GenerateRainbowWorld_initNpcs (SOLARSYS_STATE *solarSys);
static bool GenerateRainbowWorld_generatePlanets (
		SOLARSYS_STATE *solarSys);
static bool GenerateRainbowWorld_generateOrbital (SOLARSYS_STATE *solarSys,
		PLANET_DESC *world);

const GenerateFunctions generateRainbowWorldFunctions = {
	/* .initNpcs         = */ GenerateRainbowWorld_initNpcs,
	/* .reinitNpcs       = */ GenerateDefault_reinitNpcs,
	/* .uninitNpcs       = */ GenerateDefault_uninitNpcs,
	/* .generatePlanets  = */ GenerateRainbowWorld_generatePlanets,
	/* .generateMoons    = */ GenerateDefault_generateMoons,
	/* .generateName     = */ GenerateDefault_generateName,
	/* .generateOrbital  = */ GenerateRainbowWorld_generateOrbital,
	/* .generateMinerals = */ GenerateDefault_generateMinerals,
	/* .generateEnergy   = */ GenerateDefault_generateEnergy,
	/* .generateLife     = */ GenerateDefault_generateLife,
	/* .pickupMinerals   = */ GenerateDefault_pickupMinerals,
	/* .pickupEnergy     = */ GenerateDefault_pickupEnergy,
	/* .pickupLife       = */ GenerateDefault_pickupLife,
};

static bool
GenerateRainbowWorld_initNpcs (SOLARSYS_STATE *solarSys)
{
	if (DIF_HARD && GET_GAME_STATE (SLYLANDRO_MULTIPLIER) > 0)
	{
		HIPGROUP hGroup, hNextGroup;
		BYTE angle, num_groups, which_group;

		if (!GetGroupInfo (GLOBAL (BattleGroupRef), GROUP_INIT_IP))
		{// This code will run if we have no battle group generated
		 // or all are expired
			GLOBAL (BattleGroupRef) = 0;
			/* 1-3, 3-5, 5-7, 7-9 Probes total */
			num_groups = (GET_GAME_STATE (SLYLANDRO_MULTIPLIER) * 2) - 1 +
					(COUNT)TFB_Random () % 3;
			which_group = 0;
			do
			{
				CloneShipFragment (SLYLANDRO_SHIP,
						&GLOBAL (npc_built_ship_q), 0);
				PutGroupInfo (GROUPS_RANDOM, ++which_group);
				ReinitQueue (&GLOBAL (npc_built_ship_q));
			} while (--num_groups);

			GetGroupInfo (GROUPS_RANDOM, GROUP_INIT_IP);
		}
		// Fresh groups or not - force probes to rotate around rainbow
		// world and not spread around the system
		angle = (COUNT)TFB_Random () % 9; // Initial angle = 0 - OCTANT
		for (hGroup = GetHeadLink (&GLOBAL (ip_group_q));
					hGroup; hGroup = hNextGroup)
		{
			IP_GROUP *GroupPtr;

			GroupPtr = LockIpGroup (&GLOBAL (ip_group_q), hGroup);
			hNextGroup = _GetSuccLink (GroupPtr);

			GroupPtr->task = IN_ORBIT;
			GroupPtr->sys_loc = solarSys->SunDesc[0].PlanetByte + 1;
			GroupPtr->dest_loc = GroupPtr->sys_loc;
			GroupPtr->orbit_pos =
					NORMALIZE_FACING (ANGLE_TO_FACING (angle));
			GroupPtr->group_counter = 0;
			UnlockIpGroup (&GLOBAL (ip_group_q), hGroup);

			// Next ship in queue will add random value to its angle 
			// between OCTANT and HALF_CIRCLE
			angle += ((COUNT)TFB_Random() % 25) + OCTANT;

			// Normalize angle
			if (angle > FULL_CIRCLE)
				angle -= FULL_CIRCLE;
		}
	}
	else
		GenerateDefault_initNpcs (solarSys);

	return true;
}

static bool
GenerateRainbowWorld_generatePlanets (SOLARSYS_STATE *solarSys)
{
	PLANET_DESC *pSunDesc = &solarSys->SunDesc[0];
	PLANET_DESC *pPlanet;

	GenerateDefault_generatePlanets (solarSys);

	pSunDesc->PlanetByte = 0;
	pPlanet = &solarSys->PlanetDesc[pSunDesc->PlanetByte];

	pPlanet->data_index = RAINBOW_WORLD;

	if (PrimeSeed)
	{
		COUNT angle;

		pPlanet->NumPlanets = 0;
		pPlanet->radius = EARTH_RADIUS * 50L / 100;
		angle = ARCTAN (pPlanet->location.x, pPlanet->location.y);
		if (angle <= QUADRANT)
			angle += QUADRANT;
		else if (angle >= FULL_CIRCLE - QUADRANT)
			angle -= QUADRANT;
		pPlanet->location.x = COSINE (angle, pPlanet->radius);
		pPlanet->location.y = SINE (angle, pPlanet->radius);
		ComputeSpeed (pPlanet, FALSE, 1);
	}

	return true;
}

static bool
GenerateRainbowWorld_generateOrbital (SOLARSYS_STATE *solarSys,
		PLANET_DESC *world)
{
	if (matchWorld (solarSys, world, MATCH_PBYTE, MATCH_PLANET)
			&& CurStarDescPtr->Index >= RAINBOW0_DEFINED
			&& CurStarDescPtr->Index <= RAINBOW9_DEFINED)
	{
		UWORD rainbow_mask;

		rainbow_mask = MAKE_WORD (
				GET_GAME_STATE (RAINBOW_WORLD0),
				GET_GAME_STATE (RAINBOW_WORLD1));

		rainbow_mask |= 1 << (CurStarDescPtr->Index - RAINBOW0_DEFINED);
		SET_GAME_STATE (RAINBOW_WORLD0, LOBYTE (rainbow_mask));
		SET_GAME_STATE (RAINBOW_WORLD1, HIBYTE (rainbow_mask));
	}

	GenerateDefault_generateOrbital (solarSys, world);
	return true;
}

static void
GenerateSlylandro (SOLARSYS_STATE *solarSys) {
	HIPGROUP hGroup, hNextGroup;
	BYTE a, b;

	BYTE NumSly = GET_GAME_STATE (SLYLANDRO_MULTIPLIER) * 2;

	assert(CountLinks (&GLOBAL (npc_built_ship_q)) == 0);

	CloneShipFragment (SLYLANDRO_SHIP, &GLOBAL (npc_built_ship_q), 0);
	if (GLOBAL (BattleGroupRef) == 0)
		GLOBAL (BattleGroupRef) = PutGroupInfo (GROUPS_ADD_NEW, 1);

	for (a = 1; a <= NumSly; ++a)
		PutGroupInfo (GLOBAL (BattleGroupRef), a);

	ReinitQueue (&GLOBAL (npc_built_ship_q));
	GetGroupInfo (GLOBAL (BattleGroupRef), GROUP_INIT_IP);
	hGroup = GetHeadLink (&GLOBAL(ip_group_q));

	for (a = 0, b = 0; a < NumSly; ++a, b += FULL_CIRCLE / NumSly)
	{
		IP_GROUP *GroupPtr;

		if (b % (FULL_CIRCLE / NumSly) == 0)
			b += FULL_CIRCLE / NumSly;

		GroupPtr = LockIpGroup (&GLOBAL (ip_group_q), hGroup);
		hNextGroup = _GetSuccLink (GroupPtr);
		GroupPtr->task = IN_ORBIT;
		GroupPtr->sys_loc = solarSys->SunDesc[0].PlanetByte + 1;
		GroupPtr->dest_loc = GroupPtr->sys_loc;
		GroupPtr->orbit_pos = NORMALIZE_FACING (ANGLE_TO_FACING(b));
		GroupPtr->group_counter = 0;
		UnlockIpGroup (&GLOBAL (ip_group_q), hGroup);
		hGroup = hNextGroup;
	}
}
