#ifndef RANDOM_STRING_CONFIGURATION_H
#define RANDOM_STRING_CONFIGURATION_H

#include <cstdint>
#include <vector>

class CharacterConfiguration {
public:
  enum CharacterType : std::uint8_t { uppercase, lowercase, digit, special_character };

  CharacterConfiguration(CharacterType type, int number) : type(type), number(number) {}

  [[nodiscard]] CharacterType Type() const { return type; }

  [[nodiscard]] int Number() const { return number; }

private:
  CharacterType type;
  int number;
};

class RandomStringConfiguration {
public:
  RandomStringConfiguration(int string_lenght,
                            const std::vector<CharacterConfiguration> &character_configurations)
      : string_lenght(string_lenght), character_configurations(character_configurations)
  {
  }

  [[nodiscard]] int StringLenght() const { return string_lenght; }

  [[nodiscard]] size_t NumberCharacterTypes() const { return character_configurations.size(); }

  [[nodiscard]] CharacterConfiguration GetCharacterConfiguration(size_t index) const
  {
    return character_configurations[index];
  }

private:
  int string_lenght;
  std::vector<CharacterConfiguration> character_configurations;
};

#endif // RANDOM_STRING_CONFIGURATION_H
