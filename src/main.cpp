#include "boggle.h"
#include "boggle_expander.h"
#include "boggle_gridmock.h"
#include "boggle_helper.h"
#include "time_helpers.h"
#include "worddict.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

//#define DEBUG

namespace tng {
constexpr int kDefaultComputationTimeInSecs = 30;

int main(int argc, char *argv[]) {
  TimePoint t1 = GetTimePoint();
  unsigned seed = 0; // for a more random behaviour --> time(NULL)
  int nbWordsFound = 0;
  // Loop for 30 seconds to allow profiling
  while (GetTimeFrom<TimeInS>(t1).count() < kDefaultComputationTimeInSecs) {
    /* Create dictionary */
    // This is a voluntary mistake : we want people to notice that we are
    // recreating the dictionary in a loop
    std::string pathWords = TNG_DATA_PATH;
    pathWords += "words_reduced.txt";
    std::ifstream fs(pathWords);
    tng::WordDict words(fs);

    /* Create grid : todo a better create function would make it more likely to
     * find words */
    tng::Boggle::GridChar grid = tng::Boggle::RandomFactory(seed);
#ifdef DEBUG
    tng::Boggle::operator<<(std::cerr, grid);
#endif
    /* Look for words */
    std::vector<std::string> validWords =
        tng::Boggle::FindAllWords(grid, words);
    nbWordsFound += validWords.size();

#ifdef DEBUG
    /* output */
    for (std::string w : validWords) {
      std::cerr << w << std::endl;
    }
#endif
    ++seed;
  }
  std::cerr << argv[0] << "found " << nbWordsFound << std::endl;
  return 0;
}
} // namespace tng

int main(int argc, char *argv[]) { return tng::main(argc, argv); }
