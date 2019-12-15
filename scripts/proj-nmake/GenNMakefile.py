import os
scanpath = "..\..\SpaceInvaders"
sourcefiles = ''
for root, dirs, files in os.walk(scanpath):
    for file in files:
        if file.endswith(".cpp"):
             path = os.path.join(root, file)
             sourcefiles += ' ' + os.path.relpath(path, scanpath).replace("\\", "/")

# print(sourcefiles)

nmakefile = """FILES          ={}
EXECUTABLE     = SpaceInvaders.exe
CFLAGS         = /nologo /Z7 /W4 /WX /Fe$(EXECUTABLE)
CFLAGS_RELEASE = $(CFLAGS) /Ox /MT /DNDEBUG
CFLAGS_DEBUG   = $(CFLAGS) /Od /MTd /D_DEBUG
CC             = cl.exe
DEVENV         = devenv.exe

debug: dummy
	$(CC) $(CFLAGS_DEBUG) $(FILES)

release: dummy
	$(CC) $(CFLAGS_RELEASE) $(FILES)

dev: debug
	$(DEVENV) $(EXECUTABLE)

clean: dummy
	-@del $(EXECUTABLE)
	-@del *.obj
	-@del *.pdb
	-@del *.ilk

dummy:


""".format(sourcefiles)

outputpath = scanpath + '\makefile'
with open(outputpath, "w") as f:
  f.write(nmakefile)

print(nmakefile)
print(outputpath + ' updated.')
