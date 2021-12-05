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
along with this program. If not, see <https://www.gnu.org/licenses/>.
*/


#pragma once

#include "../random_string_configuration.h"
//#include "../random_string_generator.h"
#include "checkable_spin_box_widget.h"

#include <QWidget>

class RandomStringConfigurationWidget : public QWidget
{
    Q_OBJECT

public:

    explicit RandomStringConfigurationWidget(QWidget* parent = nullptr) :
        QWidget(parent),
        max_password_lenght(1024),
        inital_password_lenght(32),
        initial_minimum_number_uppercase_letters(8),
        initial_minimum_number_lowercase_letters(8),
        initial_minimum_number_digits(8),
        initial_minimum_special_characters(8)
    {
        v_box_layout = std::make_unique<QVBoxLayout>();
        setLayout(v_box_layout.get());

        v_box_layout->setContentsMargins(0, 0, 0, 0);

        password_lenght_label = std::make_unique<QLabel>(tr("String lenght:"));
        v_box_layout->addWidget(password_lenght_label.get());


        password_lenght_widget = std::make_unique<QSpinBox>();
        password_lenght_widget->setRange(0, max_password_lenght);
        password_lenght_widget->setValue(inital_password_lenght);
        v_box_layout->addWidget(password_lenght_widget.get());

        connect(password_lenght_widget.get(), &QSpinBox::valueChanged, this, &RandomStringConfigurationWidget::UpdatePasswordConfiguration);


        for (auto& character_configuration_widget : character_configuration_widgets)
        {
            character_configuration_widget = std::make_unique<CheckableSpinBox>();
            v_box_layout->addWidget(character_configuration_widget.get());
        }

        character_configuration_widgets[0]->SetText(tr("Minimum number of uppercase letters"));
        character_configuration_widgets[0]->SetValue(initial_minimum_number_uppercase_letters);

        character_configuration_widgets[1]->SetText(tr("Minimum number of lowercase letters"));
        character_configuration_widgets[1]->SetValue(initial_minimum_number_lowercase_letters);

        character_configuration_widgets[2]->SetText(tr("Minimum number of digits"));
        character_configuration_widgets[2]->SetValue(initial_minimum_number_digits);

        character_configuration_widgets[3]->SetText(tr("Minimum number of special characters"));
        character_configuration_widgets[3]->SetValue(initial_minimum_special_characters);
        character_configuration_widgets[3]->SetCheckState(Qt::CheckState::Unchecked);

        SetCharacterConfigurationWidgetsRanges(max_password_lenght);

        for (auto& character_configuration_widget : character_configuration_widgets)
        {
            connect(character_configuration_widget.get(), &CheckableSpinBox::OptionalSpinBoxChanged, this, &RandomStringConfigurationWidget::UpdatePasswordConfiguration);
        }

        /*QString special_character_tooltip(tr("Special Characters: "));
        for (const auto& special_character : special_characters)
        {
            special_character_tooltip.append(special_character);
            special_character_tooltip.append(" ");
        }
        minimum_number_widgets[3]->GetCheckBoxPtr()->setToolTip(special_character_tooltip);
        minimum_number_widgets[3]->GetCheckBoxPtr()->setToolTipDuration(0);*/
    }

    RandomStringConfiguration GetRandomStringConfiguration() const
    {
        RandomStringConfiguration configuration(password_lenght_widget->value(), GetCharacterConfigurations());
        return configuration;
    }

    std::vector<CharacterConfiguration> GetCharacterConfigurations() const
    {
        const auto checked_state_indices = GetCheckedStateIndices();
        std::vector<CharacterConfiguration> configurations;
        for (const auto& checked_state_index : checked_state_indices)
        {
            CharacterConfiguration::CharacterType type = static_cast<CharacterConfiguration::CharacterType>(checked_state_index);
            CharacterConfiguration character_configuration(type, character_configuration_widgets[checked_state_index]->Value());
            configurations.push_back(character_configuration);
        }
        return configurations;
    }

private slots:

    void UpdatePasswordConfiguration()
    {
        // prevent that there is no choice
        const auto checked_state_indices = GetCheckedStateIndices();
        if (checked_state_indices.size() == 0)
        {
            for (auto& character_configuration_widget : character_configuration_widgets)
            {
                if (sender() == character_configuration_widget.get())
                {
                    character_configuration_widget->SetCheckState(Qt::CheckState::Checked);
                }
            }
        }

        // prevent the password configuration from exceeding the string length
        while (ConfigurationExceedingSize() > 0)
        {
            if (sender() == password_lenght_widget.get())
            {
                if (GetCheckedValuesSum() < max_password_lenght)
                {
                    const int configuration_sum = GetCheckedValuesSum();
                    password_lenght_widget->setValue(configuration_sum);
                }
                else
                {
                    password_lenght_widget->setValue(max_password_lenght);
                }
            }

            for (auto& character_configuration_widget : character_configuration_widgets)
            {
                if (sender() == character_configuration_widget.get())
                {
                    if (GetCheckedValuesSum() <= max_password_lenght)
                    {
                        password_lenght_widget->setValue(GetCheckedValuesSum());
                    }
                    else
                    {
                        character_configuration_widget->SetValue(character_configuration_widget->Value() - ConfigurationExceedingSize());
                    }

                }
            }  
        }
    }

private:

    int ConfigurationExceedingSize()
    {
        const int password_lenght = password_lenght_widget->value();
        const int checked_values_sum = GetCheckedValuesSum();
        const int exceeding_size = checked_values_sum - password_lenght;
        return exceeding_size;
    }

    std::vector<int> GetCheckedStateIndices() const
    {
        std::vector<int> checked_state_indices;
        for (size_t index = 0; index < character_configuration_widgets.size(); ++index)
        {
            if (character_configuration_widgets[index]->CheckState() == Qt::CheckState::Checked)
            {
                checked_state_indices.push_back(index);
            }
        }
        return checked_state_indices;
    }

    int GetCheckedValuesSum() const
    {
        const auto checked_state_indices = GetCheckedStateIndices();
        int sum = 0;
        for (const auto& checked_state_index : checked_state_indices)
        {
            sum += character_configuration_widgets[checked_state_index]->Value();
        }
        return sum;
    }

    void SetCharacterConfigurationWidgetsRanges(int max_range)
    {
        for (auto& minimum_number_widget : character_configuration_widgets)
        {
            minimum_number_widget->SetRange(0, max_range);
        }
    }

    const int max_password_lenght;
    const int inital_password_lenght;
    const int initial_minimum_number_uppercase_letters;
    const int initial_minimum_number_lowercase_letters;
    const int initial_minimum_number_digits;
    const int initial_minimum_special_characters;

    std::unique_ptr<QVBoxLayout> v_box_layout;
    std::unique_ptr<QLabel> password_lenght_label;
    std::unique_ptr<QSpinBox> password_lenght_widget;
    std::array<std::unique_ptr<CheckableSpinBox>, 4> character_configuration_widgets;
};