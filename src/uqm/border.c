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


#include "libs/gfxlib.h"
#include "libs/threadlib.h"
#include "colors.h"
#include "setup.h"
#include "sis.h"
#include "units.h"
#include "util.h"
#include "menustat.h"

void
InitSISContexts (void)
{
	RECT r;

	SetContext (StatusContext);

	SetContext (SpaceContext);
	SetContextFGFrame (Screen);

	r.corner.x = SIS_ORG_X;
	r.corner.y = SIS_ORG_Y;
	r.extent.width = SIS_SCREEN_WIDTH;
	r.extent.height = SIS_SCREEN_HEIGHT;
	SetContextClipRect (&r);
}

void
DrawSISFrame (void)
{
	RECT r;

	SetContext (ScreenContext);

	BatchGraphics ();

	if (!IS_HD)
	{
		SetContextForeGroundColor (MENU_FOREGROUND_COLOR);

		// Top horizontal border behind SIS Title & Message (Small block in
		// between as well)
		r.corner.x = 0;
		r.corner.y = 0;
		r.extent.width = SIS_ORG_X + SIS_SCREEN_WIDTH + 1;
		r.extent.height = SIS_ORG_Y - 1;
		DrawFilledRectangle (&r);

		// Left side vertical border
		r.corner.x = 0;
		r.corner.y = 0;
		r.extent.width = SIS_ORG_X - 1;
		r.extent.height = SIS_ORG_Y + SIS_SCREEN_HEIGHT + 1;
		DrawFilledRectangle (&r);

		// Bottom horizontal border
		r.corner.x = 0;
		r.corner.y = r.extent.height;
		r.extent.width = SIS_ORG_X + SIS_SCREEN_WIDTH + 1;
		r.extent.height = SCREEN_HEIGHT - SIS_ORG_Y + SIS_SCREEN_HEIGHT;
		DrawFilledRectangle (&r);

		// Right side vertical border and Stat/Menu
		r.corner.x = SIS_ORG_X + SIS_SCREEN_WIDTH + 1;
		r.corner.y = 0;
		r.extent.width = SCREEN_WIDTH - r.corner.x;
		r.extent.height = SCREEN_HEIGHT;
		DrawFilledRectangle (&r);
		
		// Light and dark grey edges of the inner space window.
		r.corner.x = SIS_ORG_X - 1;
		r.corner.y = SIS_ORG_Y - 1;
		r.extent.width = SIS_SCREEN_WIDTH + 2;
		r.extent.height = SIS_SCREEN_HEIGHT + 2;
		DrawStarConBox (&r, 1,
				SIS_LEFT_BORDER_COLOR,
				SIS_BOTTOM_RIGHT_BORDER_COLOR,
				TRUE, BLACK_COLOR, FALSE, TRANSPARENT);

		// The big Blue box in the upper edge of screen (SIS Message)
		r.corner.y = 0;
		r.extent.height = SIS_ORG_Y;
		r.corner.x = SIS_ORG_X;
		r.extent.width = SIS_MESSAGE_BOX_WIDTH;
		DrawStarConBox (&r, 1,
				SIS_MESSAGE_TOP_LEFT_COLOR,
				SIS_MESSAGE_BOTTOM_RIGHT_COLOR,
				TRUE, SIS_MESSAGE_BACKGROUND_COLOR, FALSE, TRANSPARENT);

		// The smaller blue box (SIS Title).
		r.extent.width = SIS_TITLE_BOX_WIDTH;
		r.corner.x = SIS_ORG_X + SIS_SCREEN_WIDTH - SIS_TITLE_BOX_WIDTH;
		DrawStarConBox (&r, 1,
				SIS_TITLE_TOP_LEFT_COLOR,
				SIS_TITLE_BOTTOM_RIGHT_COLOR,
				TRUE, SIS_TITLE_BACKGROUND_COLOR, FALSE, TRANSPARENT);

		// Black border between menu area and space window area
		SetContextForeGroundColor (BLACK_COLOR);
		r.corner.x = SAFE_X + SPACE_WIDTH - 1;
		r.corner.y = 0;
		r.extent.width = 1;
		r.extent.height = SCREEN_HEIGHT;
		DrawFilledRectangle (&r);
		
		// Bottom corners of the SIS gauges
		r.corner.x = SAFE_X + SPACE_WIDTH;
		r.corner.y = SAFE_Y + 139;
		DrawPoint (&r.corner);
		r.corner.x = SCREEN_WIDTH - 1;
		DrawPoint (&r.corner);

		// Light grey border on the left side of SIS Message
		SetContextForeGroundColor (SIS_LEFT_BORDER_COLOR);
		r.corner.y = 1;
		r.extent.width = 1;
		r.extent.height = SAFE_Y + SIS_TITLE_HEIGHT;
		r.corner.x = SIS_ORG_X - 1;
		DrawFilledRectangle (&r);
		
		// Light grey border on the left side of SIS Title
		r.corner.x = SIS_ORG_X + SIS_SCREEN_WIDTH - SIS_TITLE_BOX_WIDTH - 1;
		DrawFilledRectangle (&r);

		// Light grey horizontal line at the bottom of the screen, space
		// window side
		r.corner.x = 0;
		r.corner.y = SCREEN_HEIGHT - 1;
		r.extent.width = SAFE_X + SPACE_WIDTH - 1;
		r.extent.height = 1;
		DrawFilledRectangle (&r);
		
		// Light grey vertical line at the right side of space window
		r.corner.x = SAFE_X + SPACE_WIDTH - 2;
		r.corner.y = 0;
		r.extent.width = 1;
		r.extent.height = SCREEN_HEIGHT - 1;
		DrawFilledRectangle (&r);
		
		// Vertical line at the right side of the Flagstats
		r.corner.x = SCREEN_WIDTH - 1;
		r.corner.y = 0;
		r.extent.width = 1;
		r.extent.height = SAFE_Y + 139;
		DrawFilledRectangle (&r);
		
		// Horizontal line below the in-game menu
		r.corner.x = SPACE_WIDTH + SAFE_X;
		r.corner.y = SCREEN_HEIGHT - 1;
		r.extent.width = STATUS_WIDTH + SAFE_X;
		r.extent.height = 1;
		DrawFilledRectangle (&r);
		
		// Vertical line at the right side in-game menu
		r.corner.x = SCREEN_WIDTH - 1;
		r.corner.y = SAFE_Y + 140;
		r.extent.width = 1;
		r.extent.height = (SCREEN_HEIGHT - 1) - r.corner.y;
		DrawFilledRectangle (&r);

		// Dark grey border around blue boxes.
		SetContextForeGroundColor (SIS_BOTTOM_RIGHT_BORDER_COLOR);
		// Vertical line on the right side of SIS Message
		r.corner.y = 1;
		r.extent.width = 1;
		r.extent.height = SAFE_Y + SIS_MESSAGE_HEIGHT - DOS_NUM (1);
		r.corner.x = SIS_ORG_X + SIS_MESSAGE_BOX_WIDTH;
		DrawFilledRectangle (&r);

		// Vertical line on the right side of SIS Title
		r.corner.x = SIS_ORG_X + SIS_SCREEN_WIDTH;
		++r.extent.height;
		DrawFilledRectangle (&r);

		//
		r.corner.y = 0;
		r.extent.width = (SAFE_X + SPACE_WIDTH - 2) - r.corner.x;
		r.extent.height = 1;
		DrawFilledRectangle (&r);

		//
		r.corner.x = 0;
		r.extent.width = SIS_ORG_X - r.corner.x;
		DrawFilledRectangle (&r);

		// Horizontal line between boxes
		r.corner.x = SIS_ORG_X + SIS_MESSAGE_BOX_WIDTH;
		r.extent.width = SIS_SPACER_BOX_WIDTH;
		DrawFilledRectangle (&r);

		//
		r.corner.x = 0;
		r.corner.y = 1;
		r.extent.width = 1;
		r.extent.height = (SCREEN_HEIGHT - 1) - r.corner.y;
		DrawFilledRectangle (&r);

		// Dark verticle line accent for the top left of the right panel
		r.corner.x = SAFE_X + SPACE_WIDTH;
		r.corner.y = 0;
		r.extent.width = 1;
		r.extent.height = SAFE_Y + 139;
		DrawFilledRectangle (&r);

		// Horizontal line of the separator below the SIS gauges 
		r.corner.x = SAFE_X + SPACE_WIDTH + 1;
		r.corner.y = SAFE_Y + 139;
		r.extent.width = STATUS_WIDTH - 2;
		r.extent.height = 1;
		DrawFilledRectangle (&r);

		// Dark verticle line to the left of in-game menu
		r.corner.x = SAFE_X + SPACE_WIDTH;
		r.corner.y = SAFE_Y + 140;
		r.extent.width = 1;
		r.extent.height = SCREEN_HEIGHT - r.corner.y;
		DrawFilledRectangle (&r);
	}
	else
	{
		SetContextForeGroundColor (BLACK_COLOR);
		r.corner.x = SIS_ORG_X - RES_SCALE (1);
		r.corner.y = SIS_ORG_Y - RES_SCALE (1);
		r.extent.width = SIS_SCREEN_WIDTH + RES_SCALE (2);
		r.extent.height = SIS_SCREEN_HEIGHT + RES_SCALE (2);
		DrawFilledRectangle (&r);
	}

	DrawBorder (0);

	InitSISContexts ();
	ClearSISRect (DRAW_SIS_DISPLAY);

	UnbatchGraphics ();
}