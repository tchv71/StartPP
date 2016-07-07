##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=StartPP
ConfigurationName      :=Debug
WorkspacePath          :=/home/tchv/StartPP/StartPP
ProjectPath            :=/home/tchv/StartPP/StartPP
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=tchv
Date                   :=04/07/16
CodeLitePath           :=/home/tchv/.codelite
LinkerName             :=/usr/bin/clang++
SharedObjectLinkerName :=/usr/bin/clang++ -shared -fPIC
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
MakeDirCommand         :=mkdir -p
LinkOptions            :=  $(shell /usr/local/bin/wx-config --libs) -stdlib=libstdc++
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)/usr/include $(IncludeSwitch)/usr/include/freetype2 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)wx_gtk3u_propgrid-3.1 $(LibrarySwitch)wx_gtk3u_aui-3.1 $(LibrarySwitch)wx_gtk3u_gl-3.1 $(LibrarySwitch)GL $(LibrarySwitch)GLU $(LibrarySwitch)ftgl 
ArLibs                 :=  "wx_gtk3u_propgrid-3.1" "wx_gtk3u_aui-3.1" "wx_gtk3u_gl-3.1" "GL" "GLU" "ftgl" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/clang++
CC       := /usr/bin/clang
CXXFLAGS :=  -g -O0 -std=c++11 $(shell /usr/local/bin/wx-config --cflags) $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix) $(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix) $(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix) $(IntermediateDirectory)/PropertiesWnd.cpp$(ObjectSuffix) $(IntermediateDirectory)/Recordset.cpp$(ObjectSuffix) $(IntermediateDirectory)/PipesSet.cpp$(ObjectSuffix) $(IntermediateDirectory)/MySet.cpp$(ObjectSuffix) $(IntermediateDirectory)/Material.cpp$(ObjectSuffix) $(IntermediateDirectory)/ArmatSet.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/StartPPDocWx.cpp$(ObjectSuffix) $(IntermediateDirectory)/TroinicsSet.cpp$(ObjectSuffix) $(IntermediateDirectory)/PipeAndNode.cpp$(ObjectSuffix) $(IntermediateDirectory)/PipeArray.cpp$(ObjectSuffix) $(IntermediateDirectory)/Rotate.cpp$(ObjectSuffix) $(IntermediateDirectory)/StartPPSet.cpp$(ObjectSuffix) $(IntermediateDirectory)/TempHistory.cpp$(ObjectSuffix) $(IntermediateDirectory)/PipeDesc.cpp$(ObjectSuffix) $(IntermediateDirectory)/dbf_wx.cpp$(ObjectSuffix) $(IntermediateDirectory)/wx_src_wxstreamc.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/dbf.c$(ObjectSuffix) $(IntermediateDirectory)/ioapi_ioapi.c$(ObjectSuffix) $(IntermediateDirectory)/Archive.cpp$(ObjectSuffix) $(IntermediateDirectory)/ScreenPipePresenter.cpp$(ObjectSuffix) $(IntermediateDirectory)/PipePresenter.cpp$(ObjectSuffix) $(IntermediateDirectory)/StartPPView.cpp$(ObjectSuffix) $(IntermediateDirectory)/OGLPipePresenter.cpp$(ObjectSuffix) $(IntermediateDirectory)/GLRenderer.cpp$(ObjectSuffix) $(IntermediateDirectory)/HSV2RGB.cpp$(ObjectSuffix) $(IntermediateDirectory)/PrintHelper.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/NewPipeDialog.cpp$(ObjectSuffix) $(IntermediateDirectory)/Pipe.cpp$(ObjectSuffix) $(IntermediateDirectory)/DelPipesDialog.cpp$(ObjectSuffix) $(IntermediateDirectory)/MultPipeDialog.cpp$(ObjectSuffix) $(IntermediateDirectory)/NewNodeDialog.cpp$(ObjectSuffix) $(IntermediateDirectory)/CopyParamsDialog.cpp$(ObjectSuffix) $(IntermediateDirectory)/MoveNodeDialog.cpp$(ObjectSuffix) $(IntermediateDirectory)/VecPnN.cpp$(ObjectSuffix) $(IntermediateDirectory)/SpuskDialog.cpp$(ObjectSuffix) 



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
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix): MainFrame.cpp $(IntermediateDirectory)/MainFrame.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/MainFrame.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MainFrame.cpp$(DependSuffix): MainFrame.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MainFrame.cpp$(DependSuffix) -MM "MainFrame.cpp"

$(IntermediateDirectory)/MainFrame.cpp$(PreprocessSuffix): MainFrame.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MainFrame.cpp$(PreprocessSuffix) "MainFrame.cpp"

$(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix): wxcrafter.cpp $(IntermediateDirectory)/wxcrafter.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/wxcrafter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wxcrafter.cpp$(DependSuffix): wxcrafter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/wxcrafter.cpp$(DependSuffix) -MM "wxcrafter.cpp"

$(IntermediateDirectory)/wxcrafter.cpp$(PreprocessSuffix): wxcrafter.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wxcrafter.cpp$(PreprocessSuffix) "wxcrafter.cpp"

$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix): wxcrafter_bitmaps.cpp $(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/wxcrafter_bitmaps.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(DependSuffix): wxcrafter_bitmaps.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(DependSuffix) -MM "wxcrafter_bitmaps.cpp"

$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(PreprocessSuffix): wxcrafter_bitmaps.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(PreprocessSuffix) "wxcrafter_bitmaps.cpp"

$(IntermediateDirectory)/PropertiesWnd.cpp$(ObjectSuffix): PropertiesWnd.cpp $(IntermediateDirectory)/PropertiesWnd.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/PropertiesWnd.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PropertiesWnd.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PropertiesWnd.cpp$(DependSuffix): PropertiesWnd.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PropertiesWnd.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/PropertiesWnd.cpp$(DependSuffix) -MM "PropertiesWnd.cpp"

$(IntermediateDirectory)/PropertiesWnd.cpp$(PreprocessSuffix): PropertiesWnd.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PropertiesWnd.cpp$(PreprocessSuffix) "PropertiesWnd.cpp"

$(IntermediateDirectory)/Recordset.cpp$(ObjectSuffix): Recordset.cpp $(IntermediateDirectory)/Recordset.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/Recordset.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Recordset.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Recordset.cpp$(DependSuffix): Recordset.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Recordset.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Recordset.cpp$(DependSuffix) -MM "Recordset.cpp"

$(IntermediateDirectory)/Recordset.cpp$(PreprocessSuffix): Recordset.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Recordset.cpp$(PreprocessSuffix) "Recordset.cpp"

$(IntermediateDirectory)/PipesSet.cpp$(ObjectSuffix): PipesSet.cpp $(IntermediateDirectory)/PipesSet.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/PipesSet.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PipesSet.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PipesSet.cpp$(DependSuffix): PipesSet.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PipesSet.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/PipesSet.cpp$(DependSuffix) -MM "PipesSet.cpp"

$(IntermediateDirectory)/PipesSet.cpp$(PreprocessSuffix): PipesSet.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PipesSet.cpp$(PreprocessSuffix) "PipesSet.cpp"

$(IntermediateDirectory)/MySet.cpp$(ObjectSuffix): MySet.cpp $(IntermediateDirectory)/MySet.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/MySet.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MySet.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MySet.cpp$(DependSuffix): MySet.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MySet.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MySet.cpp$(DependSuffix) -MM "MySet.cpp"

$(IntermediateDirectory)/MySet.cpp$(PreprocessSuffix): MySet.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MySet.cpp$(PreprocessSuffix) "MySet.cpp"

$(IntermediateDirectory)/Material.cpp$(ObjectSuffix): Material.cpp $(IntermediateDirectory)/Material.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/Material.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Material.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Material.cpp$(DependSuffix): Material.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Material.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Material.cpp$(DependSuffix) -MM "Material.cpp"

$(IntermediateDirectory)/Material.cpp$(PreprocessSuffix): Material.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Material.cpp$(PreprocessSuffix) "Material.cpp"

$(IntermediateDirectory)/ArmatSet.cpp$(ObjectSuffix): ArmatSet.cpp $(IntermediateDirectory)/ArmatSet.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/ArmatSet.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ArmatSet.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ArmatSet.cpp$(DependSuffix): ArmatSet.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ArmatSet.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ArmatSet.cpp$(DependSuffix) -MM "ArmatSet.cpp"

$(IntermediateDirectory)/ArmatSet.cpp$(PreprocessSuffix): ArmatSet.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ArmatSet.cpp$(PreprocessSuffix) "ArmatSet.cpp"

$(IntermediateDirectory)/StartPPDocWx.cpp$(ObjectSuffix): StartPPDocWx.cpp $(IntermediateDirectory)/StartPPDocWx.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/StartPPDocWx.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/StartPPDocWx.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/StartPPDocWx.cpp$(DependSuffix): StartPPDocWx.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/StartPPDocWx.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/StartPPDocWx.cpp$(DependSuffix) -MM "StartPPDocWx.cpp"

$(IntermediateDirectory)/StartPPDocWx.cpp$(PreprocessSuffix): StartPPDocWx.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/StartPPDocWx.cpp$(PreprocessSuffix) "StartPPDocWx.cpp"

$(IntermediateDirectory)/TroinicsSet.cpp$(ObjectSuffix): TroinicsSet.cpp $(IntermediateDirectory)/TroinicsSet.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/TroinicsSet.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TroinicsSet.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TroinicsSet.cpp$(DependSuffix): TroinicsSet.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TroinicsSet.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TroinicsSet.cpp$(DependSuffix) -MM "TroinicsSet.cpp"

$(IntermediateDirectory)/TroinicsSet.cpp$(PreprocessSuffix): TroinicsSet.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TroinicsSet.cpp$(PreprocessSuffix) "TroinicsSet.cpp"

$(IntermediateDirectory)/PipeAndNode.cpp$(ObjectSuffix): PipeAndNode.cpp $(IntermediateDirectory)/PipeAndNode.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/PipeAndNode.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PipeAndNode.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PipeAndNode.cpp$(DependSuffix): PipeAndNode.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PipeAndNode.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/PipeAndNode.cpp$(DependSuffix) -MM "PipeAndNode.cpp"

$(IntermediateDirectory)/PipeAndNode.cpp$(PreprocessSuffix): PipeAndNode.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PipeAndNode.cpp$(PreprocessSuffix) "PipeAndNode.cpp"

$(IntermediateDirectory)/PipeArray.cpp$(ObjectSuffix): PipeArray.cpp $(IntermediateDirectory)/PipeArray.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/PipeArray.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PipeArray.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PipeArray.cpp$(DependSuffix): PipeArray.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PipeArray.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/PipeArray.cpp$(DependSuffix) -MM "PipeArray.cpp"

$(IntermediateDirectory)/PipeArray.cpp$(PreprocessSuffix): PipeArray.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PipeArray.cpp$(PreprocessSuffix) "PipeArray.cpp"

$(IntermediateDirectory)/Rotate.cpp$(ObjectSuffix): Rotate.cpp $(IntermediateDirectory)/Rotate.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/Rotate.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Rotate.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Rotate.cpp$(DependSuffix): Rotate.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Rotate.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Rotate.cpp$(DependSuffix) -MM "Rotate.cpp"

$(IntermediateDirectory)/Rotate.cpp$(PreprocessSuffix): Rotate.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Rotate.cpp$(PreprocessSuffix) "Rotate.cpp"

$(IntermediateDirectory)/StartPPSet.cpp$(ObjectSuffix): StartPPSet.cpp $(IntermediateDirectory)/StartPPSet.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/StartPPSet.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/StartPPSet.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/StartPPSet.cpp$(DependSuffix): StartPPSet.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/StartPPSet.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/StartPPSet.cpp$(DependSuffix) -MM "StartPPSet.cpp"

$(IntermediateDirectory)/StartPPSet.cpp$(PreprocessSuffix): StartPPSet.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/StartPPSet.cpp$(PreprocessSuffix) "StartPPSet.cpp"

$(IntermediateDirectory)/TempHistory.cpp$(ObjectSuffix): TempHistory.cpp $(IntermediateDirectory)/TempHistory.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/TempHistory.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TempHistory.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TempHistory.cpp$(DependSuffix): TempHistory.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TempHistory.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TempHistory.cpp$(DependSuffix) -MM "TempHistory.cpp"

$(IntermediateDirectory)/TempHistory.cpp$(PreprocessSuffix): TempHistory.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TempHistory.cpp$(PreprocessSuffix) "TempHistory.cpp"

$(IntermediateDirectory)/PipeDesc.cpp$(ObjectSuffix): PipeDesc.cpp $(IntermediateDirectory)/PipeDesc.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/PipeDesc.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PipeDesc.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PipeDesc.cpp$(DependSuffix): PipeDesc.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PipeDesc.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/PipeDesc.cpp$(DependSuffix) -MM "PipeDesc.cpp"

$(IntermediateDirectory)/PipeDesc.cpp$(PreprocessSuffix): PipeDesc.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PipeDesc.cpp$(PreprocessSuffix) "PipeDesc.cpp"

$(IntermediateDirectory)/dbf_wx.cpp$(ObjectSuffix): dbf_wx.cpp $(IntermediateDirectory)/dbf_wx.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/dbf_wx.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/dbf_wx.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dbf_wx.cpp$(DependSuffix): dbf_wx.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/dbf_wx.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/dbf_wx.cpp$(DependSuffix) -MM "dbf_wx.cpp"

$(IntermediateDirectory)/dbf_wx.cpp$(PreprocessSuffix): dbf_wx.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/dbf_wx.cpp$(PreprocessSuffix) "dbf_wx.cpp"

$(IntermediateDirectory)/wx_src_wxstreamc.cpp$(ObjectSuffix): wx/src/wxstreamc.cpp $(IntermediateDirectory)/wx_src_wxstreamc.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/wx/src/wxstreamc.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wx_src_wxstreamc.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wx_src_wxstreamc.cpp$(DependSuffix): wx/src/wxstreamc.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wx_src_wxstreamc.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/wx_src_wxstreamc.cpp$(DependSuffix) -MM "wx/src/wxstreamc.cpp"

$(IntermediateDirectory)/wx_src_wxstreamc.cpp$(PreprocessSuffix): wx/src/wxstreamc.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wx_src_wxstreamc.cpp$(PreprocessSuffix) "wx/src/wxstreamc.cpp"

$(IntermediateDirectory)/dbf.c$(ObjectSuffix): dbf.c $(IntermediateDirectory)/dbf.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/tchv/StartPP/StartPP/dbf.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/dbf.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dbf.c$(DependSuffix): dbf.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/dbf.c$(ObjectSuffix) -MF$(IntermediateDirectory)/dbf.c$(DependSuffix) -MM "dbf.c"

$(IntermediateDirectory)/dbf.c$(PreprocessSuffix): dbf.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/dbf.c$(PreprocessSuffix) "dbf.c"

$(IntermediateDirectory)/ioapi_ioapi.c$(ObjectSuffix): ioapi/ioapi.c $(IntermediateDirectory)/ioapi_ioapi.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/tchv/StartPP/StartPP/ioapi/ioapi.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ioapi_ioapi.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ioapi_ioapi.c$(DependSuffix): ioapi/ioapi.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ioapi_ioapi.c$(ObjectSuffix) -MF$(IntermediateDirectory)/ioapi_ioapi.c$(DependSuffix) -MM "ioapi/ioapi.c"

$(IntermediateDirectory)/ioapi_ioapi.c$(PreprocessSuffix): ioapi/ioapi.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ioapi_ioapi.c$(PreprocessSuffix) "ioapi/ioapi.c"

$(IntermediateDirectory)/Archive.cpp$(ObjectSuffix): Archive.cpp $(IntermediateDirectory)/Archive.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/Archive.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Archive.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Archive.cpp$(DependSuffix): Archive.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Archive.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Archive.cpp$(DependSuffix) -MM "Archive.cpp"

$(IntermediateDirectory)/Archive.cpp$(PreprocessSuffix): Archive.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Archive.cpp$(PreprocessSuffix) "Archive.cpp"

$(IntermediateDirectory)/ScreenPipePresenter.cpp$(ObjectSuffix): ScreenPipePresenter.cpp $(IntermediateDirectory)/ScreenPipePresenter.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/ScreenPipePresenter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ScreenPipePresenter.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ScreenPipePresenter.cpp$(DependSuffix): ScreenPipePresenter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ScreenPipePresenter.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ScreenPipePresenter.cpp$(DependSuffix) -MM "ScreenPipePresenter.cpp"

$(IntermediateDirectory)/ScreenPipePresenter.cpp$(PreprocessSuffix): ScreenPipePresenter.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ScreenPipePresenter.cpp$(PreprocessSuffix) "ScreenPipePresenter.cpp"

$(IntermediateDirectory)/PipePresenter.cpp$(ObjectSuffix): PipePresenter.cpp $(IntermediateDirectory)/PipePresenter.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/PipePresenter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PipePresenter.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PipePresenter.cpp$(DependSuffix): PipePresenter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PipePresenter.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/PipePresenter.cpp$(DependSuffix) -MM "PipePresenter.cpp"

$(IntermediateDirectory)/PipePresenter.cpp$(PreprocessSuffix): PipePresenter.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PipePresenter.cpp$(PreprocessSuffix) "PipePresenter.cpp"

$(IntermediateDirectory)/StartPPView.cpp$(ObjectSuffix): StartPPView.cpp $(IntermediateDirectory)/StartPPView.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/StartPPView.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/StartPPView.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/StartPPView.cpp$(DependSuffix): StartPPView.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/StartPPView.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/StartPPView.cpp$(DependSuffix) -MM "StartPPView.cpp"

$(IntermediateDirectory)/StartPPView.cpp$(PreprocessSuffix): StartPPView.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/StartPPView.cpp$(PreprocessSuffix) "StartPPView.cpp"

$(IntermediateDirectory)/OGLPipePresenter.cpp$(ObjectSuffix): OGLPipePresenter.cpp $(IntermediateDirectory)/OGLPipePresenter.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/OGLPipePresenter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/OGLPipePresenter.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/OGLPipePresenter.cpp$(DependSuffix): OGLPipePresenter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/OGLPipePresenter.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/OGLPipePresenter.cpp$(DependSuffix) -MM "OGLPipePresenter.cpp"

$(IntermediateDirectory)/OGLPipePresenter.cpp$(PreprocessSuffix): OGLPipePresenter.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/OGLPipePresenter.cpp$(PreprocessSuffix) "OGLPipePresenter.cpp"

$(IntermediateDirectory)/GLRenderer.cpp$(ObjectSuffix): GLRenderer.cpp $(IntermediateDirectory)/GLRenderer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/GLRenderer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GLRenderer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GLRenderer.cpp$(DependSuffix): GLRenderer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GLRenderer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/GLRenderer.cpp$(DependSuffix) -MM "GLRenderer.cpp"

$(IntermediateDirectory)/GLRenderer.cpp$(PreprocessSuffix): GLRenderer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GLRenderer.cpp$(PreprocessSuffix) "GLRenderer.cpp"

$(IntermediateDirectory)/HSV2RGB.cpp$(ObjectSuffix): HSV2RGB.cpp $(IntermediateDirectory)/HSV2RGB.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/HSV2RGB.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/HSV2RGB.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/HSV2RGB.cpp$(DependSuffix): HSV2RGB.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/HSV2RGB.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/HSV2RGB.cpp$(DependSuffix) -MM "HSV2RGB.cpp"

$(IntermediateDirectory)/HSV2RGB.cpp$(PreprocessSuffix): HSV2RGB.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/HSV2RGB.cpp$(PreprocessSuffix) "HSV2RGB.cpp"

$(IntermediateDirectory)/PrintHelper.cpp$(ObjectSuffix): PrintHelper.cpp $(IntermediateDirectory)/PrintHelper.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/PrintHelper.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PrintHelper.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PrintHelper.cpp$(DependSuffix): PrintHelper.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PrintHelper.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/PrintHelper.cpp$(DependSuffix) -MM "PrintHelper.cpp"

$(IntermediateDirectory)/PrintHelper.cpp$(PreprocessSuffix): PrintHelper.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PrintHelper.cpp$(PreprocessSuffix) "PrintHelper.cpp"

$(IntermediateDirectory)/NewPipeDialog.cpp$(ObjectSuffix): NewPipeDialog.cpp $(IntermediateDirectory)/NewPipeDialog.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/NewPipeDialog.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/NewPipeDialog.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/NewPipeDialog.cpp$(DependSuffix): NewPipeDialog.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/NewPipeDialog.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/NewPipeDialog.cpp$(DependSuffix) -MM "NewPipeDialog.cpp"

$(IntermediateDirectory)/NewPipeDialog.cpp$(PreprocessSuffix): NewPipeDialog.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/NewPipeDialog.cpp$(PreprocessSuffix) "NewPipeDialog.cpp"

$(IntermediateDirectory)/Pipe.cpp$(ObjectSuffix): Pipe.cpp $(IntermediateDirectory)/Pipe.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/Pipe.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Pipe.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Pipe.cpp$(DependSuffix): Pipe.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Pipe.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Pipe.cpp$(DependSuffix) -MM "Pipe.cpp"

$(IntermediateDirectory)/Pipe.cpp$(PreprocessSuffix): Pipe.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Pipe.cpp$(PreprocessSuffix) "Pipe.cpp"

$(IntermediateDirectory)/DelPipesDialog.cpp$(ObjectSuffix): DelPipesDialog.cpp $(IntermediateDirectory)/DelPipesDialog.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/DelPipesDialog.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/DelPipesDialog.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/DelPipesDialog.cpp$(DependSuffix): DelPipesDialog.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/DelPipesDialog.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/DelPipesDialog.cpp$(DependSuffix) -MM "DelPipesDialog.cpp"

$(IntermediateDirectory)/DelPipesDialog.cpp$(PreprocessSuffix): DelPipesDialog.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/DelPipesDialog.cpp$(PreprocessSuffix) "DelPipesDialog.cpp"

$(IntermediateDirectory)/MultPipeDialog.cpp$(ObjectSuffix): MultPipeDialog.cpp $(IntermediateDirectory)/MultPipeDialog.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/MultPipeDialog.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MultPipeDialog.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MultPipeDialog.cpp$(DependSuffix): MultPipeDialog.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MultPipeDialog.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MultPipeDialog.cpp$(DependSuffix) -MM "MultPipeDialog.cpp"

$(IntermediateDirectory)/MultPipeDialog.cpp$(PreprocessSuffix): MultPipeDialog.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MultPipeDialog.cpp$(PreprocessSuffix) "MultPipeDialog.cpp"

$(IntermediateDirectory)/NewNodeDialog.cpp$(ObjectSuffix): NewNodeDialog.cpp $(IntermediateDirectory)/NewNodeDialog.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/NewNodeDialog.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/NewNodeDialog.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/NewNodeDialog.cpp$(DependSuffix): NewNodeDialog.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/NewNodeDialog.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/NewNodeDialog.cpp$(DependSuffix) -MM "NewNodeDialog.cpp"

$(IntermediateDirectory)/NewNodeDialog.cpp$(PreprocessSuffix): NewNodeDialog.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/NewNodeDialog.cpp$(PreprocessSuffix) "NewNodeDialog.cpp"

$(IntermediateDirectory)/CopyParamsDialog.cpp$(ObjectSuffix): CopyParamsDialog.cpp $(IntermediateDirectory)/CopyParamsDialog.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/CopyParamsDialog.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CopyParamsDialog.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CopyParamsDialog.cpp$(DependSuffix): CopyParamsDialog.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CopyParamsDialog.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/CopyParamsDialog.cpp$(DependSuffix) -MM "CopyParamsDialog.cpp"

$(IntermediateDirectory)/CopyParamsDialog.cpp$(PreprocessSuffix): CopyParamsDialog.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CopyParamsDialog.cpp$(PreprocessSuffix) "CopyParamsDialog.cpp"

$(IntermediateDirectory)/MoveNodeDialog.cpp$(ObjectSuffix): MoveNodeDialog.cpp $(IntermediateDirectory)/MoveNodeDialog.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/MoveNodeDialog.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MoveNodeDialog.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MoveNodeDialog.cpp$(DependSuffix): MoveNodeDialog.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MoveNodeDialog.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MoveNodeDialog.cpp$(DependSuffix) -MM "MoveNodeDialog.cpp"

$(IntermediateDirectory)/MoveNodeDialog.cpp$(PreprocessSuffix): MoveNodeDialog.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MoveNodeDialog.cpp$(PreprocessSuffix) "MoveNodeDialog.cpp"

$(IntermediateDirectory)/VecPnN.cpp$(ObjectSuffix): VecPnN.cpp $(IntermediateDirectory)/VecPnN.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/VecPnN.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/VecPnN.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/VecPnN.cpp$(DependSuffix): VecPnN.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/VecPnN.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/VecPnN.cpp$(DependSuffix) -MM "VecPnN.cpp"

$(IntermediateDirectory)/VecPnN.cpp$(PreprocessSuffix): VecPnN.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/VecPnN.cpp$(PreprocessSuffix) "VecPnN.cpp"

$(IntermediateDirectory)/SpuskDialog.cpp$(ObjectSuffix): SpuskDialog.cpp $(IntermediateDirectory)/SpuskDialog.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/tchv/StartPP/StartPP/SpuskDialog.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SpuskDialog.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SpuskDialog.cpp$(DependSuffix): SpuskDialog.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SpuskDialog.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SpuskDialog.cpp$(DependSuffix) -MM "SpuskDialog.cpp"

$(IntermediateDirectory)/SpuskDialog.cpp$(PreprocessSuffix): SpuskDialog.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SpuskDialog.cpp$(PreprocessSuffix) "SpuskDialog.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


