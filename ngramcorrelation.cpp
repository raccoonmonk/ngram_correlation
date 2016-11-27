#include "ngramcorrelation.h"

#include <sstream>
#include <utility>
#include <regex>
#include <cmath>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

NGramCorrelation::NGramCorrelation(const std::string & word1,
                                   const std::string & word2)
  : m_correlation(0)
{
  std::string source = getSource(word1, word2);
  timeseries data = parseSource(source);
  calculateCorrelation(data);
}

std::string NGramCorrelation::getSource(const std::string & word1,
                                        const std::string & word2,
                                        const uint16_t yearStart,
                                        const uint16_t yearEnd) const {

  //form request
  std::stringstream request;
  request << "https://books.google.com/ngrams/graph?content=";
  request << word1 << "%2C+" << word2 <<
             "&year_start=" << yearStart <<
             "&year_end=" << yearEnd;
  request <<  "&direct_url=t1%3B%2C" <<
              word1 << "%3B%2Cc0%3B.t1%3B%2C" <<
              word2 << "%3B%2Cc0";

  //get source
  std::stringstream source;
  source << curlpp::options::Url(request.str());
  return source.str();
}

timeseries NGramCorrelation::parseSource(const std::string & source) const {
  //get raw data
  std::regex expr("((?:\\[\\{)+.*(?:\\}\\]));");
  std::smatch match;
  std::regex_search(source, match, expr);
  std::stringstream data;
  data << match.str(1);

  boost::property_tree::ptree pt;
  boost::property_tree::read_json(data, pt);
  size_t i = 0;
  timeseries vec(2);

  //fill data
  //TODO change iteration
  for(boost::property_tree::ptree::value_type & v : pt.get_child("")) {
    //iterate values
    for(boost::property_tree::ptree::value_type & val : v.second.get_child("timeseries")) {
      //populate lists
      vec[i].push_back(std::stold(val.second.data()));
    }
    ++i;
  }
  return vec;
}

void NGramCorrelation::calculateCorrelation(const timeseries & data) {
  long double average1 = std::accumulate(data[0].begin(), data[0].end(), 0.0l) / data[0].size();
  long double average2 = std::accumulate(data[1].begin(), data[1].end(), 0.0l) / data[1].size();
  long double sum1 = 0, sum2 = 0, sum3 = 0;
  for(size_t i = 0, size = data[0].size(); i < size; ++i) {
    sum1 += (data[0][i] - average1) * (data[1][i] - average2);
  }
  for(size_t i = 0, size = data[0].size(); i < size; ++i) {
    sum2 += (data[0][i] - average1) * (data[0][i] - average1);
    sum3 += (data[1][i] - average2) * (data[1][i] - average2);
  }
  m_correlation = sum1 / std::sqrt(sum2 * sum3);
}

long double NGramCorrelation::getCorrelation() {
  return m_correlation;
}
