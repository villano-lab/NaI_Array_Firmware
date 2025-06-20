##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=r5560sdk_libtest
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=user
Date                   :=27/08/20
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC 
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
#SourceSwitch           :=-x c -c 
SourceSwitch           :=-c 
OutputFile             :=../linux/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
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

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := g++ -shared -fPIC
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors) -std=c++14 -m64
CFLAGS   :=  -g -O0 -Wall $(Preprocessors) -std=c++14 -m64
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
Objects0=$(IntermediateDirectory)/R5560_SDKApp.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/R5560_SDKApp.cpp$(ObjectSuffix): R5560_SDKApp.cpp $(IntermediateDirectory)/R5560_SDKApp.cpp$(DependSuffix)
	$(CC) $(SourceSwitch) "R5560_SDKApp.cpp" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/R5560_SDKApp.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/R5560_SDKApp.cpp$(DependSuffix): R5560_SDKApp.cpp
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/R5560_SDKApp.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/R5560_SDKApp.cpp$(DependSuffix) -MM R5560_SDKApp.cpp

$(IntermediateDirectory)/R5560_SDKApp.cpp$(PreprocessSuffix): R5560_SDKApp.cpp
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/R5560_SDKApp.cpp$(PreprocessSuffix) R5560_SDKApp.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


