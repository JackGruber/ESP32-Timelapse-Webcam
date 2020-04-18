auto_buildnumber_path = "C:\\git\\meine\\auto_version" # https://github.com/JackGruber/auto_buildnumber

print("")
try:
    import sys
    sys.path.insert(0, auto_buildnumber_path)
    import versioning
    print("auto versioning")
    versioning.UpdateVersionFile("include/version.h", "DEFINEHEADER", False, "include/version_build.h")
except:   
    print("No auto versioning")
print("")