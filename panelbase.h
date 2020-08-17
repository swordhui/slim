/* SLiM - Simple Login Manager
   Copyright (C) 1997, 1998 Per Liden
   Copyright (C) 2004-06 Simone Rota <sip@varlock.com>
   Copyright (C) 2004-06 Johannes Winkelmann <jw@tks6.net>
   Copyright (C) 2013 Nobuhiro Iwamatsu <iwamatsu@nigauri.org>
   Copyright (C) 2020 Lihui Zhang <swordhui@hotmail.com>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   Panel interface, for seperate backends

*/

#ifndef _PANEL_BASE_H_
#define _PANEL_BASE_H_

#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <iostream>
#include <string>

#include "cfg.h"


struct Rectangle {
	int x;
	int y;
	unsigned int width;
	unsigned int height;

	Rectangle() : x(0), y(0), width(0), height(0) {};
	Rectangle(int x, int y, unsigned int width,
					unsigned int height) :
		x(x), y(y), width(width), height(height) {};
	bool is_empty() const {
		return width == 0 || height == 0;
	}
};

class PanelBase {
public:
	enum ActionType {
		Login,
		Lock,
		Console,
		Reboot,
		Halt,
		Exit,
		Suspend
	};

	enum FieldType {
		Get_Name,
		Get_Passwd
	};

	enum PanelType {
		Mode_DM,
		Mode_Lock
	};

	virtual void InitPanel(Cfg *config, const std::string& themed, PanelType panel_mode, int testing)=0;
	virtual void OpenPanel()=0;
	virtual void ClosePanel()=0;
	virtual void ClearPanel()=0;
	virtual void WrongPassword(int timeout)=0;
	virtual void Message(const std::string &text)=0;
	virtual void Error(const std::string &text)=0;
	virtual void EventHandler(const FieldType &curfield)=0;
	virtual std::string getSession(){return session_exec;} 
	ActionType getAction(void) const{return action;}

	virtual void Reset(void)=0;
	virtual void ResetName(void)=0;
	virtual void ResetPasswd(void)=0;
	virtual void SetName(const std::string &name)=0;
	const std::string& GetName(void) const {return NameBuffer;} 
	const std::string& GetPasswd(void) const {return PasswdBuffer;}

	virtual const char* getDisplayName(void) {return DisplayName;}
	virtual const char* getDisplayEnv(void) {return DisplayEnv;}
	virtual void SwitchSession()=0;
	virtual void blankScreen()=0;
	virtual void setBackground(const std::string &themedir)=0;
	virtual void HideCursor()=0;
	virtual void CloseDisplay()=0;
	virtual void KillAllClients(Bool top)=0;
	virtual int ckSvrOpen()=0;

protected:
	ActionType action;
	std::string NameBuffer;
	std::string PasswdBuffer;
	std::string HiddenPasswdBuffer;

	/* Session handling */
	std::string session_name;
    std::string session_exec;

	/* Options */
	const char *DisplayName;
	const char *DisplayEnv;
};

#endif /* _PANEL_H_ */
