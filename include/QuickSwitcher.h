/*
 * nheko Copyright (C) 2017  Konstantinos Sideris <siderisk@auth.gr>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <QFrame>
#include <QKeyEvent>
#include <QVBoxLayout>

#include "TextField.h"

class RoomSearchInput : public TextField
{
	Q_OBJECT
public:
	explicit RoomSearchInput(QWidget *parent = nullptr);

protected:
	void keyPressEvent(QKeyEvent *event) override;
	bool focusNextPrevChild(bool next) override;
};

class QuickSwitcher : public QFrame
{
	Q_OBJECT
public:
	explicit QuickSwitcher(QWidget *parent = nullptr);

	void setRoomList(const QMap<QString, QString> &rooms);

signals:
	void closing();
	void roomSelected(const QString &roomid);

protected:
	void keyPressEvent(QKeyEvent *event) override;
	void showEvent(QShowEvent *event) override;

private:
	QVBoxLayout *topLayout_;
	RoomSearchInput *roomSearch_;

	QMap<QString, QString> rooms_;
};
