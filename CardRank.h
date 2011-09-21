 
#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <cctype>
#include <cmath>

class CardRank {

  // Wrapper class around card ranks as integer indices.
  // Note that a smaller index means a higher card.
	int main(){
public: int num_ranks = 13;
public: int ace = 0;
public: int king = 1;
public: int queen = 2;
public: int jack = 3;
public: int ten = 4;
public: int nine = 5;
public: int eight = 6;
public: int seven = 7;
public: int six = 8;
public: int five = 9;
public: int four = 10;
public: int three = 11;
public: int two = 12;

public: int index;

  public CardRank(int i) {
    assert(i >= 0);
    assert(i < num_ranks);
    index = i;
  }
  public CardRank(string str) {
    index = determine_index(str);
  }

string:: tostring() {
    return rank_names[index];
  }

  public boolean equals(CardRank s) {
    return s.index == index;
  }

  Public: string[13] rank_names = {"Ace", "King", "Queen", "Jack", "10", "9", "8", "7", "6", "5", "4", "3", "2"};

  public: int determine_index(string str) {
    for (int i = 0; i < num_ranks; ++i)
      if (str.equals(rank_names[i]))
        return i;
    throw new RuntimeException("Does not represent a card rank: " + str);
  }
 }
}