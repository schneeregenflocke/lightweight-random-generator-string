#ifndef CHECKABLE_SPINBOX_WIDGET_H
#define CHECKABLE_SPINBOX_WIDGET_H

#include <QCheckBox>
#include <QFile>
#include <QHBoxLayout>
#include <QLabel>
#include <QPointer>
#include <QResource>
#include <QSpinBox>
#include <QString>
#include <QTextEdit>
#include <QTextStream>
#include <QWidget>

class CheckableSpinBox : public QWidget {
  Q_OBJECT

public:
  explicit CheckableSpinBox(QWidget *parent = nullptr)
      : QWidget(parent), check_box(new QCheckBox(this)), spin_box(new QSpinBox(this))
  {
    QPointer<QHBoxLayout> hbox_layout = new QHBoxLayout(this);
    setLayout(hbox_layout);
    hbox_layout->setContentsMargins(0, 0, 0, 0);

    constexpr int minimum_width = 100;
    spin_box->setMinimumWidth(minimum_width);

    check_box->setCheckState(Qt::CheckState::Checked);

    hbox_layout->addWidget(check_box);
    hbox_layout->addStretch(1);
    hbox_layout->addWidget(spin_box);

    connect(check_box, &QCheckBox::stateChanged, this, &CheckableSpinBox::CheckBoxStateChanged);
    connect(spin_box, &QSpinBox::valueChanged, this, &CheckableSpinBox::SpinBoxValueChanged);
  }

  void SetText(const QString &text) { check_box->setText(text); }

  [[nodiscard]] int Value() const { return spin_box->value(); }

  void SetValue(const int value) { spin_box->setValue(value); }

  void SetCheckState(Qt::CheckState state) { check_box->setCheckState(state); }

  Qt::CheckState CheckState() const { return check_box->checkState(); }

  void SetRange(const int min, const int max) { spin_box->setRange(min, max); }

signals:

  void OptionalSpinBoxChanged();

private slots:

  void CheckBoxStateChanged(int state)
  {
    if (state == Qt::CheckState::Unchecked) {
      spin_box->setDisabled(true);
    }
    if (state == Qt::CheckState::Checked) {
      spin_box->setDisabled(false);
    }

    emit OptionalSpinBoxChanged();
  }

  void SpinBoxValueChanged(int value) { emit OptionalSpinBoxChanged(); }

private: // NOLINT(readability-redundant-access-specifiers)
  QPointer<QCheckBox> check_box;
  QPointer<QSpinBox> spin_box;
};

#endif // CHECKABLE_SPINBOX_WIDGET_H
