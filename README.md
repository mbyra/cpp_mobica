# README #

# Setting up #

## Eclipse / Windows ##
Required tools:

* git
* cmake
* mingw
* msys
* jre
* eclipse

### Generate project files with CMake ###

Create a build dir as a "sibling" dir of the checkout, i.e. in the base directory.
The structure should be
```
<base_dir>
 |
 |-<source_dir>
 |-<build_dir>
```

From the build dir run CMake as follows.

``` bash
cmake -G"Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug ../<source_dir>
```

### Import project into Eclipse ###

1. From the _File_ menu choose _Import_.
2. Select _General_->_Existing projects into workspace_.
3. Browse to the build directory CMake was run from.
4. You now have fully functional Eclipse project.

# Exercise notes
[notes](Exercise_Notes.md)

# References

* [C++ reference](http://en.cppreference.com/w/)
* [CMake tutorial](https://cmake.org/cmake-tutorial/)
* [Unit testing framework](https://github.com/philsquared/Catch/blob/master/docs/tutorial.md)
* [Valgrind tools info](http://valgrind.org/info/tools.html)
