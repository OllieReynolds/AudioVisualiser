# Audio Visualiser

This project is an OpenGL based audio visualiser written in C++. The
solution was originally created with Visual Studio and relies on a few
NuGet packages for its third‑party libraries.

## Running with VSCode on Windows 11

1. **Install Visual Studio Build Tools 2022** and select the "Desktop
   development with C++" workload. This provides the `msbuild` tool and
   the MSVC compiler used by the project.
2. **Open a Developer Command Prompt** (or ensure `msbuild` and
   `nuget` are on your `PATH`).
3. Clone this repository and open the folder in VSCode.
4. Restore the NuGet packages:

   ```console
   nuget restore AudioVisualiser.sln
   ```

   Alternatively you can run `msbuild AudioVisualiser.sln /t:Restore`.
5. Press <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd> to build the
   project. The provided tasks use `msbuild` to compile a *Debug/x64*
   configuration.
6. Start debugging (or press <kbd>F5</kbd>) to launch the program. The
   debugger configuration in `.vscode/launch.json` runs the generated
   executable from `x64/Debug/AudioVisualiser.exe`.

After these steps the audio visualiser window should appear and react to
`music/Rolemusic_-_pl4y1ng.mp3` which is included in the repository.
