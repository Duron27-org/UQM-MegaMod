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

#include <math.h>

#include "gfxintrn.h"
#include "tfb_prim.h"
#include "libs/log.h"
#include "uqm/units.h"
#include "uqm/sounds.h"
#include "uqm/controls.h"

#include "uqm/setup.h"

static inline TFB_Char *getCharFrame (FONT_DESC *fontPtr, UniChar ch);

TFB_Char*
GetFrameForFPS (UniChar ch)
{
	if (StarConFont && !(GLOBAL (CurrentActivity) & CHECK_ABORT))
		return getCharFrame (StarConFont, ch);
	else
		return NULL;
}

BOOLEAN
GoodToGoFPS (void)
{
	return (StarConFont && !(GLOBAL (CurrentActivity) & CHECK_ABORT)
			&& !optRequiresReload);
}

void
GetFontDims (SIZE *w, SIZE *h)
{
	*w = (SIZE)StarConFont->disp.width;
	*h = (SIZE)StarConFont->disp.height;
}

FONT
SetContextFont (FONT Font)
{
	FONT LastFont;

	LastFont = _CurFontPtr;
	_CurFontPtr = Font;
	if (ContextActive ())
		SwitchContextFont (Font);

	return (LastFont);
}

BOOLEAN
DestroyFont (FONT FontRef)
{
	if (FontRef == NULL)
		return (FALSE);

	if (_CurFontPtr && _CurFontPtr == FontRef)
		SetContextFont ((FONT)NULL);

	return (FreeFont (FontRef));
}

// Returns the RECT of any given TEXT
RECT
font_GetTextRect (TEXT *lpText)
{
	RECT ClipRect;
	POINT origin;
	TEXT text;

	memset(&ClipRect, 0, sizeof(RECT));

	FixContextFontEffect ();
	if (!GraphicsSystemActive () || !GetContextValidRect (NULL, &origin))
		return ClipRect;

	// TextRect() clobbers TEXT.CharCount so we have to make a copy
	text = *lpText;
	if (!TextRect (&text, &ClipRect, NULL))
		return ClipRect;

	return ClipRect;
}

// XXX: Should be in frame.c (renamed to something decent?)
void
font_DrawText (TEXT *lpText)
{
	RECT ClipRect;
	POINT origin;
	TEXT text;

	FixContextFontEffect ();
	if (!GraphicsSystemActive () || !GetContextValidRect (NULL, &origin))
		return;

	// TextRect() clobbers TEXT.CharCount so we have to make a copy
	text = *lpText;
	if (!TextRect (&text, &ClipRect, NULL))
		return;
	// ClipRect is relative to origin
	_text_blt (&ClipRect, &text, origin);
}

void
font_DrawText_Fade (TEXT *lpText, FRAME repair, BOOLEAN *skip)
{
	RECT ClipRect;
	POINT origin;
	TEXT text;

	if (!GraphicsSystemActive () || !GetContextValidRect (NULL, &origin))
		return;

	// TextRect() clobbers TEXT.CharCount so we have to make a copy
	text = *lpText;
	if (!TextRect (&text, &ClipRect, NULL))
		return;
	// ClipRect is relative to origin
	_text_blt_fade (&ClipRect, &text, origin, repair, skip);
}

/* Draw the stroke by drawing the same text in the
 * background color one pixel shifted to all 4 directions.
 */
void
font_DrawTracedText (TEXT *pText, Color text, Color trace)
{
	// Preserve current foreground color for full correctness
	const Color oldfg = SetContextForeGroundColor (trace);
	const BYTE stroke = RES_SCALE (1);
	const POINT t_baseline = pText->baseline;
	POINT offset;

	for (offset.x = -stroke; offset.x <= stroke; ++offset.x)
	{
		for (offset.y = -stroke; offset.y <= stroke; ++offset.y)
		{
			if (hypot (offset.x, offset.y) > stroke) continue;
			pText->baseline =
					MAKE_POINT (
							t_baseline.x + offset.x,
							t_baseline.y + offset.y
						);
			font_DrawText (pText);
		}
	}
	pText->baseline = t_baseline;

	SetContextForeGroundColor (text);
	font_DrawText (pText);
	SetContextForeGroundColor (oldfg);
}

// Alt stuff to handle 2 fonts at once (for Orz)
BYTE
font_DrawTextAlt (TEXT *lpText, BYTE swap, FONT AltFontPtr, UniChar key)
{
	RECT ClipRect;
	POINT origin;
	TEXT text;

	FixContextFontEffect ();
	if (!GraphicsSystemActive () || !GetContextValidRect (NULL, &origin))
		return 0;

	// TextRect() clobbers TEXT.CharCount so we have to make a copy
	text = *lpText;
	if (!TextRectAlt (&text, &ClipRect, NULL, swap, key, AltFontPtr))
		return 0;
	// ClipRect is relative to origin
	return _text_blt_alt (&ClipRect, &text, origin, swap, AltFontPtr, key);
}

void
font_DrawTracedTextAlt (TEXT* pText, Color text, Color trace, FONT AltFontPtr, 
		UniChar key)
{
	// Preserve current foreground color for full correctness
	const Color oldfg = SetContextForeGroundColor (trace);
	const BYTE stroke = RES_SCALE (1);
	const POINT t_baseline = pText->baseline;
	POINT offset;
	static BYTE swap = 0;

	for (offset.x = -stroke; offset.x <= stroke; ++offset.x)
	{
		for (offset.y = -stroke; offset.y <= stroke; ++offset.y)
		{
			if (hypot (offset.x, offset.y) > stroke) continue;
			pText->baseline =
				MAKE_POINT (
					t_baseline.x + offset.x,
					t_baseline.y + offset.y
				);
			font_DrawTextAlt (pText, swap, AltFontPtr, key);
		}
	}
	pText->baseline = t_baseline;

	SetContextForeGroundColor (text);
	swap = font_DrawTextAlt (pText, swap, AltFontPtr, key);
	SetContextForeGroundColor (oldfg);
}

void
font_DrawShadowedText (TEXT *pText, BYTE direction,
	Color text_color, Color shadow_color)
{
	POINT shadow_angle = { 0, 0 };
	Color OldColor;

	switch (direction)
	{
		case NORTH_SHADOW:
			shadow_angle = MAKE_POINT (0, -1);
			break;
		case NORTH_EAST_SHADOW:
			shadow_angle = MAKE_POINT (1, -1);
			break;
		case EAST_SHADOW:
			shadow_angle = MAKE_POINT (1, 0);
			break;
		case SOUTH_EAST_SHADOW:
			shadow_angle = MAKE_POINT (1, 1);
			break;
		case SOUTH_SHADOW:
			shadow_angle = MAKE_POINT (0, 1);
			break;
		case SOUTH_WEST_SHADOW:
			shadow_angle = MAKE_POINT (-1, 1);
			break;
		case WEST_SHADOW:
			shadow_angle = MAKE_POINT (-1, 0);
			break;
		case NORTH_WEST_SHADOW:
			shadow_angle = MAKE_POINT (-1, -1);
			break;
	}

	pText->baseline.x += RES_SCALE (shadow_angle.x);
	pText->baseline.y += RES_SCALE (shadow_angle.y);

	OldColor = SetContextForeGroundColor (shadow_color);

	font_DrawText (pText);

	pText->baseline.x -= RES_SCALE (shadow_angle.x);
	pText->baseline.y -= RES_SCALE (shadow_angle.y);

	SetContextForeGroundColor (text_color);

	font_DrawText (pText);

	SetContextForeGroundColor (OldColor);
}

BOOLEAN
GetContextFontLeading (SIZE *pheight)
{
	if (_CurFontPtr != 0)
	{
		*pheight = (SIZE)_CurFontPtr->Leading;
		return (TRUE);
	}

	*pheight = 0;
	return (FALSE);
}

BOOLEAN
GetContextFontDispHeight (SIZE *pheight)
{
	if (_CurFontPtr != 0)
	{
		*pheight = (SIZE)_CurFontPtr->disp.height;
		return (TRUE);
	}

	*pheight = 0;
	return (FALSE);
}

BOOLEAN
GetContextFontDispWidth (SIZE *pwidth)
{
	if (_CurFontPtr != 0)
	{
		*pwidth = (SIZE)_CurFontPtr->disp.width;
		return (TRUE);
	}

	*pwidth = 0;
	return (FALSE);
}

BOOLEAN
TextRect (TEXT *lpText, RECT *pRect, BYTE *pdelta)
{
	BYTE char_delta_array[MAX_DELTAS];
	FONT FontPtr;

	FontPtr = _CurFontPtr;
	if (FontPtr != 0 && lpText->CharCount != 0)
	{
		COORD top_y, bot_y;
		SIZE width;
		UniChar next_ch = 0;
		const char *pStr;
		COUNT num_chars;
	
		num_chars = lpText->CharCount;
		/* At this point lpText->CharCount contains the *maximum* number of
		 * characters that lpText->pStr may contain.
		 * After the while loop below, it will contain the actual number.
		 */
		if (pdelta == 0)
		{
			pdelta = char_delta_array;
			if (num_chars > MAX_DELTAS)
			{
				num_chars = MAX_DELTAS;
				lpText->CharCount = MAX_DELTAS;
			}
		}

		top_y = 0;
		bot_y = 0;
		width = 0;
		pStr = lpText->pStr;
		if (num_chars > 0)
		{
			next_ch = getCharFromString (&pStr);
			if (next_ch == '\0')
				num_chars = 0;
		}
		while (num_chars--)
		{
			UniChar ch;
			SIZE last_width;
			TFB_Char *charFrame;

			last_width = width;

			ch = next_ch;
			if (num_chars > 0)
			{
				next_ch = getCharFromString (&pStr);
				if (next_ch == '\0')
				{
					lpText->CharCount -= num_chars;
					num_chars = 0;
				}
			}

			charFrame = getCharFrame (FontPtr, ch);
			if (charFrame != NULL && charFrame->disp.width)
			{
				COORD y;

				y = -charFrame->HotSpot.y;
				if (y < top_y)
					top_y = y;
				y += charFrame->disp.height;
				if (y > bot_y)
					bot_y = y;

				width += charFrame->disp.width + FontPtr->CharSpace;

				if (num_chars && next_ch < MAX_UNICODE
						&& FontPtr->KernTab[ch] != (BYTE)~0
						&& !(FontPtr->KernTab[ch]
						& (FontPtr->KernTab[next_ch] >> 2)))
				{
					width -= FontPtr->KernAmount;

					//printf ("%c: %d -- %d :%c\n", ch, FontPtr->KernTab[ch],
					//		FontPtr->KernTab[next_ch] >> 2, next_ch);
				}
			}

			*pdelta++ = (BYTE)(width - last_width);
		}

		if (width > 0 && (bot_y -= top_y) > 0)
		{
			/* subtract off character spacing */
			if (pdelta[-1] > 0)
			{
				--pdelta[-1];
				width -= FontPtr->CharSpace;
			}

			if (lpText->align == ALIGN_LEFT)
				pRect->corner.x = 0;
			else if (lpText->align == ALIGN_CENTER)
				pRect->corner.x = -RES_SCALE ((RES_DESCALE (width) >> 1));
			else
				pRect->corner.x = -width;
			pRect->corner.y = top_y;
			pRect->extent.width = width;
			pRect->extent.height = bot_y;

			pRect->corner.x += lpText->baseline.x;
			pRect->corner.y += lpText->baseline.y;

			return (TRUE);
		}
	}

	pRect->corner = lpText->baseline;
	pRect->extent.width = 0;
	pRect->extent.height = 0;

	return (FALSE);
}

void
_text_blt (RECT *pClipRect, TEXT *TextPtr, POINT ctxOrigin)
{
	FONT FontPtr;
	COUNT num_chars;
	UniChar next_ch;
	const char *pStr;
	POINT origin;
	TFB_Image *backing;
	DrawMode mode = _get_context_draw_mode ();

	FontPtr = _CurFontPtr;
	if (FontPtr == NULL)
		return;
	backing = _get_context_font_backing ();
	if (!backing)
		return;
	
	origin.x = pClipRect->corner.x;
	origin.y = TextPtr->baseline.y;
	num_chars = TextPtr->CharCount;
	if (num_chars == 0)
		return;

	pStr = TextPtr->pStr;

	next_ch = getCharFromString (&pStr);
	if (next_ch == '\0')
		num_chars = 0;
	while (num_chars--)
	{
		UniChar ch;
		TFB_Char* fontChar;

		ch = next_ch;
		if (num_chars > 0)
		{
			next_ch = getCharFromString (&pStr);
			if (next_ch == '\0')
				num_chars = 0;
		}

		fontChar = getCharFrame (FontPtr, ch);
		if (fontChar != NULL && fontChar->disp.width)
		{
			RECT r;

			r.corner.x = origin.x - fontChar->HotSpot.x;
			r.corner.y = origin.y - fontChar->HotSpot.y;
			r.extent.width = fontChar->disp.width;
			r.extent.height = fontChar->disp.height;
			if (BoxIntersect (&r, pClipRect, &r))
			{
				TFB_Prim_FontChar (origin, fontChar, backing, mode,
						ctxOrigin);
			}

			origin.x += fontChar->disp.width + FontPtr->CharSpace;

			if (num_chars && next_ch < MAX_UNICODE
					&& FontPtr->KernTab[ch] != (BYTE)~0
					&& !(FontPtr->KernTab[ch]
					& (FontPtr->KernTab[next_ch] >> 2)))
			{
				origin.x -= FontPtr->KernAmount;

				//printf ("%c: %d -- %d :%c\n", ch, FontPtr->KernTab[ch],
				//		FontPtr->KernTab[next_ch] >> 2, next_ch);
			}
		}
	}
}

void
_text_blt_fade (RECT *pClipRect, TEXT *TextPtr, POINT ctxOrigin, FRAME repair, BOOLEAN *skip)
{
	FONT FontPtr;
	COUNT num_chars;
	UniChar next_ch;
	const char *pStr;
	POINT origin;
	SIZE leading;
	TFB_Image *b_first, *b_second, *b_clear;
	DrawMode mode = _get_context_draw_mode ();

	FontPtr = _CurFontPtr;
	if (FontPtr != NULL)
	{
		RECT r;
		SIZE w, h;

		if (!GetContextFontDispHeight (&h) || !GetContextFontDispWidth (&w))
			return;

		b_first = TFB_DrawImage_CreateForScreen (w, h, TRUE);
		b_second = TFB_DrawImage_CreateForScreen (w, h, TRUE);
		b_clear = TFB_DrawImage_CreateForScreen (w, h, TRUE);

		r.corner.x = r.corner.y = 0;
		r.extent.width = w;
		r.extent.height = h;

		TFB_DrawImage_Rect (&r, _get_context_bg_color (), DRAW_REPLACE_MODE, b_first);
		TFB_DrawImage_Rect (&r, _get_context_fg_color (), DRAW_REPLACE_MODE, b_second);
	}
	else
		return;
	
	origin.x = pClipRect->corner.x;
	origin.y = TextPtr->baseline.y;
	GetContextFontLeading (&leading);
	num_chars = TextPtr->CharCount;
	if (num_chars == 0)
		return;

	pStr = TextPtr->pStr;
	
	next_ch = getCharFromString (&pStr);
	if (next_ch == '\0')
		num_chars = 0;
	while (num_chars--)
	{
		UniChar ch;
		TFB_Char* fontChar;

		while (next_ch == ' ')
		{
			fontChar = getCharFrame (FontPtr, next_ch);
			origin.x += fontChar->disp.width + FontPtr->CharSpace;
			next_ch = getCharFromString (&pStr);
			num_chars--;
		}
		ch = next_ch;
		if (num_chars > 0)
		{
			next_ch = getCharFromString (&pStr);
			if (next_ch == '\0')
				num_chars = 0;
		}

		fontChar = getCharFrame (FontPtr, ch);
		if (fontChar != NULL && fontChar->disp.width)
		{
			RECT r;

			r.corner.x = origin.x - fontChar->HotSpot.x;
			r.corner.y = origin.y - fontChar->HotSpot.y;
			r.extent.width = fontChar->disp.width;
			r.extent.height = fontChar->disp.height;
			if (BoxIntersect (&r, pClipRect, &r))
			{
				if (!*skip)
				{
					TFB_Prim_FontChar (origin, fontChar, b_first, mode,
								ctxOrigin);
					PlayMenuSound (MENU_SOUND_TEXT);

					SleepThread (ONE_SECOND / 16);
				}
				BatchGraphics ();
				if (repair && !*skip)
				{
					TFB_DrawImage_Image (repair->image, -r.corner.x, -r.corner.y,
							0, 0, NULL, DRAW_REPLACE_MODE, b_clear);
					TFB_Prim_FontChar (origin, fontChar, b_clear, MAKE_DRAW_MODE (DRAW_GRAYSCALE, 0xff),
							ctxOrigin);
				}
				TFB_Prim_FontChar (origin, fontChar, b_second, mode,
						ctxOrigin);
				UnbatchGraphics ();
			}

			if (next_ch == '\n' || next_ch == '\r')
			{
				origin.x = pClipRect->corner.x;
				origin.y += leading;
				pClipRect->extent.height += leading;
				next_ch = getCharFromString(&pStr);
				num_chars--;
			}
			else if (next_ch != '\0')
			{
				origin.x += fontChar->disp.width + FontPtr->CharSpace;

				if (num_chars && next_ch < MAX_UNICODE
						&& FontPtr->KernTab[ch] != (BYTE)~0
						&& !(FontPtr->KernTab[ch]
						& (FontPtr->KernTab[next_ch] >> 2)))
				{
					origin.x -= FontPtr->KernAmount;

					//printf ("%c: %d -- %d :%c\n", ch, FontPtr->KernTab[ch],
					//		FontPtr->KernTab[next_ch] >> 2, next_ch);
				}
			}
		}
		UpdateInputState ();
		if (CurrentInputState.menu[KEY_MENU_CANCEL] || 
					(GLOBAL (CurrentActivity) & CHECK_ABORT))
			*skip = TRUE;
	}
	if (b_first)
		TFB_DrawScreen_DeleteImage (b_first);
	if (b_second)
		TFB_DrawScreen_DeleteImage (b_second);
	if (b_clear)
		TFB_DrawScreen_DeleteImage (b_clear);
}

BOOLEAN
TextRectAlt (TEXT *lpText, RECT *pRect, BYTE *pdelta, BYTE swap,
		UniChar key, FONT AltFontPtr)
{
	BYTE char_delta_array[MAX_DELTAS];
	FONT FontPtr;

	FontPtr = _CurFontPtr;
	if (FontPtr != 0 && lpText->CharCount != 0)
	{
		COORD top_y, bot_y;
		SIZE width;
		UniChar next_ch = 0;
		const char *pStr;
		COUNT num_chars;
	
		num_chars = lpText->CharCount;
		/* At this point lpText->CharCount contains the *maximum* number of
		 * characters that lpText->pStr may contain.
		 * After the while loop below, it will contain the actual number.
		 */
		if (pdelta == 0)
		{
			pdelta = char_delta_array;
			if (num_chars > MAX_DELTAS)
			{
				num_chars = MAX_DELTAS;
				lpText->CharCount = MAX_DELTAS;
			}
		}

		top_y = 0;
		bot_y = 0;
		width = 0;
		pStr = lpText->pStr;
		if (num_chars > 0)
		{
			next_ch = getCharFromString (&pStr);
			if (next_ch == '\0')
				num_chars = 0;
		}
		while (num_chars--)
		{
			UniChar ch;
			SIZE last_width;
			TFB_Char *charFrame;

			last_width = width;

			ch = next_ch;
			if (num_chars > 0)
			{
				next_ch = getCharFromString (&pStr);
				if (next_ch == '\0')
				{
					lpText->CharCount -= num_chars;
					num_chars = 0;
				}
			}

			if (ch == key)
			{
				charFrame = getCharFrame (AltFontPtr, ch);
				swap ^= 1; // switch current font
				FontPtr = swap ? AltFontPtr : _CurFontPtr;
			}
			else
			{
				FontPtr = swap ? AltFontPtr : _CurFontPtr;
				charFrame = getCharFrame (FontPtr, ch);
			}

			if (charFrame != NULL && charFrame->disp.width)
			{
				COORD y;

				y = -charFrame->HotSpot.y;
				if (y < top_y)
					top_y = y;
				y += charFrame->disp.height;
				if (y > bot_y)
					bot_y = y;

				width += charFrame->disp.width + FontPtr->CharSpace;

				if (num_chars && next_ch < MAX_UNICODE
						&& FontPtr->KernTab[ch] != (BYTE)~0
						&& !(FontPtr->KernTab[ch]
						& (FontPtr->KernTab[next_ch] >> 2)))
				{
					width -= FontPtr->KernAmount;

					//printf ("%c: %d -- %d :%c\n", ch, FontPtr->KernTab[ch],
					//		FontPtr->KernTab[next_ch] >> 2, next_ch);
				}
			}

			*pdelta++ = (BYTE)(width - last_width);
		}

		if (width > 0 && (bot_y -= top_y) > 0)
		{
			/* subtract off character spacing */
			if (pdelta[-1] > 0)
			{
				--pdelta[-1];
				width -= FontPtr->CharSpace;
			}

			if (lpText->align == ALIGN_LEFT)
				pRect->corner.x = 0;
			else if (lpText->align == ALIGN_CENTER)
				pRect->corner.x = -RES_SCALE ((RES_DESCALE (width) >> 1));
			else
				pRect->corner.x = -width;
			pRect->corner.y = top_y;
			pRect->extent.width = width;
			pRect->extent.height = bot_y;

			pRect->corner.x += lpText->baseline.x;
			pRect->corner.y += lpText->baseline.y;

			return (TRUE);
		}
	}

	pRect->corner = lpText->baseline;
	pRect->extent.width = 0;
	pRect->extent.height = 0;

	return (FALSE);
}

BYTE
_text_blt_alt (RECT *pClipRect, TEXT *TextPtr, POINT ctxOrigin, BYTE swap,
		FONT AltFontPtr, UniChar key)
{// Kruzen: To create text using 2 fonts (Orz case)
 // Safest way to do so without going too deep into
 // original code
 // Warning: GetTextRect doesn't quite work since it looks
 // for chars only in 1 font
	FONT FontPtr;
	COUNT num_chars;
	UniChar next_ch;
	const char* pStr;
	POINT origin;
	TFB_Image *backing, *stock, *ext;
	DrawMode mode = _get_context_draw_mode();
	BYTE leading_step;

	FontPtr = _CurFontPtr;
	if (FontPtr == NULL)
		return 0;
	stock = _get_context_font_backing();
	if (!stock)
		return 0;

	if (AltFontPtr != NULL)
	{// Local backing needed for alt font
	 // Create one
		SIZE w, h;
		RECT r;
		Color color = _get_context_fg_color();
		w = (SIZE)AltFontPtr->disp.width;
		h = (SIZE)AltFontPtr->disp.height;
		if (w == 0 || h == 0)
			return 0;

		ext = TFB_DrawImage_CreateForScreen (w, h, TRUE);

		r.corner = MAKE_HOT_SPOT(0, 0);
		r.extent = MAKE_EXTENT (w, h);

		TFB_DrawImage_Rect (&r, color, DRAW_REPLACE_MODE, ext);
	}
	else
		return 0;

	origin.x = pClipRect->corner.x;
	origin.y = TextPtr->baseline.y;
	num_chars = TextPtr->CharCount;
	if (num_chars == 0)
		return 0;

	leading_step = AltFontPtr->Leading - _CurFontPtr->Leading;
	pStr = TextPtr->pStr;

	next_ch = getCharFromString(&pStr);
	if (next_ch == '\0')
		num_chars = 0;
	backing = stock;
	while (num_chars--)
	{
		UniChar ch;
		TFB_Char* fontChar;

		ch = next_ch;
		if (num_chars > 0)
		{
			next_ch = getCharFromString(&pStr);
			if (next_ch == '\0')
				num_chars = 0;
		}

		if (ch == key)
		{
			fontChar = getCharFrame (AltFontPtr, ch);
			backing = ext;
			swap ^= 1; // switch current font
			FontPtr = swap ? AltFontPtr : _CurFontPtr;
			origin.y = TextPtr->baseline.y + leading_step;
		}
		else
		{
			FontPtr = swap ? AltFontPtr : _CurFontPtr;
			fontChar = getCharFrame (FontPtr, ch);
			backing = swap ? ext : stock;
			origin.y = TextPtr->baseline.y + (swap ? leading_step : 0);
		}

		if (fontChar != NULL && fontChar->disp.width)
		{
			RECT r;

			r.corner.x = origin.x - fontChar->HotSpot.x;
			r.corner.y = origin.y - fontChar->HotSpot.y;
			r.extent.width = fontChar->disp.width;
			r.extent.height = fontChar->disp.height;
			if (BoxIntersect(&r, pClipRect, &r))
			{
				TFB_Prim_FontChar(origin, fontChar, backing, mode,
					ctxOrigin);
			}

			origin.x += fontChar->disp.width + FontPtr->CharSpace;

			if (num_chars && next_ch < MAX_UNICODE
					&& FontPtr->KernTab[ch] != (BYTE)~0
					&& !(FontPtr->KernTab[ch]
					& (FontPtr->KernTab[next_ch] >> 2)))
			{
				origin.x -= FontPtr->KernAmount;

				//printf ("%c: %d -- %d :%c\n", ch, FontPtr->KernTab[ch],
				//		FontPtr->KernTab[next_ch] >> 2, next_ch);
			}
		}
	}

	if (ext)
		TFB_DrawImage_Delete (ext);

	return swap;
}

static inline TFB_Char *
getCharFrame (FONT_DESC *fontPtr, UniChar ch)
{
	UniChar pageStart = ch & CHARACTER_PAGE_MASK;
	size_t charIndex;

	FONT_PAGE *page = fontPtr->fontPages;
	for (;;)
	{
		if (page == NULL)
			return NULL;

		if (page->pageStart == pageStart)
			break;

		page = page->next;
	}

	charIndex = ch - page->firstChar;
	if (ch >= page->firstChar && charIndex < page->numChars
			&& page->charDesc[charIndex].data)
	{
		return &page->charDesc[charIndex];
	}
	else
	{
		//log_add (log_Debug, "Character %u not present", (unsigned int) ch);
		return NULL;
	}
}

