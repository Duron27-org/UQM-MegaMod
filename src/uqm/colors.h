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
#ifndef UQM_COLORS_H_
#define UQM_COLORS_H_

// To be used as an indicator that the actual value of the color does not
// matter, for instance in structure initialisations for fields which
// are irrelevant in the context.
#define UNDEFINED_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x00, 0x00), 0x00)

#if 0
#define DEFAULT_COLOR_00 \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x00, 0x00), 0x00)
#define DEFAULT_COLOR_01 \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x00, 0x14), 0x01)
#define DEFAULT_COLOR_02 \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x14, 0x00), 0x02)
#define DEFAULT_COLOR_03 \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x14, 0x14), 0x03)
#define DEFAULT_COLOR_04 \
		BUILD_COLOR (MAKE_RGB15 (0x14, 0x00, 0x00), 0x04)
#define DEFAULT_COLOR_05 \
		BUILD_COLOR (MAKE_RGB15 (0x14, 0x00, 0x14), 0x05)
#define DEFAULT_COLOR_06 \
		BUILD_COLOR (MAKE_RGB15 (0x14, 0x14, 0x00), 0x06)
#define DEFAULT_COLOR_07 \
		BUILD_COLOR (MAKE_RGB15 (0x14, 0x14, 0x14), 0x07)
#define DEFAULT_COLOR_08 \
		BUILD_COLOR (MAKE_RGB15 (0x0A, 0x0A, 0x0A), 0x08)
#define DEFAULT_COLOR_09 \
		BUILD_COLOR (MAKE_RGB15 (0x0A, 0x0A, 0x1F), 0x09)
#define DEFAULT_COLOR_0A \
		BUILD_COLOR (MAKE_RGB15 (0x0A, 0x1F, 0x0A), 0x0A)
#define DEFAULT_COLOR_0B \
		BUILD_COLOR (MAKE_RGB15 (0x0A, 0x1F, 0x1F), 0x0B)
#define DEFAULT_COLOR_0C \
		BUILD_COLOR (MAKE_RGB15 (0x1F, 0x0A, 0x0A), 0x0C)
#define DEFAULT_COLOR_0D \
		BUILD_COLOR (MAKE_RGB15 (0x1F, 0x0A, 0x1F), 0x0D)
#define DEFAULT_COLOR_0E \
		BUILD_COLOR (MAKE_RGB15 (0x1F, 0x1F, 0x00), 0x0E)
#define DEFAULT_COLOR_0F \
		BUILD_COLOR (MAKE_RGB15 (0x1F, 0x1F, 0x1F), 0x0F)
#endif

#define NULL_COLOR \
		BUILD_COLOR_RGBA (0,0,0,0)
#define BLACK_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x00, 0x00), 0x00)
#define LTGRAY_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x14, 0x14, 0x14), 0x07)
#define MLTGRAY_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x0F, 0x0F, 0x0F), 0x00)
#define DKGRAY_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x0A, 0x0A, 0x0A), 0x08)
#define MDKGRAY_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x08, 0x08, 0x08), 0x1F)
#define VDKGRAY_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x06, 0x06, 0x06), 0x00)
#define WHITE_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x1F, 0x1F, 0x1F), 0x0F)
#define BRIGHT_RED_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x1F, 0x00, 0x00), 0x04)
#define BRIGHT_GREEN_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x1F, 0x00), 0x02)
#define BRIGHT_BLUE_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x00, 0x1F), 0x01)

/* uqm-hd */
#define BRIGHT_YELLOW_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x1F, 0x1F, 0x00), 0x01)
#define DULL_YELLOW_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x0F, 0x0F, 0x00), 0x01)
/* end uqm-hd */

#define STARMAP_FUEL_RANGE_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x04, 0x04, 0x04), 0x22)
#define STARMAP_SECONDARY_RANGE_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x05, 0x05, 0x05), 0x22)

#define NORMAL_ILLUMINATED_COLOR \
		WHITE_COLOR
#define NORMAL_SHADOWED_COLOR \
		DKGRAY_COLOR
#define HIGHLIGHT_ILLUMINATED_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x1F, 0x0A, 0x0A), 0x0C)
#define HIGHLIGHT_SHADOWED_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x14, 0x00, 0x00), 0x04)
#define MENU_BACKGROUND_COLOR \
		LTGRAY_COLOR
#define MENU_FOREGROUND_COLOR \
		DKGRAY_COLOR
#define MENU_TEXT_COLOR \
		VDKGRAY_COLOR
#define MENU_HIGHLIGHT_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x1F, 0x1F, 0x00), 0x0E)
#define MENU_CURSOR_COLOR \
		WHITE_COLOR

#define STATUS_ILLUMINATED_COLOR \
		WHITE_COLOR
#define STATUS_SHADOWED_COLOR \
		DKGRAY_COLOR
#define STATUS_SHAPE_COLOR \
		BLACK_COLOR
#define STATUS_SHAPE_OUTLINE_COLOR \
		WHITE_COLOR

#define CONTROL_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x00, 0x14), 0x01)

#define ALLIANCE_BACKGROUND_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x00, 0x14), 0x01)
#define HIERARCHY_BACKGROUND_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x14, 0x00, 0x00), 0x04)
#define ALLIANCE_TEXT_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x0A, 0x1F, 0x1F), 0x0B)
#define HIERARCHY_TEXT_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x1F, 0x1F, 0x0A), 0x0E)
#define ALLIANCE_BOX_HIGHLIGHT_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x00, 0x14), 0x01)
#define HIERARCHY_BOX_HIGHLIGHT_COLOR \
		HIERARCHY_BACKGROUND_COLOR

#define MESSAGE_BACKGROUND_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x00, 0x14), 0x01)
#define MESSAGE_TEXT_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x1F, 0x1F, 0x0A), 0x0E)


// Not highlighted dialog options in comm.
#define COMM_PLAYER_TEXT_NORMAL_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x14, 0x14), 0x03)

// Currently highlighted dialog option in comm.
#define COMM_PLAYER_TEXT_HIGHLIGHT_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x1A, 0x1A, 0x1A), 0x12)

// Background color of the area containing the player's dialog options.
#define COMM_PLAYER_BACKGROUND_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x00, 0x14), 0x01)

// "(In response to your statement)"
#define COMM_RESPONSE_INTRO_TEXT_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x0A, 0x0C, 0x1F), 0x48)
		
// Your dialog option after choosing it.
#define COMM_FEEDBACK_TEXT_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x12, 0x14, 0x4F), 0x44)

// The background when reviewing the conversation history.
#define COMM_HISTORY_BACKGROUND_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x05, 0x00), 0x00)

// The text when reviewing the conversation history.
#define COMM_HISTORY_TEXT_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x10, 0x00), 0x6B)

// The text "MORE" when reviewing the conversation history.
#define COMM_MORE_TEXT_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x17, 0x00), 0x00)

// Default colors for System Dialog Boxes (DrawShadowedBox)
#define SHADOWBOX_BACKGROUND_COLOR \
		MENU_BACKGROUND_COLOR

#define SHADOWBOX_MEDIUM_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x10, 0x10, 0x10), 0x19)

#define SHADOWBOX_DARK_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x08, 0x08, 0x08), 0x1F)

// Alternate Shadowed Box colors

#define ALT_SHADOWBOX_BACKGROUND_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x0E, 0x0E, 0x0E), 0x00)

#define ALT_SHADOWBOX_TOP_LEFT \
		ALT_SHADOWBOX_BACKGROUND_COLOR

#define ALT_SHADOWBOX_BOTTOM_RIGHT \
		VDKGRAY_COLOR

#define ALT_SHADOWBOX_CORNERS \
		MDKGRAY_COLOR


// === SIS ===

// Left border of the "SIS" view (the part in which your ship flies).
#define SIS_LEFT_BORDER_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x10, 0x10, 0x10), 0x19)

// Right and bottom border of the "SIS" view.
#define SIS_BOTTOM_RIGHT_BORDER_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x08, 0x08, 0x08), 0x1F)

// Text color of the string "CAPTAIN", when using PC fonts.
#define PC_CAPTAIN_STRING_TEXT_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x02, 0x04, 0x1E), 0x38)

// Background color of the string "CAPTAIN", when using PC fonts.
#define PC_CAPTAIN_STRING_BACKGROUND_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x00, 0x14), 0x01)

// Text color of the captain's name.
#define CAPTAIN_NAME_TEXT_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x16, 0x0B, 0x1F), 0x38)

// Background color of the captain's name.
#define CAPTAIN_NAME_BACKGROUND_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x00, 0x14), 0x01)

// Text color of the flagship's name, when using 3DO fonts.
#define THREEDO_FLAGSHIP_NAME_TEXT_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x14, 0x0A, 0x00), 0x0C)

// Background color of the flagship's name.
#define FLAGSHIP_NAME_BACKGROUND_COLOR \
		BLACK_COLOR

// Text color for the message area (at the top of the screen, on the left
// hand side, containing the name of the solar system.
#define SIS_MESSAGE_TEXT_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x1B, 0x00, 0x1B), 0x33)

// Color of autocompleted text after the current cursor position,
// when editing in the title area.
#define SIS_MESSAGE_EXTRA_TEXT_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x12, 0x00, 0x12), 0x33)

// Background color for the message area.
#define SIS_MESSAGE_BACKGROUND_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x00, 0x14), 0x01)

// Cursor color when editing in the message area.
#define SIS_MESSAGE_CURSOR_COLOR \
		BLACK_COLOR

#define SIS_MESSAGE_TOP_LEFT_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x00, 0x0E), 0x54)

#define SIS_MESSAGE_BOTTOM_RIGHT_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x01, 0x1C), 0x4E)

// Text color of the title (at the top of the screen, on the right
// hand side, containing the coordinates in HyperSpace, or the planet name
// in IP.
#define SIS_TITLE_TEXT_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x1B, 0x00, 0x1B), 0x33)

// Background color of the title.
#define SIS_TITLE_BACKGROUND_COLOR \
		SIS_MESSAGE_BACKGROUND_COLOR

#define SIS_TITLE_TOP_LEFT_COLOR \
		SIS_MESSAGE_TOP_LEFT_COLOR

#define SIS_TITLE_BOTTOM_RIGHT_COLOR \
		SIS_MESSAGE_BOTTOM_RIGHT_COLOR

// Text color of the status message, below the flagship overview, containing
// the date, RU, etc.
#define STATUS_MESSAGE_TEXT_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x10, 0x00), 0x6B)

// Text color for the status message when it's displaying a warning (yellow).
#define STATUS_MESSAGE_WARNING_TEXT_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x10, 0x10, 0x00), 0x6B)

// Text color for the status message then it's displaying an alert (red).
#define STATUS_MESSAGE_ALERT_TEXT_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x10, 0x00, 0x00), 0x6B)

// Background color of the status message.
#define STATUS_MESSAGE_BACKGROUND_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x08, 0x00), 0x6E)

//	== Scavenge screen ==

// Scavenge screen text color tab
#define SCAVENGE_TEXT_COLOR_TABLE \
		{ \
			BUILD_COLOR (MAKE_RGB15_INIT (0x0A, 0x0A, 0x0A), 0x1D), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x09, 0x09, 0x09), 0x1E), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x08, 0x08, 0x08), 0x1F), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x06, 0x06, 0x06), 0x20), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x05, 0x05, 0x05), 0x21), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x04, 0x04, 0x04), 0x22), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x03, 0x03, 0x03), 0x23), \
		}

// Scavenge screen ship fading
#define SCAVENGE_SCREEN_COLOR_TABLE \
		{ \
			BUILD_COLOR (MAKE_RGB15_INIT (0x07, 0x00, 0x00), 0x2F), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x0F, 0x00, 0x00), 0x2D), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x17, 0x00, 0x00), 0x2B), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x1F, 0x0A, 0x0A), 0x27), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x1F, 0x14, 0x14), 0x25), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x1F, 0x1F, 0x1F), 0x0F), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x1F, 0x14, 0x14), 0x25), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x1F, 0x0A, 0x0A), 0x27), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x1B, 0x00, 0x00), 0x2A), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x17, 0x00, 0x00), 0x2B), \
		}

//	== Misc tables ==

// Pulsating color of the string "AUTO-PILOT"
#define AUTOPILOT_COLOR_CYCLE_TABLE \
		{ \
			BUILD_COLOR (MAKE_RGB15_INIT (0x0A, 0x14, 0x18), 0x5B), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x06, 0x10, 0x16), 0x5C), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x03, 0x0E, 0x14), 0x5D), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x02, 0x0C, 0x11), 0x5E), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x01, 0x0B, 0x0F), 0x5F), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x01, 0x09, 0x0D), 0x60), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x00, 0x07, 0x0B), 0x61), \
		}

// Pulsating color of the text cursor
#define CURSOR_COLOR_CYCLE_TABLE \
		{ \
			BUILD_COLOR (MAKE_RGB15_INIT (0x00, 0x00, 0x00), 0x00), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x00, 0x00, 0x00), 0x00), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x16, 0x0A, 0x1F), 0x5C), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x16, 0x0A, 0x1F), 0x5C), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x1F, 0x1F, 0x1F), 0x00), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x1F, 0x1F, 0x1F), 0x00), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x19, 0x19, 0x19), 0x00), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x15, 0x15, 0x15), 0x00), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x11, 0x11, 0x11), 0x00), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x0C, 0x0C, 0x0C), 0x00), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x08, 0x08, 0x08), 0x00), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x04, 0x04, 0x04), 0x00), \
		}

// Pulsating color of the PC Menu Rectangle
#define PC_RECT_COLOR_CYCLE_TABLE \
		{ \
			MAKE_RGBA_INIT (0x24, 0x00, 0x45, 0xFF), \
			MAKE_RGBA_INIT (0x38, 0x00, 0x65, 0xFF), \
			MAKE_RGBA_INIT (0x4D, 0x00, 0x8A, 0xFF), \
			MAKE_RGBA_INIT (0x61, 0x00, 0xAA, 0xFF), \
			MAKE_RGBA_INIT (0x79, 0x00, 0xCF, 0xFF), \
			MAKE_RGBA_INIT (0x96, 0x00, 0xFF, 0xFF), \
			MAKE_RGBA_INIT (0xA6, 0x34, 0xFF, 0xFF), \
			MAKE_RGBA_INIT (0xB6, 0x55, 0xFF, 0xFF), \
		}

// Pulsating color of selected ship
#define SHIP_SELECT_COLOR_CYCLE_TABLE \
		{ \
			MAKE_RGBA_INIT (0xFF, 0xFF, 0xFF, 0xFF), \
			MAKE_RGBA_INIT (0xAA, 0xAA, 0xAA, 0xFF), \
			MAKE_RGBA_INIT (0x55, 0x55, 0x55, 0xFF), \
			MAKE_RGBA_INIT (0x1F, 0x1F, 0x1F, 0xFF), \
			MAKE_RGBA_INIT (0x55, 0x55, 0x55, 0xFF), \
			MAKE_RGBA_INIT (0xAA, 0xAA, 0xAA, 0xFF), \
		}

// Dark Mode FG text Color
#define DARKMODE_FG_TABLE \
		{ \
			MAKE_RGBA_INIT (0x00, 0xFF, 0x10, 0x00), \
			MAKE_RGBA_INIT (0x00, 0xFF, 0x20, 0x00), \
			MAKE_RGBA_INIT (0x00, 0xFF, 0x30, 0x00), \
			MAKE_RGBA_INIT (0x00, 0xFF, 0x40, 0x00), \
			MAKE_RGBA_INIT (0x00, 0xFF, 0x50, 0x00), \
			MAKE_RGBA_INIT (0x00, 0xFF, 0x60, 0x00), \
			MAKE_RGBA_INIT (0x08, 0xFF, 0x70, 0x00), \
			MAKE_RGBA_INIT (0x10, 0xFF, 0x80, 0x00), \
			MAKE_RGBA_INIT (0x18, 0xFF, 0x90, 0x00), \
			MAKE_RGBA_INIT (0x20, 0xFF, 0xA0, 0x00), \
			MAKE_RGBA_INIT (0x28, 0xFF, 0xB0, 0x00), \
			MAKE_RGBA_INIT (0x30, 0xFF, 0xC0, 0x00), \
			MAKE_RGBA_INIT (0x38, 0xFF, 0xD0, 0x00), \
			MAKE_RGBA_INIT (0x40, 0xFF, 0xE0, 0x00), \
			MAKE_RGBA_INIT (0x48, 0xFF, 0xF0, 0x00), \
			MAKE_RGBA_INIT (0x55, 0xFF, 0xFF, 0x00), \
		}

// Dark Mode FG text Color
#define DARKMODE_BG_TABLE \
		{ \
			MAKE_RGBA_INIT (0xE0, 0x9A, 0x14, 0x00), \
			MAKE_RGBA_INIT (0xD2, 0x87, 0x14, 0x00), \
			MAKE_RGBA_INIT (0xC4, 0x7E, 0x14, 0x00), \
			MAKE_RGBA_INIT (0xB6, 0x75, 0x14, 0x00), \
			MAKE_RGBA_INIT (0xA8, 0x6C, 0x14, 0x00), \
			MAKE_RGBA_INIT (0x9A, 0x63, 0x14, 0x00), \
			MAKE_RGBA_INIT (0x8C, 0x5A, 0x14, 0x00), \
			MAKE_RGBA_INIT (0x7E, 0x51, 0x14, 0x00), \
			MAKE_RGBA_INIT (0x70, 0x48, 0x07, 0x00), \
			MAKE_RGBA_INIT (0x62, 0x3F, 0x07, 0x00), \
			MAKE_RGBA_INIT (0x54, 0x36, 0x07, 0x00), \
			MAKE_RGBA_INIT (0x46, 0x2D, 0x00, 0x00), \
			MAKE_RGBA_INIT (0x38, 0x24, 0x00, 0x00), \
			MAKE_RGBA_INIT (0x2A, 0x1B, 0x00, 0x00), \
			MAKE_RGBA_INIT (0x1C, 0x12, 0x00, 0x00), \
			MAKE_RGBA_INIT (0x00, 0x00, 0x00, 0x00), \
		}

// Colors for the fuel in the fuel tanks as they are filled up,
// when viewed from the shipyard.
#define FUEL_COLOR_TABLE \
		{ \
			BUILD_COLOR (MAKE_RGB15_INIT (0x0F, 0x00, 0x00), 0x2D), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x13, 0x00, 0x00), 0x2C), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x17, 0x00, 0x00), 0x2B), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x1B, 0x00, 0x00), 0x2A), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x1F, 0x03, 0x00), 0x7F), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x1F, 0x07, 0x00), 0x7E), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x1F, 0x0A, 0x00), 0x7D), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x1F, 0x0E, 0x00), 0x7C), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x1F, 0x11, 0x00), 0x7B), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x1F, 0x15, 0x00), 0x7A), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x1F, 0x18, 0x00), 0x79), \
		}

// Colors for the crew in the crew pods as they are filled up,
// when viewed from the shipyard, when using PC fonts.
#define PC_CREW_COLOR_TABLE \
		{ \
			 BUILD_COLOR (MAKE_RGB15_INIT (0x0A, 0x1E, 0x09), 0x65), \
			 BUILD_COLOR (MAKE_RGB15_INIT (0x00, 0x1E, 0x00), 0x65), \
			 BUILD_COLOR (MAKE_RGB15_INIT (0x00, 0x1B, 0x00), 0x65), \
			 BUILD_COLOR (MAKE_RGB15_INIT (0x00, 0x18, 0x00), 0x65), \
			 BUILD_COLOR (MAKE_RGB15_INIT (0x00, 0x15, 0x00), 0x65), \
			 BUILD_COLOR (MAKE_RGB15_INIT (0x00, 0x12, 0x00), 0x65), \
			 BUILD_COLOR (MAKE_RGB15_INIT (0x00, 0x10, 0x00), 0x65), \
			 BUILD_COLOR (MAKE_RGB15_INIT (0x00, 0x0D, 0x00), 0x65), \
			 BUILD_COLOR (MAKE_RGB15_INIT (0x00, 0x0A, 0x00), 0x65), \
			 BUILD_COLOR (MAKE_RGB15_INIT (0x00, 0x07, 0x00), 0x65), \
		}

// Colors for the crew in the crew pods as they are filled up,
// when viewed from the shipyard, when using 3DO fonts.
#define THREEDO_CREW_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x05, 0x10, 0x05), 0x65)

// Colors for the minerals in the storage bays as they are filled up,
// when viewed from the shipyard.
#define STORAGE_BAY_COLOR_TABLE \
		{ \
			 BUILD_COLOR (MAKE_RGB15_INIT (0x1F, 0x1F, 0x1F), 0x0F), \
			 BUILD_COLOR (MAKE_RGB15_INIT (0x1C, 0x1C, 0x1C), 0x11), \
			 BUILD_COLOR (MAKE_RGB15_INIT (0x18, 0x18, 0x18), 0x13), \
			 BUILD_COLOR (MAKE_RGB15_INIT (0x15, 0x15, 0x15), 0x15), \
			 BUILD_COLOR (MAKE_RGB15_INIT (0x12, 0x12, 0x12), 0x17), \
			 BUILD_COLOR (MAKE_RGB15_INIT (0x10, 0x10, 0x10), 0x19), \
			 BUILD_COLOR (MAKE_RGB15_INIT (0x0D, 0x0D, 0x0D), 0x1B), \
			 BUILD_COLOR (MAKE_RGB15_INIT (0x0A, 0x0A, 0x0A), 0x1D), \
			 BUILD_COLOR (MAKE_RGB15_INIT (0x08, 0x08, 0x08), 0x1F), \
			 BUILD_COLOR (MAKE_RGB15_INIT (0x05, 0x05, 0x05), 0x21), \
		}

// Color of the storage bay indicator, as shown beneath the flagship,
// for the parts which are full.
#define STORAGE_BAY_FULL_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x0A, 0x0A, 0x0A), 0x08)

// Color of the storage bay indicator, as shown beneath the flagship,
// for the parts which are empty.
#define STORAGE_BAY_EMPTY_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x06, 0x06, 0x06), 0x20)

// Colors of the oscilloscope lines
#define SCOPE_COLOR_3DO \
		BUILD_COLOR_RGBA (0x83, 0x4A, 0xFF, 0xFF)
#define SCOPE_COLOR_PC \
		BUILD_COLOR_RGBA (0x79, 0x00, 0xCE, 0xFF)

// Flagship blueprint color
#define BLUEPRINT_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x00, 0x16), 0x01)

#define FULL_CREW_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x16, 0x00), 0x01)
#define HALF_CREW_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x16, 0x16, 0x00), 0x01)
#define LOW_CREW_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x16, 0x00, 0x00), 0x01)

// Colors for the Lander damage cycle
#define LANDER_DAMAGE_COLOR_TABLE \
		{ \
			BUILD_COLOR (MAKE_RGB15_INIT (0x1F, 0x1F, 0x1F), 0x0F), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x1B, 0x00, 0x00), 0x2A), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x1F, 0x07, 0x00), 0x7E), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x1F, 0x0E, 0x00), 0x7C), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x1F, 0x15, 0x00), 0x7A), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x1F, 0x1C, 0x00), 0x78), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x1F, 0x1F, 0x0A), 0x0E), \
		}

// Colors for the lightning color cycle
#define LIGHTNING_COLOR_TABLE \
		{ \
			BUILD_COLOR (MAKE_RGB15_INIT (0x11, 0x11, 0x11), 0x18), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x13, 0x13, 0x13), 0x17), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x15, 0x15, 0x15), 0x15), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x17, 0x17, 0x17), 0x14), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x19, 0x19, 0x19), 0x13), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x1B, 0x1B, 0x1B), 0x12), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x1D, 0x1D, 0x1D), 0x10), \
			BUILD_COLOR (MAKE_RGB15_INIT (0x1F, 0x1F, 0x1F), 0x0f), \
		}

// === PC Menus ===

// Background color of the PC-style menus.
#define PCMENU_BACKGROUND_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x00, 0x15), 0x00)

// Color of the top and left segments of the border around PC-style menus.
#define PCMENU_TOP_LEFT_BORDER_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x0F, 0x0F, 0x0F), 0x00)
		
// Color of the bottom and right segments of the border around PC-style menus.
#define PCMENU_BOTTOM_RIGHT_BORDER_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x06, 0x06, 0x06), 0x00)

// Text color of an unselected menu item.
#define PCMENU_TEXT_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x15, 0x15), 0x00)

// Text color of an selected menu item.
#define PCMENU_SELECTION_TEXT_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x0A, 0x1F, 0x1F), 0x0B)

// Background color of a selected menu item.
#define PCMENU_SELECTION_BACKGROUND_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x0A, 0x0A, 0x1F), 0x09)

// === 3DO menus ===
#define THREEDOMENU_TEXT_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x1F, 0x00), 0x00)


// === Credits ===

#define CREDITS_TEXT_COLOR \
		WHITE_COLOR


// === Cargo menu ===

#define CARGO_BACK_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x00, 0x14), 0x01)

#define CARGO_WORTH_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x0A, 0x0A, 0x1F), 0x09)

#define CARGO_AMOUNT_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x14, 0x14), 0x03)

#define CARGO_SELECTED_BACK_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x0A, 0x0A, 0x1F), 0x09)

#define CARGO_SELECTED_WORTH_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x14, 0x14), 0x03)

#define CARGO_SELECTED_AMOUNT_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x0A, 0x1F, 0x1F), 0x0B)


// === Devices menu ===

#define DEVICES_BACK_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x00, 0x14), 0x01)

#define DEVICES_NAME_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x14, 0x14), 0x03)

#define DEVICES_SELECTED_BACK_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x0A, 0x0A, 0x1F), 0x09)

#define DEVICES_SELECTED_NAME_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x0A, 0x1F, 0x1F), 0x0B)

// === Modules Menu ===

#define MODULE_BACK_COLOR BUILD_COLOR_RGBA (0x00, 0x00, 0xAA, 0xFF)

#define MODULE_PRICE_COLOR BUILD_COLOR_RGBA (0x55, 0x55, 0xFF, 0xFF)

#define MODULE_SELECTED_BACK_COLOR MODULE_PRICE_COLOR

#define MODULE_NAME_COLOR BUILD_COLOR_RGBA (0x00, 0xAA, 0xAA, 0xFF)

#define MODULE_SELECTED_COLOR BUILD_COLOR_RGBA (0x55, 0xFF, 0xFF, 0xFF)

// === Roster menu ===

#define ROSTER_MODIFY_SHIP_COLOR \
		WHITE_COLOR

// === Scan menu and general ===

#define SCAN_PC_TITLE_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x00, 0x15), 0x3B)

#define SCAN_INFO_COLOR \
		BUILD_COLOR (MAKE_RGB15 (0x0F, 0x00, 0x19), 0x3B)

#define SCAN_MINERAL_TEXT_COLOR \
		BUILD_COLOR (MAKE_RGB15_INIT (0x13, 0x00, 0x00), 0x2C)

#define SCAN_ENERGY_TEXT_COLOR \
		BUILD_COLOR (MAKE_RGB15_INIT (0x0C, 0x0C, 0x0C), 0x1C)

#define SCAN_BIOLOGICAL_TEXT_COLOR \
		BUILD_COLOR (MAKE_RGB15_INIT (0x00, 0x0E, 0x00), 0x6C)

#define SCAN_MINERAL_TINT_COLOR \
		BRIGHT_RED_COLOR_INIT

#define SCAN_ENERGY_TINT_COLOR \
		WHITE_COLOR_INIT

#define SCAN_BIOLOGICAL_TINT_COLOR \
		BRIGHT_GREEN_COLOR_INIT

#define SCAN_PC_TITLE_COLOR_6014 \
		BUILD_COLOR (MAKE_RGB15 (0x00, 0x14, 0x14), 0x3B)

#define OUTLINE_COLOR (BUILD_COLOR_RGBA (0x00, 0x00, 0x00, 0x66))

// === Super-Melee ToolTips ===

#define TOOLTIP_COLOR_NAME_BACK  BUILD_SHADE_RGBA (0x2F)
#define TOOLTIP_COLOR_NAME_FRONT BUILD_SHADE_RGBA (0xC7)
#define TOOLTIP_COLOR_DESC_FRONT BUILD_SHADE_RGBA (0x81)


// Temporary, until we can use C'99 features:
#define BLACK_COLOR_INIT \
		BUILD_COLOR (MAKE_RGB15_INIT (0x00, 0x00, 0x00), 0x00)
#define WHITE_COLOR_INIT \
		BUILD_COLOR (MAKE_RGB15_INIT (0x1F, 0x1F, 0x1F), 0x0F)
#define BRIGHT_RED_COLOR_INIT \
		BUILD_COLOR (MAKE_RGB15_INIT (0x1F, 0x00, 0x00), 0x04)
#define BRIGHT_GREEN_COLOR_INIT \
		BUILD_COLOR (MAKE_RGB15_INIT (0x00, 0x1F, 0x00), 0x02)
#define BRIGHT_BLUE_COLOR_INIT \
		BUILD_COLOR (MAKE_RGB15_INIT (0x00, 0x00, 0x1F), 0x01)
#define UNDEFINED_COLOR_INIT \
		BUILD_COLOR (MAKE_RGB15_INIT (0x00, 0x00, 0x00), 0x00)

// Transparent
#define TRANSPARENT \
		BUILD_COLOR_RGBA (0x50, 0x50, 0x50, 0x00)

#endif  /* UQM_COLORS_H_ */

