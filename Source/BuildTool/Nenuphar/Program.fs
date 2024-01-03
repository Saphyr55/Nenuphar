open Nenuphar.Build.MSBuild
open Nenuphar.Build.Project.Project
open Nenuphar.Build.CMake


module Env =
    
    let fromProject path = $"D:/Documents/Programs/Nénuphar/{path}"

    let rootPath = fromProject ""

    let engineProject : NenupharProject =

        { Name = "NenupharEngine"
          BinariesLocation = fromProject "Programs/Binaries/Engine/"
          Location = fromProject "Programs/Engine/"
          OutputLocation = fromProject "Programs/Build/Engine/"
          Version = "0.0.1"
          CPPVersion = "20" }


    let createVXCProject _ =
 
        let saveModule (m, pre) =
            VSProject.saveModule m pre engineProject.OutputLocation

        let vcxProjRoot m = (m, VSProject.vcxProjRoot m)

        engineProject.Modules
        |> Seq.map vcxProjRoot  
        |> Seq.iter saveModule

    
[<EntryPoint>]
let main args =
    
    let cmakeListsFile =
        CMakeProject.createCMakeListsFile
            [Env.engineProject]

    cmakeListsFile.Save <| Env.fromProject "CMakeLists.txt"

    0
    