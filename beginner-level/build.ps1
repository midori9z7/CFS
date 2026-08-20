# build.ps1
# Compiles every C program in noob-level into the bin/ folder.
#
# Usage (from the repository root):
#     powershell -ExecutionPolicy Bypass -File .\noob-level\build.ps1
#
# Requires gcc to be on your PATH. Check with:  gcc --version

$ErrorActionPreference = "Stop"

$root = Split-Path -Parent $MyInvocation.MyCommand.Path
$bin  = Join-Path $root "bin"

New-Item -ItemType Directory -Force -Path $bin | Out-Null

# Make sure the compiler exists before we start
if (-not (Get-Command gcc -ErrorAction SilentlyContinue)) {
    Write-Host "ERROR: gcc not found on PATH. Install it first (see README.md, section 0)."
    exit 1
}

function Compile-All([string]$folder) {
    $sources = Get-ChildItem -Path (Join-Path $root $folder) -Filter *.c
    foreach ($f in $sources) {
        $out = Join-Path $bin ($f.BaseName + ".exe")
        Write-Host ("Compiling {0} ..." -f $f.Name)
        # -lm links the math library (needed by lessons 09 and shunting_calc)
        & gcc -std=c17 -Wall -Wextra -lm -o $out $f.FullName
        if ($LASTEXITCODE -ne 0) {
            throw "Compilation failed for $($f.Name)"
        }
    }
}

Compile-All "lessons"
Compile-All "projects"

Write-Host ""
Write-Host "All done. Executables are in: $bin"
