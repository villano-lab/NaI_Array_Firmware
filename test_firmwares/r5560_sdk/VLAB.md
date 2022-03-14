# How It Works

This library provides generic code to be compiled with any custom firmware that is developed on
Sci-Compiler. Having this library compile is a pre-requisite to compiling a custom firmware on the
DT5560SE device. 

The code in this directory is a copy of the library:

https://github.com/NuclearInstruments/r5560_sdk

## Modifications

This code will _not_ work as-is (from a fresh GitHub clone of the above site), there were some minor modifications I had to do to the Makefile while running on Ubuntu 18.04.

The makefile in `R5560_SDKApp/r5560sdk_libtest.mk` needs to be modified. The variable `Libs` (see
below) should be erased and the variable `LibPath` should include an explicit reference to the
library `.so` location. 

```
ObjectsFileList        :="r5560sdk_libtest.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  "r5560" 
LibPath                := $(LibraryPathSwitch). ../linux/libr5560.so.1.0.0 
```

Without these changes it seems like the make command tries to add the library libr5560.so
redundantly and therefore fails. 
