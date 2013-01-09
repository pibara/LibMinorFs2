#ifndef LIBMINORFS_GRANFS_HPP
#define LIBMINORFS_GRANFS_HPP
#include <string>
#include <minorfs/capfs.hpp>
#include <minorfs/granularities.h>
namespace minorfs {
  class granfs_node {
        std::string mNodePath;
        bool mOnGranFs;
     public:
        granfs_node(std::string nodepath,bool ongranfs);
        operator std::string();
        capfs_node decomposable(); 
  };
  class private_storage {
        std::string mGranFsMountPoint;
     public:
        private_storage();
        granfs_node operator[](int granspec);
        operator bool();
  };
}
#endif
