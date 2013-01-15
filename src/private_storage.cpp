#ifdef __unix__
#define PLATFORM_POSIX 1
#endif
#ifdef __linux__
#define PLATFORM_POSIX 1
#endif
#include <minorfs.hpp>
#include <boost/filesystem.hpp>
#include <string>
#ifdef PLATFORM_POSIX
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#else
#error "only builds on POSIX system."
#endif

namespace minorfs {
  //The granfs private_storage constructor
  private_storage::private_storage():mGranFsMountPoint(""){
#ifdef PLATFORM_POSIX
     struct stat statrec;
     //If granfs is mounted than the ctime of the top level directory should show a 0 value.
     if  ((stat("/minorfs2/gran",&statrec) == 0) && (statrec.st_ctime == 0)) {
        mGranFsMountPoint="/minorfs2/gran";
     }
#endif  
  }
  granfs_node private_storage::operator[](int gran) {
     std::string dir=boost::filesystem::current_path().string();
     bool isminorfs=false;
#ifdef PLATFORM_POSIX
     if ((mGranFsMountPoint != "")||(gran == GRAN_BASIC_USER)) {
        struct passwd *pw;
        switch (gran) {
          case GRAN_BASIC_NON:
             break;
          case GRAN_BASIC_USER:
             pw=getpwuid(geteuid());
             if ((pw) && (pw->pw_dir)) {
                dir=pw->pw_dir;
             }
             break;
          case GRAN_ENHANCED_USER_BASE_SINGLE:
             dir=mGranFsMountPoint + "/user/base/single";
             isminorfs=true;
             break;
          case GRAN_ENHANCED_TOOLSET_BASE_SINGLE:
             dir=mGranFsMountPoint + "/toolset/base/single";
             isminorfs=true;
             break;
          case GRAN_ENHANCED_TOOLSET_CALLCHAIN1_SINGLE:
             dir=mGranFsMountPoint + "/toolset/callchain1/single";
             isminorfs=true;
             break;
          case GRAN_ENHANCED_TOOLSET_CALLCHAIN2_SINGLE:
             dir=mGranFsMountPoint + "/toolset/callchain2/single";
             isminorfs=true;
             break;
          case GRAN_ENHANCED_EXE_BASE_SINGLE:
             dir=mGranFsMountPoint + "/exe/base/single";
             isminorfs=true;
             break;
          case GRAN_ENHANCED_EXE_CALLCHAIN1_SINGLE:
             dir=mGranFsMountPoint + "/exe/callchain1/single";
             isminorfs=true;
             break;
          case GRAN_ENHANCED_EXE_CALLCHAIN2_SINGLE:
             dir=mGranFsMountPoint + "/exe/callchain2/single";
             isminorfs=true;
             break;
          case GRAN_ENHANCED_SCRIPT_BASE_SINGLE:
             dir=mGranFsMountPoint + "/script/base/single";
             isminorfs=true;
             break;
          case GRAN_ENHANCED_SCRIPT_CALLCHAIN1_SINGLE:
             dir=mGranFsMountPoint + "/script/callchain1/single";
             isminorfs=true;
             break;
          case GRAN_ENHANCED_SCRIPT_CALLCHAIN2_SINGLE:
             dir=mGranFsMountPoint + "/script/callchain2/single";
             isminorfs=true;
             break;
          case GRAN_ENHANCED_CMDLINE_BASE_SINGLE:
             dir=mGranFsMountPoint + "/cmdline/base/single";
             isminorfs=true;
             break;
          case GRAN_ENHANCED_CMDLINE_CALLCHAIN2_SINGLE:
             dir=mGranFsMountPoint + "/cmdline/callchain1/single";
             isminorfs=true;
             break;
          case GRAN_ENHANCED_CMDLINE_CALLCHAIN2_MULTI:
             dir=mGranFsMountPoint + "/cmdline/callchain2/multi";
             isminorfs=true;
             break;
          default: 
             break;
        }
     }
#endif
     return granfs_node(dir,isminorfs);
  }
  private_storage::operator bool() { 
    return (mGranFsMountPoint != "");
  }
}
