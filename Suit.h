#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <stdio.h>


class Suit {

  // Wrapper class around suites as integer indices.

static const int num_suites = 4;
static const int clubs = 0;
static const int spades = 1;
static const int hearts = 2;
static const int diamonds = 3;
static const char suit_names[] = {"clubs", "spades", "hearts", "diamonds" };

public: int index;

public: Suit( int i) {
    assert(i >= 0);
    assert(i < num_suites);
    index = i;
  }
public: Suit(std::string str) {
    index = determine_index(str);
  }

public: bool:: equals(Suit s) {
    return s.index == index;
  }

char:: toString() {
	char result = "";
    for (int i = 1; i < suit_names; ++i) {
      for (int j = i+1; j <= suit_names; ++j)
        result += get(i,j) + " ";
      result += "\n";
    }
    //return result;
    return (suit_names[index]);
}

public: int determine_index(char str) {
    for (int i = 0; i < num_suites; ++i)
      if (str.equals(suit_names[i]))
        return i;
    throw new RuntimeException("Does not represent a suit: " + str);
  }
}