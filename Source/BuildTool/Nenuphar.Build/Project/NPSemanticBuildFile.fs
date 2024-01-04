module Nenuphar.Build.Project.NPSemanticBuildFile

open System.IO
open Nenuphar.Build.Project
open Nenuphar.Build.Project.NPBuildFileError
open Nenuphar.Build.Project.NPProject


let rec nenupharProjectsOfBuildFile
    (root: Location)
    (buildFile: NPBuildFile)
    : Result<NenupharProject list, NPError list>=

    buildFile.Projects
    |> Seq.map (projectOfNenupharProject root)
    |> Seq.fold (fun acc r ->
        match acc, r with
        | Error e1, Error e2 -> Error <| e1 @ [e2]
        | _, Error errs2 -> Error <| [errs2]
        | Error errs1, _ -> Error <| errs1
        | Ok v1, Ok v2 -> Ok <| v1 @ [v2]) (Ok [])


and private projectOfNenupharProject
    (root: Location)
    (project: Project)
    : Result<NenupharProject, NPError> =
    
   let fullPath = Path.GetFullPath << Path.Combine 
    
   let loc = fullPath [| root; project.Location |]
   
   if Path.Exists loc then
       Ok { Name = project.Name
            Location = loc
            BinariesLocation = fullPath [|root; project.BinariesLocation|]
            OutputLocation = fullPath [|root; project.BuildLocation|]
            Version = project.Version
            CPPVersion = project.CPPVersion }
   else
       Error <| errorMessage $"The location '{project.Location}' does not exist."
