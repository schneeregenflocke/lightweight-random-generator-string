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


#include "random_string_configuration.h"

#include <array>
#include <vector>
#include <list>
#include <iterator>
#include <string>
#include <memory>
#include <algorithm>
#include <utility>
#include <numeric>
#include <random>






class RandomStringGenerator
{
public:

    RandomStringGenerator()
    {
        InitializeSpecialCharacters();
    }

    std::vector<size_t> GenerateRandomIndices(size_t number) const
    {
        //fill vector with numbers equal to their index
        std::vector<size_t> unused_indices;
        for (size_t index = 0; index < number; ++index)
        {
            unused_indices.push_back(index);
        }

        std::vector<size_t> random_indices(number);
        for (size_t index = 0; index < random_indices.size(); ++index)
        {
            //generate a random number not larger than the size of the vector with the unused indexes
            const auto random_index = RandomIntegerNumber(0, (unused_indices.size() - 1));
            
            const auto unused_index = unused_indices[random_index];
            random_indices[unused_index] = index;
            
            //delete the index now used from the vector of unused indices
            auto iterator = unused_indices.begin();
            std::advance(iterator, random_index);
            unused_indices.erase(iterator);
        }

        return random_indices;
    }

    std::string GeneratePasswordString(const RandomStringConfiguration& password_configuration) const
    {
        const auto random_indices = GenerateRandomIndices(password_configuration.StringLenght());
        
        std::string random_string;
        random_string.resize(password_configuration.StringLenght());

        size_t random_indices_position = 0;
        for (size_t index = 0; index < password_configuration.NumberCharacterTypes(); ++index)
        {
            for (size_t subindex = 0; subindex < password_configuration.GetCharacterConfiguration(index).Number(); ++subindex)
            {
                const auto string_position = random_indices[random_indices_position];
                random_string[string_position] = GetRandomLetter(password_configuration.GetCharacterConfiguration(index).Type());
                ++random_indices_position; 
            }
        }

        size_t remaining_password_lenght = password_configuration.StringLenght() - random_indices_position;

        for (size_t index = 0; index < remaining_password_lenght; ++index)
        {
            const auto random_select = RandomIntegerNumber(0, password_configuration.NumberCharacterTypes() - 1);
            const auto string_position = random_indices[random_indices_position];
            random_string[string_position] = GetRandomLetter(password_configuration.GetCharacterConfiguration(random_select).Type());
            ++random_indices_position;
        }

        return random_string;
    }

private:

    size_t RandomIntegerNumber(const size_t min, const size_t max) const
    {
        std::random_device random_device;
        std::uniform_int_distribution<size_t> uniform_int(min, max);
        size_t random_number = uniform_int(random_device);
        return random_number;
    }

    char GetRandomLetter(CharacterConfiguration::CharacterType type) const
    {
        char random_letter = 0;

        if (type == CharacterConfiguration::CharacterType::uppercase)
        {
            random_letter = static_cast<char>(RandomIntegerNumber(65, 90));
        }

        if (type == CharacterConfiguration::CharacterType::lowercase)
        {
            random_letter = static_cast<char>(RandomIntegerNumber(97, 122));
        }

        if (type == CharacterConfiguration::CharacterType::digit)
        {
            random_letter = static_cast<char>(RandomIntegerNumber(48, 57));
        }

        if (type == CharacterConfiguration::CharacterType::special_character)
        {
            random_letter = static_cast<char>(special_characters[RandomIntegerNumber(0, special_characters.size() - 1)]);
        }

        return random_letter;
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
