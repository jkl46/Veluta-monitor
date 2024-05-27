// Do not change this file
// Work in master/master.cpp and slave/slave.cpp as if this that the main file

/*----------------CHANGE COMMENT BELOW------------------*/

#define MASTER
// #define SLAVE

/*----------------DO NOT CHANGE BELOW-------------------*/

#ifdef MASTER
#define master_main build_main
#include <master/master.cpp>
#endif

#ifdef SLAVE
#define slave_main build_main
#include <slave/slave.cpp>
#endif


int main(int argc, char** argv)
{
    return build_main(argc, argv);
}
