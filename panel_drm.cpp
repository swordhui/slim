/* SLiM - Simple Login Manager
   Copyright (C) 1997, 1998 Per Liden
   Copyright (C) 2004-06 Simone Rota <sip@varlock.com>
   Copyright (C) 2004-06 Johannes Winkelmann <jw@tks6.net>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
*/

#include <sstream>
#include <poll.h>
#include "app.h"
#include "panel_drm.h"
#include "log.h"

using namespace std;


extern App* LoginApp;

Panel_drm::Panel_drm()
{
	printf("Panel_drm: on construction.\n");
	DisplayName = "wayland-0";
	DisplayEnv = "WAYLAND_DISPLAY";
}

void Panel_drm::InitPanel(Cfg* config, const string& themedir, PanelType panel_mode, int testing) 
{
	string welcome_message;
	string intro_message;

	/* Read (and substitute vars in) the welcome message */
	welcome_message = cfg->getWelcomeMessage();
	intro_message = cfg->getOption("intro_msg");

	cfg=config;
	mode=panel_mode;


	printf("Panel_drm: begin InitPanel, mode=%d, test=%d\n", panel_mode, testing);
	printf("%s\n%s\n", welcome_message.c_str(), intro_message.c_str());

	if (mode == Mode_Lock) {
		SetName(getenv("USER"));
	}
}

Panel_drm::~Panel_drm() 
{
	printf("Panel_drm: de-construction.\n");
}

void Panel_drm::OpenPanel() 
{
	printf("Panel_drm: open panel.\n");
}

void Panel_drm::ClosePanel() 
{
	printf("Panel_drm: close panel.\n");
}

void Panel_drm::ClearPanel() 
{
	printf("Panel_drm: clear_panel.\n");
}

void Panel_drm::WrongPassword(int timeout) 
{
	string message;

	message = cfg->getOption("passwd_feedback_msg");

	printf(">>>> WrongPassword: %s\n", message.c_str());

}

void Panel_drm::Message(const string& text) 
{
	printf(">>>> Message: %s\n", text.c_str());
}

void Panel_drm::Error(const string& text) 
{
	ClosePanel();
	Message(text);
	sleep(ERROR_DURATION);
	OpenPanel();
	ClearPanel();
}



void Panel_drm::EventHandler(const Panel_drm::FieldType& curfield) {
	printf("On EventHandler: curfield=%d\n", curfield);
	return;
}








/* choose next available session type */
void Panel_drm::SwitchSession() {
        pair<string,string> ses = cfg->nextSession();
        session_name = ses.first;
        session_exec = ses.second;
        if (session_name.size() > 0) {
			printf("Switch Session: Session name: %s\n", session_exec.c_str());
        }
 }

void Panel_drm::Reset(void){
	ResetName();
	ResetPasswd();
}

void Panel_drm::ResetName(void){
	NameBuffer.clear();
}

void Panel_drm::ResetPasswd(void){
	PasswdBuffer.clear();
	HiddenPasswdBuffer.clear();
}

void Panel_drm::SetName(const string& name){
	NameBuffer=name;
	if (mode == Mode_DM)
		action = Login;
	else
		action = Lock;
}



/* Hide the cursor */
void Panel_drm::HideCursor()
{

}

void Panel_drm::setBackground(const string& themedir)
{
}

void Panel_drm::blankScreen()
{

}

void Panel_drm::CloseDisplay()
{
}

void Panel_drm::KillAllClients(Bool top)
{
}



int Panel_drm::ckSvrOpen()
{
		return 1;
}

