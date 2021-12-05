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


#include "qt_moc/main_window.h"

#include <QApplication>
//#include <QWindow>
//#include <QScreen>

//#include <iostream>


int main(int argc, char** argv)
{
	//QLocale::system().name();

	//see https://doc.qt.io/qt-5/highdpi.html
	//auto high_dpi_policy = QApplication::highDpiScaleFactorRoundingPolicy();
	QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Round);

	QApplication app(argc, argv);

	MainWindow main_window;
	main_window.show();

	//auto window_device_pixel_ratio = main_window.devicePixelRatio();

	return app.exec();
}
