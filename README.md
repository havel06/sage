## How to build:

```
git clone https://github.com/havel06/sage
cd sage
mkdir build
cd build
meson --buildtype=release ..
ninja
```

For a debug build, change `--buildtype=release` to `--buildtype=debug`.

### Tested compilers:

- clang 14.0.6
- gcc 12.2.0
