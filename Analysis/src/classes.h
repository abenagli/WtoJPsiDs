#include <string>
#include <vector>

namespace DataFormats_StdDictionaries {
  struct dictionarymap {
    std::vector<std::vector<std::string> > myvvs;
    std::vector<std::vector<std::vector<int> > > myvvvi;
    std::vector<std::vector<std::vector<float> > > myvvvf;
    std::vector<std::vector<std::vector<std::string> > > myvvvs;
  };
}
