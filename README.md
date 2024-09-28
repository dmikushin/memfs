# MEMFS implementation via FUSE3

This is MEMFS in-memory filesystem based on FUSE3 developed as a part of WinFsp project.

Here, we inherit them from the WinFsp project repository to focus around MEMFS applications.

The filesystem engine is built as shared library, with optional executable driver. This way the filesystem could be embedded into executable pipelines that require fast embedded file systems.
 

## Building

```
mkdir build
cd buld
cmake ..
make
```


## Testing
