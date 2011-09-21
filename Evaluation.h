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
#include "EvaluationResult.h"
#include "Card.h"
#include "EvaluatedOutcome.h"
#include "ExchangeRequest.h"
#include "HandRank.h"

class Evaluation {

public: Evaluation(Hand h) {
    assert h != null;
    hand = h;
    other_cards = new Card[num_other_cards];
    int[] deck = new int[Card.num_cards];
    for (int i = 0; i < Card.num_cards; ++i)
      deck[i] = i;
    for (int i = 1; i <= Hand.hand_size; ++i)
      deck[h.get(i).index()] = -1;
    int next_index = 0;
    for (int i = 0; i < Card.num_cards; ++i)
      if (deck[i] != -1)
        other_cards[next_index++] = new Card(deck[i]);
  }

  // For an exchange-request e, compute the array of possible outcomes
  // as hand-ranks, together with their probabilities, sorted by
  // descending hand-ranks:
public: EvaluationResult; evaluate(ExchangeRequest e) {
    if (e.number_cards == 0) {
      EvaluatedOutcome eo = new EvaluatedOutcome(new HandRank(hand), 1.0);
      EvaluatedOutcome[] result = new EvaluatedOutcome[1];
      result[0] = eo;
      return new EvaluationResult(result);
    }
    int[] count_outcomes = new int[HandRank.num_hand_ranks+1];
    int num_possibilities;
    // run through all possibilities, and enter the result into count_outcomes:
    Card[] new_hand = new Card[5];
    for (int i = 0; i < Hand.hand_size; ++i)
      new_hand[i] = hand.get(i+1);
    if (e.number_cards == 1) {
      num_possibilities = num_other_cards;
      final int exchange_index = e.get_index(1)-1;
      for (int i = 0; i < num_other_cards; ++i) {
        new_hand[exchange_index] = other_cards[i];
        ++count_outcomes[new HandRank((new Hand(new_hand))).rank];
      }
    }
    else {
      num_possibilities = num_other_cards * (num_other_cards-1);
      int exchange_index_1 = e.get_index(1)-1;
      int exchange_index_2 = e.get_index(2)-1;
      for (int i = 0; i < num_other_cards; ++i) {
        new_hand[exchange_index_1] = other_cards[i];
        for (int j = i+1; j < num_other_cards; ++j) {
          new_hand[exchange_index_2] = other_cards[j];
          ++count_outcomes[new HandRank((new Hand(new_hand))).rank];
        }
      }
    }
    int count_different_ranks = 0;
    // determine the number of different ranks entered into count_outcomes:
    for (int i = 1; i <= HandRank.num_hand_ranks; ++i)
      if (count_outcomes[i] != 0) ++count_different_ranks;
    // transfer the results into an array of evaluated outcomes:
    EvaluatedOutcome[] result = new EvaluatedOutcome[count_different_ranks];
    int next_index = 0;
    for (int i = 1; i <= HandRank.num_hand_ranks; ++i)
      if (count_outcomes[i] != 0)
        result[next_index++] = new EvaluatedOutcome(new HandRank(i), (double) count_outcomes[i] / num_possibilities);
    return new EvaluationResult(result);//removing the brackets and/or new EvaluationResult doesn't help.
  }

public :Hand; hand;
public :Card[]; other_cards;

  int main() {
	using std::cout;

	public: int num_other_cards = Card.num_cards - Hand.hand_size;

    Bank b = new Bank(1);
    Hand h = b.orig_hand(1);
    Cout << h;
    Evaluation E = new Evaluation(h);
    {
      cout << "\nNo exchange:";
      ExchangeRequest e = new ExchangeRequest();
      EvaluationResult R = E.evaluate(e);
      assert R.length == 1;
      cout << R;
     }
    {
      cout << "\nExchange last card:";
      int[] ea = new int[1];
      ea[0] = 5;
      ExchangeRequest e = new ExchangeRequest(ea);
      EvaluationResult R = E.evaluate(e);
      cout << R;
	  return 0;
    }
  }
}