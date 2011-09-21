#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <stdio.h>
#include "ExchangeRequest.h"
#include "HandRank.h"
#include "Strategy.h"
#include "Storage.h"

class TwoPlayers {

  // Plays a single game between two players, using all available strategies
  // from the Strategy class, and returns an object of type Storage with
  // entries from {-1,0,+1}, where an entry -1 means player 2 wins, +1 means
  // player 1 wins, and 0 means draw:
public: int Storage; play() {
     Storage R = new Storage(Strategy.number_strategies);
     Bank b = new Bank(2);
     ExchangeRequest[] ep1 = new ExchangeRequest[Strategy.number_strategies-1];
    {
       Strategy p1 = new Strategy(b.orig_hand(1));
      for (int s1 = 1; s1 < Strategy.number_strategies; ++s1)
        ep1[s1-1] = p1.exchange(s1);
    }
     ExchangeRequest[] ep2 = new ExchangeRequest[Strategy.number_strategies-1];
    {
       Strategy p2 = new Strategy(b.orig_hand(2));      
      for (int s2 = 2; s2 <= Strategy.number_strategies; ++s2)
        ep2[s2-2] = p2.exchange(s2);
    }
     ExchangeRequest[] E = new ExchangeRequest[2];
    for (int s1 = 1; s1 < Strategy.number_strategies; ++s1)
      for (int s2 = s1+1; s2 <= Strategy.number_strategies; ++s2) {
        E[0] = ep1[s1-1];
        E[1] = ep2[s2-2];
        b.perform_exchanges(E);
         HandRank hr1 = new HandRank(b.new_hand(1));
         HandRank hr2 = new HandRank(b.new_hand(2));
        if (hr1.rank < hr2.rank)
          R.set(s1,s2,+1);
        else if (hr2.rank < hr1.rank)
          R.set(s1,s2,-1);
        else
          R.set(s1,s2,0);
      }
    return R;
  }

int main() {
	using std::cout;
     Storage S = TwoPlayers.play();
    cout << S;
  }
}