namespace Nenuphar.Build.Project

open System.Collections.Generic
open System.IO
open Tomlyn
open Tomlyn.Model
open Microsoft.FSharp.Core
open Nenuphar.Build.Project.NPBuildFileError


type private Location = string

type private Name = string

type private Version = string


type NPBuildFile =
    { Location: Location
      Configuration: Configuration option
      Projects: Project list }
    
    member this.LocationDirectory = Path.GetPathRoot this.Location

    static member FileName = "NPBuild.toml"

    static member ConfigurationName = "Configuration"

    static member LocationName = "Location"

    static member NameName = "Name"

    static member FromDirectory (dir: Location) =
        let filepath = Path.Combine [|dir; NPBuildFile.FileName|] 
        if not <| Path.Exists filepath then
            Error BuildFileNotFound
        else
            Ok <| NPBuildFile.Read filepath


    static member Read
        (path: Location)
        : Result<NPBuildFile, NPError list> =
        
        let errors = List.empty
        let content = File.ReadAllText path
        let model = Toml.ToModel content

        let conf = Configuration.FromModel model
        let conf, errors = appendRError errors conf

        let projects = Project.FromModel model
        let projects, errors =
            match projects with
            | Ok p -> p, errors
            | Error errs -> [], errors @ errs 

        if List.isEmpty errors then
            { Location = path
              Configuration = conf
              Projects = projects } |> Ok
        else
            Error errors 


and Project =
    { Name: Name
      Location: Location
      Template: Template option
      Version: string option
      CPPVersion: string option
      BinariesLocation: Location
      BuildLocation: Location  }

    
    static member FromModel (model: TomlTable) =
        
        let errors = ref []

        let makeProj (couple: KeyValuePair<string,obj>) =
            Project.MapProject
                errors
                couple.Key
                (couple.Value :?> TomlTable)

        let projects = model["Project"] :?> TomlTable
        let projects =
            projects
            |> Seq.map makeProj
            |> Seq.toList

        let result = Ok []

        let projects =
            projects |>
            List.fold (fun acc result -> begin
                match acc, result with
                | Ok projects, Ok project -> Ok (projects @ [project])
                | Error errs, Ok _ -> Error errs
                | Ok _, Error errs -> Error errs
                | Error errs1, Error errs2 -> Error (errs1 @ errs2)
                end) result 
        projects

    static member private MapProject
        (errors: NPError list ref)
        (subSectionName: Name)
        (project: TomlTable) =

        let onContain f name = 
             f project name subSectionName

        let rst name =
            match onContain expectOnContain<string> name with
            | Error errs -> !errors @ errs |> Error
            | Ok c -> Ok c

        let opt name =
            match onContain optOnContain<string> name with
            | Error errs -> !errors @ errs |> Error
            | Ok c -> Ok c

        rst "Name" |> Result.bind begin
            fun name        -> opt "Version" |> Result.bind (
            fun version     -> rst "Location" |> Result.bind (
            fun location    -> rst "BinariesLocation" |> Result.bind (
            fun bin         -> rst "BuildLocation" |> Result.bind (
            fun build       -> opt "CPPVersion" |> Result.map (
            fun cppVersion ->
                { Name = name
                  Location = location
                  Template = None
                  Version = version
                  CPPVersion = cppVersion
                  BuildLocation = build
                  BinariesLocation = bin }
            )))))
        end


and Template = Modular

and Configuration =
    { Location: Location }
    
    static member FromModel (model: TomlTable) =
        
        let someOk = Some >> Ok
        let errors = []

        let errorMsgMissingLocation =
            error "NPBuild Error: Missing the configuration location in 'NPBuild.toml'."

        let errorMsgMismatch =
            error "NPBuild Error: Location configuration is not a path."

        let isContainsConfiguration =
            model.ContainsKey NPBuildFile.ConfigurationName
        
        match isContainsConfiguration with
        | false -> None
        | true -> begin
            
            let conf = model[NPBuildFile.ConfigurationName] :?> TomlTable
            let isContainsLocation = conf.ContainsKey NPBuildFile.LocationName
            
            Some <|
            match isContainsLocation with
            | false -> errors @ [errorMsgMissingLocation]
                       |> Error
            | true -> 
                let location = conf[NPBuildFile.LocationName] 
                try
                   someOk { Location = location :?> string }
                with _ ->
                    errors @ [ errorMsgMismatch ]
                    |> Error
        end
    