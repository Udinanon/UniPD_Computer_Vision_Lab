# Notes

## Discussion

! i find myself often having to rush and don't have time to focus on getting ahead, such as learning C++ beyond what is needed
! this expands to code structure and better practices

Code has to compile
    mine has issues iwth paths, i need to find a better way to handle them
    it should not have any other issues ??
    
decent folder structure OK
    I should learn the better folder structure for c++, things like src include etc

decent code structure (returns, main, indeintation, linting) OK

Header files
    we have the include statement OK
    we have the include guards, by chance! OK
        the thing with
            #ifndef
            #define
            #endif 
    grouping similar funcs together OK   
    functions must be defined elsewhere OK
    include ONLY header files OK

System
    avoid absolute paths!!
        how?
            either learn how to control CMake and read locally, or use argv
    if you use command args, check for them!

Functions
    define in .h, write in .cpp OK
    don0t put everything in main OK?
    use good names 
    
Func Args
    you should pass things by reference or pointer IDK?
    if you pass bt reference ( `Mat&` ) use const
    no global variables
        i need to understand structs/similar stuff

not too bad i guess
    
## TODO
 - do first chapter tutorial C++
 - read some of the C++ book
 - fund way to load files from local folder OR read folder of file and combine it with relavie paths

## Pointers
Int* denotes a value that is a pointer to a Int value
Void* is a generic pointer that has no details about type and can be cast using (Type*) pointer to any type

`Mat* p = &object;` creates a Pointer to the object, here specifying it's poointing to a Mat object

`Mat obj2 = *p;` instead is reopening the pointer to an object

Be very carfeuk of not mixing up type stuff as it's gonna cause a mess!

## OpenCV
pay extra attention to loading images as Grayscale, as it default reads them as color and this meses up things

WHY IS .at<>(y, x) Y X AND NOT X Y WHY WHY WHY WHY

Canny() accepts flawlessy bgr and grayscale images

## Libs
to make a lib you need:

a lib.cpp file where 
    you make the code, the way you want
    

a lib.h file where 
    you declare the functions in and outs and 

    #ifndef lib
    #define lib

    #endif

    and u think imoport the relevant libraries, not sure

and in main.cpp 
    #include "lib.h"

## CMake
I think it's not deisgned to handle multiple projects together, even though it's a requested feature and it has all the garments of supporting it

easiest way is have neat subfolders, ueach with its CMakeLists and hide the ones y8ou don0t wanna use, then call
`Clean Reconfigure All Projects`, ocate the desired fikle manually and you0re good to go

not easy to switch from compiling one to the other but good enough and makes code reuse easy and quick



## misc

can i include unused libraries in the project? yes



g++ main.cpp -o Task4 -I/usr/local/include/opencv4 -lopencv_highgui -lopencv_core -lopencv_imgcodecs -lopencv_imgproc

g++ main.cpp task2.cpp -o Task2 -I/usr/local/include/opencv4 -lopencv_highgui -lopencv_core -lopencv_imgcodecs -lopencv_imgproc
