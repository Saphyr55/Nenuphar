open System
open System.IO
open Nenuphar.Build.MSBuild
open Nenuphar.Build.CMake
open Nenuphar.Build.Project
open Nenuphar.Build.Project.NPBuildFileError
open Nenuphar.Build.Project.NPProject
open Nenuphar.Build.Project.NPSemanticBuildFile


module Env =

    let engineProject root : NenupharProject =
        
        { Name = "NenupharEngine"
          BinariesLocation = Path.Combine [|root; "Bin/Engine/" |]
          Location = Path.Combine [|root; "Source/Engine/" |]
          OutputLocation = Path.Combine [|root; "Build/Engine/" |]
          Version = Some "0.0.0"
          CPPVersion = Some "20" }

    
    let createVXCProject engineProject =
 
        let saveModule (m, pre) =
            VSProject.saveModule m pre engineProject.OutputLocation

        let vcxProjRoot m = (m, VSProject.vcxProjRoot m)

        engineProject.Modules
        |> Seq.map vcxProjRoot  
        |> Seq.iter saveModule

    
[<EntryPoint>]
let main args =
    
    let root =
        if args.Length > 0 then
            args.GetValue(0) :?> string
        else
            Directory.GetCurrentDirectory()
    
    let resultFile = NPBuildFile.FromDirectory root

    match resultFile with
    | Error BuildFileNotFound ->
        eprintf "NPBuild Error: NPBuild.toml not found."
    | Ok result ->
        match result with
        | Error errors -> logErrors errors
        | Ok buildFile ->
            let projects = nenupharProjectsOfBuildFile root buildFile
            match projects with
            | Error errors -> logErrors errors
            | Ok projects -> begin
                let cmakeListsFile = CMakeProject.createCMakeListsFile projects
                cmakeListsFile.Save
                <| Path.Combine [|root; "CMakeLists.txt"|] 
            end
    0
    
