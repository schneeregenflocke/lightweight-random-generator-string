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


#include <vector>


class CharacterConfiguration
{
public:

    enum CharacterType : int
    {
        uppercase,
        lowercase,
        digit,
        special_character
    };

    CharacterConfiguration(CharacterType type, int number) :
        type(type),
        number(number)
    {}

    CharacterType Type() const
    {
        return type;
    }

    int Number() const
    {
        return number;
    }

private:

    CharacterType type;
    int number;
};


class RandomStringConfiguration
{
public:

    RandomStringConfiguration(int string_lenght, const std::vector<CharacterConfiguration>& character_configurations) :
        string_lenght(string_lenght),
        character_configurations(character_configurations)
    {}

    int StringLenght() const
    {
        return string_lenght;
    }

    size_t NumberCharacterTypes() const
    {
        return character_configurations.size();
    }

    CharacterConfiguration GetCharacterConfiguration(size_t index) const
    {
        return character_configurations[index];
    }

private:

    int string_lenght;
    std::vector<CharacterConfiguration> character_configurations;
};
