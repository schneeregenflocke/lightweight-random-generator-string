#ifndef GENERATOR_H
#define GENERATOR_H

#include "configuration.hpp"
#include <iterator>
#include <random>
#include <string>
#include <vector>

class Generator {
public:
  Generator() { init_special_characters(); }

  static std::vector<size_t> generate_random_indices(const size_t number)
  {
    std::vector<size_t> available_indices(number);
    for (size_t index = 0; index < number; ++index) {
      available_indices[index] = index;
    }

    std::vector<size_t> random_indices(number);
    for (auto &random_index : random_indices) {

      const auto random_number = generate_random_integer(0, (available_indices.size() - 1));
      const auto available_index = available_indices[random_number];
      random_index = available_index;

      auto iterator = available_indices.begin();
      std::advance(iterator, random_number);
      available_indices.erase(iterator);
    }

    return random_indices;
  }

  [[nodiscard]] std::string generate_string(const StringConfiguration &configuration)
  {
    random_indices = generate_random_indices(configuration.StringLenght());

    std::string random_string;
    random_string.resize(configuration.StringLenght());

    size_t random_indices_position = 0;
    for (size_t index = 0; index < configuration.NumberCharacterTypes(); ++index) {
      for (size_t subindex = 0; subindex < configuration.GetCharacterConfiguration(index).Number();
           ++subindex) {
        const auto string_position = random_indices[random_indices_position];
        random_string[string_position] =
            generate_random_char(configuration.GetCharacterConfiguration(index).Type());
        ++random_indices_position;
      }
    }

    size_t remaining_password_lenght = configuration.StringLenght() - random_indices_position;

    for (size_t index = 0; index < remaining_password_lenght; ++index) {
      const auto random_select =
          generate_random_integer(0, configuration.NumberCharacterTypes() - 1);
      const auto string_position = random_indices[random_indices_position];
      random_string[string_position] =
          generate_random_char(configuration.GetCharacterConfiguration(random_select).Type());
      ++random_indices_position;
    }

    return random_string;
  }

  auto get_random_indices() { return random_indices; }

private:
  static size_t generate_random_integer(const size_t min, const size_t max)
  {
    std::random_device random_device;
    std::uniform_int_distribution<size_t> uniform_int(min, max);
    size_t random_number = uniform_int(random_device);
    return random_number;
  }

  [[nodiscard]] char generate_random_char(CharacterConfiguration::CharacterType type) const
  {
    char random_letter = 0;

    if (type == CharacterConfiguration::CharacterType::uppercase) {
      random_letter = static_cast<char>(generate_random_integer(65, 90));
    }

    if (type == CharacterConfiguration::CharacterType::lowercase) {
      random_letter = static_cast<char>(generate_random_integer(97, 122));
    }

    if (type == CharacterConfiguration::CharacterType::digit) {
      random_letter = static_cast<char>(generate_random_integer(48, 57));
    }

    if (type == CharacterConfiguration::CharacterType::special_character) {
      random_letter = static_cast<char>(
          special_characters[generate_random_integer(0, special_characters.size() - 1)]);
    }

    return random_letter;
  }

  void init_special_characters()
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
  std::vector<size_t> random_indices;
};

#endif // GENERATOR_H
