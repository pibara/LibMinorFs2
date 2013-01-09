#include <minorfs.hpp>
#include <iostream>

int main(int argc,char **argv) {
  minorfs::private_storage privs;
  if (privs) {
     std::cerr << "have private storage: TRUE" << std::endl;
  } else {
     std::cerr << "have private storage: FALSE" << std::endl;
  }
  minorfs::granfs_node homenode=privs[GRAN_BASIC_USER];
  minorfs::granfs_node cwdnode=privs[GRAN_BASIC_CWD];
  std::cerr << "home node :" << std::string(homenode) << std::endl;
  std::cerr << "cwd node :" << std::string(cwdnode) << std::endl; 
  minorfs::capfs_node captop=cwdnode.decomposable();
  std::cerr << "cap-top node :" << std::string(captop) << std::endl;  
  minorfs::capfs_node captopro=captop.ro();
  std::cerr << "cap-top-ro node :" << std::string(captopro) << std::endl;
  minorfs::capfs_node subdir=captopro["Downloads"];
  std::cerr << "subdir node :" << std::string(subdir) << std::endl;
}
