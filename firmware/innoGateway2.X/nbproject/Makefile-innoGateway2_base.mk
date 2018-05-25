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
ifeq "$(wildcard nbproject/Makefile-local-innoGateway2_base.mk)" "nbproject/Makefile-local-innoGateway2_base.mk"
include nbproject/Makefile-local-innoGateway2_base.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=innoGateway2_base
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/innoGateway2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/innoGateway2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
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
SOURCEFILES_QUOTED_IF_SPACED=../src/system_config/innoGateway2_base/framework/system/wdt/sys_wdt.c ../src/system_config/innoGateway2_base/bsp/bsp.c ../src/system_config/innoGateway2_base/framework/driver/can/src/drv_can_mapping.c ../src/system_config/innoGateway2_base/framework/driver/can/src/drv_can_static.c ../src/system_config/innoGateway2_base/framework/driver/tmr/src/drv_tmr_static.c ../src/system_config/innoGateway2_base/framework/driver/tmr/src/drv_tmr_mapping.c ../src/system_config/innoGateway2_base/framework/driver/usart/src/drv_usart_mapping.c ../src/system_config/innoGateway2_base/framework/driver/usart/src/drv_usart_static.c ../src/system_config/innoGateway2_base/framework/driver/usart/src/drv_usart_static_byte_model.c ../src/system_config/innoGateway2_base/framework/system/clk/src/sys_clk_pic32mx.c ../src/system_config/innoGateway2_base/framework/system/devcon/src/sys_devcon.c ../src/system_config/innoGateway2_base/framework/system/devcon/src/sys_devcon_pic32mx.c ../src/system_config/innoGateway2_base/framework/system/ports/src/sys_ports_static.c ../src/system_config/innoGateway2_base/system_init.c ../src/system_config/innoGateway2_base/system_interrupt.c ../src/system_config/innoGateway2_base/system_exceptions.c ../src/system_config/innoGateway2_base/system_tasks.c ../src/app.c ../src/main.c ../src/IRMA.c ../src/errorCheck.c ../src/fifoBuffer.c ../src/helper.c ../src/i2c_eeprom.c ../src/timerDefinitions.c ../src/uart.c ../src/uart_protocol_handler.c ../../../../../../../microchip/harmony/v2_04/framework/driver/i2c/src/dynamic/drv_i2c.c ../../../../../../../microchip/harmony/v2_04/framework/system/int/src/sys_int_pic32.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1756686434/sys_wdt.o ${OBJECTDIR}/_ext/797593781/bsp.o ${OBJECTDIR}/_ext/1834457159/drv_can_mapping.o ${OBJECTDIR}/_ext/1834457159/drv_can_static.o ${OBJECTDIR}/_ext/715447426/drv_tmr_static.o ${OBJECTDIR}/_ext/715447426/drv_tmr_mapping.o ${OBJECTDIR}/_ext/124120942/drv_usart_mapping.o ${OBJECTDIR}/_ext/124120942/drv_usart_static.o ${OBJECTDIR}/_ext/124120942/drv_usart_static_byte_model.o ${OBJECTDIR}/_ext/1532472558/sys_clk_pic32mx.o ${OBJECTDIR}/_ext/1960096935/sys_devcon.o ${OBJECTDIR}/_ext/1960096935/sys_devcon_pic32mx.o ${OBJECTDIR}/_ext/1024927934/sys_ports_static.o ${OBJECTDIR}/_ext/1332166779/system_init.o ${OBJECTDIR}/_ext/1332166779/system_interrupt.o ${OBJECTDIR}/_ext/1332166779/system_exceptions.o ${OBJECTDIR}/_ext/1332166779/system_tasks.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/IRMA.o ${OBJECTDIR}/_ext/1360937237/errorCheck.o ${OBJECTDIR}/_ext/1360937237/fifoBuffer.o ${OBJECTDIR}/_ext/1360937237/helper.o ${OBJECTDIR}/_ext/1360937237/i2c_eeprom.o ${OBJECTDIR}/_ext/1360937237/timerDefinitions.o ${OBJECTDIR}/_ext/1360937237/uart.o ${OBJECTDIR}/_ext/1360937237/uart_protocol_handler.o ${OBJECTDIR}/_ext/108923032/drv_i2c.o ${OBJECTDIR}/_ext/1082766828/sys_int_pic32.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1756686434/sys_wdt.o.d ${OBJECTDIR}/_ext/797593781/bsp.o.d ${OBJECTDIR}/_ext/1834457159/drv_can_mapping.o.d ${OBJECTDIR}/_ext/1834457159/drv_can_static.o.d ${OBJECTDIR}/_ext/715447426/drv_tmr_static.o.d ${OBJECTDIR}/_ext/715447426/drv_tmr_mapping.o.d ${OBJECTDIR}/_ext/124120942/drv_usart_mapping.o.d ${OBJECTDIR}/_ext/124120942/drv_usart_static.o.d ${OBJECTDIR}/_ext/124120942/drv_usart_static_byte_model.o.d ${OBJECTDIR}/_ext/1532472558/sys_clk_pic32mx.o.d ${OBJECTDIR}/_ext/1960096935/sys_devcon.o.d ${OBJECTDIR}/_ext/1960096935/sys_devcon_pic32mx.o.d ${OBJECTDIR}/_ext/1024927934/sys_ports_static.o.d ${OBJECTDIR}/_ext/1332166779/system_init.o.d ${OBJECTDIR}/_ext/1332166779/system_interrupt.o.d ${OBJECTDIR}/_ext/1332166779/system_exceptions.o.d ${OBJECTDIR}/_ext/1332166779/system_tasks.o.d ${OBJECTDIR}/_ext/1360937237/app.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/1360937237/IRMA.o.d ${OBJECTDIR}/_ext/1360937237/errorCheck.o.d ${OBJECTDIR}/_ext/1360937237/fifoBuffer.o.d ${OBJECTDIR}/_ext/1360937237/helper.o.d ${OBJECTDIR}/_ext/1360937237/i2c_eeprom.o.d ${OBJECTDIR}/_ext/1360937237/timerDefinitions.o.d ${OBJECTDIR}/_ext/1360937237/uart.o.d ${OBJECTDIR}/_ext/1360937237/uart_protocol_handler.o.d ${OBJECTDIR}/_ext/108923032/drv_i2c.o.d ${OBJECTDIR}/_ext/1082766828/sys_int_pic32.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1756686434/sys_wdt.o ${OBJECTDIR}/_ext/797593781/bsp.o ${OBJECTDIR}/_ext/1834457159/drv_can_mapping.o ${OBJECTDIR}/_ext/1834457159/drv_can_static.o ${OBJECTDIR}/_ext/715447426/drv_tmr_static.o ${OBJECTDIR}/_ext/715447426/drv_tmr_mapping.o ${OBJECTDIR}/_ext/124120942/drv_usart_mapping.o ${OBJECTDIR}/_ext/124120942/drv_usart_static.o ${OBJECTDIR}/_ext/124120942/drv_usart_static_byte_model.o ${OBJECTDIR}/_ext/1532472558/sys_clk_pic32mx.o ${OBJECTDIR}/_ext/1960096935/sys_devcon.o ${OBJECTDIR}/_ext/1960096935/sys_devcon_pic32mx.o ${OBJECTDIR}/_ext/1024927934/sys_ports_static.o ${OBJECTDIR}/_ext/1332166779/system_init.o ${OBJECTDIR}/_ext/1332166779/system_interrupt.o ${OBJECTDIR}/_ext/1332166779/system_exceptions.o ${OBJECTDIR}/_ext/1332166779/system_tasks.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/IRMA.o ${OBJECTDIR}/_ext/1360937237/errorCheck.o ${OBJECTDIR}/_ext/1360937237/fifoBuffer.o ${OBJECTDIR}/_ext/1360937237/helper.o ${OBJECTDIR}/_ext/1360937237/i2c_eeprom.o ${OBJECTDIR}/_ext/1360937237/timerDefinitions.o ${OBJECTDIR}/_ext/1360937237/uart.o ${OBJECTDIR}/_ext/1360937237/uart_protocol_handler.o ${OBJECTDIR}/_ext/108923032/drv_i2c.o ${OBJECTDIR}/_ext/1082766828/sys_int_pic32.o

# Source Files
SOURCEFILES=../src/system_config/innoGateway2_base/framework/system/wdt/sys_wdt.c ../src/system_config/innoGateway2_base/bsp/bsp.c ../src/system_config/innoGateway2_base/framework/driver/can/src/drv_can_mapping.c ../src/system_config/innoGateway2_base/framework/driver/can/src/drv_can_static.c ../src/system_config/innoGateway2_base/framework/driver/tmr/src/drv_tmr_static.c ../src/system_config/innoGateway2_base/framework/driver/tmr/src/drv_tmr_mapping.c ../src/system_config/innoGateway2_base/framework/driver/usart/src/drv_usart_mapping.c ../src/system_config/innoGateway2_base/framework/driver/usart/src/drv_usart_static.c ../src/system_config/innoGateway2_base/framework/driver/usart/src/drv_usart_static_byte_model.c ../src/system_config/innoGateway2_base/framework/system/clk/src/sys_clk_pic32mx.c ../src/system_config/innoGateway2_base/framework/system/devcon/src/sys_devcon.c ../src/system_config/innoGateway2_base/framework/system/devcon/src/sys_devcon_pic32mx.c ../src/system_config/innoGateway2_base/framework/system/ports/src/sys_ports_static.c ../src/system_config/innoGateway2_base/system_init.c ../src/system_config/innoGateway2_base/system_interrupt.c ../src/system_config/innoGateway2_base/system_exceptions.c ../src/system_config/innoGateway2_base/system_tasks.c ../src/app.c ../src/main.c ../src/IRMA.c ../src/errorCheck.c ../src/fifoBuffer.c ../src/helper.c ../src/i2c_eeprom.c ../src/timerDefinitions.c ../src/uart.c ../src/uart_protocol_handler.c ../../../../../../../microchip/harmony/v2_04/framework/driver/i2c/src/dynamic/drv_i2c.c ../../../../../../../microchip/harmony/v2_04/framework/system/int/src/sys_int_pic32.c


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
	${MAKE}  -f nbproject/Makefile-innoGateway2_base.mk dist/${CND_CONF}/${IMAGE_TYPE}/innoGateway2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=
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
${OBJECTDIR}/_ext/1756686434/sys_wdt.o: ../src/system_config/innoGateway2_base/framework/system/wdt/sys_wdt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1756686434" 
	@${RM} ${OBJECTDIR}/_ext/1756686434/sys_wdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1756686434/sys_wdt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1756686434/sys_wdt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1756686434/sys_wdt.o.d" -o ${OBJECTDIR}/_ext/1756686434/sys_wdt.o ../src/system_config/innoGateway2_base/framework/system/wdt/sys_wdt.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/797593781/bsp.o: ../src/system_config/innoGateway2_base/bsp/bsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/797593781" 
	@${RM} ${OBJECTDIR}/_ext/797593781/bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/797593781/bsp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/797593781/bsp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/797593781/bsp.o.d" -o ${OBJECTDIR}/_ext/797593781/bsp.o ../src/system_config/innoGateway2_base/bsp/bsp.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1834457159/drv_can_mapping.o: ../src/system_config/innoGateway2_base/framework/driver/can/src/drv_can_mapping.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1834457159" 
	@${RM} ${OBJECTDIR}/_ext/1834457159/drv_can_mapping.o.d 
	@${RM} ${OBJECTDIR}/_ext/1834457159/drv_can_mapping.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1834457159/drv_can_mapping.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1834457159/drv_can_mapping.o.d" -o ${OBJECTDIR}/_ext/1834457159/drv_can_mapping.o ../src/system_config/innoGateway2_base/framework/driver/can/src/drv_can_mapping.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1834457159/drv_can_static.o: ../src/system_config/innoGateway2_base/framework/driver/can/src/drv_can_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1834457159" 
	@${RM} ${OBJECTDIR}/_ext/1834457159/drv_can_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1834457159/drv_can_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1834457159/drv_can_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1834457159/drv_can_static.o.d" -o ${OBJECTDIR}/_ext/1834457159/drv_can_static.o ../src/system_config/innoGateway2_base/framework/driver/can/src/drv_can_static.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/715447426/drv_tmr_static.o: ../src/system_config/innoGateway2_base/framework/driver/tmr/src/drv_tmr_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/715447426" 
	@${RM} ${OBJECTDIR}/_ext/715447426/drv_tmr_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/715447426/drv_tmr_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/715447426/drv_tmr_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/715447426/drv_tmr_static.o.d" -o ${OBJECTDIR}/_ext/715447426/drv_tmr_static.o ../src/system_config/innoGateway2_base/framework/driver/tmr/src/drv_tmr_static.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/715447426/drv_tmr_mapping.o: ../src/system_config/innoGateway2_base/framework/driver/tmr/src/drv_tmr_mapping.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/715447426" 
	@${RM} ${OBJECTDIR}/_ext/715447426/drv_tmr_mapping.o.d 
	@${RM} ${OBJECTDIR}/_ext/715447426/drv_tmr_mapping.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/715447426/drv_tmr_mapping.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/715447426/drv_tmr_mapping.o.d" -o ${OBJECTDIR}/_ext/715447426/drv_tmr_mapping.o ../src/system_config/innoGateway2_base/framework/driver/tmr/src/drv_tmr_mapping.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/124120942/drv_usart_mapping.o: ../src/system_config/innoGateway2_base/framework/driver/usart/src/drv_usart_mapping.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/124120942" 
	@${RM} ${OBJECTDIR}/_ext/124120942/drv_usart_mapping.o.d 
	@${RM} ${OBJECTDIR}/_ext/124120942/drv_usart_mapping.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/124120942/drv_usart_mapping.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/124120942/drv_usart_mapping.o.d" -o ${OBJECTDIR}/_ext/124120942/drv_usart_mapping.o ../src/system_config/innoGateway2_base/framework/driver/usart/src/drv_usart_mapping.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/124120942/drv_usart_static.o: ../src/system_config/innoGateway2_base/framework/driver/usart/src/drv_usart_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/124120942" 
	@${RM} ${OBJECTDIR}/_ext/124120942/drv_usart_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/124120942/drv_usart_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/124120942/drv_usart_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/124120942/drv_usart_static.o.d" -o ${OBJECTDIR}/_ext/124120942/drv_usart_static.o ../src/system_config/innoGateway2_base/framework/driver/usart/src/drv_usart_static.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/124120942/drv_usart_static_byte_model.o: ../src/system_config/innoGateway2_base/framework/driver/usart/src/drv_usart_static_byte_model.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/124120942" 
	@${RM} ${OBJECTDIR}/_ext/124120942/drv_usart_static_byte_model.o.d 
	@${RM} ${OBJECTDIR}/_ext/124120942/drv_usart_static_byte_model.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/124120942/drv_usart_static_byte_model.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/124120942/drv_usart_static_byte_model.o.d" -o ${OBJECTDIR}/_ext/124120942/drv_usart_static_byte_model.o ../src/system_config/innoGateway2_base/framework/driver/usart/src/drv_usart_static_byte_model.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1532472558/sys_clk_pic32mx.o: ../src/system_config/innoGateway2_base/framework/system/clk/src/sys_clk_pic32mx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1532472558" 
	@${RM} ${OBJECTDIR}/_ext/1532472558/sys_clk_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/1532472558/sys_clk_pic32mx.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1532472558/sys_clk_pic32mx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1532472558/sys_clk_pic32mx.o.d" -o ${OBJECTDIR}/_ext/1532472558/sys_clk_pic32mx.o ../src/system_config/innoGateway2_base/framework/system/clk/src/sys_clk_pic32mx.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1960096935/sys_devcon.o: ../src/system_config/innoGateway2_base/framework/system/devcon/src/sys_devcon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1960096935" 
	@${RM} ${OBJECTDIR}/_ext/1960096935/sys_devcon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1960096935/sys_devcon.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1960096935/sys_devcon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1960096935/sys_devcon.o.d" -o ${OBJECTDIR}/_ext/1960096935/sys_devcon.o ../src/system_config/innoGateway2_base/framework/system/devcon/src/sys_devcon.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1960096935/sys_devcon_pic32mx.o: ../src/system_config/innoGateway2_base/framework/system/devcon/src/sys_devcon_pic32mx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1960096935" 
	@${RM} ${OBJECTDIR}/_ext/1960096935/sys_devcon_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/1960096935/sys_devcon_pic32mx.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1960096935/sys_devcon_pic32mx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1960096935/sys_devcon_pic32mx.o.d" -o ${OBJECTDIR}/_ext/1960096935/sys_devcon_pic32mx.o ../src/system_config/innoGateway2_base/framework/system/devcon/src/sys_devcon_pic32mx.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1024927934/sys_ports_static.o: ../src/system_config/innoGateway2_base/framework/system/ports/src/sys_ports_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1024927934" 
	@${RM} ${OBJECTDIR}/_ext/1024927934/sys_ports_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1024927934/sys_ports_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1024927934/sys_ports_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1024927934/sys_ports_static.o.d" -o ${OBJECTDIR}/_ext/1024927934/sys_ports_static.o ../src/system_config/innoGateway2_base/framework/system/ports/src/sys_ports_static.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1332166779/system_init.o: ../src/system_config/innoGateway2_base/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1332166779" 
	@${RM} ${OBJECTDIR}/_ext/1332166779/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1332166779/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1332166779/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1332166779/system_init.o.d" -o ${OBJECTDIR}/_ext/1332166779/system_init.o ../src/system_config/innoGateway2_base/system_init.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1332166779/system_interrupt.o: ../src/system_config/innoGateway2_base/system_interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1332166779" 
	@${RM} ${OBJECTDIR}/_ext/1332166779/system_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1332166779/system_interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1332166779/system_interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1332166779/system_interrupt.o.d" -o ${OBJECTDIR}/_ext/1332166779/system_interrupt.o ../src/system_config/innoGateway2_base/system_interrupt.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1332166779/system_exceptions.o: ../src/system_config/innoGateway2_base/system_exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1332166779" 
	@${RM} ${OBJECTDIR}/_ext/1332166779/system_exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1332166779/system_exceptions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1332166779/system_exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1332166779/system_exceptions.o.d" -o ${OBJECTDIR}/_ext/1332166779/system_exceptions.o ../src/system_config/innoGateway2_base/system_exceptions.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1332166779/system_tasks.o: ../src/system_config/innoGateway2_base/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1332166779" 
	@${RM} ${OBJECTDIR}/_ext/1332166779/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1332166779/system_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1332166779/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1332166779/system_tasks.o.d" -o ${OBJECTDIR}/_ext/1332166779/system_tasks.o ../src/system_config/innoGateway2_base/system_tasks.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/IRMA.o: ../src/IRMA.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/IRMA.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/IRMA.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/IRMA.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1360937237/IRMA.o.d" -o ${OBJECTDIR}/_ext/1360937237/IRMA.o ../src/IRMA.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/errorCheck.o: ../src/errorCheck.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/errorCheck.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/errorCheck.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/errorCheck.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1360937237/errorCheck.o.d" -o ${OBJECTDIR}/_ext/1360937237/errorCheck.o ../src/errorCheck.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/fifoBuffer.o: ../src/fifoBuffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/fifoBuffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/fifoBuffer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/fifoBuffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1360937237/fifoBuffer.o.d" -o ${OBJECTDIR}/_ext/1360937237/fifoBuffer.o ../src/fifoBuffer.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/helper.o: ../src/helper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/helper.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/helper.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/helper.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1360937237/helper.o.d" -o ${OBJECTDIR}/_ext/1360937237/helper.o ../src/helper.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/i2c_eeprom.o: ../src/i2c_eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/i2c_eeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/i2c_eeprom.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/i2c_eeprom.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1360937237/i2c_eeprom.o.d" -o ${OBJECTDIR}/_ext/1360937237/i2c_eeprom.o ../src/i2c_eeprom.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/timerDefinitions.o: ../src/timerDefinitions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/timerDefinitions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/timerDefinitions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/timerDefinitions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1360937237/timerDefinitions.o.d" -o ${OBJECTDIR}/_ext/1360937237/timerDefinitions.o ../src/timerDefinitions.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/uart.o: ../src/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/uart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1360937237/uart.o.d" -o ${OBJECTDIR}/_ext/1360937237/uart.o ../src/uart.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/uart_protocol_handler.o: ../src/uart_protocol_handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/uart_protocol_handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/uart_protocol_handler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/uart_protocol_handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1360937237/uart_protocol_handler.o.d" -o ${OBJECTDIR}/_ext/1360937237/uart_protocol_handler.o ../src/uart_protocol_handler.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/108923032/drv_i2c.o: ../../../../../../../microchip/harmony/v2_04/framework/driver/i2c/src/dynamic/drv_i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/108923032" 
	@${RM} ${OBJECTDIR}/_ext/108923032/drv_i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/108923032/drv_i2c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/108923032/drv_i2c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/108923032/drv_i2c.o.d" -o ${OBJECTDIR}/_ext/108923032/drv_i2c.o ../../../../../../../microchip/harmony/v2_04/framework/driver/i2c/src/dynamic/drv_i2c.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1082766828/sys_int_pic32.o: ../../../../../../../microchip/harmony/v2_04/framework/system/int/src/sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1082766828" 
	@${RM} ${OBJECTDIR}/_ext/1082766828/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1082766828/sys_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1082766828/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DICD3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1082766828/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/1082766828/sys_int_pic32.o ../../../../../../../microchip/harmony/v2_04/framework/system/int/src/sys_int_pic32.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/1756686434/sys_wdt.o: ../src/system_config/innoGateway2_base/framework/system/wdt/sys_wdt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1756686434" 
	@${RM} ${OBJECTDIR}/_ext/1756686434/sys_wdt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1756686434/sys_wdt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1756686434/sys_wdt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1756686434/sys_wdt.o.d" -o ${OBJECTDIR}/_ext/1756686434/sys_wdt.o ../src/system_config/innoGateway2_base/framework/system/wdt/sys_wdt.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/797593781/bsp.o: ../src/system_config/innoGateway2_base/bsp/bsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/797593781" 
	@${RM} ${OBJECTDIR}/_ext/797593781/bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/797593781/bsp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/797593781/bsp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/797593781/bsp.o.d" -o ${OBJECTDIR}/_ext/797593781/bsp.o ../src/system_config/innoGateway2_base/bsp/bsp.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1834457159/drv_can_mapping.o: ../src/system_config/innoGateway2_base/framework/driver/can/src/drv_can_mapping.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1834457159" 
	@${RM} ${OBJECTDIR}/_ext/1834457159/drv_can_mapping.o.d 
	@${RM} ${OBJECTDIR}/_ext/1834457159/drv_can_mapping.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1834457159/drv_can_mapping.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1834457159/drv_can_mapping.o.d" -o ${OBJECTDIR}/_ext/1834457159/drv_can_mapping.o ../src/system_config/innoGateway2_base/framework/driver/can/src/drv_can_mapping.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1834457159/drv_can_static.o: ../src/system_config/innoGateway2_base/framework/driver/can/src/drv_can_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1834457159" 
	@${RM} ${OBJECTDIR}/_ext/1834457159/drv_can_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1834457159/drv_can_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1834457159/drv_can_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1834457159/drv_can_static.o.d" -o ${OBJECTDIR}/_ext/1834457159/drv_can_static.o ../src/system_config/innoGateway2_base/framework/driver/can/src/drv_can_static.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/715447426/drv_tmr_static.o: ../src/system_config/innoGateway2_base/framework/driver/tmr/src/drv_tmr_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/715447426" 
	@${RM} ${OBJECTDIR}/_ext/715447426/drv_tmr_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/715447426/drv_tmr_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/715447426/drv_tmr_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/715447426/drv_tmr_static.o.d" -o ${OBJECTDIR}/_ext/715447426/drv_tmr_static.o ../src/system_config/innoGateway2_base/framework/driver/tmr/src/drv_tmr_static.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/715447426/drv_tmr_mapping.o: ../src/system_config/innoGateway2_base/framework/driver/tmr/src/drv_tmr_mapping.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/715447426" 
	@${RM} ${OBJECTDIR}/_ext/715447426/drv_tmr_mapping.o.d 
	@${RM} ${OBJECTDIR}/_ext/715447426/drv_tmr_mapping.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/715447426/drv_tmr_mapping.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/715447426/drv_tmr_mapping.o.d" -o ${OBJECTDIR}/_ext/715447426/drv_tmr_mapping.o ../src/system_config/innoGateway2_base/framework/driver/tmr/src/drv_tmr_mapping.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/124120942/drv_usart_mapping.o: ../src/system_config/innoGateway2_base/framework/driver/usart/src/drv_usart_mapping.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/124120942" 
	@${RM} ${OBJECTDIR}/_ext/124120942/drv_usart_mapping.o.d 
	@${RM} ${OBJECTDIR}/_ext/124120942/drv_usart_mapping.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/124120942/drv_usart_mapping.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/124120942/drv_usart_mapping.o.d" -o ${OBJECTDIR}/_ext/124120942/drv_usart_mapping.o ../src/system_config/innoGateway2_base/framework/driver/usart/src/drv_usart_mapping.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/124120942/drv_usart_static.o: ../src/system_config/innoGateway2_base/framework/driver/usart/src/drv_usart_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/124120942" 
	@${RM} ${OBJECTDIR}/_ext/124120942/drv_usart_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/124120942/drv_usart_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/124120942/drv_usart_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/124120942/drv_usart_static.o.d" -o ${OBJECTDIR}/_ext/124120942/drv_usart_static.o ../src/system_config/innoGateway2_base/framework/driver/usart/src/drv_usart_static.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/124120942/drv_usart_static_byte_model.o: ../src/system_config/innoGateway2_base/framework/driver/usart/src/drv_usart_static_byte_model.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/124120942" 
	@${RM} ${OBJECTDIR}/_ext/124120942/drv_usart_static_byte_model.o.d 
	@${RM} ${OBJECTDIR}/_ext/124120942/drv_usart_static_byte_model.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/124120942/drv_usart_static_byte_model.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/124120942/drv_usart_static_byte_model.o.d" -o ${OBJECTDIR}/_ext/124120942/drv_usart_static_byte_model.o ../src/system_config/innoGateway2_base/framework/driver/usart/src/drv_usart_static_byte_model.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1532472558/sys_clk_pic32mx.o: ../src/system_config/innoGateway2_base/framework/system/clk/src/sys_clk_pic32mx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1532472558" 
	@${RM} ${OBJECTDIR}/_ext/1532472558/sys_clk_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/1532472558/sys_clk_pic32mx.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1532472558/sys_clk_pic32mx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1532472558/sys_clk_pic32mx.o.d" -o ${OBJECTDIR}/_ext/1532472558/sys_clk_pic32mx.o ../src/system_config/innoGateway2_base/framework/system/clk/src/sys_clk_pic32mx.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1960096935/sys_devcon.o: ../src/system_config/innoGateway2_base/framework/system/devcon/src/sys_devcon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1960096935" 
	@${RM} ${OBJECTDIR}/_ext/1960096935/sys_devcon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1960096935/sys_devcon.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1960096935/sys_devcon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1960096935/sys_devcon.o.d" -o ${OBJECTDIR}/_ext/1960096935/sys_devcon.o ../src/system_config/innoGateway2_base/framework/system/devcon/src/sys_devcon.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1960096935/sys_devcon_pic32mx.o: ../src/system_config/innoGateway2_base/framework/system/devcon/src/sys_devcon_pic32mx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1960096935" 
	@${RM} ${OBJECTDIR}/_ext/1960096935/sys_devcon_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/1960096935/sys_devcon_pic32mx.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1960096935/sys_devcon_pic32mx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1960096935/sys_devcon_pic32mx.o.d" -o ${OBJECTDIR}/_ext/1960096935/sys_devcon_pic32mx.o ../src/system_config/innoGateway2_base/framework/system/devcon/src/sys_devcon_pic32mx.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1024927934/sys_ports_static.o: ../src/system_config/innoGateway2_base/framework/system/ports/src/sys_ports_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1024927934" 
	@${RM} ${OBJECTDIR}/_ext/1024927934/sys_ports_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1024927934/sys_ports_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1024927934/sys_ports_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1024927934/sys_ports_static.o.d" -o ${OBJECTDIR}/_ext/1024927934/sys_ports_static.o ../src/system_config/innoGateway2_base/framework/system/ports/src/sys_ports_static.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1332166779/system_init.o: ../src/system_config/innoGateway2_base/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1332166779" 
	@${RM} ${OBJECTDIR}/_ext/1332166779/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1332166779/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1332166779/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1332166779/system_init.o.d" -o ${OBJECTDIR}/_ext/1332166779/system_init.o ../src/system_config/innoGateway2_base/system_init.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1332166779/system_interrupt.o: ../src/system_config/innoGateway2_base/system_interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1332166779" 
	@${RM} ${OBJECTDIR}/_ext/1332166779/system_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1332166779/system_interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1332166779/system_interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1332166779/system_interrupt.o.d" -o ${OBJECTDIR}/_ext/1332166779/system_interrupt.o ../src/system_config/innoGateway2_base/system_interrupt.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1332166779/system_exceptions.o: ../src/system_config/innoGateway2_base/system_exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1332166779" 
	@${RM} ${OBJECTDIR}/_ext/1332166779/system_exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1332166779/system_exceptions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1332166779/system_exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1332166779/system_exceptions.o.d" -o ${OBJECTDIR}/_ext/1332166779/system_exceptions.o ../src/system_config/innoGateway2_base/system_exceptions.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1332166779/system_tasks.o: ../src/system_config/innoGateway2_base/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1332166779" 
	@${RM} ${OBJECTDIR}/_ext/1332166779/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1332166779/system_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1332166779/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1332166779/system_tasks.o.d" -o ${OBJECTDIR}/_ext/1332166779/system_tasks.o ../src/system_config/innoGateway2_base/system_tasks.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/IRMA.o: ../src/IRMA.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/IRMA.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/IRMA.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/IRMA.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1360937237/IRMA.o.d" -o ${OBJECTDIR}/_ext/1360937237/IRMA.o ../src/IRMA.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/errorCheck.o: ../src/errorCheck.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/errorCheck.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/errorCheck.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/errorCheck.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1360937237/errorCheck.o.d" -o ${OBJECTDIR}/_ext/1360937237/errorCheck.o ../src/errorCheck.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/fifoBuffer.o: ../src/fifoBuffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/fifoBuffer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/fifoBuffer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/fifoBuffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1360937237/fifoBuffer.o.d" -o ${OBJECTDIR}/_ext/1360937237/fifoBuffer.o ../src/fifoBuffer.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/helper.o: ../src/helper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/helper.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/helper.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/helper.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1360937237/helper.o.d" -o ${OBJECTDIR}/_ext/1360937237/helper.o ../src/helper.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/i2c_eeprom.o: ../src/i2c_eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/i2c_eeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/i2c_eeprom.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/i2c_eeprom.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1360937237/i2c_eeprom.o.d" -o ${OBJECTDIR}/_ext/1360937237/i2c_eeprom.o ../src/i2c_eeprom.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/timerDefinitions.o: ../src/timerDefinitions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/timerDefinitions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/timerDefinitions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/timerDefinitions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1360937237/timerDefinitions.o.d" -o ${OBJECTDIR}/_ext/1360937237/timerDefinitions.o ../src/timerDefinitions.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/uart.o: ../src/uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/uart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1360937237/uart.o.d" -o ${OBJECTDIR}/_ext/1360937237/uart.o ../src/uart.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/uart_protocol_handler.o: ../src/uart_protocol_handler.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/uart_protocol_handler.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/uart_protocol_handler.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/uart_protocol_handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1360937237/uart_protocol_handler.o.d" -o ${OBJECTDIR}/_ext/1360937237/uart_protocol_handler.o ../src/uart_protocol_handler.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/108923032/drv_i2c.o: ../../../../../../../microchip/harmony/v2_04/framework/driver/i2c/src/dynamic/drv_i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/108923032" 
	@${RM} ${OBJECTDIR}/_ext/108923032/drv_i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/108923032/drv_i2c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/108923032/drv_i2c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/108923032/drv_i2c.o.d" -o ${OBJECTDIR}/_ext/108923032/drv_i2c.o ../../../../../../../microchip/harmony/v2_04/framework/driver/i2c/src/dynamic/drv_i2c.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1082766828/sys_int_pic32.o: ../../../../../../../microchip/harmony/v2_04/framework/system/int/src/sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1082766828" 
	@${RM} ${OBJECTDIR}/_ext/1082766828/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1082766828/sys_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1082766828/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../../microchip/harmony/v2_04/framework" -I"../src" -I"../src/system_config/innoGateway2_base" -I"../src/innoGateway2_base" -I"../../../../../../../microchip/harmony/v2_04/framework" -I"../src/system_config/innoGateway2_base/framework" -I"../src/system_config/innoGateway2_base/bsp" -MMD -MF "${OBJECTDIR}/_ext/1082766828/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/1082766828/sys_int_pic32.o ../../../../../../../microchip/harmony/v2_04/framework/system/int/src/sys_int_pic32.c    -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/innoGateway2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../../../../microchip/harmony/v2_04/bin/framework/peripheral/PIC32MX795F512L_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -DICD3PlatformTool=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/innoGateway2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\..\..\..\microchip\harmony\v2_04\bin\framework\peripheral\PIC32MX795F512L_peripherals.a      -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=ICD3PlatformTool=1,--defsym=_min_heap_size=0,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/innoGateway2.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../../../../microchip/harmony/v2_04/bin/framework/peripheral/PIC32MX795F512L_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/innoGateway2.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\..\..\..\microchip\harmony\v2_04\bin\framework\peripheral\PIC32MX795F512L_peripherals.a      -DXPRJ_innoGateway2_base=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=0,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/innoGateway2.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/innoGateway2_base
	${RM} -r dist/innoGateway2_base

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
