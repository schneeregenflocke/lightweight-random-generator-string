#ifndef RANDOM_STRING_GENERATOR_H
#define RANDOM_STRING_GENERATOR_H

#include "random_string_configuration.h"
#include <iterator>
#include <random>
#include <string>
#include <vector>

class RandomStringGenerator {
public:
  RandomStringGenerator() { InitializeSpecialCharacters(); }

  static std::vector<size_t> GenerateRandomIndices(size_t number)
  {
    std::vector<size_t> available_indices(number);
    for (size_t index = 0; index < number; ++index) {
      available_indices[index] = index;
    }

    std::vector<size_t> random_indices(number);
    for (size_t index = 0; index < random_indices.size(); ++index) {

      const auto random_index = RandomIntegerNumber(0, (available_indices.size() - 1));
      const auto available_index = available_indices[random_index];
      random_indices[index] = available_index;

      auto iterator = available_indices.begin();
      std::advance(iterator, random_index);
      available_indices.erase(iterator);
    }

    return random_indices;
  }

  [[nodiscard]] std::string
  GeneratePasswordString(const RandomStringConfiguration &password_configuration) const
  {
    const auto random_indices = GenerateRandomIndices(password_configuration.StringLenght());

    std::string random_string;
    random_string.resize(password_configuration.StringLenght());

    size_t random_indices_position = 0;
    for (size_t index = 0; index < password_configuration.NumberCharacterTypes(); ++index) {
      for (size_t subindex = 0;
           subindex < password_configuration.GetCharacterConfiguration(index).Number();
           ++subindex) {
        const auto string_position = random_indices[random_indices_position];
        random_string[string_position] =
            GetRandomLetter(password_configuration.GetCharacterConfiguration(index).Type());
        ++random_indices_position;
      }
    }

    size_t remaining_password_lenght =
        password_configuration.StringLenght() - random_indices_position;

    for (size_t index = 0; index < remaining_password_lenght; ++index) {
      const auto random_select =
          RandomIntegerNumber(0, password_configuration.NumberCharacterTypes() - 1);
      const auto string_position = random_indices[random_indices_position];
      random_string[string_position] =
          GetRandomLetter(password_configuration.GetCharacterConfiguration(random_select).Type());
      ++random_indices_position;
    }

    return random_string;
  }

private:
  static size_t RandomIntegerNumber(const size_t min, const size_t max)
  {
    std::random_device random_device;
    std::uniform_int_distribution<size_t> uniform_int(min, max);
    size_t random_number = uniform_int(random_device);
    return random_number;
  }

  [[nodiscard]] char GetRandomLetter(CharacterConfiguration::CharacterType type) const
  {
    char random_letter = 0;

    if (type == CharacterConfiguration::CharacterType::uppercase) {
      random_letter = static_cast<char>(RandomIntegerNumber(65, 90));
    }

    if (type == CharacterConfiguration::CharacterType::lowercase) {
      random_letter = static_cast<char>(RandomIntegerNumber(97, 122));
    }

    if (type == CharacterConfiguration::CharacterType::digit) {
      random_letter = static_cast<char>(RandomIntegerNumber(48, 57));
    }

    if (type == CharacterConfiguration::CharacterType::special_character) {
      random_letter = static_cast<char>(
          special_characters[RandomIntegerNumber(0, special_characters.size() - 1)]);
    }

    return random_letter;
  }

  void InitializeSpecialCharacters()
  {
    // static constexpr std::array<char, 4> special_characters = {'!', '@', '#', '$'};

    for (char index = 33; index <= 47; ++index) {
      special_characters.push_back(index);
    }

    for (char index = 58; index <= 64; ++index) {
      special_characters.push_back(index);
    }

    for (char index = 91; index <= 96; ++index) {
      special_characters.push_back(index);
    }

    for (char index = 123; index <= 126; ++index) {
      special_characters.push_back(index);
    }
  }

  std::vector<char> special_characters;
};

#endif // RANDOM_STRING_GENERATOR_H
