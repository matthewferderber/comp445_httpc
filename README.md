## COMP445 Assignment #1

### Usage

- `httpc get 'http://google.ca'` (Basic GET request to URL)
- `httpc get -v 'http://google.ca'` (Prints verbose information)
- `httpc post -v 'http://google.ca'` (POSTS to URL)
- `httpc post -v -f filename 'http://localhost:8000/file_uploader'` (Uploads file to URL)
- `httpc help` (Prints help information)


### Requirements

- Unix environment to build and run the application (MacOS, Linux, Cygwin)
- CMake
- Make
- C Compiler (gcc, clang)
- glibc

### Build instructions

- Clone/Unzip the project.
- Create a new folder to build the application in.
- From inside the build folder, run `cmake /path/to/cloned/project`
- Run `make`

After following the build instructions, the build folder should contain a `httpc` driver for the assignment.

