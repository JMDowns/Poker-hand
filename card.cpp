#include <fstream>
#include <iostream>
#include <string>

enum Value { two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace };
enum Suit { club, diamond, heart, spade };

struct Card {
  Value v;
  Suit s;
  std::string value;
  std::string suit;
};

std::ostream& operator << (std::ostream& out, const Card& c)
{
  return(out << c.v << " " << c.s << std::endl);
}

Card stoC (std::string cardStr) {
  Value v;
  Suit s;
  std::string value;
  std::string suit;
  if (cardStr.length() == 3) {
    if (cardStr[0] == '1' && cardStr[1] == '0') {
      v = ten;
      value = "ten";
    }
    else
      exit(-1);
  }
  if (cardStr[0] == '2')
    {
      v = two;
      value = "two";
    }
  else if (cardStr[0] == '3')
    {
    v = three;
    value = "three";
    }
  else if (cardStr[0] == '4')
    {
    v = four;
    value = "four";
    }
  else if (cardStr[0] == '5')
    {
    v = five;
    value = "five";
    }
  else if (cardStr[0] == '6')
    {
    v = six;
    value = "six";
    }
  else if (cardStr[0] == '7')
    {
    v = seven;
    value = "seven";
    }
  else if (cardStr[0] == '8')
    {
    v = eight;
    value = "eight";
    }
  else if (cardStr[0] == '9')
    {
    v = nine;
    value = "nine";
    }
  else if (cardStr[0] == 'j')
    {
    v = jack;
    value = "jack";
    }
  else if (cardStr[0] == 'q')
    {
    v = queen;
    value = "queen";
    }
  else if (cardStr[0] == 'k')
    {
    v = king;
    value = "king";
    }
  else if (cardStr[0] == 'a')
    {
    v = ace;
    value = "ace";
    }
  else
    exit(-1);

  if (cardStr[1] == 'c')
    {
    s = club;
    suit = "club";
    }
  else if (cardStr[1] == 'd')
    {
    s = diamond;
    suit = "diamond";
    }
  else if (cardStr[1] == 'h')
    {
    s = heart;
    suit = "heart";
    }
  else if (cardStr[1] == 's')
    {
    s = spade;
    suit = "spade";
    }
  else
    exit(-1);

  return Card { v, s, value, suit };
  
}

bool isRFlush(Card* hand)
{
  if (!(hand[0].v == ace && hand[1].v == king && hand[2].v == queen && hand[3].v == jack && hand[4].v == ten))
    return false;
  for (int i = 0; i < 5; i++)
    {
      for (int j = 0; j < 5; j++)
	{
	  if (hand[i].s != hand[j].s)
	    return false;
	}
    }
  return true;
}

bool isSFlush(Card* hand)
{
  for (int i = 0; i < 5; i++)
    {
      for (int j = 0; j < 5; j++)
	{
	  if (hand[i].s != hand[j].s)
	    return false;
	}
    }
  for (int i = 0; i < 4; i++)
    {
      if (hand[i].v != hand[i+1].v + 1)
	return false;
    }
  return true;
}

bool isFourKind(Card* hand, std::string& value)
{
  if (hand[0].v != hand[1].v)
    {
      for (int i = 1; i < 4; i++)
	{
	  if (hand[i].v != hand[i+1].v)
	    return false;
	}
    }
  else
    {
      for (int i = 0; i < 3; i++)
	{
	  if (hand[i].v != hand[i+1].v)
	    return false;
	}
    }
  value = hand[3].value;
  return true;
}

bool isFHouse(Card* hand)
{
  if (hand[0].v != hand[2].v)
    {
      if (hand[0].v != hand[1].v)
	return false;
      for (int i = 2; i < 4; i++)
	{
	  if (hand[i].v != hand[i+1].v)
	    return false;
	}
    }
  else
    {
      for (int i = 0; i < 3; i++)
	{
	  if (hand[i].v != hand[i+1].v)
	    return false;
	}
      if (hand[3].v != hand[4].v)
	return false;
    }
  return true;
}

bool isFlush(Card* hand)
{
  for (int i = 0; i < 5; i++)
    {
      for (int j = 0; j < 5; j++)
	{
	  if (hand[i].s != hand[j].s)
	    return false;
	}
    }
  return true;
}

bool isStraight(Card* hand)
{
  for (int i = 0; i < 4; i++)
    {
      if (hand[i].v != hand[i+1].v + 1)
	return false;
    }
  return true;
}

bool isThree(Card* hand, std::string& value)
{
  if ((hand[0].v == hand[2].v) || (hand[1].v == hand[3].v) || (hand[2].v == hand[4].v))
    {
      value = hand[2].value;
      return true;
    }
  return false;
				     
}

bool isTwoPair(Card* hand, std::string& value1, std::string& value2)
{
  if (hand[0].v == hand[1].v)
    {
      if (hand[2].v == hand[3].v)
	return true;
      if (hand[3].v == hand[4].v)
	return true;
    }
  if ((hand[1].v == hand[2].v) && (hand[3].v == hand[4].v))
    return true;
  return false;
}

bool isPair(Card* hand, std::string& value)
{
  for (int i = 0; i < 4; i++)
    {
      if (hand[i].v == hand[i+1].v)
	value = hand[i].value;
	return true;
    }
}

int main(int argc, char** argv) {
  std::ifstream inFile;
  inFile.open(argv[1]);

  Card hand[5];
  std::string handStr[5];
  
  inFile >> handStr[0] >> handStr[1] >> handStr[2] >> handStr[3] >> handStr[4];
  for (int i = 0; i < 5; i++)
      hand[i] = stoC(handStr[i]);
  for (int i = 0; i < 5; i++)
    {
      for (int j = 0; j < 4-i; j++)
	{
	  if (hand[j].v < hand[j+1].v)
	    {
	      Card temp = hand[j+1];
	      hand[j+1] = hand[j];
	      hand[j] = temp;
	    }
	}
    }

  std::string suitVal, suitVal2;
  if (isRFlush(hand))
    std::cout << "Royal Flush";
  else if (isSFlush(hand))
    std::cout << "Straight Flush";
  else if (isFourKind(hand, suitVal))
    std::cout << "Four of a kind of " + suitVal + "\n";
  else if (isFHouse(hand))
    std::cout << "Full House";
  else if (isFlush(hand))
    std::cout << "Flush";
  else if (isStraight(hand))
    std::cout << "Straight";
  else if (isThree(hand, suitVal))
    std::cout << "Three of a kind of " + suitVal + "\n"; 
  else if (isTwoPair(hand, suitVal, suitVal2))
    std::cout << "Two pair of " + suitVal + "\n";
  else if (isPair(hand, suitVal))
    std::cout << "Pair of " + suitVal + "\n";
  
  else
    std::cout << "High card " + hand[0].value + "\n";
}

