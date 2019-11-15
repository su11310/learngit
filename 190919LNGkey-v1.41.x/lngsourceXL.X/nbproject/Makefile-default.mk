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
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/lngsourceXL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/lngsourceXL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../source/drivers/24lcxxx.c ../source/drivers/25vfxxx.c ../source/drivers/buzzer.c ../source/drivers/clock.c ../source/drivers/company.c ../source/drivers/des.c ../source/drivers/disp.c ../source/drivers/ic_card.c ../source/drivers/iic.c ../source/source/init.c ../source/source/kernel.c ../source/drivers/key.c ../source/drivers/lcd.c ../source/drivers/lngctrl.c ../source/drivers/lngdebug.c ../source/source/main.c ../source/source/main_ui.c ../source/source/module_test.c ../source/drivers/nand.c ../source/drivers/print.c ../source/drivers/qry.c ../source/source/sign.c ../source/drivers/soe.c ../source/source/store.c ../source/source/sysset.c ../source/drivers/TempDetection.c ../source/drivers/uart.c ../source/drivers/gas_log.c ../source/drivers/gas_log_sp.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1246622842/24lcxxx.o ${OBJECTDIR}/_ext/1246622842/25vfxxx.o ${OBJECTDIR}/_ext/1246622842/buzzer.o ${OBJECTDIR}/_ext/1246622842/clock.o ${OBJECTDIR}/_ext/1246622842/company.o ${OBJECTDIR}/_ext/1246622842/des.o ${OBJECTDIR}/_ext/1246622842/disp.o ${OBJECTDIR}/_ext/1246622842/ic_card.o ${OBJECTDIR}/_ext/1246622842/iic.o ${OBJECTDIR}/_ext/1218090624/init.o ${OBJECTDIR}/_ext/1218090624/kernel.o ${OBJECTDIR}/_ext/1246622842/key.o ${OBJECTDIR}/_ext/1246622842/lcd.o ${OBJECTDIR}/_ext/1246622842/lngctrl.o ${OBJECTDIR}/_ext/1246622842/lngdebug.o ${OBJECTDIR}/_ext/1218090624/main.o ${OBJECTDIR}/_ext/1218090624/main_ui.o ${OBJECTDIR}/_ext/1218090624/module_test.o ${OBJECTDIR}/_ext/1246622842/nand.o ${OBJECTDIR}/_ext/1246622842/print.o ${OBJECTDIR}/_ext/1246622842/qry.o ${OBJECTDIR}/_ext/1218090624/sign.o ${OBJECTDIR}/_ext/1246622842/soe.o ${OBJECTDIR}/_ext/1218090624/store.o ${OBJECTDIR}/_ext/1218090624/sysset.o ${OBJECTDIR}/_ext/1246622842/TempDetection.o ${OBJECTDIR}/_ext/1246622842/uart.o ${OBJECTDIR}/_ext/1246622842/gas_log.o ${OBJECTDIR}/_ext/1246622842/gas_log_sp.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1246622842/24lcxxx.o.d ${OBJECTDIR}/_ext/1246622842/25vfxxx.o.d ${OBJECTDIR}/_ext/1246622842/buzzer.o.d ${OBJECTDIR}/_ext/1246622842/clock.o.d ${OBJECTDIR}/_ext/1246622842/company.o.d ${OBJECTDIR}/_ext/1246622842/des.o.d ${OBJECTDIR}/_ext/1246622842/disp.o.d ${OBJECTDIR}/_ext/1246622842/ic_card.o.d ${OBJECTDIR}/_ext/1246622842/iic.o.d ${OBJECTDIR}/_ext/1218090624/init.o.d ${OBJECTDIR}/_ext/1218090624/kernel.o.d ${OBJECTDIR}/_ext/1246622842/key.o.d ${OBJECTDIR}/_ext/1246622842/lcd.o.d ${OBJECTDIR}/_ext/1246622842/lngctrl.o.d ${OBJECTDIR}/_ext/1246622842/lngdebug.o.d ${OBJECTDIR}/_ext/1218090624/main.o.d ${OBJECTDIR}/_ext/1218090624/main_ui.o.d ${OBJECTDIR}/_ext/1218090624/module_test.o.d ${OBJECTDIR}/_ext/1246622842/nand.o.d ${OBJECTDIR}/_ext/1246622842/print.o.d ${OBJECTDIR}/_ext/1246622842/qry.o.d ${OBJECTDIR}/_ext/1218090624/sign.o.d ${OBJECTDIR}/_ext/1246622842/soe.o.d ${OBJECTDIR}/_ext/1218090624/store.o.d ${OBJECTDIR}/_ext/1218090624/sysset.o.d ${OBJECTDIR}/_ext/1246622842/TempDetection.o.d ${OBJECTDIR}/_ext/1246622842/uart.o.d ${OBJECTDIR}/_ext/1246622842/gas_log.o.d ${OBJECTDIR}/_ext/1246622842/gas_log_sp.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1246622842/24lcxxx.o ${OBJECTDIR}/_ext/1246622842/25vfxxx.o ${OBJECTDIR}/_ext/1246622842/buzzer.o ${OBJECTDIR}/_ext/1246622842/clock.o ${OBJECTDIR}/_ext/1246622842/company.o ${OBJECTDIR}/_ext/1246622842/des.o ${OBJECTDIR}/_ext/1246622842/disp.o ${OBJECTDIR}/_ext/1246622842/ic_card.o ${OBJECTDIR}/_ext/1246622842/iic.o ${OBJECTDIR}/_ext/1218090624/init.o ${OBJECTDIR}/_ext/1218090624/kernel.o ${OBJECTDIR}/_ext/1246622842/key.o ${OBJECTDIR}/_ext/1246622842/lcd.o ${OBJECTDIR}/_ext/1246622842/lngctrl.o ${OBJECTDIR}/_ext/1246622842/lngdebug.o ${OBJECTDIR}/_ext/1218090624/main.o ${OBJECTDIR}/_ext/1218090624/main_ui.o ${OBJECTDIR}/_ext/1218090624/module_test.o ${OBJECTDIR}/_ext/1246622842/nand.o ${OBJECTDIR}/_ext/1246622842/print.o ${OBJECTDIR}/_ext/1246622842/qry.o ${OBJECTDIR}/_ext/1218090624/sign.o ${OBJECTDIR}/_ext/1246622842/soe.o ${OBJECTDIR}/_ext/1218090624/store.o ${OBJECTDIR}/_ext/1218090624/sysset.o ${OBJECTDIR}/_ext/1246622842/TempDetection.o ${OBJECTDIR}/_ext/1246622842/uart.o ${OBJECTDIR}/_ext/1246622842/gas_log.o ${OBJECTDIR}/_ext/1246622842/gas_log_sp.o

# Source Files
SOURCEFILES=../source/drivers/24lcxxx.c ../source/drivers/25vfxxx.c ../source/drivers/buzzer.c ../source/drivers/clock.c ../source/drivers/company.c ../source/drivers/des.c ../source/drivers/disp.c ../source/drivers/ic_card.c ../source/drivers/iic.c ../source/source/init.c ../source/source/kernel.c ../source/drivers/key.c ../source/drivers/lcd.c ../source/drivers/lngctrl.c ../source/drivers/lngdebug.c ../source/source/main.c ../source/source/main_ui.c ../source/source/module_test.c ../source/drivers/nand.c ../source/drivers/print.c ../source/drivers/qry.c ../source/source/sign.c ../source/drivers/soe.c ../source/source/store.c ../source/source/sysset.c ../source/drivers/TempDetection.c ../source/drivers/uart.c ../source/drivers/gas_log.c ../source/drivers/gas_log_sp.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/lngsourceXL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=,--script="..\linker_scripts\app_32MX795F512L.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1246622842/24lcxxx.o: ../source/drivers/24lcxxx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/24lcxxx.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/24lcxxx.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/24lcxxx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/24lcxxx.o.d" -o ${OBJECTDIR}/_ext/1246622842/24lcxxx.o ../source/drivers/24lcxxx.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/25vfxxx.o: ../source/drivers/25vfxxx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/25vfxxx.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/25vfxxx.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/25vfxxx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/25vfxxx.o.d" -o ${OBJECTDIR}/_ext/1246622842/25vfxxx.o ../source/drivers/25vfxxx.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/buzzer.o: ../source/drivers/buzzer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/buzzer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/buzzer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/buzzer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/buzzer.o.d" -o ${OBJECTDIR}/_ext/1246622842/buzzer.o ../source/drivers/buzzer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/clock.o: ../source/drivers/clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/clock.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/clock.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/clock.o.d" -o ${OBJECTDIR}/_ext/1246622842/clock.o ../source/drivers/clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/company.o: ../source/drivers/company.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/company.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/company.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/company.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/company.o.d" -o ${OBJECTDIR}/_ext/1246622842/company.o ../source/drivers/company.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/des.o: ../source/drivers/des.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/des.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/des.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/des.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/des.o.d" -o ${OBJECTDIR}/_ext/1246622842/des.o ../source/drivers/des.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/disp.o: ../source/drivers/disp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/disp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/disp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/disp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/disp.o.d" -o ${OBJECTDIR}/_ext/1246622842/disp.o ../source/drivers/disp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/ic_card.o: ../source/drivers/ic_card.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/ic_card.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/ic_card.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/ic_card.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/ic_card.o.d" -o ${OBJECTDIR}/_ext/1246622842/ic_card.o ../source/drivers/ic_card.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/iic.o: ../source/drivers/iic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/iic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/iic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/iic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/iic.o.d" -o ${OBJECTDIR}/_ext/1246622842/iic.o ../source/drivers/iic.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1218090624/init.o: ../source/source/init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1218090624" 
	@${RM} ${OBJECTDIR}/_ext/1218090624/init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1218090624/init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1218090624/init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1218090624/init.o.d" -o ${OBJECTDIR}/_ext/1218090624/init.o ../source/source/init.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1218090624/kernel.o: ../source/source/kernel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1218090624" 
	@${RM} ${OBJECTDIR}/_ext/1218090624/kernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/1218090624/kernel.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1218090624/kernel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1218090624/kernel.o.d" -o ${OBJECTDIR}/_ext/1218090624/kernel.o ../source/source/kernel.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/key.o: ../source/drivers/key.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/key.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/key.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/key.o.d" -o ${OBJECTDIR}/_ext/1246622842/key.o ../source/drivers/key.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/lcd.o: ../source/drivers/lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/lcd.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/lcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/lcd.o.d" -o ${OBJECTDIR}/_ext/1246622842/lcd.o ../source/drivers/lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/lngctrl.o: ../source/drivers/lngctrl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/lngctrl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/lngctrl.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/lngctrl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/lngctrl.o.d" -o ${OBJECTDIR}/_ext/1246622842/lngctrl.o ../source/drivers/lngctrl.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/lngdebug.o: ../source/drivers/lngdebug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/lngdebug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/lngdebug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/lngdebug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/lngdebug.o.d" -o ${OBJECTDIR}/_ext/1246622842/lngdebug.o ../source/drivers/lngdebug.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1218090624/main.o: ../source/source/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1218090624" 
	@${RM} ${OBJECTDIR}/_ext/1218090624/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1218090624/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1218090624/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1218090624/main.o.d" -o ${OBJECTDIR}/_ext/1218090624/main.o ../source/source/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1218090624/main_ui.o: ../source/source/main_ui.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1218090624" 
	@${RM} ${OBJECTDIR}/_ext/1218090624/main_ui.o.d 
	@${RM} ${OBJECTDIR}/_ext/1218090624/main_ui.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1218090624/main_ui.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1218090624/main_ui.o.d" -o ${OBJECTDIR}/_ext/1218090624/main_ui.o ../source/source/main_ui.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1218090624/module_test.o: ../source/source/module_test.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1218090624" 
	@${RM} ${OBJECTDIR}/_ext/1218090624/module_test.o.d 
	@${RM} ${OBJECTDIR}/_ext/1218090624/module_test.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1218090624/module_test.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1218090624/module_test.o.d" -o ${OBJECTDIR}/_ext/1218090624/module_test.o ../source/source/module_test.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/nand.o: ../source/drivers/nand.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/nand.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/nand.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/nand.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/nand.o.d" -o ${OBJECTDIR}/_ext/1246622842/nand.o ../source/drivers/nand.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/print.o: ../source/drivers/print.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/print.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/print.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/print.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/print.o.d" -o ${OBJECTDIR}/_ext/1246622842/print.o ../source/drivers/print.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/qry.o: ../source/drivers/qry.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/qry.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/qry.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/qry.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/qry.o.d" -o ${OBJECTDIR}/_ext/1246622842/qry.o ../source/drivers/qry.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1218090624/sign.o: ../source/source/sign.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1218090624" 
	@${RM} ${OBJECTDIR}/_ext/1218090624/sign.o.d 
	@${RM} ${OBJECTDIR}/_ext/1218090624/sign.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1218090624/sign.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1218090624/sign.o.d" -o ${OBJECTDIR}/_ext/1218090624/sign.o ../source/source/sign.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/soe.o: ../source/drivers/soe.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/soe.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/soe.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/soe.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/soe.o.d" -o ${OBJECTDIR}/_ext/1246622842/soe.o ../source/drivers/soe.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1218090624/store.o: ../source/source/store.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1218090624" 
	@${RM} ${OBJECTDIR}/_ext/1218090624/store.o.d 
	@${RM} ${OBJECTDIR}/_ext/1218090624/store.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1218090624/store.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1218090624/store.o.d" -o ${OBJECTDIR}/_ext/1218090624/store.o ../source/source/store.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1218090624/sysset.o: ../source/source/sysset.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1218090624" 
	@${RM} ${OBJECTDIR}/_ext/1218090624/sysset.o.d 
	@${RM} ${OBJECTDIR}/_ext/1218090624/sysset.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1218090624/sysset.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1218090624/sysset.o.d" -o ${OBJECTDIR}/_ext/1218090624/sysset.o ../source/source/sysset.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/TempDetection.o: ../source/drivers/TempDetection.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/TempDetection.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/TempDetection.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/TempDetection.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/TempDetection.o.d" -o ${OBJECTDIR}/_ext/1246622842/TempDetection.o ../source/drivers/TempDetection.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/uart.o: ../source/drivers/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/uart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/uart.o.d" -o ${OBJECTDIR}/_ext/1246622842/uart.o ../source/drivers/uart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/gas_log.o: ../source/drivers/gas_log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/gas_log.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/gas_log.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/gas_log.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/gas_log.o.d" -o ${OBJECTDIR}/_ext/1246622842/gas_log.o ../source/drivers/gas_log.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/gas_log_sp.o: ../source/drivers/gas_log_sp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/gas_log_sp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/gas_log_sp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/gas_log_sp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/gas_log_sp.o.d" -o ${OBJECTDIR}/_ext/1246622842/gas_log_sp.o ../source/drivers/gas_log_sp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/1246622842/24lcxxx.o: ../source/drivers/24lcxxx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/24lcxxx.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/24lcxxx.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/24lcxxx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/24lcxxx.o.d" -o ${OBJECTDIR}/_ext/1246622842/24lcxxx.o ../source/drivers/24lcxxx.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/25vfxxx.o: ../source/drivers/25vfxxx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/25vfxxx.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/25vfxxx.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/25vfxxx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/25vfxxx.o.d" -o ${OBJECTDIR}/_ext/1246622842/25vfxxx.o ../source/drivers/25vfxxx.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/buzzer.o: ../source/drivers/buzzer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/buzzer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/buzzer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/buzzer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/buzzer.o.d" -o ${OBJECTDIR}/_ext/1246622842/buzzer.o ../source/drivers/buzzer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/clock.o: ../source/drivers/clock.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/clock.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/clock.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/clock.o.d" -o ${OBJECTDIR}/_ext/1246622842/clock.o ../source/drivers/clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/company.o: ../source/drivers/company.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/company.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/company.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/company.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/company.o.d" -o ${OBJECTDIR}/_ext/1246622842/company.o ../source/drivers/company.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/des.o: ../source/drivers/des.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/des.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/des.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/des.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/des.o.d" -o ${OBJECTDIR}/_ext/1246622842/des.o ../source/drivers/des.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/disp.o: ../source/drivers/disp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/disp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/disp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/disp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/disp.o.d" -o ${OBJECTDIR}/_ext/1246622842/disp.o ../source/drivers/disp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/ic_card.o: ../source/drivers/ic_card.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/ic_card.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/ic_card.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/ic_card.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/ic_card.o.d" -o ${OBJECTDIR}/_ext/1246622842/ic_card.o ../source/drivers/ic_card.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/iic.o: ../source/drivers/iic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/iic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/iic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/iic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/iic.o.d" -o ${OBJECTDIR}/_ext/1246622842/iic.o ../source/drivers/iic.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1218090624/init.o: ../source/source/init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1218090624" 
	@${RM} ${OBJECTDIR}/_ext/1218090624/init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1218090624/init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1218090624/init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1218090624/init.o.d" -o ${OBJECTDIR}/_ext/1218090624/init.o ../source/source/init.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1218090624/kernel.o: ../source/source/kernel.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1218090624" 
	@${RM} ${OBJECTDIR}/_ext/1218090624/kernel.o.d 
	@${RM} ${OBJECTDIR}/_ext/1218090624/kernel.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1218090624/kernel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1218090624/kernel.o.d" -o ${OBJECTDIR}/_ext/1218090624/kernel.o ../source/source/kernel.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/key.o: ../source/drivers/key.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/key.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/key.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/key.o.d" -o ${OBJECTDIR}/_ext/1246622842/key.o ../source/drivers/key.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/lcd.o: ../source/drivers/lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/lcd.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/lcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/lcd.o.d" -o ${OBJECTDIR}/_ext/1246622842/lcd.o ../source/drivers/lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/lngctrl.o: ../source/drivers/lngctrl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/lngctrl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/lngctrl.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/lngctrl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/lngctrl.o.d" -o ${OBJECTDIR}/_ext/1246622842/lngctrl.o ../source/drivers/lngctrl.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/lngdebug.o: ../source/drivers/lngdebug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/lngdebug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/lngdebug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/lngdebug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/lngdebug.o.d" -o ${OBJECTDIR}/_ext/1246622842/lngdebug.o ../source/drivers/lngdebug.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1218090624/main.o: ../source/source/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1218090624" 
	@${RM} ${OBJECTDIR}/_ext/1218090624/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1218090624/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1218090624/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1218090624/main.o.d" -o ${OBJECTDIR}/_ext/1218090624/main.o ../source/source/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1218090624/main_ui.o: ../source/source/main_ui.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1218090624" 
	@${RM} ${OBJECTDIR}/_ext/1218090624/main_ui.o.d 
	@${RM} ${OBJECTDIR}/_ext/1218090624/main_ui.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1218090624/main_ui.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1218090624/main_ui.o.d" -o ${OBJECTDIR}/_ext/1218090624/main_ui.o ../source/source/main_ui.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1218090624/module_test.o: ../source/source/module_test.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1218090624" 
	@${RM} ${OBJECTDIR}/_ext/1218090624/module_test.o.d 
	@${RM} ${OBJECTDIR}/_ext/1218090624/module_test.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1218090624/module_test.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1218090624/module_test.o.d" -o ${OBJECTDIR}/_ext/1218090624/module_test.o ../source/source/module_test.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/nand.o: ../source/drivers/nand.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/nand.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/nand.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/nand.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/nand.o.d" -o ${OBJECTDIR}/_ext/1246622842/nand.o ../source/drivers/nand.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/print.o: ../source/drivers/print.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/print.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/print.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/print.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/print.o.d" -o ${OBJECTDIR}/_ext/1246622842/print.o ../source/drivers/print.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/qry.o: ../source/drivers/qry.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/qry.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/qry.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/qry.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/qry.o.d" -o ${OBJECTDIR}/_ext/1246622842/qry.o ../source/drivers/qry.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1218090624/sign.o: ../source/source/sign.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1218090624" 
	@${RM} ${OBJECTDIR}/_ext/1218090624/sign.o.d 
	@${RM} ${OBJECTDIR}/_ext/1218090624/sign.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1218090624/sign.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1218090624/sign.o.d" -o ${OBJECTDIR}/_ext/1218090624/sign.o ../source/source/sign.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/soe.o: ../source/drivers/soe.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/soe.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/soe.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/soe.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/soe.o.d" -o ${OBJECTDIR}/_ext/1246622842/soe.o ../source/drivers/soe.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1218090624/store.o: ../source/source/store.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1218090624" 
	@${RM} ${OBJECTDIR}/_ext/1218090624/store.o.d 
	@${RM} ${OBJECTDIR}/_ext/1218090624/store.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1218090624/store.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1218090624/store.o.d" -o ${OBJECTDIR}/_ext/1218090624/store.o ../source/source/store.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1218090624/sysset.o: ../source/source/sysset.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1218090624" 
	@${RM} ${OBJECTDIR}/_ext/1218090624/sysset.o.d 
	@${RM} ${OBJECTDIR}/_ext/1218090624/sysset.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1218090624/sysset.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1218090624/sysset.o.d" -o ${OBJECTDIR}/_ext/1218090624/sysset.o ../source/source/sysset.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/TempDetection.o: ../source/drivers/TempDetection.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/TempDetection.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/TempDetection.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/TempDetection.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/TempDetection.o.d" -o ${OBJECTDIR}/_ext/1246622842/TempDetection.o ../source/drivers/TempDetection.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/uart.o: ../source/drivers/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/uart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/uart.o.d" -o ${OBJECTDIR}/_ext/1246622842/uart.o ../source/drivers/uart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/gas_log.o: ../source/drivers/gas_log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/gas_log.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/gas_log.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/gas_log.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/gas_log.o.d" -o ${OBJECTDIR}/_ext/1246622842/gas_log.o ../source/drivers/gas_log.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1246622842/gas_log_sp.o: ../source/drivers/gas_log_sp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1246622842" 
	@${RM} ${OBJECTDIR}/_ext/1246622842/gas_log_sp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1246622842/gas_log_sp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1246622842/gas_log_sp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1246622842/gas_log_sp.o.d" -o ${OBJECTDIR}/_ext/1246622842/gas_log_sp.o ../source/drivers/gas_log_sp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/lngsourceXL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../linker_scripts/app_32MX795F512L.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_ICD3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/lngsourceXL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/lngsourceXL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../linker_scripts/app_32MX795F512L.ld ../Bootloader/MPLAB_X_Workspace/BootLoader.X/dist/default/production/BootLoader.X.production.hex
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/lngsourceXL.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/lngsourceXL.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
	@echo "Creating unified hex file"
	@"D:/Program Files (x86)/Microchip/MPLABX/v5.05/mplab_platform/platform/../mplab_ide/modules/../../bin/hexmate" --edf="D:/Program Files (x86)/Microchip/MPLABX/v5.05/mplab_platform/platform/../mplab_ide/modules/../../dat/en_msgs.txt" dist/${CND_CONF}/${IMAGE_TYPE}/lngsourceXL.X.${IMAGE_TYPE}.hex ../Bootloader/MPLAB_X_Workspace/BootLoader.X/dist/default/production/BootLoader.X.production.hex -odist/${CND_CONF}/production/lngsourceXL.X.production.unified.hex

endif


# Subprojects
.build-subprojects:
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
	cd /D ../Bootloader/MPLAB_X_Workspace/BootLoader.X && ${MAKE}  -f Makefile CONF=default TYPE_IMAGE=DEBUG_RUN
else
	cd /D ../Bootloader/MPLAB_X_Workspace/BootLoader.X && ${MAKE}  -f Makefile CONF=default
endif


# Subprojects
.clean-subprojects:
	cd /D ../Bootloader/MPLAB_X_Workspace/BootLoader.X && rm -rf "build/default" "dist/default"

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
