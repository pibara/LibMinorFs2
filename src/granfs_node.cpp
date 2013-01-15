//FIXME: split up in s 1everal files.
#define HAS_EXTENDED_ATTRIBUTES 1 //FIXME, needs to go into cmake config file.
#ifdef __unix__
#define PLATFORM_POSIX 1
#endif
#ifdef __linux__
#define PLATFORM_POSIX 1
#endif
#include <minorfs.hpp>
#include <string.h>
#include <string>
#ifdef PLATFORM_POSIX
#ifdef HAS_EXTENDED_ATTRIBUTES
#include <attr/xattr.h>
#endif
#else
#error "only builds on POSIX system."
#endif

namespace minorfs {
  //The granfs_node constructor
  granfs_node::granfs_node(std::string nodepath,bool ongranfs):mNodePath(nodepath),mOnGranFs(ongranfs){}
  granfs_node::operator std::string() { 
     return mNodePath; 
  }
  capfs_node granfs_node::decomposable() {
#ifdef HAS_EXTENDED_ATTRIBUTES
     if (mOnGranFs) {
       char capval[57];
       memset(capval,0,57);
       if (getxattr(mNodePath.c_str(),"rwcap",static_cast<void *>(capval),57)>0) {
         return capfs_node(std::string("/minorfs2/cap/") + capval,true);
       }
     }
#endif      
     return capfs_node(mNodePath,false);
  }
}
