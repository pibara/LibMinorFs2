//FIXME: split up in s 1everal files.
#define HAS_EXTENDED_ATTRIBUTES 1 //FIXME, needs to go into cmake config file.
#ifdef __unix__
#define PLATFORM_POSIX 1
#endif
#ifdef __linux__
#define PLATFORM_POSIX 1
#endif
#include <minorfs.hpp>
#include <string>
#ifdef PLATFORM_POSIX
#ifdef HAS_EXTENDED_ATTRIBUTES
#include <attr/xattr.h>
#include <string.h>
#endif
#else
#error "only builds on POSIX system."
#endif

namespace minorfs {
  capfs_node::capfs_node(std::string nodepath,bool oncapfs):mNodePath(nodepath),mOnCapFs(oncapfs){}
  capfs_node::operator std::string() { return mNodePath; }
  capfs_node capfs_node::ro() { 
#ifdef HAS_EXTENDED_ATTRIBUTES
     if (mOnCapFs) {
       char capval[57];
       memset(capval,0,57);
       if (getxattr(mNodePath.c_str(),"rocap",static_cast<void *>(capval),57)>0) {
         return capfs_node(std::string("/minorfs2/cap/") + capval,true);
       }
     }
#endif
     return *this; 
  } 
  capfs_node capfs_node::operator[](std::string subd) { 
    std::string weakpath=mNodePath + std::string("/") + subd;
#ifdef HAS_EXTENDED_ATTRIBUTES
    if (mOnCapFs) {
       char capval[57];
       memset(capval,0,57);
       if (getxattr(mNodePath.c_str(),"rwcap",static_cast<void *>(capval),57)>0) {
         return capfs_node(std::string("/minorfs2/cap/") + capval,true);
       }
       if (getxattr(mNodePath.c_str(),"rocap",static_cast<void *>(capval),57)>0) {
         return capfs_node(std::string("/minorfs2/cap/") + capval,true);
       }
    }
#endif
    return capfs_node(mNodePath + std::string("/") + subd,false);
  }
  capfs_node capfs_node::operator[](char const * subd) {
    return (*this)[std::string(subd)];
  }
}
