param (
    [string]$srcDir
)

# Ensure the directory is passed, if not, exit with an error
if (-not $srcDir) {
    Write-Error "No source directory specified"
    exit 1
}

Get-ChildItem -Recurse -File -Filter *.cpp -Path $srcDir | ForEach-Object { ($_.FullName -replace '\\', '/') -replace "^.*$srcDir/", "$srcDir/" }