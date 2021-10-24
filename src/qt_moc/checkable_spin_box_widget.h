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


#include "../random_string_generator.h"

#include <QString>
#include <QWidget>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QSpinBox>


#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QResource>
#include <QLabel>

#include <memory>


class CheckableSpinBox : public QWidget
{
	Q_OBJECT

public:

	explicit CheckableSpinBox(QWidget* parent = nullptr) :
		QWidget(parent)
	{
		h_box_layout = std::make_unique<QHBoxLayout>();
        setLayout(h_box_layout.get());

        h_box_layout->setContentsMargins(0, 0, 0, 0);
		
		check_box = std::make_unique<QCheckBox>();
		check_box->setCheckState(Qt::CheckState::Checked);

		spin_box = std::make_unique<QSpinBox>();
		spin_box->setMinimumWidth(100);

        h_box_layout->addWidget(check_box.get());
        h_box_layout->addStretch(1);
        h_box_layout->addWidget(spin_box.get());
		
		connect(check_box.get(), &QCheckBox::stateChanged, this, &CheckableSpinBox::CheckBoxStateChanged);
		connect(spin_box.get(), &QSpinBox::valueChanged, this, &CheckableSpinBox::SpinBoxValueChanged);
	}

    void SetText(const QString& text)
    {
        check_box->setText(text);
    }

    int Value() const
    {
        return spin_box->value();
    }

    void SetValue(const int value)
    {
        spin_box->setValue(value);
    }

    void SetCheckState(Qt::CheckState state)
    {
        check_box->setCheckState(state);
    }

    Qt::CheckState CheckState() const
    {
        return check_box->checkState();
    }

    void SetRange(const int min, const int max)
    {
        spin_box->setRange(min, max);
    }

signals:

	void OptionalSpinBoxChanged();

private slots:
	
    void CheckBoxStateChanged(int state)
	{
		if (state == Qt::CheckState::Unchecked)
		{
			spin_box->setDisabled(true);
		}
		if (state == Qt::CheckState::Checked)
		{
			spin_box->setDisabled(false);
		}

		emit OptionalSpinBoxChanged();
	}

	void SpinBoxValueChanged(int value)
	{
		emit OptionalSpinBoxChanged();
	}

private:

    std::unique_ptr<QHBoxLayout> h_box_layout;
	std::unique_ptr<QCheckBox> check_box;
	std::unique_ptr<QSpinBox> spin_box;
};
