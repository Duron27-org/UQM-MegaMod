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
#include "../lander.h"
#include "../lifeform.h"
#include "../planets.h"
#include "../../build.h"
#include "../../comm.h"
#include "../../gendef.h"
#include "../../starmap.h"
#include "../../globdata.h"
#include "../../ipdisp.h"
#include "../../nameref.h"
#include "../../setup.h"
#include "../../sounds.h"
#include "../../state.h"
#include "libs/mathlib.h"


static bool GenerateVux_generatePlanets (SOLARSYS_STATE *solarSys);
static bool GenerateVux_generateOrbital (SOLARSYS_STATE *solarSys,
		PLANET_DESC *world);
static COUNT GenerateVux_generateEnergy (const SOLARSYS_STATE *,
		const PLANET_DESC *world, COUNT whichNode, NODE_INFO *);
static COUNT GenerateVux_generateLife (const SOLARSYS_STATE *,
		const PLANET_DESC *world, COUNT whichNode, NODE_INFO *);
static bool GenerateVux_pickupEnergy (SOLARSYS_STATE *, PLANET_DESC *world,
		COUNT whichNode);
static bool GenerateVux_pickupLife (SOLARSYS_STATE *, PLANET_DESC *world,
		COUNT whichNode);


const GenerateFunctions generateVuxFunctions = {
	/* .initNpcs         = */ GenerateDefault_initNpcs,
	/* .reinitNpcs       = */ GenerateDefault_reinitNpcs,
	/* .uninitNpcs       = */ GenerateDefault_uninitNpcs,
	/* .generatePlanets  = */ GenerateVux_generatePlanets,
	/* .generateMoons    = */ GenerateDefault_generateMoons,
	/* .generateName     = */ GenerateDefault_generateName,
	/* .generateOrbital  = */ GenerateVux_generateOrbital,
	/* .generateMinerals = */ GenerateDefault_generateMinerals,
	/* .generateEnergy   = */ GenerateVux_generateEnergy,
	/* .generateLife     = */ GenerateVux_generateLife,
	/* .pickupMinerals   = */ GenerateDefault_pickupMinerals,
	/* .pickupEnergy     = */ GenerateVux_pickupEnergy,
	/* .pickupLife       = */ GenerateVux_pickupLife,
};


static bool
GenerateVux_generatePlanets (SOLARSYS_STATE *solarSys)
{
	PLANET_DESC *pSunDesc = &solarSys->SunDesc[0];
	PLANET_DESC *pPlanet;

	GenerateDefault_generatePlanets (solarSys);

	pSunDesc->PlanetByte = 0;
	pPlanet = &solarSys->PlanetDesc[pSunDesc->PlanetByte];

	if (PrimeSeed)
	{
		COUNT angle;

		if (CurStarDescPtr->Index == MAIDENS_DEFINED)
		{
			GenerateDefault_generatePlanets (solarSys);
				// XXX: this is the second time that this function is
				// called. Is it safe to remove one, or does this change
				// the RNG so that the outcome is different?
			pPlanet->data_index = REDUX_WORLD;
			pPlanet->radius = EARTH_RADIUS * 212L / 100;
			angle = ARCTAN (pPlanet->location.x, pPlanet->location.y);
			pPlanet->location.x = COSINE (angle, pPlanet->radius);
			pPlanet->location.y = SINE (angle, pPlanet->radius);
		}
		else
		{
			if (CurStarDescPtr->Index == VUX_DEFINED)
			{
				pPlanet->data_index = REDUX_WORLD;
				pPlanet->NumPlanets = 1;
				pPlanet->radius = EARTH_RADIUS * 42L / 100;
				angle = HALF_CIRCLE + OCTANT;
			}
			else /* if (CurStarDescPtr->Index == VUX_BEAST_DEFINED) */
			{
				memmove (&solarSys->PlanetDesc[1],
						&solarSys->PlanetDesc[0],
						sizeof (solarSys->PlanetDesc[0])
						* pSunDesc->NumPlanets);
				++pSunDesc->NumPlanets;

				angle = HALF_CIRCLE - OCTANT;
				pPlanet->data_index = WATER_WORLD;
				pPlanet->radius = EARTH_RADIUS * 110L / 100;
				pPlanet->NumPlanets = 0;
			}

			pPlanet->location.x = COSINE (angle, pPlanet->radius);
			pPlanet->location.y = SINE (angle, pPlanet->radius);
			pPlanet->rand_seed = MAKE_DWORD (
				pPlanet->location.x,
				pPlanet->location.y);
		}

		ComputeSpeed (pPlanet, FALSE, 1);
	}
	else
	{
		if (StarSeed)
		{
			pSunDesc->PlanetByte = PickClosestHabitable (solarSys);
			pPlanet = &solarSys->PlanetDesc[pSunDesc->PlanetByte];
		}
		else
			CheckForHabitable (solarSys);

		pPlanet->data_index = GenerateHabitableWorld ();
	}

	return true;
}

static bool
GenerateVux_generateOrbital (SOLARSYS_STATE *solarSys, PLANET_DESC *world)
{
	if ((matchWorld (solarSys, world, MATCH_PBYTE, MATCH_PLANET)
			&& (CurStarDescPtr->Index == VUX_DEFINED
			|| (CurStarDescPtr->Index == MAIDENS_DEFINED
			&& !GET_GAME_STATE (ZEX_IS_DEAD))))
			&& StartSphereTracking (VUX_SHIP))
	{
		NotifyOthers (VUX_SHIP, IPNL_ALL_CLEAR);
		PutGroupInfo (GROUPS_RANDOM, GROUP_SAVE_IP);
		ReinitQueue (&GLOBAL (ip_group_q));
		assert (CountLinks (&GLOBAL (npc_built_ship_q)) == 0);

		CloneShipFragment (VUX_SHIP,
				&GLOBAL (npc_built_ship_q), INFINITE_FLEET);
		if (CurStarDescPtr->Index == VUX_DEFINED)
		{
			SET_GAME_STATE (GLOBAL_FLAGS_AND_DATA, 1 << 7);
		}
		else
		{
			SET_GAME_STATE (GLOBAL_FLAGS_AND_DATA, 1 << 6);
		}

		GLOBAL (CurrentActivity) |= START_INTERPLANETARY;
		InitCommunication (VUX_CONVERSATION);

		if (GLOBAL (CurrentActivity) & (CHECK_ABORT | CHECK_LOAD))
			return true;

		{
			GLOBAL (CurrentActivity) &= ~START_INTERPLANETARY;
			ReinitQueue (&GLOBAL (npc_built_ship_q));
			GetGroupInfo (GROUPS_RANDOM, GROUP_LOAD_IP);

			if (CurStarDescPtr->Index == VUX_DEFINED
					|| !GET_GAME_STATE (ZEX_IS_DEAD))
				return true;

			RepairSISBorder ();
		}
	}

	if (matchWorld (solarSys, world, MATCH_PBYTE, MATCH_PLANET))
	{
		if (CurStarDescPtr->Index == MAIDENS_DEFINED)
		{
			if (!GET_GAME_STATE (SHOFIXTI_MAIDENS))
			{
				LoadStdLanderFont (&solarSys->SysInfo.PlanetInfo);
				solarSys->PlanetSideFrame[1] = CaptureDrawable (
						LoadGraphic (MAIDENS_MASK_PMAP_ANIM));
				solarSys->SysInfo.PlanetInfo.DiscoveryString =
						CaptureStringTable (
						LoadStringTable (MAIDENS_STRTAB));
			}
		}
		else if (CurStarDescPtr->Index == VUX_BEAST_DEFINED)
		{
			if (!GET_GAME_STATE (VUX_BEAST))
			{
				LoadStdLanderFont (&solarSys->SysInfo.PlanetInfo);
				solarSys->PlanetSideFrame[1] = 0;
				solarSys->SysInfo.PlanetInfo.DiscoveryString =
						CaptureStringTable (
						LoadStringTable (BEAST_STRTAB));
			}
		}
		else // if (CurStarDescPtr->Index == VUX_DEFINED)
		{
			LoadStdLanderFont (&solarSys->SysInfo.PlanetInfo);
			solarSys->PlanetSideFrame[1] =
					CaptureDrawable (LoadGraphic (RUINS_MASK_PMAP_ANIM));
			solarSys->SysInfo.PlanetInfo.DiscoveryString =
					CaptureStringTable (LoadStringTable (RUINS_STRTAB));
		}
	}

	GenerateDefault_generateOrbital (solarSys, world);

	if (matchWorld (solarSys, world, MATCH_PBYTE, MATCH_PLANET)
			&& !DIF_HARD)
	{
		solarSys->SysInfo.PlanetInfo.Weather = 2;
		solarSys->SysInfo.PlanetInfo.Tectonics = 0;
	}

	return true;
}

static COUNT
GenerateVux_generateEnergy (const SOLARSYS_STATE *solarSys,
		const PLANET_DESC *world, COUNT whichNode, NODE_INFO *info)
{
	if (CurStarDescPtr->Index == MAIDENS_DEFINED
		&& matchWorld (solarSys, world, MATCH_PBYTE, MATCH_PLANET))
	{
		// This check is redundant since the retrieval bit will keep the
		// node from showing up again
		if (GET_GAME_STATE (SHOFIXTI_MAIDENS))
		{	// already picked up
			return 0;
		}

		if (info)
		{
			info->loc_pt.x = SCALED_MAP_WIDTH / 3;
			info->loc_pt.y = MAP_HEIGHT * 5 / 8;
		}

		return 1; // only matters when count is requested
	}

	if (CurStarDescPtr->Index == VUX_DEFINED
		&& matchWorld (solarSys, world, MATCH_PBYTE, MATCH_PLANET))
	{
		return GenerateDefault_generateRuins (solarSys, whichNode, info);
	}

	return 0;
}

static bool
GenerateVux_pickupEnergy (SOLARSYS_STATE *solarSys, PLANET_DESC *world,
		COUNT whichNode)
{
	if (CurStarDescPtr->Index == MAIDENS_DEFINED
		&& matchWorld (solarSys, world, MATCH_PBYTE, MATCH_PLANET))
	{
		assert (!GET_GAME_STATE (SHOFIXTI_MAIDENS) && whichNode == 0);

		GenerateDefault_landerReport (solarSys);
		SetLanderTakeoff ();

		SET_GAME_STATE (SHOFIXTI_MAIDENS, 1);
		SET_GAME_STATE (MAIDENS_ON_SHIP, 1);

		return true; // picked up
	}

	if (CurStarDescPtr->Index == VUX_DEFINED
			&& matchWorld (solarSys, world, MATCH_PBYTE, MATCH_PLANET))
	{
		// Standard ruins report
		GenerateDefault_landerReportCycle (solarSys);
		return false;
	}

	(void) whichNode;
	return false;
}

#define LIFE_BOOL (EXTENDED && GET_GAME_STATE (VUX_BEAST))

static COUNT
GenerateVux_generateLife (const SOLARSYS_STATE *solarSys,
		const PLANET_DESC *world, COUNT whichNode, NODE_INFO *info)
{
	if (CurStarDescPtr->Index == MAIDENS_DEFINED
		&& matchWorld (solarSys, world, MATCH_PBYTE, MATCH_PLANET))
	{
		static const SBYTE life[] =
		{
			 9,  9,  9,  9, /* Carousel Beast */
			14, 14, 14, 14, /* Amorphous Trandicula */
			18, 18, 18, 18, /* Penguin Cyclops */
			-1 /* term */
		};
		static const SBYTE lifeEx[] =
		{
			9,  9,  9,  9,  9, /* Carousel Beast */
			18, 18, 18, 18, 18, /* Penguin Cyclops */
			ZEX_BEAUTY, /* VUX Beast */
			-1 /* term */
		};

		return GeneratePresetLife (
				&solarSys->SysInfo, EXTENDED ? lifeEx : life,
				whichNode, info);
	}

	if (CurStarDescPtr->Index == VUX_BEAST_DEFINED
		&& matchWorld (solarSys, world, MATCH_PBYTE, MATCH_PLANET))
	{
		static const SBYTE life[] =
		{
			ZEX_BEAUTY, /* VUX Beast */
					// Must be the first node, see pickupLife() below
			3, 3, 3, 3, 3, /* Whackin' Bush */
			8, 8, 8, 8, 8, /* Glowing Medusa */
			-1 /* term */
		};
		return GeneratePresetLife (
				&solarSys->SysInfo, life, whichNode, info);
	}

	return GenerateDefault_generateLife (solarSys, world, whichNode, info);
}

static bool
GenerateVux_pickupLife (SOLARSYS_STATE *solarSys, PLANET_DESC *world,
		COUNT whichNode)
{
	if (CurStarDescPtr->Index == VUX_BEAST_DEFINED
		&& matchWorld (solarSys, world, MATCH_PBYTE, MATCH_PLANET))
	{
		if (whichNode == 0)
		{	// Picked up Zex' Beauty
			if (GET_GAME_STATE (VUX_BEAST) && StarSeed)
				return true; // no need to core, just pick it up
			assert (!GET_GAME_STATE (VUX_BEAST));

			GenerateDefault_landerReport (solarSys);
			SetLanderTakeoff ();

			SET_GAME_STATE (VUX_BEAST, 1);
			SET_GAME_STATE (VUX_BEAST_ON_SHIP, 1);
		}

		return true; // picked up
	}

	if (LIFE_BOOL && CurStarDescPtr->Index == MAIDENS_DEFINED
		&& matchWorld (solarSys, world, MATCH_PBYTE, MATCH_PLANET))
	{
		if (whichNode == 10)
		{	// Picked up Zex' Beauty... Again.
			LoadStdLanderFont (&solarSys->SysInfo.PlanetInfo);
			solarSys->SysInfo.PlanetInfo.DiscoveryString =
					SetRelStringTableIndex (
						CaptureStringTable (
							LoadStringTable (BEAST_STRTAB)), 1);

			GenerateDefault_landerReport (solarSys);
			SetLanderTakeoff ();

			SET_GAME_STATE (VUX_BEAST, 2);
			SET_GAME_STATE (VUX_BEAST_ON_SHIP, 2);

			if (!GET_GAME_STATE (SHOFIXTI_MAIDENS))
			{	// Reinitialize the Maiden's report as the Beast report
				// overrides it
				LoadStdLanderFont (&solarSys->SysInfo.PlanetInfo);
				solarSys->PlanetSideFrame[1] = CaptureDrawable (
						LoadGraphic (MAIDENS_MASK_PMAP_ANIM));
				solarSys->SysInfo.PlanetInfo.DiscoveryString =
						CaptureStringTable (
							LoadStringTable (MAIDENS_STRTAB));
			}
		}

		return true; // picked up
	}

	return GenerateDefault_pickupLife (solarSys, world, whichNode);
}