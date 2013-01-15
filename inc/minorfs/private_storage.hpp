#ifndef LIBMINORFS_GRANFS_PRIVATE_STORAGE_HPP
#define LIBMINORFS_GRANFS_PRIVATE_STORAGE_HPP
#include <string>
#include <minorfs/granfs_node.hpp>
#include <minorfs/granularities.h>
namespace minorfs {
  class private_storage {
        std::string mGranFsMountPoint;
     public:
        private_storage();
        granfs_node operator[](int granspec);
        operator bool();
  };
}
#endif
