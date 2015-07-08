#include <iostream>
#include "ngramcorrelation.h"

int main()
{
  std::cout << "Correlation coefficient between 2 words using Google books NGrams" << std::endl;
  std:: cout << "Enter 2 words: " << std::endl;
  std::string word1, word2;
  std::cin >> word1;
  std::cin >> word2;

  std::cout << "Corelation coefficient = " <<
               NGramCorrelation(word1, word2).getCorrelation() <<
               std::endl;
  return 0;
}
