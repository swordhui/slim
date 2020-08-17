/* SLiM - Simple Login Manager
   Copyright (C) 1997, 1998 Per Liden
   Copyright (C) 2004-06 Simone Rota <sip@varlock.com>
   Copyright (C) 2004-06 Johannes Winkelmann <jw@tks6.net>
   Copyright (C) 2013 Nobuhiro Iwamatsu <iwamatsu@nigauri.org>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
*/

#ifndef _PANEL_H_
#define _PANEL_H_

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>
#include <X11/Xft/Xft.h>
#include <X11/cursorfont.h>
#include <X11/Xmu/WinUtil.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <iostream>
#include <string>

#ifdef NEEDS_BASENAME
#include <libgen.h>
#endif

#include "log.h"
#include "image.h"
#include "panelbase.h"

class Panel : public PanelBase {
public:
	Panel();
	virtual ~Panel();
	void InitPanel(Cfg *config, const std::string& themed, PanelType panel_mode, int testing);
	void OpenPanel();
	void ClosePanel();
	void ClearPanel();
	void WrongPassword(int timeout);
	void Message(const std::string &text);
	void Error(const std::string &text);
	void EventHandler(const FieldType &curfield);

	void Reset(void);
	void ResetName(void);
	void ResetPasswd(void);
	void SetName(const std::string &name);
	void SwitchSession();
	void blankScreen();
	void setBackground(const std::string &themedir);
	void HideCursor();
	void CloseDisplay();
	void KillAllClients(Bool top);
	int ckSvrOpen();


private:
	void SetCursor(int visible);
	unsigned long GetColor(const char *colorname);
	void OnExpose(void);
	void EraseLastChar(string &formerString);
	bool OnKeyPress(XEvent& event);
	void ShowText();
	void ShowSession();

	void SlimDrawString8(XftDraw *d, XftColor *color, XftFont *font,
							int x, int y, const std::string &str,
							XftColor *shadowColor,
							int xOffset, int yOffset);

	Rectangle GetPrimaryViewport();
	void ApplyBackground(Rectangle = Rectangle());

	/* Private data */
	PanelType mode; /* work mode */
	Cfg *cfg;
	Window Win;
	Window Root;
	Display *Dpy;
	int Scr;
	int X, Y;
	GC TextGC;
	GC WinGC;
	XftFont *font;
	XftColor inputshadowcolor;
	XftColor inputcolor;
	XftColor msgcolor;
	XftColor msgshadowcolor;
	XftFont *msgfont;
	XftColor introcolor;
	XftFont *introfont;
	XftFont *welcomefont;
	XftColor welcomecolor;
	XftFont *sessionfont;
	XftColor sessioncolor;
	XftColor sessionshadowcolor;
	XftColor welcomeshadowcolor;
	XftFont *enterfont;
	XftColor entercolor;
	XftColor entershadowcolor;
	FieldType field;
	//Pixmap   background;
	
	/* Username/Password */

	/* screen stuff */
	Rectangle viewport;

	/* Configuration */
	int input_name_x;
	int input_name_y;
	int input_pass_x;
	int input_pass_y;
	int inputShadowXOffset;
	int inputShadowYOffset;
	int input_cursor_height;
	int welcome_x;
	int welcome_y;
	int welcome_shadow_xoffset;
	int welcome_shadow_yoffset;
	int session_shadow_xoffset;
	int session_shadow_yoffset;
	int intro_x;
	int intro_y;
	int username_x;
	int username_y;
	int username_shadow_xoffset;
	int username_shadow_yoffset;
	int password_x;
	int password_y;
	std::string welcome_message;
	std::string intro_message;

	/* Pixmap data */
	Pixmap PanelPixmap;

	Image *image;

	/* For thesting themes */
	bool testing;
	std::string themedir;


	Pixmap BackgroundPixmap;
	Atom BackgroundPixmapId;

};

#endif /* _PANEL_H_ */
