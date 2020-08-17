/* SLiM - Simple Login Manager
   Copyright (C) 2020 Lihui Zhang <swordhui@hotmail.com>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
*/

#ifndef _PANEL_DRM_H_
#define _PANEL_DRM_H_

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

class Panel_drm : public PanelBase {
public:
	Panel_drm();
	virtual ~Panel_drm();
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

	PanelType mode; /* work mode */
	Cfg *cfg;

};

#endif /* _PANEL_H_ */
