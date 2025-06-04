Param(
    [string]$Configuration = "Debug",
    [string]$Platform = "x64"
)

$ErrorActionPreference = 'Stop'

function Get-NuGet {
    if (Get-Command nuget -ErrorAction SilentlyContinue) {
        return 'nuget'
    }
    $nugetLocal = Join-Path $PSScriptRoot 'nuget.exe'
    if (-not (Test-Path $nugetLocal)) {
        Write-Host 'Downloading NuGet...' -ForegroundColor Cyan
        Invoke-WebRequest 'https://dist.nuget.org/win-x86-commandline/latest/nuget.exe' -OutFile $nugetLocal
    }
    return $nugetLocal
}

$nuget = Get-NuGet
& $nuget restore "$PSScriptRoot/AudioVisualiser.sln"

$msbuildArgs = @(
    'AudioVisualiser.sln',
    "/p:Configuration=$Configuration",
    "/p:Platform=$Platform"
)

& msbuild @msbuildArgs
