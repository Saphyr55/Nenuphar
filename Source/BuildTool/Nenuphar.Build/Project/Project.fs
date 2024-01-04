module rec Nenuphar.Build.Project.NPProject

open System
open System.IO
open Nenuphar.Build.Project.ModuleBuildFile
open Nenuphar.Build.Project.NPBuildFileError


type Location = string

type Version = string


type BuildConfiguration =
    | Release
    | Debug


type OutputType =
    | Executable
    | Shared
    | Static


type FileType =
    | Source
    | Header
    | Image
    | None


    static member Extensions = 
        [| ("*.cpp", Source)
           ("*.hpp", Header)
           ("*.bmp", Image)
           ("*.png", Image)
           ("*.jpg", Image)
           ("*.jpeg", Image) |]


let PatternBuildToml = "*.Build.toml"

type ModuleName = ModuleName of string

type Module =
    { Name: ModuleName
      Location: Location
      OutputType: OutputType
      PrivateFiles: (Location * FileType) List
      PublicFiles: (Location * FileType) List
      Project: NenupharProject
      Dependencies : ModuleName List }     

    member m.PrivateFilesFirst =
         m.PrivateFiles
         |> Seq.map fst
         |> Seq.toList
    
    
    member m.PublicFilesFirst =
         m.PublicFiles
         |> Seq.map fst
         |> Seq.toList

                
    member m.PublicFolder =
        [|m.Location; "Public"|]
        |> Path.Combine
        |> Path.GetFullPath

    
    member m.PrivateFolder =
        [|m.Location; "Private"|]
        |> Path.Combine
        |> Path.GetFullPath


type NenupharProject =
    { Name: string
      Location: string
      BinariesLocation: Location
      OutputLocation: Location
      Version: Version option
      CPPVersion: Version option }        
    

    member this.Modules : Module List =
        
        Directory.EnumerateDirectories(this.Location)
        |> Seq.map this.buildFilesFromPath
        |> Seq.filter Option.isSome
        |> Seq.map Option.get
        |> Seq.map this.directoryToModule
        |> Seq.toList

    
    member private this.buildFilesFromPath path : ModuleBuildFile option =   
        
        let path = Path.GetFullPath path
        let buildFileToml =
            Directory.EnumerateFiles(path, PatternBuildToml)
            |> Seq.tryHead
            |> Option.map (interpretModuleBuildFile TomlFile)
            
        match buildFileToml with
        | Option.None -> Option.None
        | Some r ->
            match r with
            | Error errors ->
                logErrors errors.Value
                Option.None
            | Ok v -> Some v
        
        
        
    member private this.directoryToModule
        (buildFile: ModuleBuildFile) : Module =

        let directory = Path.GetFullPath (buildFile.Location)
        let moduleName = ModuleName buildFile.ModuleName

        let filesIn folder =
            let folder = Path.Combine [|directory; folder|]
            this.filesPattern folder FileType.Extensions

        let dependencies =
            buildFile.Dependencies
            |> Seq.map (fun (Dependency m) -> ModuleName m)
            |> Seq.toList
        
        let outputType =
            this.mapOutputTypeElement buildFile.OutputType
        
        { Name = moduleName
          OutputType = outputType
          Location = directory
          PrivateFiles = filesIn "Private"
          PublicFiles = filesIn "Public"
          Project = this
          Dependencies = dependencies }
    
    
    member _.mapOutputTypeElement = function
        | OutputTypeElement.Executable -> Executable
        | OutputTypeElement.Shared -> Shared
        | OutputTypeElement.Static -> Static

        
    member private this.filesPattern<'T>
        (directory: string)
        (patterns: (string * 'T) array)
        : (string * 'T) List =

        let files (pattern, t) =
            Directory.EnumerateFiles(
                    directory,
                    pattern,
                    SearchOption.AllDirectories
                )
            |> Seq.map (fun file -> file, t)
            
        patterns
        |> Seq.collect files
        |> Seq.toList
        

let wrapString (s: string) = $"\"{s}\""

let wrapModuleName (ModuleName name) = wrapString name

let wrapPath path =
    path
    |> wrapString
    |> (fun input -> begin
            match Environment.OSVersion.Platform with
            | PlatformID.Win32NT
            | PlatformID.Win32S
            | PlatformID.Win32Windows
            | PlatformID.WinCE -> input.Replace("\\", "\\\\")
            | _ -> input
    end) 