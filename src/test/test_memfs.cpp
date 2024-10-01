#include "memfs/memfs.h"

using namespace memfs;

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s <mountpoint>\n", argv[0]);
		return 0;
	}
	
	const std::string mountpoint(argv[1]);
	FuseMemfs* memfs;
    FuseStatus status = memfs::mount(&memfs, mountpoint);
    if (status != FuseSuccess)
    {
    	fprintf(stderr, "FuseMemfs error %d: %s\n", static_cast<int>(status), fuseGetErrorString(status).c_str());
    	exit(EXIT_FAILURE);
    }
    
    // TODO Wait until exit or signal
    
    status = memfs::umount(memfs);
    if (status != FuseSuccess)
    {
    	fprintf(stderr, "FuseMemfs error %d: %s\n", static_cast<int>(status), fuseGetErrorString(status).c_str());
    	exit(EXIT_FAILURE);
    }

    return 0;
}

