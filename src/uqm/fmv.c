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

#include "fmv.h"

#include "controls.h"
#include "hyper.h"
#include "options.h"
#include "master.h"
#include "resinst.h"
#include "nameref.h"
#include "settings.h"
#include "setup.h"
#include "libs/vidlib.h"
#include "libs/graphics/gfx_common.h"
#include "libs/inplib.h"
#include "libs/sound/sound.h"

const RESOURCE ditties[25] =
{
	"ship.androsynth.ditty",
	"ship.arilou.ditty",
	"ship.chenjesu.ditty",
	"ship.chmmr.ditty",
	"ship.druuge.ditty",
	"ship.earthling.ditty",
	"ship.ilwrath.ditty",
	"ship.kohrah.ditty",
	"ship.melnorme.ditty",
	"ship.mmrnmhrm.ditty",
	"ship.mycon.ditty",
	"ship.orz.ditty",
	"ship.pkunk.ditty",
	"ship.shofixti.ditty",
	"ship.slylandro.ditty",
	"ship.spathi.ditty",
	"ship.supox.ditty",
	"ship.syreen.ditty",
	"ship.thraddash.ditty",
	"ship.umgah.ditty",
	"ship.urquan.ditty",
	"ship.utwig.ditty",
	"ship.vux.ditty",
	"ship.yehat.ditty",
	"ship.zoqfotpik.ditty"
};

void
DoShipSpin (COUNT index, MUSIC_REF hMusic)
{
	char vnbuf[24]; // From 32 to 24
	RECT old_r;

	LoadIntoExtraScreen (NULL, FALSE);
#if 0
	/* This is cut out right now but should be part of the 3DO side */
	SleepThreadUntil (FadeScreen (FadeAllToBlack, ONE_SECOND / 4));
	FlushColorXForms ();
#endif
	
	if (hMusic && optMainMenuMusic)
		StopMusic ();

	if (!optMainMenuMusic && musicVolume == 0)
		FadeMusic (NORMAL_VOLUME, 0);

	FreeHyperData ();

	// TODO: It would be nice to have better resource names for these.
	sprintf (vnbuf, "slides.spins.%02u", (unsigned)index);

	if (optWhichIntro == OPT_PC)
		PlayMusic (LoadMusic (ditties[index]), FALSE, 1);

	ShowPresentation (vnbuf);

	SleepThreadUntil (FadeScreen (FadeAllToBlack, ONE_SECOND / 4));
	FlushColorXForms ();

	GetContextClipRect (&old_r);
	SetContextClipRect (NULL);
	DrawFromExtraScreen (NULL, FALSE);
	SetContextClipRect (&old_r);

	if (hMusic && optMainMenuMusic)
		PlayMusic (hMusic, TRUE, 1);
	else
		FadeMusic(0, 0);
		
	SleepThreadUntil (FadeScreen (FadeAllToColor, ONE_SECOND / 4));
	FlushColorXForms ();
}

void
SplashScreen (void (* DoProcessing)(DWORD TimeOut))
{
	STAMP s;
	DWORD TimeOut;

	SleepThreadUntil (FadeScreen (FadeAllToBlack, ONE_SECOND / 120));
	SetContext (ScreenContext);
	s.origin.x = s.origin.y = 0;

	//DC: Title Splashscreen.
	if (!IS_HD) {
		printf("Loading Splashscreen\n\n");
		s.frame = CaptureDrawable (LoadGraphic (TITLE_ANIM));
	} else {
		printf("Loading HD Splashscreen\n\n");
		s.frame = CaptureDrawable (LoadGraphic (TITLE_HD));
	}

	DrawStamp (&s);
	DestroyDrawable (ReleaseDrawable (s.frame));

	TimeOut = FadeScreen (FadeAllToColor, ONE_SECOND / 2);

	if (DoProcessing)
		DoProcessing (TimeOut);
	if (GLOBAL (CurrentActivity) & CHECK_ABORT)
	{
		return;
	}
	
	/* There was a forcible setting of CHECK_ABORT here.  I cannot
	 * find any purpose for this that DoRestart doesn't handle
	 * better (forcing all other threads but this one to quit out,
	 * I believe), and have thus removed it.  It was interfering
	 * with the proper operation of the quit operation.
	 * --Michael */

	WaitForAnyButton (FALSE, ONE_SECOND * 3, TRUE);
	if (GLOBAL (CurrentActivity) & CHECK_ABORT)
	{
		return;
	}
	GLOBAL (CurrentActivity) &= ~CHECK_ABORT;

	SleepThreadUntil (FadeScreen (FadeAllToBlack, ONE_SECOND / 2));
}

void
Introduction (void)
{

	updateDiscordPresence ("It is a factory...", "for building starships!",
			optWhichIntro == OPT_3DO ? "intro-3do" : "intro-pc", "");

	ShowPresentation (INTROPRES_STRTAB);
	SleepThreadUntil (FadeScreen (FadeAllToBlack, ONE_SECOND / 2));
}

void
Victory (void)
{
	SleepThreadUntil (FadeScreen (FadeAllToBlack, ONE_SECOND / 2));

	/* by default we do 3DO cinematics; or PC slides when 3DO files are
	 * not present */
	updateDiscordPresence ("Victory!", "You have defeated the Ur-Quan!", "victory", "");
	ShowPresentation (FINALPRES_STRTAB);
		
	FadeScreen (FadeAllToBlack, 0);
}

void
GameOver (BYTE DeathType) 
{
	if (DeathType != SUICIDE)
		SleepThreadUntil (FadeScreen (FadeAllToBlack, ONE_SECOND / 2));

	switch (DeathType)
	{
		case DEATH_MARCH:
			updateDiscordPresence ("Game Over", "Better luck next time.", "death_march", "");
			ShowPresentation (DEATHMARCHPRES_STRTAB);
			break;
		case SUICIDE:
			updateDiscordPresence ("Game Over", "Better luck next time.", "suicide", "");
			SleepThreadUntil (FadeScreen (FadeAllToWhite, ONE_SECOND / 2));
			ShowPresentation (SUICIDEPRES_STRTAB);
			break;
		case SURRENDERED:
			updateDiscordPresence ("Game Over", "Better luck next time.", "surrendered", "");
			ShowPresentation (SURRENDEREDPRES_STRTAB);
			break;
		case DIED_IN_BATTLE:
		default:
			updateDiscordPresence ("Game Over", "Better luck next time.", "kia", "");
			ShowPresentation (DEFEATEDPRES_STRTAB);
			break;
	}
	FadeScreen (FadeAllToBlack, 0);
}

void
Logo (void)
{	
	ShowPresentation (LOGOPRES_STRTAB);
	SleepThreadUntil (FadeScreen (FadeAllToBlack, ONE_SECOND / 2));
}

void
Drumall (void)
{
	updateDiscordPresence ("Man, this blows...", "", "drumall", "");
	ShowPresentation (DRUMALLPRES_STRTAB);
	SleepThreadUntil (FadeScreen (FadeAllToBlack, ONE_SECOND / 2));
}



