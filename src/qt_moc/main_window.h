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


#include "random_string_configuration_widget.h"
#include "license_info_dialog.h"

#include <QMainWindow>
#include <QMenuBar>
#include <QPushButton>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr) :
        QMainWindow(parent)
    {
        setMinimumSize(400, 400);

        QWidget* central_widget = new QWidget;
        setCentralWidget(central_widget);

        central_widget->setLayout(new QVBoxLayout);

        password_configuration_widget = new RandomStringConfigurationWidget;

        central_widget->layout()->addWidget(password_configuration_widget);

        QPushButton* generate_password_button = new QPushButton(tr("Generate random string"));
        generate_password_button->setAutoDefault(true);
        //generate_password_button->setShortcut(QKeySequence(Qt::Key::Key_Space));
        central_widget->layout()->addWidget(generate_password_button);

        connect(generate_password_button, &QPushButton::clicked, this, &MainWindow::GeneratePasswordString);

        password_text_edit = new QTextEdit;
        central_widget->layout()->addWidget(password_text_edit);

        license_info_dialog = new LicenseInfoDialog(this);

        password_generator = std::make_unique<RandomStringGenerator>();

        InitMenu();
    }

private slots:

    void GeneratePasswordString()
    {
        std::string password_string = password_generator->GeneratePasswordString(password_configuration_widget->GetRandomStringConfiguration());
        password_text_edit->setText(password_string.c_str());
    }

private:

    void InitMenu()
    {
        QMenu* file_menu = menuBar()->addMenu(tr("&File"));

        QAction* action_license_info = file_menu->addAction(tr("&Open Source License Info"));
        QAction* seperator = file_menu->addSeparator();
        QAction* action_exit = file_menu->addAction(tr("&Exit"));
        
        connect(action_exit, &QAction::triggered, this, &QMainWindow::close);
        connect(action_license_info, &QAction::triggered, license_info_dialog, &QDialog::show);
    }

    QTextEdit* password_text_edit;
    RandomStringConfigurationWidget* password_configuration_widget;
    std::unique_ptr<RandomStringGenerator> password_generator;
    LicenseInfoDialog* license_info_dialog;
};
