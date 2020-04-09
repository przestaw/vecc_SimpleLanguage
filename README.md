# Project VecC 
## Vector Capable Language

### Program Usage

- program is run from command line in following format

    ``$ ./vecc-program <options> <files list>``
   
   example :
   
   ``$ ./vecc-program --vec -i file1.vecc file2.vecc main.vecc`` 
- Available parameters are :
    - -h [ --help ]               
    Help screen
    - -i [ --input ]          
    Input files list
    - --vec                       
    Incude standard vecc::vec library
    - --fib                       
    Incude Fibonacci library
    - -v [ --verbosity ] (=0)    
    verbosity level : 
        - 0   -  no information
        - 1   -  errors
        - 2   -  errors & information about parsed files
        - 3   -  errors & files & any created function
        - 4   -  errors & files & functions & any parsed token
        - 5+  -  full available log
        
- run *./demo.sh* to see example files parse and output

### Build instructions

- Project uses *boost* library for testing and parsing program parameters 
  *[version 1.72 has been confirmed to work, older might work as well]*
- When calling CMake for the first time, all needed compiler options must be
  specified on the command line.  After this initial call to CMake, the compiler
  definitions must not be included for further calls to CMake.  Other options
  can be specified on the command line multiple times including all definitions
  in the build options section below.
- Example of configuring, building, reconfiguring, rebuilding:


  #### Initial configuration
    $ mkdir build
    $ cd build
    $ cmake -DCMAKE_CXX_COMPILER=clang++ ..  
    $ make
    ...
  #### Second configuration
    $ make clean
    $ cmake -DCMAKE_BUILD_TYPE=Debug ..                               
    $ make
    ...
  #### Third configuration
    $ rm -rf *
    $ cmake -DCMAKE_CXX_COMPILER=g++ ..        
    $ make


- CMake variables
    - **CMAKE_BUILD_TYPE** = ``Release|Debug``
      Build type can be ``Release``, ``Debug`` which chooses
      the optimization level and presence of debugging symbols.
    
    - **CMAKE_CXX_COMPILER** = <C++ compiler name>
      Specify the C++ compiler.
  
- For full documentation consult the CMake manual or execute
    ```
    cmake --help-variable VARIABLE_NAME 
  
- Project targets :

    - **build-all** - builds all available targets
    - **vecc-doc** - available if *LaTeX*  or *Doxygen* is found on device
    - **vecc-test** - UnitTest made with *boost*
    - **vecc-check** - dummy target for test run during library compilation
    - **vecc-library** - library containing all classes excluding parameters
    - **vecc-program** - program available for command line usage
