##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            =Test
ConfigurationName      =Debug
WorkspacePath          = "C:\Users\dmitry.tsvetkov\Documents\GitHub\StartPP\StartPP"
ProjectPath            = "C:\Users\dmitry.tsvetkov\Documents\GitHub\StartPP\Test"
IntermediateDirectory  =./Debug
OutDir                 = $(IntermediateDirectory)
CurrentFileName        =
CurrentFilePath        =
CurrentFileFullPath    =
User                   =dmitry.tsvetkov
Date                   =10/06/2016
CodeLitePath           ="C:\Program Files\CodeLite"
LinkerName             ="C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\link.exe" -nologo
SharedObjectLinkerName ="C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\link.exe" -DLL -nologo
ObjectSuffix           =.obj
DependSuffix           =
PreprocessSuffix       =.i
DebugSwitch            =/Zi 
IncludeSwitch          =/I
LibrarySwitch          = 
OutputSwitch           =/OUT:
LibraryPathSwitch      =/LIBPATH:
PreprocessorSwitch     =/D
SourceSwitch           =-c 
OutputFile             =$(IntermediateDirectory)\$(ProjectName)
Preprocessors          =
ObjectSwitch           =/Fo
ArchiveOutputSwitch    =/OUT:
PreprocessOnlySwitch   =-E
ObjectsFileList        ="Test.txt"
PCHCompileFlags        =
MakeDirCommand         =makedir
RcCmpOptions           = $(shell wx-config --rcflags)
RcCompilerName         =windres
LinkOptions            =  $(shell wx-config --libs) -mwindows
IncludePath            = $(IncludeSwitch)"C:\Program Files\Microsoft SDKs\Windows\v6.0A\include" $(IncludeSwitch)"C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\include"  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             = 
RcIncludePath          = 
Libs                   = 
ArLibs                 =  
LibPath                =$(LibraryPathSwitch)"C:\Program Files\Microsoft SDKs\Windows\v6.0A\lib" $(LibraryPathSwitch)"C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\lib"  $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       = "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\lib.exe" -nologo
CXX      = "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\cl.exe" -nologo -FC -EHs
CC       = "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\cl.exe" -nologo -FC
CXXFLAGS =  -g -O0 -Wall $(shell wx-config --wxcfg=vc_dll/mswud --cflags)  $(Preprocessors)
CFLAGS   =  -g -O0 -Wall $(Preprocessors)
ASFLAGS  = 
AS       = as


##
## User defined environment variables
##
CodeLiteDir=C:\Program Files\CodeLite
##
## Object Targets Lists 
##
Objects0=$(IntermediateDirectory)\main.cpp$(ObjectSuffix) $(IntermediateDirectory)\MainFrame.cpp$(ObjectSuffix) $(IntermediateDirectory)\wxcrafter.cpp$(ObjectSuffix) $(IntermediateDirectory)\wxcrafter_bitmaps.cpp$(ObjectSuffix) $(IntermediateDirectory)\win_resources.rc$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)\.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)\.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)
.PHONY: clean PrePreBuild PreBuild MakeIntermediateDirs all PostBuild 

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)\.d:
	@echo Creating Intermediate Directory
	@$(MakeDirCommand) "./Debug"
	@echo Intermediate directories created
PreBuild:


##
## Objects
##
$(IntermediateDirectory)\main.cpp$(ObjectSuffix): main.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:\Users\dmitry.tsvetkov\Documents\GitHub\StartPP\Test\main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)\main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)\main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)\MainFrame.cpp$(ObjectSuffix): MainFrame.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:\Users\dmitry.tsvetkov\Documents\GitHub\StartPP\Test\MainFrame.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)\MainFrame.cpp$(PreprocessSuffix): MainFrame.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)\MainFrame.cpp$(PreprocessSuffix) "MainFrame.cpp"

$(IntermediateDirectory)\wxcrafter.cpp$(ObjectSuffix): wxcrafter.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:\Users\dmitry.tsvetkov\Documents\GitHub\StartPP\Test\wxcrafter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)\wxcrafter.cpp$(PreprocessSuffix): wxcrafter.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)\wxcrafter.cpp$(PreprocessSuffix) "wxcrafter.cpp"

$(IntermediateDirectory)\wxcrafter_bitmaps.cpp$(ObjectSuffix): wxcrafter_bitmaps.cpp 
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:\Users\dmitry.tsvetkov\Documents\GitHub\StartPP\Test\wxcrafter_bitmaps.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)\wxcrafter_bitmaps.cpp$(PreprocessSuffix): wxcrafter_bitmaps.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)\wxcrafter_bitmaps.cpp$(PreprocessSuffix) "wxcrafter_bitmaps.cpp"

$(IntermediateDirectory)\win_resources.rc$(ObjectSuffix): win_resources.rc
	$(RcCompilerName) -i "C:\Users\dmitry.tsvetkov\Documents\GitHub\StartPP\Test\win_resources.rc" $(RcCmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/win_resources.rc$(ObjectSuffix) $(RcIncludePath)
##
## Clean
##
clean:
	@if exist $(IntermediateDirectory) rmdir /S /Q $(IntermediateDirectory)


