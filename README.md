## Getting Started

### Installing Dependencies

Before building the project, you will need to install all relevant dependencies for your platform so that the project has access to all the tools required, and raylib can compile and link correctly. You can find intructions for installing dependencies on macOS, Linux, and Windows in the [docs file on installing dependencies](docs/InstallingDependencies.md).

### Building the Project
Once you have cloned this repository and installed dependencies, building the project is as simple as running these two commands in its root directory:

#### macOS & Linux
```console
$ make setup
$ make
```

#### Windows
```console
> mingw32-make setup
> mingw32-make
```

The first command will clone in the lastest C++ bindings and targeted version of raylib, copy across any relevant header files into `/includes`, and build a static library file from them, placing it in `/lib`. The second command then compiles, runs and cleans up your project using the source code in `/src/main.cpp`.

#### macOS & Linux

```console
$ make bin/app; make execute
```

#### Windows

```console
> mingw32-make bin/app && mingw32-make execute
```

Using this method can save you a huge amount of time compiling *(in reality, just a few seconds)* each time you make a small change to your code! If you want to know more about how it works, you should have a read through [the docs entry explaining the Makefile](docs/MakefileExplanation.md).

While separate compilation works quite well in most scenarios, it's not magic, and there are a few caveats to take note of here:

1. Changing `.h` files will often result in longer compile times by causing all files that include them to recompile
2. Constant changes to files included by many others in your program (like a base-class) will also cause all of those dependent to recompile
3. Including widely-scoped files (like the whole of `raylib-cpp.hpp`) will add all of its own includes as dependent and increase the build time
4. Placing includes in `.h` files instead of forward-declarations will also increase recursive includes and therefore the build time

### Passing Args to the Executable
For working with some projects, you may want to pass arguments to the program once it's been built. This can be achieved by assigning values to the `ARGS` flag in the Makefile like below:

#### macOS & Linux

```console
$ make ARGS="--somearg"
```

#### Windows

```console
> mingw32-make ARGS="--somearg"
```

### Specifying Custom Macro Definitions
You may also want to pass in your own macro definitions for certain configurations (such as setting log levels). You can pass in your definitions using `CXXFLAGS`:

#### macOS & Linux

```console
$ make CXXFLAGS=-DMY_MACRO=1
```

#### Windows

```console
> mingw32-make CXXFLAGS=-DMY_MACRO=1
```

### Specifying a Non-Default Compiler
If you want to use a compiler for your platform that isn't the default for your system (or potentially you would like to explicitly state it), you can make use of the system-implicit `CXX` variable like so:

#### macOS & Linux

```console
$ make CXX=g++
```

#### Windows

```console
> mingw32-make CXX=g++
```