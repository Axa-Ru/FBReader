/*
 * FBReader -- electronic book reader
 * Copyright (C) 2004, 2005 Nikolay Pultsin <geometer@mawhrin.net>
 * Copyright (C) 2005 Mikhail Sobolev <mss@mawhrin.net>
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include <abstract/ZLFSManager.h>

#include "PdbPlugin.h"
#include "PluckerBookReader.h"
#include "../../description/BookDescription.h"

bool PluckerPlugin::acceptsFile(const ZLFile &file) const {
	return PdbPlugin::fileType(file) == "DataPlkr";
}

bool PluckerPlugin::readDescription(const std::string &path, BookDescription &description) const {
	ZLFile file(path);
	WritableBookDescription(description).encoding() = "US_ASCII";
	defaultAuthor(description);
	defaultTitle(description, file.name());
	return true;
}

bool PluckerPlugin::readModel(const BookDescription &description, BookModel &model) const {
	return PluckerBookReader(description.fileName(), model).readDocument();
}

const std::string &PluckerPlugin::iconName() const {
	static const std::string ICON_NAME = "FBReader/plucker";
	return ICON_NAME;
}
