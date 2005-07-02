/*
 * Copyright (C) 2005 Nikolay Pultsin <geometer@mawhrin.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "PalmDialogManager.h"
//#include "PalmOptionsDialog.h"
//#include "PalmOpenFileDialog.h"

void PalmDialogManager::createInstance() {
	ourInstance = new PalmDialogManager();
}

PalmDialogManager::PalmDialogManager() {
}

PalmDialogManager::~PalmDialogManager() {
}

ZLOptionsDialog *PalmDialogManager::createOptionsDialog(const std::string &id, const std::string &title) const {
	return 0;
	//return new PalmOptionsDialog(id, title);
}

int PalmDialogManager::informationBox(const char *title, const char *message, const char *button0, const char *button1, const char *button2) const {
	return 0;
	//return QMessageBox::information(qApp->mainWidget(), title, message, button0, button1, button2);
}

void PalmDialogManager::openFileDialog(const std::string &title, const ZLTreeHandler &handler) const {
	//PalmOpenFileDialog(title.c_str(), handler).exec();
}
