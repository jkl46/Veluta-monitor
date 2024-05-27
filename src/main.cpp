#define MASTER
// #define SLAVE

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
