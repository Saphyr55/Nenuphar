module rec Nenuphar.Build.MSBuild.VSProject

open System.IO
open Microsoft.Build.Construction
open Nenuphar.Build.Project.Project


type MSCondition = string

type MSFile = string * FileType


type Platform =
    | Arm 
    | Arm64
    | X64 
    | X86
    | Win32
    

type TypeProject =
    | CSharp
    | FSharp
    | VisualCPP
    | None

    member this.ProjectExtension =
        match this with
        | VisualCPP -> ".vcxproj"
        | FSharp -> ".fsproj"
        | CSharp -> ".csproj"
        | None -> ".proj"


module MSBuildName = 
    
    let msItemFileTypeName = function
        | Source -> "ClCompile"
        | Header -> "ClInclude"
        | Image -> "Image"
        | _ -> "None"

    
    let msOutputTypeName = function
        | Shared -> "DynamicLibrary"
        | Static -> "StaticLibrary"
        | Executable -> "Application"

    
    let msBuildConfigurationName = function
        | Debug -> "Debug"
        | Release -> "Release"

    
    let msPlatformName = function
        | Arm -> "ARM32"
        | Arm64 -> "ARM64"
        | X64  -> "x64"
        | X86  -> "x86"
        | Win32 -> "Win32"


let vcxProjRoot (m: Module) : ProjectRootElement =

    let root = ProjectRootElement.Create()
    
    root           
    |> defaultVSConfiguration m  
    |> ignore

    root.AddItemGroup()
    |> appendFiles m.PrivateFiles
    |> ignore

    root.AddItemGroup()
    |> appendFiles m.PublicFiles
    |> ignore
    
    root
    |> appendMicrosoftCPPTarget
        
    root


let appendConfiguration
    (m: Module)
    (condition: MSCondition)
    (root: ProjectRootElement) =
    
    let outputTypeName = MSBuildName.msOutputTypeName m.OutputType
    let configuration  = root.AddPropertyGroup()

    configuration.Label <- "Configuration"
    configuration.Condition <- condition

    configuration.AddProperty("ConfigurationType", outputTypeName) |> ignore
    configuration.AddProperty("CharacterSet", "Unicode") |> ignore
    configuration.AddProperty("PlatformToolset", "v142") |> ignore

    root


let appendProjectConfiguration
    (buildConfiguration: BuildConfiguration)
    (architectureConfiguration: Platform)
    (projectConfigurations: ProjectItemGroupElement) =

    let archName =
        MSBuildName.msPlatformName architectureConfiguration
    
    let buildConfigurationName =
        MSBuildName.msBuildConfigurationName buildConfiguration

    let name = buildConfigurationName + "|" + archName 
    let projectConfiguration = projectConfigurations.AddItem("ProjectConfiguration", name)

    projectConfiguration.AddMetadata("Configuration", buildConfigurationName) |> ignore
    projectConfiguration.AddMetadata("Platform", archName) |> ignore

    projectConfigurations


let platformCondition build platform =
    let name = MSBuildName.msBuildConfigurationName build +
               "|" +
               MSBuildName.msPlatformName platform
    $"'$(Configuration)|$(Platform)'=='{name}'"


/// <summary>
/// Append the default configuration for visual studio. 
/// <see cref="https://learn.microsoft.com/fr-fr/cpp/build/reference/vcxproj-file-structure?view=msvc-170#vcxproj-file-elements"/>
/// </summary>>
let defaultVSConfiguration
    (m: Module)
    (root: ProjectRootElement)
    : ProjectRootElement =

    root.ToolsVersion <- "Current"
    root.DefaultTargets <- "Build"

    let ProjectConfigurations = root.AddItemGroup()
    ProjectConfigurations.Label <- "ProjectConfigurations"
    ProjectConfigurations
    |> appendProjectConfiguration Debug Win32
    |> appendProjectConfiguration Release Win32
    |> ignore
 
    let globals = root.AddPropertyGroup()
    let (ModuleName moduleName) = m.Name
    
    globals.Label <- "Globals"
    globals.AddProperty("ModuleName", moduleName) |> ignore

    ignore <|
    root.AddImport($"$(VCTargetsPath){Path.PathSeparator}Microsoft.Cpp.default.props")

    root
    |> appendConfiguration m (platformCondition Release Win32)
    |> appendConfiguration m (platformCondition Debug Win32)
    |> ignore

    root.AddImport("$(VCTargetsPath)\Microsoft.Cpp.props") |> ignore
    root.AddImportGroup().Label <- "ExtensionSettings"
    root.AddImportGroup().Label <- "PropertySheets"
    root.AddPropertyGroup().Label <- "UserMacros"
    
    root.AddPropertyGroup()
    |> appendBuildDir m Release Win32
    |> appendBuildDir m Debug Win32
    |> ignore

    root


let appendBuildDir
    (m: Module)
    (build: BuildConfiguration)
    (platform: Platform)
    (group: ProjectPropertyGroupElement) =
          
    
    let condition =
        platformCondition build platform
    
    let binariesPath =
        [| m.Project.BinariesLocation;
           MSBuildName.msBuildConfigurationName build;
           MSBuildName.msPlatformName platform; |]
        |> Path.Combine
        |> Path.GetFullPath

    group
        .AddProperty("OutDir", binariesPath)
        .Condition <- condition

    group
        .AddProperty("IntDir", binariesPath)
        .Condition <- condition

    group
        .AddProperty("LinkIncremental", "true")
        .Condition <- condition
    
    group


let appendMicrosoftCPPTarget
    (root: ProjectRootElement) =
    
    root.AddImport("$(VCTargetsPath)\Microsoft.Cpp.targets") |> ignore
    root.AddImportGroup().Label <- "ExtensionTargets"


let appendFiles
    (files: MSFile List)
    (itemGroup: ProjectItemGroupElement)
    : ProjectItemGroupElement =
 
    Seq.iter (fun (path, ft) -> begin
        
        let ft = MSBuildName.msItemFileTypeName ft
        let path = Path.GetFullPath path
        ignore <| itemGroup.AddItem(ft, path)
        
    end) files

    itemGroup


let saveModule
    (m: Module)
    (root: ProjectRootElement)
    (buildDir: Location)
    : unit =
    
    let (ModuleName moduleName) = m.Name
    let filename = moduleName + VisualCPP.ProjectExtension
    
    Path.Combine [|buildDir; moduleName; filename|]
    |> root.Save




    