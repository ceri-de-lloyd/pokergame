#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <stdio.h>

class Tournament {

  // Read the number N of rounds from the command-line, and for each
  // pair 1 <= i < j <= Strategy.number_strategies of strategies from Strategy,
  // play N rounds, showing the difference of the number of games won by
  // strategy i minus the number of games won by strategy j.
  int main() {
	  using std::cout;
    if (args.length == 0) {
      cout << "ERROR[Tournament]: One parameter is needed, the number N of games.";
      return;
    }
     long N = Long.parseLong(args[0]);
     Storage S = new Storage(Strategy.number_strategies);
    for (long t = 1; t <= N; ++t) {
       Storage R = TwoPlayers.play();
      for (int i = 1; i < Strategy.number_strategies; ++i)
        for (int j = i+1; j <= Strategy.number_strategies; ++j)
          S.set(i,j, S.get(i,j)+ R.get(i,j));
    }
    cout << S;
  }
}