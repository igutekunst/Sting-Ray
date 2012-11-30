CC:=c++
CFLAGS:= $(shell sdl-config --libs --cflags)
SOURCES:= RayColor.cpp \
	RTColor.cpp \
	RTLight.cpp \
	RTPointLight.cpp \
	RTSphere.cpp \
	RTVector.cpp \
	vectors.cpp \
	RTAppearance.cpp     \
	RTIntersection.cpp     \
	RTObject.cpp    \
	RTShader.cpp     \
	RTTransformation.cpp    \
	RayVector.cpp \
	RTADSShader.cpp   \
	RTDebug.cpp      \
	RTMatrix.cpp \
	RTRay.cpp             \
	RTtexture.cpp      \
	test.cpp
OBJ:= $(SOURCES:.c=.o)
compile: $(SOURCES)
	$(CC)  $(CFLAGS)  $? 

main: $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o stingray

