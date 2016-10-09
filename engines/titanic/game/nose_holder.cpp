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

#include "titanic/game/nose_holder.h"

namespace Titanic {

BEGIN_MESSAGE_MAP(CNoseHolder, CDropTarget)
	ON_MESSAGE(ActMsg)
	ON_MESSAGE(FrameMsg)
	ON_MESSAGE(LeaveViewMsg)
	ON_MESSAGE(MovieEndMsg)
	ON_MESSAGE(EnterViewMsg)
END_MESSAGE_MAP()

CNoseHolder::CNoseHolder() : CDropTarget(), _dragObject(nullptr),
		_field11C(0) {
}

void CNoseHolder::save(SimpleFile *file, int indent) {
	file->writeNumberLine(1, indent);
	file->writeNumberLine(_field11C, indent);

	CDropTarget::save(file, indent);
}

void CNoseHolder::load(SimpleFile *file) {
	file->readNumber();
	_field11C = file->readNumber();

	CDropTarget::load(file);
}

bool CNoseHolder::ActMsg(CActMsg *msg) {
	if (msg->_action == "Sneeze" && !_itemName.empty() && _fieldF4) {
		CProximity prox;
		prox._positioningMode = POSMODE_VECTOR;
		playSound("z#35.wav", prox);

		if (getView() == findView()) {
			setVisible(true);
			playMovie(1, 13, MOVIE_NOTIFY_OBJECT);
		}
	}

	return true;
}

bool CNoseHolder::FrameMsg(CFrameMsg *msg) {
	if (!_dragObject) {
		CGameObject *dragObj = getDraggingObject();
		if (!dragObj)
			return false;

		if (!dragObj->isEquals("Feathers") || getView() != findView())
			return false;

		_dragObject = dragObj;
	}

	if (_dragObject) {
		if (!checkPoint(Point(_dragObject->_bounds.left,
				_dragObject->_bounds.top))) {
			_field11C = false;
		} else if (!_field11C) {
			CActMsg actMsg("Sneeze");
			actMsg.execute(this);
			_field11C = true;
		}
	}

	return true;
}

bool CNoseHolder::LeaveViewMsg(CLeaveViewMsg *msg) {
	_field11C = false;
	_dragObject = nullptr;
	if (_fieldF4) {
		loadFrame(_dropFrame);
		setVisible(false);
	}

	return true;
}

bool CNoseHolder::MovieEndMsg(CMovieEndMsg *msg) {
	if (_fieldF4) {
		loadFrame(_dropFrame);
		setVisible(false);
	}

	return true;
}

bool CNoseHolder::EnterViewMsg(CEnterViewMsg *msg) {
	if (_fieldF4)
		setVisible(false);

	return CDropTarget::EnterViewMsg(msg);
}

} // End of namespace Titanic
