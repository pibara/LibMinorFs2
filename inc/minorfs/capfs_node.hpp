#ifndef LIBMINORFS_CAPFS_NODE_HPP
#define LIBMINORFS_CAPFS_NODE_HPP
#include <string>
namespace minorfs {
  class capfs_node;
  class capfs_node {
        std::string mNodePath;
        bool mOnCapFs;
     public:
        capfs_node(std::string nodepath,bool oncapfs);
        operator std::string();
        operator bool();
        capfs_node operator[](std::string);
        capfs_node operator[](char const *);
        capfs_node ro(); 
  };
}
#endif
