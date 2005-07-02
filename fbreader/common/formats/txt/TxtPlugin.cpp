/*
 * FBReader -- electronic book reader
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

#include <abstract/ZLStringUtil.h>
#include <abstract/ZLFSManager.h>
#include <abstract/ZLInputStream.h>

#include "TxtPlugin.h"
#include "TxtBookReader.h"
#include "PlainTextFormat.h"
#include "../EncodingDetector.h"
#include "../../description/BookDescription.h"

bool TxtPlugin::acceptsFile(const std::string &fileName) const {
	return ZLStringUtil::stringEndsWith(fileName, ".txt");
}

bool TxtPlugin::readDescription(const std::string &fileName, BookDescription &description) const {
	WritableBookDescription wDescription(description);

	std::string encoding = description.encoding();
	if (encoding.empty()) {
		ZLInputStream *stream = ZLFSManager::instance().createInputStream(fileName);
		encoding = EncodingDetector::detect(*stream);
		delete stream;
		if (encoding.empty()) {
			return false;
		}
		wDescription.encoding() = encoding;
	}

	if (description.author() == 0) {
		wDescription.addAuthor("Unknown", "", "Author");
	}

	if (description.language().empty()) {
		int index = std::max((int)fileName.rfind('/'), (int)fileName.rfind(':'));
		std::string title = (index > 0) ? fileName.substr(index + 1) : fileName;
		index = title.rfind('.');
		wDescription.title() = (index > 0) ? title.substr(0, index) : title;
		if (wDescription.language().empty()) {
			if (wDescription.encoding() == "US-ASCII") {
				wDescription.language() = "en";
			} else if ((wDescription.encoding() == "KOI8-R") ||
					(wDescription.encoding() == "windows-1251") ||
					(wDescription.encoding() == "ISO-8859-5") ||
					(wDescription.encoding() == "IBM866")) {
				wDescription.language() = "ru";
			}
		}
	}

	return true;
}

bool TxtPlugin::readModel(const BookDescription &description, BookModel &model) const {
	ZLInputStream *stream = ZLFSManager::instance().createInputStream(description.fileName());
	if (stream == 0) {
		return false;
	}

	PlainTextFormat format(description.fileName());
	if (!format.initialized()) {
		PlainTextFormatDetector detector;
		detector.detect(*stream, format);
	}

	TxtBookReader *reader = new TxtBookReader(model, format);
	reader->readDocument(*stream, description.encoding());
	delete stream;
	delete reader;
	return true;
}

const std::string &TxtPlugin::iconName() const {
	static const std::string ICON_NAME = "FBReader/unknown";
	return ICON_NAME;
}

FormatInfoPage *TxtPlugin::createInfoPage(ZLOptionsDialog &dialog, const std::string &fileName) {
	return new PlainTextInfoPage(dialog, fileName);
}
