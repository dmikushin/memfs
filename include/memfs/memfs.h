#ifndef MEMFS_H
#define MEMFS_H

#include <string>

enum FuseStatus
{
	FuseSuccess = 0,
	FuseErrorNew = 1,
	FuseErrorMount = 2,
	FuseErrorUnmount = 3,
	FuseErrorSignalHandlers = 4,
	FuseErrorLoopConfig = 5,
	FuseErrorLoop = 6,
	FuseErrorUnitialized = 7,
	FuseErrorAlreadyStarted = 8,
	FuseErrorRootDisallowed = 9
};

const std::string fuseGetErrorString(FuseStatus status);

namespace memfs {

class FuseMemfs;

FuseStatus mount(FuseMemfs** memfs,
	const std::string& mountpoint, unsigned int mode = 00777,
	unsigned int uid = 0, unsigned int gid = 0, unsigned int dev = 0);

FuseStatus status(FuseMemfs* memfs);

FuseStatus umount(FuseMemfs* memfs);

} // namespace memfs

#endif // MEMFS_H

