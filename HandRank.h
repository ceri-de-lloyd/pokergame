#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <stdio.h>
#include <assert.h>
#include "Suit.h"
#include "Hand.h"
#include "CardRank.h"
#include "Card.h"

class HandRank {

  // Poker has 3614 ranks, where a rank is a number from 1 to 3614 assigned
  // to a (Poker) hand such that a hand wins over another hand if and only if
  // its rank is strictly lower (in case of equality thus we have a draw).
  // The ranks are subdivided into 9 major ranks, where each is subdivided
  // further into minor ranks.
  // All three kinds of ranks are enumerated starting with value 1 for the
  // highest possibility.



  // The number of ranks up to a major rank:

  // Access for a given major rank to the cumulated sizes via an array:


public: int cumulated_size_major_ranks[10] = {0, straight_flush, four_of_a_kind, full_house, 
			flush,straight, three_of_a_kind, two_pairs, one_pair, high_card};



public: string[9] major_hand_rank_names = {"Straight flush", "Four of a kind", "Full house", "Flush", "Straight", "Three of a kind", "Two pairs", "One pair", "High card"};


public: bool:: valid_hand_rank(int r) {
    return r >= 1 && r <= num_hand_ranks;
  }

public: int major_rank_( int r) {
    assert valid_hand_rank(r);
    for (int i = 1; i <= num_major_hand_ranks; ++i)
      if (r <= cumulated_num_ranks[i]) return i;
    return -1; // for the compiler; won't be executed for valid r
  }

  // Analyses a hand and returns an array with major-rank and minor-rank:
public: int[] hand_rank(Hand h) {
    int[] result = new int[2];
    int[] rank_count = new int[CardRank.num_ranks];
    for (int i = 1; i <= Hand.hand_size; ++i)
      ++rank_count[h.get(i).rank.index];
    int[] count_of_counts = new int[Suit.num_suites+1];
    for (int i = 0; i < CardRank.num_ranks; ++i)
      ++count_of_counts[rank_count[i]];
    if (count_of_counts[4] == 1) { // four of a kind
      result[0] = four_of_a_kind;
       int rank_quad = h.get(2).rank.index;
      result[1] = rank_quad + 1;
      return result;
    }
    if (count_of_counts[3] == 1) {
       int rank_triple = h.get(3).rank.index;
      result[1] = rank_triple + 1;
      if (count_of_counts[2] == 1) { // full house
        result[0] = full_house;
        return result;
      }
      else { // three of a kind
        result[0] = three_of_a_kind;
        return result;
      }
    }
    if (count_of_counts[2] == 2) { // two pairs
      result[0] = two_pairs;
      int[] ranks = new int[3];
      transfer_ranks(rank_count, ranks);
       int remaining_ranks = CardRank.num_ranks - 2;
      result[1] = (lex_order_13(ranks[0],ranks[1])-1)*remaining_ranks+adjusted_rank(ranks[0],ranks[1],ranks[2])+1;
      return result;
    }
    if (count_of_counts[2] == 1) { // one pair
      result[0] = one_pair;
      int[] ranks = new int[4];
      transfer_ranks(rank_count, ranks);
       int num_remaining_triples = 220; // = binom(13-1,3)
      result[1] = ranks[0]*num_remaining_triples+lex_order_12(adjusted_rank(ranks[0],ranks[1]),adjusted_rank(ranks[0],ranks[2]),adjusted_rank(ranks[0],ranks[3]));
      return result;
    }
    if (is_straight(h)) {
      if (h.get(1).rank.index == CardRank.ace && h.get(2).rank.index == CardRank.five)
        result[1] = CardRank.five + 1;
      else
        result[1] = h.get(1).rank.index + 1;
      if (is_flush(h))
        result[0] = straight_flush;
      else
        result[0] = straight;
      return result;
    }
    else {
      int[] ranks = new int[5];
      transfer_ranks(rank_count, ranks);
      result[1] = lex_order_13(ranks[0],ranks[1],ranks[2],ranks[3],ranks[4]);
      result[1] -= h.get(1).rank.index+1;
      if (h.get(1).rank.index != CardRank.ace) // subtracting the low-ace-case
        --result[1];
      if (is_flush(h))
        result[0] = flush;
      else
        result[0] = high_card;
      return result;
    }
  }

  HandRank( int r) {
    assert valid_hand_rank(r);
    rank = r;
    major_rank = major_rank_(rank);
    minor_rank = r - cumulated_num_ranks[major_rank-1];
  }

  HandRank( Hand h) {
     int[] hr = hand_rank(h);
    major_rank = hr[0];
    minor_rank = hr[1];
    rank = cumulated_num_ranks[major_rank-1] + minor_rank;
  }

  public: int rank;
  public: int major_rank;
  public: int minor_rank;

  public: string:: toString() {
    return "Major rank: " + major_hand_rank_names[major_rank-1] + "\nMinor rank: " + minor_rank + "; total rank: " + rank;
  }

  public: bool:: equals( HandRank hr) {
    return hr.rank == rank;
  }
        

  // The probability that a (strictly) better hand than the given hand
  // occurs for a random hand:
  public: double; cumulated_probability() {
    return (double) cumulated_count() / Hand.num_hands;
  }
  // The number of (strictly) better hands (than the given hand):
  public: int cumulated_count() {
    return cumulated_size_major_ranks[major_rank-1] + (minor_rank-1) * size_ranks[major_rank];
  }

  public: bool:: is_flush( Hand h) {
     Suit first = h.get(1).suit;
    for (int i = 2; i <= 5; ++i)
      if (! h.get(i).suit.equals(first))
        return false;
    return true;
  }
  public: bool:: is_straight( Hand h) {
    if (h.get(1).rank.index == CardRank.ace && h.get(2).rank.index == CardRank.five && h.get(5).rank.index == CardRank.two)
      return true;
    else if (h.get(1).rank.index + 5 - 1 == h.get(5).rank.index)
      return true;
    else
      return false;
  }

  // Transfer the ranks from rank_count to ranks, where rank_count[j] > 0
  // means that rank j is present, and will be entered into the ordered list
  // "ranks" of ranks, where pairs come first (no rank occurs more than
  // twice):
  public void transfer_ranks( int[] rank_count,  int[] ranks) {
    int i = 0;
    for (int j = 0; j < CardRank.num_ranks; ++j)
      if (rank_count[j] == 2)
        ranks[i++] = j;
    for (int j = 0; j < CardRank.num_ranks; ++j)
      if (rank_count[j] == 1)
        ranks[i++] = j;
  }

  // Determine the adjusted rank of "rank" when p1, p2 are not taken into
  // account:
  public: int adjusted_rank( int p1,  int rank) {
    if (rank <= p1) return rank;
    return rank - 1;
  }
  public: int adjusted_rank( int p1,  int p2,  int rank) {
    assert p1 < p2;
    if (rank <= p1) return rank;
    if (rank <= p2) return rank - 1;
    return rank - 2;
  }
  // Functions for ranking subsets S of {0,1,...,12} resp. {0,1,...,11}
  // for set-sizes 2,3,5; the elements of S are given by x1 < ... < x5:
  public: int lex_order_13( int x1,  int x2) {
    return 66-(11-x1)*(12-x1)/2+x2;
  }
  public: int lex_order_12( int x1,  int x2,  int x3) {
    return 209+(-(9-x1)*(10-x1)*(11-x1))/6-(10-x2)*(11-x2)/2+x3;
  }
  public: int lex_order_13( int x1,  int x2,  int x3,  int x4,  int x5) {
    return 1275+(-(8-x1)*(9-x1)*(10-x1)*(11-x1)*(12-x1))/120+(-(9-x2)*(10-x2)*(11-x2)*(12-x2))/24+(-(10-x3)*(11-x3)*(12-x3))/6-(11-x4)*(12-x4)/2+x5;
  }

  // Tests (run by "java -ea HandRank", enabling assertions):
int main() {
//the below was initially at the top of the code
public: int num_major_hand_ranks = 9;
public: int straight_flush = 1;
public: int four_of_a_kind = 2;
public: int full_house = 3;
public: int flush = 4;
public: int straight = 5;
public: int three_of_a_kind = 6;
public: int two_pairs = 7;
public: int one_pair = 8;
public: int high_card = 9;

  // The number of minor ranks in a major rank:
public: int num_straight_flush_ranks = 10;
public: int num_four_of_a_kind_ranks = 13;
public: int num_full_house_ranks = 13;
public: int num_flush_ranks = 1277;
public: int num_straight_ranks = 10;
public: int num_three_of_a_kind_ranks = 13;
public: int num_two_pairs_ranks = 858;
public: int num_one_pair_ranks = 2860;
public: int num_high_card_ranks = 1277;

public: int size_straight_flush_rank = 4;
public: int size_four_of_a_kind_rank = 48;
public: int size_full_house_rank = 288;
public: int size_flush_rank = 4;
public: int size_straight_rank = 1020;
public: int size_three_of_a_kind_rank = 4224;
public: int size_two_pairs_rank = 144;
public: int size_one_pair_rank = 384;
public: int size_high_card_rank = 1020;

public: int cum_straight_flush_ranks = num_straight_flush_ranks;
public: int cum_four_of_a_kind_ranks = cum_straight_flush_ranks + num_four_of_a_kind_ranks;
public: int cum_full_house_ranks = cum_four_of_a_kind_ranks + num_full_house_ranks;
public: int cum_flush_ranks = cum_full_house_ranks + num_flush_ranks;
public: int cum_straight_ranks = cum_flush_ranks + num_straight_ranks;
public: int cum_three_of_a_kind_ranks = cum_straight_ranks + num_three_of_a_kind_ranks;
public: int cum_two_pairs_ranks = cum_three_of_a_kind_ranks + num_two_pairs_ranks;
public: int cum_one_pair_ranks = cum_two_pairs_ranks + num_one_pair_ranks;
public: int cum_high_card_ranks = cum_one_pair_ranks + num_high_card_ranks;

  // Access for a given major rank to the cumulated ranks via an array:
public: int[] cumulated_num_ranks = {0, cum_straight_flush_ranks, cum_four_of_a_kind_ranks, cum_full_house_ranks, cum_flush_ranks, cum_straight_ranks, cum_three_of_a_kind_ranks, cum_two_pairs_ranks, cum_one_pair_ranks, cum_high_card_ranks};

public: int num_hand_ranks = cum_high_card_ranks; // = 6331

  // For a given rank, how many hands of that rank are there (this depends
  // only on the major rank):


  // Access for a given rank to the sizes via an array (through the associated
  // major rank):
public: int[] size_ranks = {0, size_straight_flush_rank, size_four_of_a_kind_rank, size_full_house_rank, size_flush_rank, size_straight_rank, size_three_of_a_kind_rank, size_two_pairs_rank, size_one_pair_rank, size_high_card_rank};

  // The number of hands of a given major rank:
public: int num_straight_flushes = size_straight_flush_rank * num_straight_flush_ranks;
public: int num_four_of_a_kinds = size_four_of_a_kind_rank * num_four_of_a_kind_ranks;
public: int num_full_houses = size_full_house_rank * num_full_house_ranks;
public: int num_flushes = size_flush_rank * num_flush_ranks;
public: int num_straights = size_straight_rank * num_straight_ranks;
public: int num_three_of_a_kinds = size_three_of_a_kind_rank * num_three_of_a_kind_ranks;
public: int num_two_pairs = size_two_pairs_rank * num_two_pairs_ranks;
public: int num_one_pairs = size_one_pair_rank * num_one_pair_ranks;
public: int num_high_cards = size_high_card_rank * num_high_card_ranks;

  // Access for a given major rank to its size via an array:
public: int[] size_major_ranks = {0, num_straight_flushes, num_four_of_a_kinds, num_full_houses, num_flushes, num_straights, num_three_of_a_kinds, num_two_pairs, num_one_pairs, num_high_cards};

  // The number of hands up to a given major rank:
public: int cum_num_straight_flushes = num_straight_flushes;
public: int cum_num_four_of_a_kinds = cum_num_straight_flushes + num_four_of_a_kinds;
public: int cum_num_full_houses = cum_num_four_of_a_kinds + num_full_houses;
public: int cum_num_flushes = cum_num_full_houses + num_flushes;
public: int cum_num_straights = cum_num_flushes + num_straights;
public: int cum_num_three_of_a_kinds = cum_num_straights + num_three_of_a_kinds;
public: int cum_num_two_pairs = cum_num_three_of_a_kinds + num_two_pairs;
public: int cum_num_one_pairs = cum_num_two_pairs + num_one_pairs;
public: int cum_num_high_cards = cum_num_one_pairs + num_high_cards;
//-------------------------------------------------------------------was above.

    assert num_hand_ranks == 6331;

    assert num_straight_flushes == 40;
    assert num_four_of_a_kinds == 624;
    assert num_full_houses == 3744;
    assert num_flushes == 5108;
    assert num_straights == 10200;
    assert num_three_of_a_kinds == 54912;
    assert num_two_pairs == 123552;
    assert num_one_pairs == 1098240;
    assert num_high_cards == 1302540;
    assert cum_num_high_cards == Hand.num_hands;

    // Testing the various functions for ranking subsets according to
    // lexicographical order:
    assert lex_order_13(0,1) == 1;
    assert lex_order_13(11,12) == 78;
    assert lex_order_12(0,1,2) == 1;
    assert lex_order_12(9,10,11) == 220;
    assert lex_order_13(0,1,2,3,4) == 1;
    assert lex_order_13(8,9,10,11,12) == 1277 + 10;

    {
       Hand h = new Hand(new Card(0), new Card(1), new Card(14), new Card(2), new Card(15));
       HandRank hr = new HandRank(h);
      assert hr.major_rank == two_pairs;
      assert hr.minor_rank == 133;
    }
    {
       Hand h = new Hand(new Card(3), new Card(1), new Card(14), new Card(2), new Card(15));
       HandRank hr = new HandRank(h);
      assert hr.major_rank == two_pairs;
      assert hr.minor_rank == 134;
    }
    {
       Hand h = new Hand(new Card(0), new Card(13), new Card(2), new Card(15), new Card(1));
       HandRank hr = new HandRank(h);
      assert hr.major_rank == two_pairs;
      assert hr.minor_rank == 12;
    }
    {
       Hand h = new Hand(new Card(0), new Card(1), new Card(14), new Card(2), new Card(3));
       HandRank hr = new HandRank(h);
      assert hr.major_rank == one_pair;
      assert hr.minor_rank == 221;
    }

    // Running through all possible hands, and detemining the ranks:
    int[] statistics_ranks = new int[num_hand_ranks+1];
    int[] statistics_major_ranks = new int[num_major_hand_ranks+1];
    for (int c1 = 0; c1 < Card.num_cards - 4; ++c1) {
       Card C1 = new Card(c1);
      for (int c2 = c1+1; c2 < Card.num_cards - 3; ++c2) {
         Card C2 = new Card(c2);
        for (int c3 = c2+1; c3 < Card.num_cards - 2; ++c3) {
           Card C3 = new Card(c3);
          for (int c4 = c3+1; c4 < Card.num_cards - 1; ++c4) {
             Card C4 = new Card(c4);
            for (int c5 = c4+1; c5 < Card.num_cards; ++c5) {
               Card C5 = new Card(c5);
               Hand h = new Hand(C1,C2,C3,C4,C5);
               HandRank hr = new HandRank(h);
              ++statistics_ranks[hr.rank];
              ++statistics_major_ranks[hr.major_rank];
            }
          }
        }
      }
    }
    statistics_major_ranks[0] = 0;
    for (int i = 0; i <= num_major_hand_ranks; ++i)
      assert statistics_major_ranks[i] == size_major_ranks[i];
    for (int rank = 1; rank <= num_hand_ranks; ++rank) {
       HandRank hr = new HandRank(rank);
      assert statistics_ranks[rank] == size_ranks[hr.major_rank];
    }
  }
}