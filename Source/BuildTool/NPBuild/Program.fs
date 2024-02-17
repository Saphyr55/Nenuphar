open System.IO
open Microsoft.FSharp.Core
open Nenuphar.Build.CMake
open Nenuphar.Build.Project
open Nenuphar.Build.Project.NPBuildFileError
open Nenuphar.Build.Project.NPSemanticBuildFile

    
[<EntryPoint>]
let main args =

    let success = 0
    let failure = 1
    
    let root =
        if args.Length > 0 then
            args.GetValue(0) :?> string
        else
            Directory.GetCurrentDirectory()

    let resultFile = NPBuildFile.FromDirectory root
    
    match resultFile with 
    | Error BuildFileNotFound ->
        errorMessage "NPBuild.toml not found." :: []
        |> logErrors
        failure
    | Ok result ->
        match result with
        | Error errors ->
            logErrors errors
            failure
        | Ok buildFile ->
            let projects = nenupharProjectsOfBuildFile root buildFile
            match projects with
            | Error errors ->
                logErrors errors
                failure
            | Ok projects -> begin
                let cmakeListsFile =
                    CMakeProject.createCMakeListsFile projects
                CMakeProject.getCMakeListsFileName root
                |> cmakeListsFile.Save
                success
            end

    
