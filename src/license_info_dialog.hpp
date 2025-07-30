#ifndef LICENSE_INFO_DIALOG_H
#define LICENSE_INFO_DIALOG_H

#include <QDialog>
#include <QFile>
#include <QLabel>
#include <QPointer>
#include <QResource>
#include <QString>
#include <QTextEdit>
#include <QTextStream>
#include <QVBoxLayout>

class LicenseInfoDialog : public QDialog {
  Q_OBJECT

public:
  explicit LicenseInfoDialog(QWidget *parent = nullptr) : QDialog(parent)
  {
    setWindowTitle(tr("Open Source License Info"));
    setSizeGripEnabled(true);
    setModal(false);

    constexpr int min_window_width = 600;
    constexpr int min_window_height = 400;
    setMinimumSize(min_window_width, min_window_height);

    QPointer<QVBoxLayout> vbox_layout = new QVBoxLayout(this);
    setLayout(vbox_layout);

    QResource resource(":/LICENSE.txt");
    const QByteArray bytes = resource.uncompressedData();
    const QString license_text = QString::fromUtf8(bytes);

    QPointer<QTextEdit> license_text_edit = new QTextEdit(this);
    license_text_edit->setText(license_text);
    vbox_layout->addWidget(license_text_edit);

    QPointer<QLabel> application_name_label =
        new QLabel("lightweight-random-string-generator", this);
    QPointer<QLabel> copyright_notice_label =
        new QLabel(QString::fromWCharArray(L"Copyright \xa9 2021 - 2025 Marco Peyer"));
    application_name_label->setTextInteractionFlags(Qt::TextSelectableByMouse);
    copyright_notice_label->setTextInteractionFlags(Qt::TextSelectableByMouse);
    vbox_layout->addWidget(application_name_label);
    vbox_layout->addWidget(copyright_notice_label);
  }

private:
};

#endif
