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


#include <array>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <utility>
#include <numeric>
#include <random>



struct RandomStringConfiguration
{
public:

    struct CharacterConfiguration
    {
        int type;
        int number;
    };

    std::vector<CharacterConfiguration> character_configuration;
    int password_lenght;

    enum
    {
        uppercase,
        lowercase,
        digit,
        special_character
    };
};


class RandomStringGenerator
{
public:

    RandomStringGenerator()
    {
        InitializeSpecialCharacters();
    }

    std::vector<size_t> RandomIndices(size_t number) const
    {
        std::vector<size_t> non_taken_indices(number);
        for (size_t index = 0; index < non_taken_indices.size(); ++index)
        {
            non_taken_indices[index] = index;
        }

        std::vector<size_t> random_indices(number);
        for (size_t index = 0; index < random_indices.size(); ++index)
        {
            const auto random_index = RandomIntegerNumber(0, (non_taken_indices.size() - 1));
            random_indices[non_taken_indices[random_index]] = index;
            non_taken_indices.erase(non_taken_indices.begin() + random_index);
        }

        return random_indices;
    }

    std::string GeneratePasswordString(const RandomStringConfiguration& password_configuration) const
    {
        const auto random_indices = RandomIndices(password_configuration.password_lenght);
        
        std::string password_string;
        password_string.resize(password_configuration.password_lenght);

        size_t password_string_position = 0;
        for (size_t index = 0; index < password_configuration.character_configuration.size(); ++index)
        {
            for (size_t counter = 0; counter < password_configuration.character_configuration[index].number; ++counter)
            {
                if (password_configuration.character_configuration[index].type == RandomStringConfiguration::uppercase)
                {
                    password_string[random_indices[password_string_position]] = GetRandomUppercaseLetter();
                    ++password_string_position;
                }

                if (password_configuration.character_configuration[index].type == RandomStringConfiguration::lowercase)
                {
                    password_string[random_indices[password_string_position]] = GetRandomLowercaseLetter();
                    ++password_string_position;
                }

                if (password_configuration.character_configuration[index].type == RandomStringConfiguration::digit)
                {
                    password_string[random_indices[password_string_position]] = GetRandomDigit();
                    ++password_string_position;
                }

                if (password_configuration.character_configuration[index].type == RandomStringConfiguration::special_character)
                {
                    password_string[random_indices[password_string_position]] = GetRandomSpecialCharacter();
                    ++password_string_position;
                }
            }
        }

        size_t remaining_password_lenght = password_configuration.password_lenght - password_string_position;

        for (size_t index = 0; index < remaining_password_lenght; ++index)
        {
            auto random_select = RandomIntegerNumber(0, password_configuration.character_configuration.size() - 1);

            if (password_configuration.character_configuration[random_select].type == RandomStringConfiguration::uppercase)
            {
                password_string[random_indices[password_string_position]] = GetRandomUppercaseLetter();
                ++password_string_position;
            }

            if (password_configuration.character_configuration[random_select].type == RandomStringConfiguration::lowercase)
            {
                password_string[random_indices[password_string_position]] = GetRandomLowercaseLetter();
                ++password_string_position;
            }

            if (password_configuration.character_configuration[random_select].type == RandomStringConfiguration::digit)
            {
                password_string[random_indices[password_string_position]] = GetRandomDigit();
                ++password_string_position;
            }

            if (password_configuration.character_configuration[random_select].type == RandomStringConfiguration::special_character)
            {
                password_string[random_indices[password_string_position]] = GetRandomSpecialCharacter();
                ++password_string_position;
            }
        }

        return password_string;
    }

private:

    size_t RandomIntegerNumber(const size_t min, const size_t max) const
    {
        std::random_device random_device;
        std::uniform_int_distribution<size_t> uniform_int(min, max);
        size_t random_number = uniform_int(random_device);
        return random_number;
    }

    char GetRandomUppercaseLetter() const
    {
        return static_cast<char>(RandomIntegerNumber(65, 90));
    }

    char GetRandomLowercaseLetter() const
    {
        return static_cast<char>(RandomIntegerNumber(97, 122));
    }

    char GetRandomDigit() const
    {
        return static_cast<char>(RandomIntegerNumber(48, 57));
    }

    char GetRandomSpecialCharacter() const
    {
        return static_cast<char>(special_characters[RandomIntegerNumber(0, special_characters.size() - 1)]);
    }

    void InitializeSpecialCharacters()
    {
        for (char index = 33; index <= 47; ++index)
        {
            special_characters.push_back(index);
        }

        for (char index = 58; index <= 64; ++index)
        {
            special_characters.push_back(index);
        }

        for (char index = 91; index <= 96; ++index)
        {
            special_characters.push_back(index);
        }

        for (char index = 123; index <= 126; ++index)
        {
            special_characters.push_back(index);
        }
    }

    std::vector<char> special_characters;
};
