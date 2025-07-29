#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "license_info_dialog.h"
#include "random_string_configuration_widget.h"
#include "random_string_generator.h"
#include <QIcon>
#include <QMainWindow>
#include <QMenuBar>
#include <QPointer>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr)
      : QMainWindow(parent), password_configuration_widget(new ConfigurationWidget(this)),
        password_text_edit(new QTextEdit(this)), license_info_dialog(new LicenseInfoDialog(this))
  {
    constexpr int min_window_width = 400;
    constexpr int min_window_height = 400;
    setMinimumSize(min_window_width, min_window_height);

    QPointer<QWidget> central_widget = new QWidget(this);
    setCentralWidget(central_widget);

    QPointer<QVBoxLayout> vbox_layout = new QVBoxLayout(this);
    central_widget->setLayout(vbox_layout);

    central_widget->layout()->addWidget(password_configuration_widget);
    central_widget->layout()->addWidget(password_text_edit);

    QPointer<QPushButton> generate_password_button =
        new QPushButton(tr("Generate random string"), this);
    generate_password_button->setAutoDefault(true);
    central_widget->layout()->addWidget(generate_password_button);
    // generate_password_button->setShortcut(QKeySequence(Qt::Key::Key_Space));

    connect(generate_password_button, &QPushButton::clicked, this,
            &MainWindow::GeneratePasswordString);

    password_generator = std::make_unique<RandomStringGenerator>();

    InitMenu();
  }

private slots:

  void GeneratePasswordString()
  {
    std::string password_string = password_generator->GeneratePasswordString(
        password_configuration_widget->GetRandomStringConfiguration());
    password_text_edit->setText(password_string.c_str());
  }

private: // NOLINT(readability-redundant-access-specifiers)
  void InitMenu()
  {
    QMenu *file_menu = menuBar()->addMenu(tr("&File"));

    QAction *action_license_info =
        file_menu->addAction(QIcon::fromTheme("help-about"), tr("&Open Source License Info"));
    QAction *seperator = file_menu->addSeparator();
    QAction *action_exit = file_menu->addAction(QIcon::fromTheme("application-exit"), tr("&Exit"));

    connect(action_exit, &QAction::triggered, this, &QMainWindow::close);
    connect(action_license_info, &QAction::triggered, license_info_dialog, &QDialog::show);
  }

  QPointer<QTextEdit> password_text_edit;
  QPointer<ConfigurationWidget> password_configuration_widget;
  std::unique_ptr<RandomStringGenerator> password_generator;
  QPointer<LicenseInfoDialog> license_info_dialog;
};

#endif // MAIN_WINDOW_H