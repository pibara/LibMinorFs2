#ifndef LIBMINORFS_GRANFS_NODE_HPP
#define LIBMINORFS_GRANFS_NODE_HPP
#include <string>
#include <minorfs/capfs_node.hpp>
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
}
#endif
