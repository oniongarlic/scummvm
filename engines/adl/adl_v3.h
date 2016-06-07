/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef ADL_ADL_V3_H
#define ADL_ADL_V3_H

#include "adl/adl_v2.h"

// Note: this version of ADL redraws only when necessary, but
// this is not currently implemented.

namespace Common {
class RandomSource;
}

struct DiskOffset {
	byte track;
	byte sector;
};

namespace Adl {

class AdlEngine_v3 : public AdlEngine_v2 {
public:
	virtual ~AdlEngine_v3() { }

protected:
	AdlEngine_v3(OSystem *syst, const AdlGameDescription *gd);

	// AdlEngine
	virtual void setupOpcodeTables();
	virtual Common::String loadMessage(uint idx) const;
	Common::String getItemDescription(const Item &item) const;

	// AdlEngine_v2
	virtual DataBlockPtr readDataBlockPtr(Common::ReadStream &f) const;

	void applyDiskOffset(byte &track, byte &sector) const;

	int o3_isVarGT(ScriptEnv &e);
	int o3_isItemInRoom(ScriptEnv &e);
	int o3_isNounNotInRoom(ScriptEnv &e);
	int o3_skipOneCommand(ScriptEnv &e);
	int o3_moveItem(ScriptEnv &e);
	int o3_dummy(ScriptEnv &e);
	int o3_setTextMode(ScriptEnv &e);
	int o3_setDisk(ScriptEnv &e);
	int o3_sound(ScriptEnv &e);

	Common::Array<Common::String> _itemDesc;
	byte _curDisk;
	Common::Array<DiskOffset> _diskOffsets;
};

} // End of namespace Adl

#endif
