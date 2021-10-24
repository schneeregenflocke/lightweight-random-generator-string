/*
SimpleRandomStringGenerator
Copyright (c) 2021 Marco Peyer

This program is free software: you can redistribute it and /or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see < https://www.gnu.org/licenses/>.
*/


#pragma once


#include <QDialog>
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QResource>
#include <QLabel>
#include <QVBoxLayout>

#include <memory>


class LicenseInfoDialog : public QDialog
{

	Q_OBJECT

public:
	explicit LicenseInfoDialog(QWidget* parent = nullptr) :
		QDialog(parent)
	{
		setWindowTitle(tr("Open Source License Info"));
		setSizeGripEnabled(true);
		setModal(false);
		setMinimumSize(600, 400);

		QResource res(":/gpl-3.0-standalone.html");
		QByteArray byte_array(reinterpret_cast<const char*>(res.data()), res.size());
		QString html_license(byte_array);

		license_text_edit = std::make_unique<QTextEdit>();
		license_text_edit->setHtml(html_license);


		application_name_label = std::make_unique<QLabel>("SimpleRandomStringGenerator");
		copyright_notice_label = std::make_unique<QLabel>(QString::fromWCharArray(L"Copyright \xa9 2021 Marco Peyer"));
		application_name_label->setTextInteractionFlags(Qt::TextSelectableByMouse);
		copyright_notice_label->setTextInteractionFlags(Qt::TextSelectableByMouse);


		v_box_layout = std::make_unique<QVBoxLayout>();
		setLayout(v_box_layout.get());

		v_box_layout->addWidget(application_name_label.get());
		v_box_layout->addWidget(copyright_notice_label.get());
		v_box_layout->addWidget(license_text_edit.get());
	}

private:

	std::unique_ptr<QVBoxLayout> v_box_layout;
	std::unique_ptr<QTextEdit> license_text_edit;
	std::unique_ptr<QLabel> application_name_label;
	std::unique_ptr<QLabel> copyright_notice_label;
};