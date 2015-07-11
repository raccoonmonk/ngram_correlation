#ifndef NGRAMCORRELATION_H
#define NGRAMCORRELATION_H

#include <sstream>
#include <utility>
#include <regex>
#include <cmath>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using timeseries = std::vector<std::vector<long double>>;

class NGramCorrelation
{
public:
  NGramCorrelation(const std::string & word1, const std::string & word2);
  const long double & getCorrelation(); //returns final correlation

private:

  /*!
   * \brief getSource get html data from google
   * \param word1
   * \param word2
   * \param yearStart
   * \return raw http response
   */
  std::string getSource(const std::string & word1,
                        const std::string & word2,
                        const uint16_t yearStart = 1500,
                        const uint16_t yearEnd = 2012) const;

  /*!
   * \brief parseSource get data from html source
   * \param source - html data
   * \return parsed json data
   */
  timeseries parseSource(const std::string & source) const;

  /*!
   * \brief calculateCorrelation calculates Pearson's correlation coefficient
   * \param data json data
   */
  void calculateCorrelation(const timeseries & data);

  long double m_correlation; //! correlation coefficient value
};
#endif // NGRAMCORRELATION_H
