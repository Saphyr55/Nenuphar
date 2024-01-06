module rec Nenuphar.Build.Project.ModuleBuildFile

open System.IO
open System.Xml.Linq
open FSharp.Compiler.CodeAnalysis
open Microsoft.FSharp.Core
open Nenuphar.Build.Project.NPBuildFileError
open Tomlyn
open NPBuildFileError
open Tomlyn.Model


type Dependency = Dependency of string

type OutputTypeElement =
    | Static
    | Shared
    | Executable


type ModuleBuildFile = 
    { ModuleName: string
      Location: string
      OutputType: OutputTypeElement
      Dependencies: Dependency List }


type ModuleBuildFileType =
    | FSharpScript
    | TomlFile


let interpretModuleBuildFile bft path =
    match bft with
    | FSharpScript -> FSharpBuild.parse path
    | TomlFile -> TomlBuild.parse path


module TomlBuild = 
    
    let parse (path: string) =
        
        let errors = ref []
        let location = Path.GetDirectoryName path        
        let content = File.ReadAllText path
        let table = Toml.ToModel content

        let moduleTable =
            expectOnContain<TomlTable>
                table
                "Module"
                "globals"

        let appendErrors errs =
            errors.Value <- errors.Value @ errs
            errors.Value

        let values = 
            moduleTable
            |> Result.bind (fun mt ->
                parseModuleName mt
                |> Result.map (fun n -> mt, n)
                |> Result.mapError appendErrors)

            |> Result.bind (fun (mt, name) ->
                parseOutputTypeElement mt
                |> Result.map (fun ote -> mt, name, ote)
                |> Result.mapError appendErrors)

            |> Result.bind (fun (mt, name, ote) ->
                parseDependencies mt
                |> Result.map (fun deps -> name, Option.defaultValue "Static" ote, deps)
                |> Result.mapError appendErrors)

            |> Result.map (fun (name, outputTypeEl, deps) ->
                Some (name, parseOutputTypeElementName outputTypeEl, deps))
            
            |> Result.mapError appendErrors
            |> Result.defaultValue None

        match values with
        | None -> Error errors
        | Some (name, outputType, deps) -> 
            { ModuleName = name
              Location = location
              OutputType = outputType
              Dependencies = deps } |> Ok

    
    let parseOutputTypeElement
        (table: TomlTable)
        : Result<string option, NPError list> =

        optOnContain<string>
                table
                "OutputType"
                "Module"
    
    let parseOutputTypeElementName name =
        match name with
        | "Static" -> Static
        | "Shared" -> Shared
        | "Exe" | "Executable" 
        | "App" | "Application"
        | "Binary" -> Executable
        | _ -> failwith $"Error: Unknown {name} as value."
        
    
    let parseModuleName (table: TomlTable) : Result<string, NPError list> =
        
        expectOnContain<string> table "Name" "Module"
        
        
    let parseDependencies (table: TomlTable) =
        
        let dependencies =
            optOnContain<TomlArray>
                table "Dependencies" "Module"
        
        let mapDep (dep: obj) =
            let dep = dep :?> TomlTable
            Dependency <| (dep["Name"] :?> string)

        let mapDeps (deps: TomlArray option) =
            match deps with
            | None -> Ok []
            | Some deps ->
                deps
                |> Seq.map mapDep
                |> Seq.toList
                |> Ok

        match dependencies with
        | Error errors -> Error errors
        | Ok dependencies -> mapDeps dependencies


module FSharpBuild =
        

    let parse (path: string) =
        failwith "Use xml build file."


    let executeFSharpScript path =
        
        // Create a compiler instance
        let checker = FSharpChecker.Create()

        ()