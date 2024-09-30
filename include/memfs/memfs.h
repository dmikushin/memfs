#ifndef MEMFS_H
#define MEMFS_H

#include <string>

enum FuseStatus
{
	FuseSuccess = 0,
	FuseErrorNew = 1,
	FuseErrorMount = 2,
	FuseErrorSignalHandlers = 3,
	FuseErrorLoopConfig = 4,
	FuseErrorLoop = 5,
	FuseErrorUnitialized = 6,
	FuseErrorAlreadyStarted
};

const char* fuseGetErrorString(FuseStatus status);

namespace memfs {

class FuseMemfs;

FuseStatus mount(FuseMemfs** memfs,
	const std::string& mountpoint, unsigned int mode = 00777,
	unsigned int uid = 0, unsigned int gid = 0, unsigned int dev = 0);

FuseStatus umount(FuseMemfs* memfs);

} // namespace memfs

#endif // MEMFS_H

