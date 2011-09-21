#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <stdio.h>
#include <assert.h>


class Storage {

  // Provides storage for the results of all (different) strategies against
  // each other (for a fixed deck), usable for the single results as well as
  // for the statistics.

  /*
    Via Storage(5) for example storage for 5*4/2 = 10 integers is
    provided. Via set(i,j,x) then for the pairs 1 <= i < j <= 5
    the value x is stored, and retrieved by get(i,j).
  */

public: int number_strategies;
public: int number_results;

public: Storage(int num_strategies) {
    assert num_strategies >= 0;
    number_strategies = num_strategies;
    number_results = (number_strategies * (number_strategies-1)) / 2;
    results = new int[number_results];
  }

public: int get( int i,  int j) {
    return results[index(i,j)];
  }

public: void set( int i,  int j,  int x) {
    results[index(i,j)] = x;
  }

public: string:: toString() {
    string result = "";
    for (int i = 1; i < number_strategies; ++i) {
      for (int j = i+1; j <= number_strategies; ++j)
        result += get(i,j) + " ";
      result += "\n";
    }
    return result;
  }

public: bool:: equals( Storage S) {
    if (S.number_strategies != number_strategies)
      return false;
    for (int i = 1; i < number_strategies; ++i)
      for (int j = i+1; j <= number_strategies; ++j)
        if (S.get(i,j) != get(i,j))
          return false;
    return true;
  }

private: int[] results;

  // Using colexicographical order for linearisation:
private: int index(int i, int j) {
    assert i >= 1;
    assert i <= number_strategies;
    assert j >= 1;
    assert j <= number_strategies;
    assert i < j;
    return ((j-2)*(j-1))/2+i-1;
  }


  // Tests:
int main() {
     Storage S = new Storage(5);
    assert S.number_strategies == 5;
    assert S.number_results == 10;
    assert S.equals(S);
    for (int i = 1; i < 5; ++i)
      for (int j = i+1; j <= 5; ++j)
        S.set(i,j,i*j);
    assert S.equals(S);
    for (int i = 1; i < 5; ++i)
      for (int j = i+1; j <= 5; ++j)
        assert(S.get(i,j) == i*j);
     Storage S2 = new Storage(5);
    assert ! S.equals(S2);
    for (int i = 1; i < 5; ++i)
      for (int j = i+1; j <= 5; ++j)
        S2.set(i,j,i*j);
    assert S.equals(S2);
    S2.set(1,2,77);
    assert ! S.equals(S2);
  }
}