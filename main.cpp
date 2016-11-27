#include <iostream>
#include <algorithm>
#include "ngramcorrelation.h"

int main()
{
  std::cout << "Correlation coefficient between 2 phrases using Google Books NGrams\n";
  std:: cout << "Enter 2 phrases in the separate lines: \n";
  std::string word1, word2;
  std::getline(std::cin, word1);
  std::getline(std::cin, word2);
  std::replace(word1.begin(), word1.end(), ' ', '+');
  std::replace(word2.begin(), word2.end(), ' ', '+');

  std::cout << "Corelation coefficient = " <<
               NGramCorrelation(word1, word2).getCorrelation() <<
               std::endl;
  return 0;
}
