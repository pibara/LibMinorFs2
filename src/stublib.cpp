#include <minorfs.hpp>
#include <boost/filesystem.hpp>
#include <string>
#ifdef __gnu_linux__
#define HAS_GET_PWENT 1
#endif
#ifdef HAS_GET_PWENT
#include <sys/types.h>
#include <pwd.h>
#endif
namespace minorfs {
  capfs_node::capfs_node(std::string nodepath,bool oncapfs):mNodePath(nodepath),mOnCapFs(oncapfs){}
  capfs_node::operator std::string() { return mNodePath; }
  capfs_node capfs_node::ro() { return *this; } 
  capfs_node capfs_node::operator[](std::string subd) { 
    return capfs_node(mNodePath + std::string("/") + subd,false);
  }
  granfs_node::granfs_node(std::string nodepath,bool ongranfs):mNodePath(nodepath),mOnGranFs(ongranfs){}
  granfs_node::operator std::string() { return mNodePath; }
  capfs_node granfs_node::decomposable() { return capfs_node(mNodePath,false);}
  private_storage::private_storage():mGranFsMountPoint(""){}
  granfs_node private_storage::operator[](int gran) {
     std::string dir=boost::filesystem::current_path().string();
#ifdef HAS_GET_PWENT
     if (gran == GRAN_BASIC_USER) {
       struct passwd *pw=getpwuid(geteuid());
       if ((pw) && (pw->pw_dir)) {
         dir=pw->pw_dir;
       }
     }
#endif
     return granfs_node(dir,false);
  }
  private_storage::operator bool() { return false;}
}
