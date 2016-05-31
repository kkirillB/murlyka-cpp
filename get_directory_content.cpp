#include "get_directory_content.h"
#include <boost/filesystem.hpp>
#include <boost/optional.hpp>
#include <string>
#include <vector>

using namespace boost::filesystem;

boost::optional<std::vector<std::string>> get_directory_content(const std::string& dir)
{
  std::vector<std::string> v;
  path p (dir);
    if (exists(p) && is_directory(p))
    {
      for (auto& x : directory_iterator(p))
        v.push_back(x.path().filename().string());

      return v;
    }
  return boost::none;
}
