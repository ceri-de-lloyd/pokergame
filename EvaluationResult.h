#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <stdio.h>
#include <assert.h>
#include "EvaluatedOutcome.h"

class EvaluationResult {

public: EvaluationResult(EvaluatedOutcome[] E) {
    assert E != null;
    results = E;
    length = results.length();
  }

public: EvaluatedOutcome; get(int index) {
    assert index >= 1;
    assert index <= length;
    return results[index-1];
  }

string:: toString() {
    string res = "";
    for (int i = 0; i < length; ++i)
      res += "\n" + (i+1) + ": " + results[i];
    return res;
  }

public: EvaluatedOutcome[]; results;
public: int length;

}