import qbs
import qbs.File
import qbs.FileInfo
import qbs.ModUtils

Module {
    // Inputs
    property string capnpPath: qbs.hostOS.contains("osx")? "/usr/local/bin" : "/usr/bin"

    PropertyOptions {
        name: "capnpPath"
        description: "Path to the capnp executables"
    }

    validate: {
        // Check if an absolute path to capnp was provided
        if (FileInfo.isAbsolutePath(capnpPath) && File.exists(capnpPath) + "/capnp" &&
                File.exists(FileInfo.path(capnpPath) + "/capnpc-c++")) {
            return
        }

        var delimiter = qbs.hostOS.contains("windows")? ";" : ":"
        var paths = qbs.getEnv("PATH").split(delimiter)
        if (qbs.hostOS === "osx")
            paths.push("/usr/local/bin")

        // Check if capnp is in PATH
        for (var i = 0; i < paths.length; ++i)
            if (File.exists(paths[i] + "/capnp") && File.exists(paths[i] + "/capnpc-c++"))
                return

        throw "Unable to find capnp binaries. Please set capnpPath property."
    }

    FileTagger {
        patterns: ["*.capnp"]
        fileTags: ["capnp"]
    }
    Rule {
        inputs: ["capnp"]
        Artifact {
            filePath: input.filePath + ".c++"
            fileTags: ["cpp"]
        }
        Artifact {
            filePath: input.filePath + ".h"
            fileTags: ["hpp"]
        }

        prepare: {
            var command = "capnp"
            var compilerOption = "-oc++"
            if (product.moduleProperty("capnp", "capnpPath") !== "") {
                command = product.moduleProperty("capnp", "capnpPath") + "/capnp"
                compilerOption = "-o" + product.moduleProperty("capnp", "capnpPath") + "/capnpc-c++"
            }

            var cmd = new Command(command, ["compile", compilerOption, input.filePath]);
            cmd.description = "Generating Cap'n Proto code for " + input.fileName;
            cmd.highlight = "codegen";
            cmd.workingDirectory = FileInfo.path(input.filePath)
            return cmd;
        }
    }
}
