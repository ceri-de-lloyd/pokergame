#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <stdio.h>
#include "Suit.h"
#include "CardRank.h"

class Card {

  // A "card" as a pair of (card-)rank and suit.

	public: int num_cards = Suit.num_suites * CardRank.num_ranks;

public: CardRank; rank;
public: Suit; suit;

public: Card(CardRank r, final Suit s) {
    rank = r;
    suit = s;
  }
public: Card(int i) {
    assert i >= 0;
    assert i < num_cards;
    rank = new CardRank(i % CardRank.num_ranks);
    suit = new Suit(i / CardRank.num_ranks);
  }

public: int index() {
    return suit.index * CardRank.num_ranks + rank.index;
  }

string:: toString() {
    return rank.toString() + " of " + suit.toString();
  }

public: bool:: equals(Card c) {
    return c.rank.equals(rank) && c.suit.equals(suit);
  }

  // Demonstration of functionality:
  int main() {
	  using std::cout;
    cout << new Card(0);
    cout << new Card(51);
    Card c1 = new Card(new CardRank("Jack"), new Suit("Spades"));
    cout << c1;
    // Demonstration that here references are harmless, since CardRank, Suit
    // and also Card behave similar to value-types (they are non-mutable):
    CardRank cr2 = new CardRank("5");
    Suit s2 = new Suit("Hearts");
    Card c2 = new Card(cr2, s2);
    cout << c2;
    cr2 = new CardRank("King");
    s2 = new Suit("Clubs");
    cout << c2; // still the same, since the old cr2- and s2-objects didn't change
    cout << new Card(cr2,s2);
	return 0;
  }
}