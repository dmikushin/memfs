#include <chrono>
#include <signal.h>
#include <thread>

#include "memfs/memfs.h"

using namespace memfs;

static FuseMemfs *fs = nullptr;

// Signal handler function
static void signalHandler(int signum) {
  if (fs) {
    FuseStatus status = memfs::umount(fs);
    if (status != FuseSuccess)
      fprintf(stderr, "FuseMemfs error %d: %s\n", static_cast<int>(status),
              fuseGetErrorString(status).c_str());
  }
  exit(signum);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <mountpoint>\n", argv[0]);
    return 0;
  }

  // Register signal handler
  signal(SIGINT, signalHandler);
  signal(SIGTERM, signalHandler);

  const std::string mountpoint(argv[1]);
  FuseStatus status = memfs::mount(&fs, mountpoint);
  if (status != FuseSuccess) {
    fprintf(stderr, "FuseMemfs error %d: %s\n", static_cast<int>(status),
            fuseGetErrorString(status).c_str());
    exit(EXIT_FAILURE);
  }

  while (1) {
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Periodically check the error status.
    status = memfs::status(fs);
    if (status != FuseSuccess) {
      fprintf(stderr, "FuseMemfs error %d: %s\n", static_cast<int>(status),
              fuseGetErrorString(status).c_str());
      break;
    }
  }

  status = memfs::umount(fs);
  if (status != FuseSuccess) {
    fprintf(stderr, "FuseMemfs error %d: %s\n", static_cast<int>(status),
            fuseGetErrorString(status).c_str());
    exit(EXIT_FAILURE);
  }

  return 0;
}
