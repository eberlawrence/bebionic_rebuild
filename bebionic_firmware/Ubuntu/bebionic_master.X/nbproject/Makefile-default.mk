#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/bebionic_master.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/bebionic_master.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../../current_files/main_master.c ../../current_files/libraries/I2C_master.c ../../current_files/libraries/motor_pwm.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/725218671/main_master.o ${OBJECTDIR}/_ext/1673019547/I2C_master.o ${OBJECTDIR}/_ext/1673019547/motor_pwm.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/725218671/main_master.o.d ${OBJECTDIR}/_ext/1673019547/I2C_master.o.d ${OBJECTDIR}/_ext/1673019547/motor_pwm.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/725218671/main_master.o ${OBJECTDIR}/_ext/1673019547/I2C_master.o ${OBJECTDIR}/_ext/1673019547/motor_pwm.o

# Source Files
SOURCEFILES=../../current_files/main_master.c ../../current_files/libraries/I2C_master.c ../../current_files/libraries/motor_pwm.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/bebionic_master.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ32MC204
MP_LINKER_FILE_OPTION=,--script=p33FJ32MC204.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/725218671/main_master.o: ../../current_files/main_master.c  .generated_files/flags/default/ea039ea76bce7d79a331e5f0ec137eb85c6e1be4 .generated_files/flags/default/3b94104c82cf0fd39bbff45abc1dbc073067cc36
	@${MKDIR} "${OBJECTDIR}/_ext/725218671" 
	@${RM} ${OBJECTDIR}/_ext/725218671/main_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/725218671/main_master.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../current_files/main_master.c  -o ${OBJECTDIR}/_ext/725218671/main_master.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/725218671/main_master.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=coff -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1673019547/I2C_master.o: ../../current_files/libraries/I2C_master.c  .generated_files/flags/default/2d1eed3228aa6819518313c955c7c6aa44929c5e .generated_files/flags/default/3b94104c82cf0fd39bbff45abc1dbc073067cc36
	@${MKDIR} "${OBJECTDIR}/_ext/1673019547" 
	@${RM} ${OBJECTDIR}/_ext/1673019547/I2C_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/1673019547/I2C_master.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../current_files/libraries/I2C_master.c  -o ${OBJECTDIR}/_ext/1673019547/I2C_master.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1673019547/I2C_master.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=coff -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1673019547/motor_pwm.o: ../../current_files/libraries/motor_pwm.c  .generated_files/flags/default/346d821d141b69eebb847468f7238fbfb78c838c .generated_files/flags/default/3b94104c82cf0fd39bbff45abc1dbc073067cc36
	@${MKDIR} "${OBJECTDIR}/_ext/1673019547" 
	@${RM} ${OBJECTDIR}/_ext/1673019547/motor_pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1673019547/motor_pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../current_files/libraries/motor_pwm.c  -o ${OBJECTDIR}/_ext/1673019547/motor_pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1673019547/motor_pwm.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1    -omf=coff -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/_ext/725218671/main_master.o: ../../current_files/main_master.c  .generated_files/flags/default/9dbf47f7d02c6fe1f32d2a3923cb0cba0d799cb7 .generated_files/flags/default/3b94104c82cf0fd39bbff45abc1dbc073067cc36
	@${MKDIR} "${OBJECTDIR}/_ext/725218671" 
	@${RM} ${OBJECTDIR}/_ext/725218671/main_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/725218671/main_master.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../current_files/main_master.c  -o ${OBJECTDIR}/_ext/725218671/main_master.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/725218671/main_master.o.d"        -g -omf=coff -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1673019547/I2C_master.o: ../../current_files/libraries/I2C_master.c  .generated_files/flags/default/59f6d75a6f31068a1d1622ab621f1da380ce6a93 .generated_files/flags/default/3b94104c82cf0fd39bbff45abc1dbc073067cc36
	@${MKDIR} "${OBJECTDIR}/_ext/1673019547" 
	@${RM} ${OBJECTDIR}/_ext/1673019547/I2C_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/1673019547/I2C_master.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../current_files/libraries/I2C_master.c  -o ${OBJECTDIR}/_ext/1673019547/I2C_master.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1673019547/I2C_master.o.d"        -g -omf=coff -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1673019547/motor_pwm.o: ../../current_files/libraries/motor_pwm.c  .generated_files/flags/default/a0fc0f14cf73470cd531e397cacf03b688ed8b8e .generated_files/flags/default/3b94104c82cf0fd39bbff45abc1dbc073067cc36
	@${MKDIR} "${OBJECTDIR}/_ext/1673019547" 
	@${RM} ${OBJECTDIR}/_ext/1673019547/motor_pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1673019547/motor_pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../current_files/libraries/motor_pwm.c  -o ${OBJECTDIR}/_ext/1673019547/motor_pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1673019547/motor_pwm.o.d"        -g -omf=coff -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/bebionic_master.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/bebionic_master.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -omf=coff -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)      -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/bebionic_master.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/bebionic_master.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=coff -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/bebionic_master.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=coff   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
