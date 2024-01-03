module rec Nenuphar.Build.Project.BuildFile

open System.IO
open System.Xml.Linq
open FSharp.Compiler.CodeAnalysis
open Microsoft.FSharp.Core


type Dependency = Dependency of string

type OutputTypeElement =
    | Static
    | Shared
    | Exe


type BuildModuleFile = 
    { ModuleName: string
      Location: string
      OutputType: OutputTypeElement
      Dependencies: Dependency List }


type BuildFileType =
    | FSharpScript
    | XML


let interpretBuildFile bft path =
    match bft with
    | FSharpScript -> FSharpBuild.parse path
    | XML -> XMLBuild.parse path


module XMLBuild = 

    let parse (path: string) =

        let location = Path.GetDirectoryName path        
        let content = File.ReadAllText path
        let doc = XDocument.Parse content
        let dependencies = parseDependencies doc 
        let moduleName = parseModuleName doc
        
        if Option.isNone moduleName then
            "Missing Element: Need to have a module name.\n" +
            $"File: {path}"
            |> failwith
        else ()
            
        let outputTypeElement =
            parseOutputTypeElement doc
            |> Option.defaultValue (Static)
                
        { ModuleName = moduleName |> Option.get
          Location = location
          OutputType = outputTypeElement
          Dependencies = dependencies }

        
    let parseOutputTypeElement (doc: XDocument) =
        
        query {
            for element in doc.Descendants "OutputType" do
                select element
        }
        |> Seq.tryLast
        |> Option.map parseOutputTypeElementName
    
    
    let parseOutputTypeElementName (name: XElement) =
        match name.Value with
        | "Static" -> Static
        | "Shared" -> Shared
        | "Exe" | "Application" | "App" -> Exe
        | _ -> failwith $"Error: Unknown {name.Value} as value."
        
    
    
    let parseModuleName (doc: XDocument) =

        query {
            for element in doc.Descendants "ModuleName" do
                select element
        }
        |> Seq.tryLast
        |> Option.map (_.Value)

      
    let parseDependencies (doc: XDocument) =
        
        let dependencies = 
            query {
                for element in doc.Descendants "Dependencies" do
                    select element
            }

        let dependencies = 
             query {
                for element in dependencies.Descendants "Dependency" do
                    select element
            }
        
        dependencies
        |> Seq.map (fun dep -> Dependency dep.Value )
        |> Seq.toList        



module FSharpBuild =
        

    let parse (path: string) =
        failwith "Use xml build file."


    let executeFSharpScript path =
        
        // Create a compiler instance
        let checker = FSharpChecker.Create()

        ()