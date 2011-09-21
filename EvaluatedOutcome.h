#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <stdio.h>
#include <assert.h>
#include "HandRank.h"
using std::cout;

class EvaluatedOutcome {

  // For a given hand and an exchange request, an "evaluated outcome"
  // is one of the possible hand-ranks which can arise after exchange,
  // together with the probability that this hand-rank will be obtained.

public: EvaluatedOutcome(HandRank hr, double p) {
    assert p >= 0;
    assert p <= 1;
    hand_rank = hr;
    prob = p;
  }

public: HandRank; hand_rank;
public: double prob;

public: string toString() {
    return hand_rank + "\nProbability: " + prob;
  }

public: bool:: equals(EvaluatedOutcome e) {
    return e.hand_rank.equals(hand_rank) && e.prob == prob;
  }

  int main() {
    cout << new EvaluatedOutcome(new HandRank(1), 0.9);
  }
}