#ifndef MEMFS_FUSE_H
#define MEMFS_FUSE_H

#include "memfs/memfs.h"

#include <fuse.h>
#include <fuse_common.h>
#include <string>
#include <thread>

namespace memfs {

class Fuse {
  Fuse(Fuse const &) = delete;
  void operator=(Fuse const &) = delete;

protected:
  virtual void getFuseOperations(const struct fuse_operations **op,
                                 size_t *op_size) = 0;

  FuseStatus status = FuseErrorUnitialized;

private:
  const std::string mountpoint;
  void *user_data;

  struct fuse *fuse = nullptr;
  struct fuse_session *se = nullptr;
#if 0
    struct fuse_loop_config *loop_config = nullptr;
#endif
protected:
  Fuse(const std::string &mountpoint_, void *user_data_);

public:
  FuseStatus getStatus() const;

  virtual FuseStatus start();

  virtual FuseStatus stop();

  virtual ~Fuse();
};

class FuseThread : public Fuse {
  std::thread fuseThread;

public:
  FuseThread(const std::string &mountpoint_, void *user_data_);

  virtual FuseStatus start() override;

  virtual FuseStatus stop() override;

  virtual ~FuseThread();
};

} // namespace memfs

#endif // MEMFS_FUSE_H
