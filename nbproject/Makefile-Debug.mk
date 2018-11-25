#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/AppFloodPuzz.o \
	${OBJECTDIR}/src/CtxGame.o \
	${OBJECTDIR}/src/CtxScore.o \
	${OBJECTDIR}/src/CtxTitle.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=`sdl2-config --cflags` -fexceptions 
CXXFLAGS=`sdl2-config --cflags` -fexceptions 

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../../Libs/dakiilib/dist/Debug/GNU-Linux -L/usr/lib64 -ldakiilib -lSDL2_image -lSDL2_mixer

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/floodpuzz

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/floodpuzz: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/floodpuzz ${OBJECTFILES} ${LDLIBSOPTIONS} `sdl2-config --libs`

${OBJECTDIR}/src/AppFloodPuzz.o: src/AppFloodPuzz.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_DEBUG -D_LINUX -Isrc -I../../Libs/dakiilib/src/dfc -I../../Libs/dakiilib/src/helper -I../../Libs/dakiilib/src/lib -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/AppFloodPuzz.o src/AppFloodPuzz.cpp

${OBJECTDIR}/src/CtxGame.o: src/CtxGame.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_DEBUG -D_LINUX -Isrc -I../../Libs/dakiilib/src/dfc -I../../Libs/dakiilib/src/helper -I../../Libs/dakiilib/src/lib -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CtxGame.o src/CtxGame.cpp

${OBJECTDIR}/src/CtxScore.o: src/CtxScore.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_DEBUG -D_LINUX -Isrc -I../../Libs/dakiilib/src/dfc -I../../Libs/dakiilib/src/helper -I../../Libs/dakiilib/src/lib -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CtxScore.o src/CtxScore.cpp

${OBJECTDIR}/src/CtxTitle.o: src/CtxTitle.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -D_DEBUG -D_LINUX -Isrc -I../../Libs/dakiilib/src/dfc -I../../Libs/dakiilib/src/helper -I../../Libs/dakiilib/src/lib -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CtxTitle.o src/CtxTitle.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
