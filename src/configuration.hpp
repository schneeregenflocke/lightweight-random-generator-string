#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <cstddef>
#include <cstdint>
#include <vector>

class CharacterConfiguration {
public:
  enum CharacterType : std::uint8_t { uppercase, lowercase, digit, special_character };

  CharacterConfiguration(CharacterType type, size_t number) : type(type), number(number) {}

  [[nodiscard]] CharacterType Type() const { return type; }

  [[nodiscard]] size_t Number() const { return number; }

private:
  CharacterType type;
  size_t number;
};

class StringConfiguration {
public:
  StringConfiguration(size_t string_lenght,
                      const std::vector<CharacterConfiguration> &character_configurations)
      : string_lenght(string_lenght), character_configurations(character_configurations)
  {
  }

  [[nodiscard]] size_t StringLenght() const { return string_lenght; }

  [[nodiscard]] size_t NumberCharacterTypes() const { return character_configurations.size(); }

  [[nodiscard]] CharacterConfiguration GetCharacterConfiguration(size_t index) const
  {
    return character_configurations[index];
  }

private:
  size_t string_lenght;
  std::vector<CharacterConfiguration> character_configurations;
};

#endif // CONFIGURATION_H
