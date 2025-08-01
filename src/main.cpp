#include "main_window.hpp"
#include <QApplication>
#include <iostream>
#include <qstylehints.h>

int main(int argc, char **argv)
{
  std::cout << argc << '\n';

  QApplication app(argc, argv);

  QGuiApplication::styleHints()->setColorScheme(Qt::ColorScheme::Light);

  QApplication::setWindowIcon(QIcon(QPixmap(":/images/SRSG_icon.svg")));

  MainWindow main_window;
  main_window.show();

  return QApplication::exec();
}
