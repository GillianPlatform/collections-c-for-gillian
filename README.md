# Collections-C for symbolic testing with Gillian-C

This project is a fork of [Collections-C](https://github.com/srdja/Collections-C).
It contains the library as well as symbolic tests for it. There are two 
versions of the library and two corresponding test suites included.

The following instructions were tests with the following Gillian commit : [GillianPlatform/Gillian@b3ab5d2](https://github.com/GillianPlatform/Gillian/commit/b3ab5d2c335bcab4768e755276d62357f4e60670)

The first can be found under `lib-with-bugs`, and contains the library 
without the bug fixes that are detailed in the Gillian-C [documentation](https://gillianplatform.github.io/docs/c/cstest/). This corresponds to the Collections-C repo at commit [82878fd](https://github.com/srdja/Collections-C/tree/82878fd92a4586e7f2b1e476be335441f07ca92f), after accounting for only the files
that are relevant to the tests. The tests for this version 
(both of which should fail) can be run with the following script:

```
$ ./runGillianBuggyTests.sh
```

The second version of the library is found under `lib`. This incorporates the
bug fixes detailed above and corresponds to the Collections-C repo at commit [584e113](https://github.com/srdja/Collections-C/tree/584e113e123ac30fe78b3e92d70f6c40a066960d). The tests for this version 
(all of which should pass) can be run with the following script:

```
$ ./runGillianTests.sh
```

Finally, both versions of the library in this repo have had to be modified
slightly in order to account for the current limitations of Gillian-C. The changes are:

- The redefinition of the `CC_MAX_ELEMENTS` macro (in `include/common.h`) from 
  `((size_t) - 2)` to `16777216LU` (i.e. 2 ^ 24), as casts are not yet supported
  by Gillian.

- The removal of the `#include <stdio.h>` directive from `include/ring_buffer.h`,
  as Gillian does not yet support all standard library functions.

## Running examples with KLEE

Make sure that Klee, as well as `clang` and `llvm-link` is installed globally on your machine.
You also need the `klee_src` folder that contains `include/klee/klee.h` to be next to the `collections-c-gillian` folder.

Then, you can run a specific test suite (e.g. `array`) using

```
$ ./testKleeFolder.sh klee/normal/array
```

or

```
$ ./testKleeFolder.sh klee/bugs
```

The Makefile is configured to correctly build each file you will be testing, based on the bugs or normal library.
