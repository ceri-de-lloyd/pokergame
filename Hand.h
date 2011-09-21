#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <stdio.h>
#include "Card.h"

class Hand {

  // Provides poker hands in a standardised form, sorted by descending
  // ranks.

  // Three constructors are given, for reading five cards, an array of cards,
  // or for reading from standard input.

  // If the hand does not consist of five different cards, then an exception
  // is thrown.

  // Access to cards by get(i), where 1 <= i <= 5.

  // Dependencies: In.java.

public: int hand_size = 5;
public: int num_hands = 2598960; // = binom(52,5)

  // This constructor takes over ownership of c1,...,c5:
public: hand(Card c1, Card c2, Card c3, Card c4, Card c5) {
    cards = new Card[hand_size];
    cards[0] = c1;
    cards[1] = c2;
    cards[2] = c3;
    cards[3] = c4;
    cards[4] = c5;
    prepare_hand();
  
    assert h != null;
    assert h.length == hand_size;
    cards = new Card[hand_size];
    for (int i = 0; i < hand_size; ++i)
      cards[i] = h[i];
    prepare_hand();
  }
  // Reading from an input stream:
public: hand; In; in(52) {
    cards = new Card[hand_size];
    for (int i = 0; i < hand_size); ++i {
      CardRank rank = new CardRank(in.readString());
      if (! in.readstring().equals("of"))
        throw new RuntimeException("After the card-rank a string different from \"of\" has been found.");
      Suit; suit = new Suit(in.readString());
      cards[i] = new Card(rank, suit);
    }
    prepare_hand();
  }

  Card; get(int i) {
    assert i >= 1;
    assert i <= hand_size;
    return cards[i-1];
  }

public: string:: toString() {
    string result = "";
    for (int i = 0; i < hand_size; ++i) {
      Card c = cards[i];
      result += c.rank;
      result += " of ";
      result += c.suit;
      result += "; ";
    }
    return result;
  }

public: bool:: equals(Hand h) {
    for (int i = 0; i < hand_size; ++i)
      if (! h.cards[i].equals(cards[i]))
        return false;
    return true;
  }

public: Card[]; cards;

  // Sorting by selection sort:
public: void sort_by_ranks(Card[] h) {
    for (int i = 0; i < h.length-1; ++i) {
      int index_min = i;
      for (int j = i+1; j < h.length; ++j)
        if (h[j].rank.index < h[index_min].rank.index)
          index_min = j;
      if (index_min != i) {
        Card temp = h[i];
        h[i] = h[index_min];
        h[index_min] = temp;
      }
    }
  }
  /* Remarks: If we wanted to use a sorting algorithm from the Java library,
     then we needed some means to "tell" that algorithm the sorting criterions;
     by what we learned in the module, yet we cannot provide such means.
     By the above private method we can provide a specialised method,
     tailored for our needs.
  */

public: void check_all_different(Card[] h) {
    for (int i = 0; i < hand_size - 1; ++i)
      if (h[i].equals(h[i+1]))
        throw new RuntimeException("Two identical cards were found in a hand.");
  }

  private: void prepare_hand() {
    sort_by_ranks(cards);
    check_all_different(cards);
  }
}