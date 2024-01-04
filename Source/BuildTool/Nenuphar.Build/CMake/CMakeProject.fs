module Nenuphar.Build.CMake.CMakeProject

open System.IO
open Nenuphar.Build.Project.NPProject


module Mapper =
    
    let contentOfOutputType (m: Module): CMakeDeclaration =
        let name = wrapModuleName m.Name

        match m.OutputType with
        | Static -> AddLibrary (name, CMakeLibraryType.Static) 
        | Shared -> AddLibrary (name, CMakeLibraryType.Shared) 
        | Executable -> AddExecutable name

    
    let rec mapNenupharProject
        (project: NenupharProject)
        : CMakeDeclaration List =
                
        [ Project(wrapString project.Name)
          Variable("CMAKE_CXX_STANDARD", Option.defaultValue "20" project.CPPVersion)
          Variable("CMAKE_CXX_STANDARD_REQUIRED", On.CapitalizedName)
          Variable("CMAKE_RUNTIME_OUTPUT_DIRECTORY", wrapPath project.BinariesLocation)
          Variable("CMAKE_LIBRARY_OUTPUT_DIRECTORY ", wrapPath project.OutputLocation)
          Variable("CMAKE_ARCHIVE_OUTPUT_DIRECTORY ", wrapPath project.OutputLocation) ]
        @
        ( project.Modules
        |> Seq.collect mapModule
        |> Seq.toList )
        
    
    and mapModule (m: Module) : CMakeDeclaration List =
        
        let name = wrapModuleName m.Name

        let result = 
          [ contentOfOutputType m
            TargetSource (name, m.PrivateFilesFirst, m.PublicFilesFirst)
            TargetIncludeDirectory (name, [m.PrivateFolder], [m.PublicFolder]) ]

        if not m.Dependencies.IsEmpty then 
            result @ [TargetLinkLibraries (name, mapDependencies m.Dependencies)] 
        else 
            result 
    
    
    and mapDependencies deps = 
        deps
        |> Seq.map (fun (ModuleName name) -> CMakeTarget name)
        |> Seq.toList
         
                  
let createCMakeListsFile
    (projects : NenupharProject List)
    : CMakeLists =
            
     { MinimumVersion = "3.19"
       Declarations =
           projects
           |> Seq.collect Mapper.mapNenupharProject
           |> Seq.toList } 

