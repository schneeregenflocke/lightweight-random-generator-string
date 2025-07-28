#include "main_window.h"
#include <QApplication>
#include <qstylehints.h>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  QGuiApplication::styleHints()->setColorScheme(Qt::ColorScheme::Light);

  QApplication::setWindowIcon(QIcon(QPixmap(":/images/SRSG_icon.svg")));

  MainWindow main_window;
  main_window.show();

  return QApplication::exec();
}
