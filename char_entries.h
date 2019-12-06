#pragma once

#include <wchar.h>

typedef struct {
  wint_t origin;
  char* target;
} CharEntry;

/**
 * Defines conversion table, 33 uppercase and same number of lowercase letters.
 * See also http://translit.cc/
 */
static CharEntry ENTRIES[] = {
  {L'А', "A"}, {L'Б', "B"}, {L'В', "V"}, {L'Г', "G"}, {L'Д', "D"}, {L'Е', "E"}, {L'Ё', "Jo"}, {L'Ж', "Zh"},
  {L'З', "Z"}, {L'И', "I"}, {L'Й', "J"}, {L'К', "K"}, {L'Л', "L"}, {L'М', "M"}, {L'Н', "N"}, {L'О', "O"},
  {L'П', "P"}, {L'Р', "R"}, {L'С', "S"}, {L'Т', "T"}, {L'У', "U"}, {L'Ф', "F"}, {L'Х', "H"}, {L'Ц', "C"},
  {L'Ч', "Ch"}, {L'Ш', "Sh"}, {L'Щ', "Shh"}, {L'Ъ', "''"}, {L'Ы', "Y"}, {L'Ь', "'"}, {L'Э', "Je"}, {L'Ю', "Yu"},
  {L'Я', "Ya"},
  {L'а', "a"}, {L'б', "b"}, {L'в', "v"}, {L'г', "g"}, {L'д', "d"}, {L'е', "e"}, {L'ё', "jo"}, {L'ж', "zh"},
  {L'з', "z"}, {L'и', "i"}, {L'й', "j"}, {L'к', "k"}, {L'л', "l"}, {L'м', "m"}, {L'н', "n"}, {L'о', "o"},
  {L'п', "p"}, {L'р', "r"}, {L'с', "s"}, {L'т', "t"}, {L'у', "u"}, {L'ф', "f"}, {L'х', "h"}, {L'ц', "c"},
  {L'ч', "ch"}, {L'ш', "sh"}, {L'щ', "shh"}, {L'ъ', "''"}, {L'ы', "y"}, {L'ь', "'"}, {L'э', "je"}, {L'ю', "yu"},
  {L'я', "ya"},

  // unicode characters from the other locales
  // ... {L'?', "?"}, 
};

const size_t ENTRIES_SIZE = sizeof(ENTRIES)/sizeof(ENTRIES[0]);
