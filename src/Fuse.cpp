#include "Fuse.h"

#include <cstring>
#include <fuse_lowlevel.h>
#include <unistd.h>

using namespace memfs;

Fuse::Fuse(const std::string &mountpoint_, void *user_data_)
    : mountpoint(mountpoint_), user_data(user_data_) {}

FuseStatus Fuse::getStatus() const { return status; }

FuseStatus Fuse::start() {
  if (geteuid() == 0) {
    status = FuseErrorRootDisallowed;
    return status;
  }
  if (status == FuseSuccess)
    return FuseErrorAlreadyStarted;

  const struct fuse_operations *op;
  size_t op_size;
  getFuseOperations(&op, &op_size);

  const char *argv[] = {"memfs", nullptr};
  struct fuse_args args = FUSE_ARGS_INIT(1, const_cast<char **>(argv));
  fuse = fuse_new(&args, op, op_size, user_data);
  if (fuse == NULL) {
    status = FuseErrorNew;
    return status;
  }

  if (fuse_mount(fuse, mountpoint.c_str())) {
    status = FuseErrorMount;
    return status;
  }

  se = fuse_get_session(fuse);
  if (fuse_set_signal_handlers(se)) {
    status = FuseErrorSignalHandlers;
    return status;
  }

  status = FuseSuccess;
#if 0
loop_config = fuse_loop_cfg_create();
if (loop_config == NULL) {
  status = FuseErrorLoopConfig;
  goto out3;
}

const unsigned int enable = 1;
fuse_loop_cfg_set_clone_fd(loop_config, enable);

long num_threads = sysconf(_SC_NPROCESSORS_ONLN);
fuse_loop_cfg_set_idle_threads(loop_config, num_threads);
fuse_loop_cfg_set_max_threads(loop_config, num_threads);

status = FuseSuccess;
    
if (fuse_loop_mt(fuse, loop_config))
  status = FuseErrorLoop;
#else
  if (fuse_loop(fuse))
    status = FuseErrorLoop;
#endif
  return status;
}

FuseStatus Fuse::stop() {
  if (status != FuseSuccess)
    return status;

  fuse_session_exit(se);
  se = nullptr;

  fuse_unmount(fuse);
  fuse = nullptr;

  status = FuseErrorUnitialized;
  return FuseSuccess;
}

Fuse::~Fuse() {
  if (se)
    fuse_remove_signal_handlers(se);

  if (status != FuseErrorMount)
    fuse_unmount(fuse);

  if (fuse)
    fuse_destroy(fuse);
}

FuseThread::FuseThread(const std::string &mountpoint_, void *user_data_)
    : Fuse(mountpoint_, user_data_) {}

FuseStatus FuseThread::start() {
  fuseThread = std::thread([this] { Fuse::start(); });

  return FuseSuccess;
}

FuseStatus FuseThread::stop() {
  FuseStatus status = Fuse::stop();

  if ((std::this_thread::get_id() != fuseThread.get_id()) &&
      fuseThread.joinable()) {
    fuseThread.join();
  }

  return status;
}

FuseThread::~FuseThread() {
  if ((std::this_thread::get_id() != fuseThread.get_id()) &&
      fuseThread.joinable()) {
    fuseThread.join();
  }
}
