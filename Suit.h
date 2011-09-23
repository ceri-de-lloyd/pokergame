#ifndef SUIT_Kneo
#define SUIT_Kneo

#include <cassert>
#include <string>
#include <stdexcept>

class Suit {
  // Wrapper class around suites as integer indices.
 public :
  typedef int index_type;

 private :
  static const index_type num_suites = 4;
  static const index_type clubs = 0;
  static const index_type spades = 1;
  static const index_type hearts = 2;
  static const index_type diamonds = 3;

  static std::string suit_names(const index_type i) {
    assert(i >= 0);
    assert(i < num_suites);
    switch (i) {
    case clubs : return "clubs";
    case spades : return "spades";
    case hearts : return "hearts";
    case diamonds : return "diamonds";
    }
  }

 public :

  const index_type index;

  Suit(const index_type i) : index(i) {
    assert(i >= 0);
    assert(i < num_suites);
  }
  Suit(const std::string& str) : index(determine_index(str)) {}

  bool equals(const Suit s) const { return s.index == index; }
  std::string toString() const { return suit_names(index); }

  index_type determine_index(const std::string& str) const {
    for (index_type i = 0; i < num_suites; ++i)
      if (str == suit_names(i)) return i;
    throw std::domain_error("Does not represent a suit: " + str);
  }
};

#endif
