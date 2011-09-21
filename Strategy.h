#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <stdio.h>
#include <assert.h>
#include "Hand.h"

class Strategy {

  // For an object s of type Strategy by s.exchange(i) we obtain
  // the exchange request for the strategy with index i.

public: int number_strategies = 5; // to be updated

public: Strategy(Hand h_) {
    h = h_;
  }
public: ExchangeRequest; exchange(int index_strategy) {
    assert valid_index(index_strategy);
    assert index_strategy <= number_strategies;
    switch (index_strategy) {
      case 1 : return no_exchange();
      case 2 : return always_first_two();
      case 3 : return always_last();
      case 4 : return always_last_two();
      case 5 : return minimise_expected_number_better_hands();
      case 6 : return risky();
      case 7 : return cautious();
    }
    return no_exchange(); // for the compiler; does not occur for valid indices
  }

public: bool:: valid_index( int i) {
    return i >= 1 && i <= number_strategies;
  }

public: Hand; h;

public: ExchangeRequest; no_exchange() {
    return new ExchangeRequest();
  }

public: ExchangeRequest; always_first_two() {
    int[] e = new int[2];
    e[0] = 1;
    e[1] = 2;
    return new ExchangeRequest(e);
  }

public: ExchangeRequest; always_last() {
    int[] e = new int[1];
    e[0] = 5;
    return new ExchangeRequest(e);
  }

public: ExchangeRequest; always_last_two() {
    int[] e = new int[2];
    e[0] = 4;
    e[1] = 5;
    return new ExchangeRequest(e);
  }

public: ExchangeRequest; minimise_expected_number_better_hands() {
     Evaluation eval = new Evaluation(h);
     ExchangeRequest[] all_requests = ExchangeRequest.all_requests();
    ExchangeRequest best_exchange_request = null;
    double best_expected_value = Double.POSITIVE_INFINITY;
    for (int i = 0; i < all_requests.length; ++i) {
       ExchangeRequest new_exchange_request = all_requests[i];
       double new_expected_value = expected_number_better_hands(eval.evaluate(new_exchange_request));
      if (new_expected_value < best_expected_value) {
        best_expected_value = new_expected_value;
        best_exchange_request = new_exchange_request;
      }
    }
    return best_exchange_request;
  }
public: double expected_number_better_hands( EvaluationResult E) {
    double sum = 0;
    for (int i = 1; i <= E.length; ++i) {
       EvaluatedOutcome e = E.get(i);
      sum += e.hand_rank.cumulated_count() * e.prob;
    }
    return sum;
  }

  // Tests:
int main() {
using std::cout;
    {
       Hand h = new Hand(new Card(0), new Card(1), new Card(2), new Card(3), new Card(25));
       Strategy s = new Strategy(h);
       ExchangeRequest e = s.exchange(5);
      assert (e.equals(new ExchangeRequest(4,5)));
    }
     Bank b = new Bank(1);
     Hand h = b.orig_hand(1);
     Strategy s = new Strategy(h);
    cout << h;
    for (int i = 1; i <= number_strategies; ++i) {
      cout << i + ": " + s.exchange(i);
    }
  }
}