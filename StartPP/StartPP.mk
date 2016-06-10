##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=StartPP
ConfigurationName      :=Debug
WorkspacePath          :=C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP
ProjectPath            :=C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=dmitry.tsvetkov
Date                   :=10/06/2016
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/TDM-GCC-64/bin/g++.exe
SharedObjectLinkerName :=C:/TDM-GCC-64/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)WX $(PreprocessorSwitch)_MAX_PATH=260 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="StartPP.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := $(shell /usr/local/lib/wx-config --rcflags)
RcCompilerName         :=C:/TDM-GCC-64/bin/windres.exe
LinkOptions            :=  $(shell /usr/local/bin/wx-config --libs) -stdlib=libstdc++
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)/usr/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)wx_gtk3u_propgrid-3.1 $(LibrarySwitch)wx_gtk3u_aui-3.1 $(LibrarySwitch)wx_gtk3u_gl-3.1 $(LibrarySwitch)GL $(LibrarySwitch)GLU 
ArLibs                 :=  "wx_gtk3u_propgrid-3.1" "wx_gtk3u_aui-3.1" "wx_gtk3u_gl-3.1" "GL" "GLU" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/TDM-GCC-64/bin/ar.exe rcu
CXX      := C:/TDM-GCC-64/bin/g++.exe
CC       := C:/TDM-GCC-64/bin/gcc.exe
CXXFLAGS :=  -g -O0 -std=c++11 $(shell /usr/local/bin/wx-config --cflags) $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/TDM-GCC-64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix) $(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix) $(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix) $(IntermediateDirectory)/PropertiesWnd.cpp$(ObjectSuffix) $(IntermediateDirectory)/Recordset.cpp$(ObjectSuffix) $(IntermediateDirectory)/PipesSet.cpp$(ObjectSuffix) $(IntermediateDirectory)/MySet.cpp$(ObjectSuffix) $(IntermediateDirectory)/Material.cpp$(ObjectSuffix) $(IntermediateDirectory)/ArmatSet.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/StartPPDocWx.cpp$(ObjectSuffix) $(IntermediateDirectory)/TroinicsSet.cpp$(ObjectSuffix) $(IntermediateDirectory)/PipeAndNode.cpp$(ObjectSuffix) $(IntermediateDirectory)/PipeArray.cpp$(ObjectSuffix) $(IntermediateDirectory)/Rotate.cpp$(ObjectSuffix) $(IntermediateDirectory)/StartPPSet.cpp$(ObjectSuffix) $(IntermediateDirectory)/TempHistory.cpp$(ObjectSuffix) $(IntermediateDirectory)/PipeDesc.cpp$(ObjectSuffix) $(IntermediateDirectory)/dbf_wx.cpp$(ObjectSuffix) $(IntermediateDirectory)/wx_src_wxstreamc.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/dbf.c$(ObjectSuffix) $(IntermediateDirectory)/ioapi_ioapi.c$(ObjectSuffix) $(IntermediateDirectory)/Archive.cpp$(ObjectSuffix) $(IntermediateDirectory)/ScreenPipePresenter.cpp$(ObjectSuffix) $(IntermediateDirectory)/PipePresenter.cpp$(ObjectSuffix) $(IntermediateDirectory)/StartPPView.cpp$(ObjectSuffix) $(IntermediateDirectory)/OGLPipePresenter.cpp$(ObjectSuffix) $(IntermediateDirectory)/GLRenderer.cpp$(ObjectSuffix) $(IntermediateDirectory)/HSV2RGB.cpp$(ObjectSuffix) $(IntermediateDirectory)/win_resources.rc$(ObjectSuffix) \
	$(IntermediateDirectory)/StartPP.rc$(ObjectSuffix) 



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
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix): MainFrame.cpp $(IntermediateDirectory)/MainFrame.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/MainFrame.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MainFrame.cpp$(DependSuffix): MainFrame.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MainFrame.cpp$(DependSuffix) -MM "MainFrame.cpp"

$(IntermediateDirectory)/MainFrame.cpp$(PreprocessSuffix): MainFrame.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MainFrame.cpp$(PreprocessSuffix) "MainFrame.cpp"

$(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix): wxcrafter.cpp $(IntermediateDirectory)/wxcrafter.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/wxcrafter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wxcrafter.cpp$(DependSuffix): wxcrafter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/wxcrafter.cpp$(DependSuffix) -MM "wxcrafter.cpp"

$(IntermediateDirectory)/wxcrafter.cpp$(PreprocessSuffix): wxcrafter.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wxcrafter.cpp$(PreprocessSuffix) "wxcrafter.cpp"

$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix): wxcrafter_bitmaps.cpp $(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/wxcrafter_bitmaps.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(DependSuffix): wxcrafter_bitmaps.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(DependSuffix) -MM "wxcrafter_bitmaps.cpp"

$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(PreprocessSuffix): wxcrafter_bitmaps.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(PreprocessSuffix) "wxcrafter_bitmaps.cpp"

$(IntermediateDirectory)/PropertiesWnd.cpp$(ObjectSuffix): PropertiesWnd.cpp $(IntermediateDirectory)/PropertiesWnd.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/PropertiesWnd.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PropertiesWnd.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PropertiesWnd.cpp$(DependSuffix): PropertiesWnd.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PropertiesWnd.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/PropertiesWnd.cpp$(DependSuffix) -MM "PropertiesWnd.cpp"

$(IntermediateDirectory)/PropertiesWnd.cpp$(PreprocessSuffix): PropertiesWnd.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PropertiesWnd.cpp$(PreprocessSuffix) "PropertiesWnd.cpp"

$(IntermediateDirectory)/Recordset.cpp$(ObjectSuffix): Recordset.cpp $(IntermediateDirectory)/Recordset.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/Recordset.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Recordset.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Recordset.cpp$(DependSuffix): Recordset.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Recordset.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Recordset.cpp$(DependSuffix) -MM "Recordset.cpp"

$(IntermediateDirectory)/Recordset.cpp$(PreprocessSuffix): Recordset.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Recordset.cpp$(PreprocessSuffix) "Recordset.cpp"

$(IntermediateDirectory)/PipesSet.cpp$(ObjectSuffix): PipesSet.cpp $(IntermediateDirectory)/PipesSet.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/PipesSet.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PipesSet.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PipesSet.cpp$(DependSuffix): PipesSet.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PipesSet.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/PipesSet.cpp$(DependSuffix) -MM "PipesSet.cpp"

$(IntermediateDirectory)/PipesSet.cpp$(PreprocessSuffix): PipesSet.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PipesSet.cpp$(PreprocessSuffix) "PipesSet.cpp"

$(IntermediateDirectory)/MySet.cpp$(ObjectSuffix): MySet.cpp $(IntermediateDirectory)/MySet.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/MySet.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MySet.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MySet.cpp$(DependSuffix): MySet.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MySet.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MySet.cpp$(DependSuffix) -MM "MySet.cpp"

$(IntermediateDirectory)/MySet.cpp$(PreprocessSuffix): MySet.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MySet.cpp$(PreprocessSuffix) "MySet.cpp"

$(IntermediateDirectory)/Material.cpp$(ObjectSuffix): Material.cpp $(IntermediateDirectory)/Material.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/Material.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Material.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Material.cpp$(DependSuffix): Material.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Material.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Material.cpp$(DependSuffix) -MM "Material.cpp"

$(IntermediateDirectory)/Material.cpp$(PreprocessSuffix): Material.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Material.cpp$(PreprocessSuffix) "Material.cpp"

$(IntermediateDirectory)/ArmatSet.cpp$(ObjectSuffix): ArmatSet.cpp $(IntermediateDirectory)/ArmatSet.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/ArmatSet.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ArmatSet.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ArmatSet.cpp$(DependSuffix): ArmatSet.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ArmatSet.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ArmatSet.cpp$(DependSuffix) -MM "ArmatSet.cpp"

$(IntermediateDirectory)/ArmatSet.cpp$(PreprocessSuffix): ArmatSet.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ArmatSet.cpp$(PreprocessSuffix) "ArmatSet.cpp"

$(IntermediateDirectory)/StartPPDocWx.cpp$(ObjectSuffix): StartPPDocWx.cpp $(IntermediateDirectory)/StartPPDocWx.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/StartPPDocWx.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/StartPPDocWx.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/StartPPDocWx.cpp$(DependSuffix): StartPPDocWx.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/StartPPDocWx.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/StartPPDocWx.cpp$(DependSuffix) -MM "StartPPDocWx.cpp"

$(IntermediateDirectory)/StartPPDocWx.cpp$(PreprocessSuffix): StartPPDocWx.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/StartPPDocWx.cpp$(PreprocessSuffix) "StartPPDocWx.cpp"

$(IntermediateDirectory)/TroinicsSet.cpp$(ObjectSuffix): TroinicsSet.cpp $(IntermediateDirectory)/TroinicsSet.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/TroinicsSet.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TroinicsSet.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TroinicsSet.cpp$(DependSuffix): TroinicsSet.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TroinicsSet.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TroinicsSet.cpp$(DependSuffix) -MM "TroinicsSet.cpp"

$(IntermediateDirectory)/TroinicsSet.cpp$(PreprocessSuffix): TroinicsSet.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TroinicsSet.cpp$(PreprocessSuffix) "TroinicsSet.cpp"

$(IntermediateDirectory)/PipeAndNode.cpp$(ObjectSuffix): PipeAndNode.cpp $(IntermediateDirectory)/PipeAndNode.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/PipeAndNode.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PipeAndNode.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PipeAndNode.cpp$(DependSuffix): PipeAndNode.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PipeAndNode.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/PipeAndNode.cpp$(DependSuffix) -MM "PipeAndNode.cpp"

$(IntermediateDirectory)/PipeAndNode.cpp$(PreprocessSuffix): PipeAndNode.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PipeAndNode.cpp$(PreprocessSuffix) "PipeAndNode.cpp"

$(IntermediateDirectory)/PipeArray.cpp$(ObjectSuffix): PipeArray.cpp $(IntermediateDirectory)/PipeArray.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/PipeArray.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PipeArray.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PipeArray.cpp$(DependSuffix): PipeArray.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PipeArray.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/PipeArray.cpp$(DependSuffix) -MM "PipeArray.cpp"

$(IntermediateDirectory)/PipeArray.cpp$(PreprocessSuffix): PipeArray.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PipeArray.cpp$(PreprocessSuffix) "PipeArray.cpp"

$(IntermediateDirectory)/Rotate.cpp$(ObjectSuffix): Rotate.cpp $(IntermediateDirectory)/Rotate.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/Rotate.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Rotate.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Rotate.cpp$(DependSuffix): Rotate.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Rotate.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Rotate.cpp$(DependSuffix) -MM "Rotate.cpp"

$(IntermediateDirectory)/Rotate.cpp$(PreprocessSuffix): Rotate.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Rotate.cpp$(PreprocessSuffix) "Rotate.cpp"

$(IntermediateDirectory)/StartPPSet.cpp$(ObjectSuffix): StartPPSet.cpp $(IntermediateDirectory)/StartPPSet.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/StartPPSet.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/StartPPSet.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/StartPPSet.cpp$(DependSuffix): StartPPSet.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/StartPPSet.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/StartPPSet.cpp$(DependSuffix) -MM "StartPPSet.cpp"

$(IntermediateDirectory)/StartPPSet.cpp$(PreprocessSuffix): StartPPSet.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/StartPPSet.cpp$(PreprocessSuffix) "StartPPSet.cpp"

$(IntermediateDirectory)/TempHistory.cpp$(ObjectSuffix): TempHistory.cpp $(IntermediateDirectory)/TempHistory.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/TempHistory.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TempHistory.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TempHistory.cpp$(DependSuffix): TempHistory.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TempHistory.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TempHistory.cpp$(DependSuffix) -MM "TempHistory.cpp"

$(IntermediateDirectory)/TempHistory.cpp$(PreprocessSuffix): TempHistory.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TempHistory.cpp$(PreprocessSuffix) "TempHistory.cpp"

$(IntermediateDirectory)/PipeDesc.cpp$(ObjectSuffix): PipeDesc.cpp $(IntermediateDirectory)/PipeDesc.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/PipeDesc.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PipeDesc.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PipeDesc.cpp$(DependSuffix): PipeDesc.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PipeDesc.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/PipeDesc.cpp$(DependSuffix) -MM "PipeDesc.cpp"

$(IntermediateDirectory)/PipeDesc.cpp$(PreprocessSuffix): PipeDesc.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PipeDesc.cpp$(PreprocessSuffix) "PipeDesc.cpp"

$(IntermediateDirectory)/dbf_wx.cpp$(ObjectSuffix): dbf_wx.cpp $(IntermediateDirectory)/dbf_wx.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/dbf_wx.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/dbf_wx.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dbf_wx.cpp$(DependSuffix): dbf_wx.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/dbf_wx.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/dbf_wx.cpp$(DependSuffix) -MM "dbf_wx.cpp"

$(IntermediateDirectory)/dbf_wx.cpp$(PreprocessSuffix): dbf_wx.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/dbf_wx.cpp$(PreprocessSuffix) "dbf_wx.cpp"

$(IntermediateDirectory)/wx_src_wxstreamc.cpp$(ObjectSuffix): wx/src/wxstreamc.cpp $(IntermediateDirectory)/wx_src_wxstreamc.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/wx/src/wxstreamc.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wx_src_wxstreamc.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wx_src_wxstreamc.cpp$(DependSuffix): wx/src/wxstreamc.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wx_src_wxstreamc.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/wx_src_wxstreamc.cpp$(DependSuffix) -MM "wx/src/wxstreamc.cpp"

$(IntermediateDirectory)/wx_src_wxstreamc.cpp$(PreprocessSuffix): wx/src/wxstreamc.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wx_src_wxstreamc.cpp$(PreprocessSuffix) "wx/src/wxstreamc.cpp"

$(IntermediateDirectory)/dbf.c$(ObjectSuffix): dbf.c $(IntermediateDirectory)/dbf.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/dbf.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/dbf.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dbf.c$(DependSuffix): dbf.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/dbf.c$(ObjectSuffix) -MF$(IntermediateDirectory)/dbf.c$(DependSuffix) -MM "dbf.c"

$(IntermediateDirectory)/dbf.c$(PreprocessSuffix): dbf.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/dbf.c$(PreprocessSuffix) "dbf.c"

$(IntermediateDirectory)/ioapi_ioapi.c$(ObjectSuffix): ioapi/ioapi.c $(IntermediateDirectory)/ioapi_ioapi.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/ioapi/ioapi.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ioapi_ioapi.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ioapi_ioapi.c$(DependSuffix): ioapi/ioapi.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ioapi_ioapi.c$(ObjectSuffix) -MF$(IntermediateDirectory)/ioapi_ioapi.c$(DependSuffix) -MM "ioapi/ioapi.c"

$(IntermediateDirectory)/ioapi_ioapi.c$(PreprocessSuffix): ioapi/ioapi.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ioapi_ioapi.c$(PreprocessSuffix) "ioapi/ioapi.c"

$(IntermediateDirectory)/Archive.cpp$(ObjectSuffix): Archive.cpp $(IntermediateDirectory)/Archive.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/Archive.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Archive.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Archive.cpp$(DependSuffix): Archive.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Archive.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Archive.cpp$(DependSuffix) -MM "Archive.cpp"

$(IntermediateDirectory)/Archive.cpp$(PreprocessSuffix): Archive.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Archive.cpp$(PreprocessSuffix) "Archive.cpp"

$(IntermediateDirectory)/ScreenPipePresenter.cpp$(ObjectSuffix): ScreenPipePresenter.cpp $(IntermediateDirectory)/ScreenPipePresenter.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/ScreenPipePresenter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ScreenPipePresenter.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ScreenPipePresenter.cpp$(DependSuffix): ScreenPipePresenter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ScreenPipePresenter.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ScreenPipePresenter.cpp$(DependSuffix) -MM "ScreenPipePresenter.cpp"

$(IntermediateDirectory)/ScreenPipePresenter.cpp$(PreprocessSuffix): ScreenPipePresenter.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ScreenPipePresenter.cpp$(PreprocessSuffix) "ScreenPipePresenter.cpp"

$(IntermediateDirectory)/PipePresenter.cpp$(ObjectSuffix): PipePresenter.cpp $(IntermediateDirectory)/PipePresenter.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/PipePresenter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PipePresenter.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PipePresenter.cpp$(DependSuffix): PipePresenter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PipePresenter.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/PipePresenter.cpp$(DependSuffix) -MM "PipePresenter.cpp"

$(IntermediateDirectory)/PipePresenter.cpp$(PreprocessSuffix): PipePresenter.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PipePresenter.cpp$(PreprocessSuffix) "PipePresenter.cpp"

$(IntermediateDirectory)/StartPPView.cpp$(ObjectSuffix): StartPPView.cpp $(IntermediateDirectory)/StartPPView.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/StartPPView.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/StartPPView.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/StartPPView.cpp$(DependSuffix): StartPPView.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/StartPPView.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/StartPPView.cpp$(DependSuffix) -MM "StartPPView.cpp"

$(IntermediateDirectory)/StartPPView.cpp$(PreprocessSuffix): StartPPView.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/StartPPView.cpp$(PreprocessSuffix) "StartPPView.cpp"

$(IntermediateDirectory)/OGLPipePresenter.cpp$(ObjectSuffix): OGLPipePresenter.cpp $(IntermediateDirectory)/OGLPipePresenter.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/OGLPipePresenter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/OGLPipePresenter.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/OGLPipePresenter.cpp$(DependSuffix): OGLPipePresenter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/OGLPipePresenter.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/OGLPipePresenter.cpp$(DependSuffix) -MM "OGLPipePresenter.cpp"

$(IntermediateDirectory)/OGLPipePresenter.cpp$(PreprocessSuffix): OGLPipePresenter.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/OGLPipePresenter.cpp$(PreprocessSuffix) "OGLPipePresenter.cpp"

$(IntermediateDirectory)/GLRenderer.cpp$(ObjectSuffix): GLRenderer.cpp $(IntermediateDirectory)/GLRenderer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/GLRenderer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GLRenderer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GLRenderer.cpp$(DependSuffix): GLRenderer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GLRenderer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/GLRenderer.cpp$(DependSuffix) -MM "GLRenderer.cpp"

$(IntermediateDirectory)/GLRenderer.cpp$(PreprocessSuffix): GLRenderer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GLRenderer.cpp$(PreprocessSuffix) "GLRenderer.cpp"

$(IntermediateDirectory)/HSV2RGB.cpp$(ObjectSuffix): HSV2RGB.cpp $(IntermediateDirectory)/HSV2RGB.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/HSV2RGB.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/HSV2RGB.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/HSV2RGB.cpp$(DependSuffix): HSV2RGB.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/HSV2RGB.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/HSV2RGB.cpp$(DependSuffix) -MM "HSV2RGB.cpp"

$(IntermediateDirectory)/HSV2RGB.cpp$(PreprocessSuffix): HSV2RGB.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/HSV2RGB.cpp$(PreprocessSuffix) "HSV2RGB.cpp"

$(IntermediateDirectory)/win_resources.rc$(ObjectSuffix): win_resources.rc
	$(RcCompilerName) -i "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/win_resources.rc" $(RcCmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/win_resources.rc$(ObjectSuffix) $(RcIncludePath)
$(IntermediateDirectory)/StartPP.rc$(ObjectSuffix): StartPP.rc
	$(RcCompilerName) -i "C:/Users/dmitry.tsvetkov/Documents/GitHub/StartPP/StartPP/StartPP.rc" $(RcCmpOptions)   $(ObjectSwitch)$(IntermediateDirectory)/StartPP.rc$(ObjectSuffix) $(RcIncludePath)

-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


