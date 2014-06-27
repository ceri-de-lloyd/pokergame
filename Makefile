# Oliver Kullmann, 23.9.2011 (Swansea)

SHELL = /bin/bash
.SUFFIXES :

CXX = g++

header_file = Card.h EvaluatedOutcome.h EvaluationResult.h Hand.h Storage.h Suit.h TwoPlayers.h CardRank.h Evaluation.h ExchangeRequest.h HandRank.h Strategy.h Tournament.h

.PHONY : all cleanall

all : Poker

Poker : Poker.cpp $(header_files)
	$(CXX) -o Poker $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) Poker.cpp

cleanall :
	- rm Poker
