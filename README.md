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

Teh following test uses two terminals to test MEMFS.

In the first terminal:

```
./test_memfs ./test
```

In the second terminal:

```
cd test/
touch a
echo "hello" >a
rm -rf a
cd ..
```

Meanwhile, in the first terminal the memory allocations and deallocations should be reported:

```
[ 0x5e618fad01c0 ] Allocating 64 bytes (64 high, 64 current)
[ 0x5e618fad01c0 ] Allocating 104 bytes (168 high, 168 current)
[ 0x5e618fad01c0 ] Allocating 72 bytes (240 high, 240 current)
[ 0x5e618fad01c0 ] Allocating 104 bytes (344 high, 344 current)
[ 0x5e618fad01c0 ] Deallocating 64 bytes (344 high, 280 current)
[ 0x5e618fad01c0 ] Deallocating 72 bytes (344 high, 208 current)
[ 0x5e618fad01c0 ] Deallocating 104 bytes (344 high, 104 current)
```

Press Ctrl+C in the first terminal to stop MEMFS and exit.
