module Nenuphar.Build.Project.NPBuildFileError

open System
open System.Collections.Generic


type BuildFileNotFound = BuildFileNotFound
            
type NPError = NPError of string

let error = NPError

let errorMessage msg = error $"NPBuild Error: {msg}"

let tryCastWith 
    (success : 'sub -> 'a)
    (fallback: 'super -> 'a)
    (x : 'super) : 'a =
    
    let o = box x
    if o :? 'sub then
        success (o :?> 'sub)
    else
        fallback x


let appendError errors error = function
    | None ->  error :: errors
    | Some _ -> errors


let appendRError errors opt =
    match opt with
    | None -> (None, errors)
    | Some r -> begin
        match r with
        | Ok v -> v, errors 
        | Error es -> (None, es @ errors) 
    end


let expectOnContain<'a> (dic: IDictionary<string, obj>) key sectionName =

        let notFoundErr =
            errorMessage $"Missing '{key}' in '{sectionName}' section."

        let misMatchErr =
            errorMessage $"Mismatch type with '{key}' in '{sectionName}' section." 

        match dic.ContainsKey(key) with
        | false -> [ notFoundErr ] |> Error
        | true ->
            let value = dic[key]
            try
                value :?> 'a |> Ok
            with _ ->
                [ misMatchErr ] |> Error


let optOnContain<'a> (dic: IDictionary<string, obj>) key sectionName =

        let misMatchErr =
            errorMessage $"Mismatch type with '{key}' in '{sectionName}' section." 

        match dic.ContainsKey(key) with
        | false -> None |> Ok
        | true ->
            let value = dic[key]
            try
                value :?> 'a |> Some |> Ok
            with _ ->
                [ misMatchErr ] |> Error


let logErrors errors =
    
    let errors =
        errors
        |> Seq.map (fun (NPError msg) -> msg)
        |> Seq.toList

    let msg = 
        String.Join(" \n", errors)

    eprintf $"{msg}\n"
