namespace Nenuphar.Build.CMake

open System
open System.IO
open System.Text
open Nenuphar.Build.Project.Project


type Switch = 
    | On
    | Off

    member this.CapitalizedName =
        match this with
        | Off -> "OFF"
        | On -> "ON"


type CMakeLists =
    { MinimumVersion: Version
      Declarations: CMakeDeclaration List
    }
    
        
    member this.Save (filePath: string) =
        File.WriteAllText(filePath, this.Content)
    
    
    member this.Content =
        
        let content = StringBuilder()
        let content = $"cmake_minimum_required(VERSION {this.MinimumVersion})"
                      |> content.Append
        
        for decl in this.Declarations do
            ignore <| content
                .Append("\n\n")
                .Append(decl.Content)
                
        content.ToString ()

and CMakeTarget = string


and CMakeLibraryType =
    | Shared
    | Static

    member this.CapitalizedName =
        match this with
        | Shared -> "SHARED"
        | Static -> "STATIC"


and CMakeDeclaration =
    | NewLine
    | Project of
        Name: string
    | Variable of
        Name: string *
        Value: string
    | Option of
        Name: string *
        Text: string *
        Switch: Switch
    | AddSubdirectory of
        Path: Location
    | TargetIncludeDirectory of
        Target: CMakeTarget *
        Private: Location List *
        Public: Location List
    | TargetSource of
        Target: CMakeTarget *
        Private: Location List *
        Public: Location List
    | AddLibrary of
        Target: CMakeTarget * 
        Type: CMakeLibraryType 
    | AddExecutable of
        Target: CMakeTarget
    | TargetLinkLibraries of
        Target: CMakeTarget *
        Libraries: CMakeTarget List

    
    member this.Content : string =
        let newLineP4 = "\n    "
        let newLineP2 = "\n  "
        let wrapPaths paths = String.Join ("\n    \n", paths |> Seq.map wrapPath)
        
        match this with
        | NewLine -> "\n"
        | Project name -> $"project({name})"
        | AddLibrary(target, ``type``) -> $"add_library({target} {``type``.CapitalizedName})"
        | AddExecutable target -> $"add_executable({target})"
        | Variable (name, value) -> $"set({name} {value})"
        | Option (name, text, switch) -> $"option({name} {text} {switch.CapitalizedName})"
        | AddSubdirectory path -> $"add_subdirectory({path})"
        | TargetIncludeDirectory (target, pri, pub) ->
            $"target_include_directories({target}{newLineP2}" +
            $"PRIVATE{newLineP4}{wrapPaths pri}{newLineP2}" +
            $"PUBLIC{newLineP4}{wrapPaths pub}\n)"
        | TargetSource (target, pri, pub) ->
            $"target_sources({target}{newLineP2}" +
            $"PRIVATE{newLineP4}{wrapPaths pri}{newLineP4}{wrapPaths pub}\n)"
        | TargetLinkLibraries(target, libraries) ->            
            $"target_link_libraries({target}{newLineP2}" +
            $"PRIVATE{newLineP4}{wrapPaths libraries}\n)"



