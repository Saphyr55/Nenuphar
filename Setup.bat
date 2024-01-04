@echo off

cd ./Source/BuildTool

dotnet publish^
    --output "../../Bin"^
    --configuration Release^
    -p:PublishSingleFile=true^
    -p:PublishTrimmed=true

cd ../../

