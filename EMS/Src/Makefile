#
# The material contained herein is not a license, either      
# expressly or impliedly, to any intellectual property owned  
# or controlled by any of the authors or developers of this   
# material or to any contribution thereto. The material       
# contained herein is provided on an "AS IS" basis and, to the
# maximum extent permitted by applicable law, this information
# is provided AS IS AND WITH ALL FAULTS, and the authors and  
# developers of this material hereby disclaim all other       
# warranties and conditions, either express, implied or       
# statutory, including, but not limited to, any (if any)      
# implied warranties, duties or conditions of merchantability,
# of fitness for a particular purpose, of accuracy or         
# completeness of responses, of results, of workmanlike       
# effort, of lack of viruses and of lack of negligence, all   
# with regard to this material and any contribution thereto.  
# Designers must not rely on the absence or characteristics of
# any features or instructions marked "reserved" or           
# "undefined." The Unified EFI Forum, Inc. reserves any       
# features or instructions so marked for future definition and
# shall have no responsibility whatsoever for conflicts or    
# incompatibilities arising from future changes to them. ALSO,
# THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,
# QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR          
# NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY      
# CONTRIBUTION THERETO.                                       
#                                                             
# IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR
# ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR   
# THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST    
# PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,      
# CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER 
# UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY
# WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS     
# DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF   
# THE POSSIBILITY OF SUCH DAMAGES.                            
#                                                             
# Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All
# Rights Reserved, subject to all existing rights in all      
# matters included within this Test Suite, to which United    
# EFI, Inc. makes no claim of right.                          
#                                                             
# Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR> 
#
#
#/*++
#   
# Module Name:  Makefile.win
#   
#  Abstract:
#   
#    This file is used to build the Ems.exe 
#   
#--*/

#
# Everything depends on EMS_DIR. Make sure it's defined
#
!IFNDEF EMS_DIR
!ERROR EMS_DIR environmental variable not set 
!ENDIF

MAKE            = nmake -nologo

#MSDEV_BASE           = C:\Program Files\Microsoft Visual Studio 8
MSDEV_BASE           = C:\Program Files (x86)\Microsoft Visual Studio 8
DevEnvDir            = $(MSDEV_BASE)\Common7\IDE
MSVCDIR              = $(MSDEV_BASE)\VC
MSVS_INC             = $(MSVCDIR)\Include
MSVS_LIB             = $(MSVCDIR)\Lib
MSVS_PLATFORMSDK_INC = $(MSVCDIR)\PlatformSdk\Include
MSVS_PLATFORMSDK_LIB = $(MSVCDIR)\PlatformSdk\Lib
MSVS_ATL_INC         = $(MSVCDIR)\atlmfc\Include
MSVS_ATL_LIB         = $(MSVCDIR)\atlmfc\Lib
VCINSTALLDIR         = $(MSDEV_BASE)

!IFNDEF VCPATH
PATH=$(MSVCDIR)\Bin;$(DevEnvDir);$(VCINSTALLDIR)\Common7\Tools;$(VCINSTALLDIR)\Common7\Tools\bin;\$(FrameworkVersion);$(PATH);
INCLUDE=$(MSVCDIR)\ATLMFC\INCLUDE;$(MSVCDIR)\INCLUDE;$(MSVCDIR)\PlatformSDK\include;$(INCLUDE)
LIB=$(MSVCDIR)\ATLMFC\LIB;$(MSVCDIR)\LIB;$(MSVCDIR)\PlatformSDK\lib;$(LIB)
VCPATH = YES
!ENDIF

SOURCE_DIR            = $(EMS_DIR)\Src
EMSINCPATH            = $(SOURCE_DIR)\Include 
EMSLIBPATH            = $(EMS_DIR)\Lib
EMSBINPATH            = $(EMS_DIR)\Bin

CC                   = cl
LINK                 = link
LIB                  = lib


#
# Dependency libraries
#
WPCAP_INCPATH     = $(EMSLIBPATH)\WpdPack\Include
WPCAP_LIBPATH     = $(EMSLIBPATH)\WpdPack\Lib

LIBNET_INCPATH     = $(EMSLIBPATH)\Libnet\Include\Win32
LIBNET_LIBPATH     = $(EMSLIBPATH)\Libnet\Lib
                   
TCL_INCPATH        = $(EMSLIBPATH)\Tcl\Include
TCL_LIBPATH        = $(EMSLIBPATH)\Tcl\Lib
                   
EMS_LINK_LIBPATHS  = /LIBPATH:"$(MSVS_LIB)" /LIBPATH:"$(MSVS_PLATFORMSDK_LIB)" \
                     /LIBPATH:"$(WPCAP_LIBPATH)" /LIBPATH:"$(LIBNET_LIBPATH)" \
                     /LIBPATH:"$(TCL_LIBPATH)"

EMS_INCPATHS       = /I"$(WPCAP_INCPATH)" /I"$(LIBNET_INCPATH)" /I"$(MSVS_INC)"\
                     /I"$(TCL_INCPATH)" /I"$(EMS_DIR)/Src/EmsProtocol"        \
                     /I"$(EMS_DIR)/Src/Include"

EMS_LIBS           = libnet.lib tcl84.lib tk84.lib tclstub84.lib wpcap.lib iphlpapi.lib Advapi32.lib

CFLAGS             = /nologo /W3 /Gy /c $(EMS_INCPATHS) /D "WIN32"        \
                     /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Gm /EHsc  /RTC1 /MTd \
                     /TC  /D "__WIN32__" /D "__CYGWIN__"        \
                     /D "WITH_GUI" /LDd /Zi /D "TCL_THREADS" /D "_CRT_SECURE_NO_DEPRECATE"

#LFLAGS       = $(EMS_LINK_LIBPATHS)
LFLAGS      = $(EMS_LINK_LIBPATHS) /DEBUG /PDB:"..\bin\ems.pdb"

TARGETNAME   =  $(EMSBINPATH)\Ems.exe

MAINOBJ      =  $(SOURCE_DIR)\EmsMain.obj
TCLOBJS      =  $(SOURCE_DIR)\EmsTclInit\EmsTclInit.obj                \
                $(SOURCE_DIR)\EmsTclInit\EmsTclCleanup.obj
EFTPOBJS     =  $(SOURCE_DIR)\EmsEftp\EmsEftp.obj                      \
                $(SOURCE_DIR)\EmsEftp\EmsEftpSession.obj               \
                $(SOURCE_DIR)\EmsEftp\EmsEftpRrqStrategy.obj           \
                $(SOURCE_DIR)\EmsEftp\EmsEftpWrqStrategy.obj

LOGOBJS      =  $(SOURCE_DIR)\EmsLog\EmsLogUtility.obj                 \
                $(SOURCE_DIR)\EmsLog\EmslogCommand.obj                 \
                $(SOURCE_DIR)\EmsLog\EmsLogReport.obj

PACKETOBJS   =  $(SOURCE_DIR)\EmsPacket\EmsPktPattern.obj              \
                $(SOURCE_DIR)\EmsPacket\EmsPktValidate.obj             \
                $(SOURCE_DIR)\EmsPacket\EmsPktMain.obj                 \
                $(SOURCE_DIR)\EmsPacket\EmsPktCapture.obj              \
                $(SOURCE_DIR)\EmsPacket\EmsPktCcb.obj                  \
                $(SOURCE_DIR)\EmsPacket\EmsPktCreate.obj               \
                $(SOURCE_DIR)\EmsPacket\EmsPktParse.obj                \
                $(SOURCE_DIR)\EmsPacket\EmsPktPayload.obj              \
                $(SOURCE_DIR)\EmsPacket\EmsPktDump.obj                 \
                $(SOURCE_DIR)\EmsPacket\EmsPktSend.obj                 \
                $(SOURCE_DIR)\EmsPacket\EmsPktRecvAssertion.obj

PROTOCOLOBJS =  $(SOURCE_DIR)\EmsProtocol\EmsProtocols.obj             \
                $(SOURCE_DIR)\EmsProtocol\EmsProtoEth.obj              \
                $(SOURCE_DIR)\EmsProtocol\EmsProtoIp.obj               \
                $(SOURCE_DIR)\EmsProtocol\EmsProtoIgmp.obj             \
                $(SOURCE_DIR)\EmsProtocol\EmsProtoArp.obj              \
                $(SOURCE_DIR)\EmsProtocol\EmsProtoUdp.obj              \
                $(SOURCE_DIR)\EmsProtocol\EmsProtoIcmp.obj             \
                $(SOURCE_DIR)\EmsProtocol\EmsProtoDhcp.obj             \
                $(SOURCE_DIR)\EmsProtocol\EmsProtoTcp.obj              \
                $(SOURCE_DIR)\EmsProtocol\EmsProtoIpv6.obj

INTERFACEOBJ =  $(SOURCE_DIR)\EmsInterface\EmsInterfaceMain.obj        \
                $(SOURCE_DIR)\EmsInterface\EmsVirtualInterface.obj

RPCOBJS      =  $(SOURCE_DIR)\EmsRpc\EmsRpcMain.obj                    \
                $(SOURCE_DIR)\EmsRpc\EmsRpcEth.obj                     \
                $(SOURCE_DIR)\EmsRpc\EmsRpcTarget.obj                  \
                $(SOURCE_DIR)\EmsRpc\EmsRpcMsg.obj
                                                                       
UTILITYOBJS  =  $(SOURCE_DIR)\EmsUtility\EmsUtilityString.obj          \
                $(SOURCE_DIR)\EmsUtility\EmsUtilityStall.obj           \
                $(SOURCE_DIR)\EmsUtility\EmsUtilityInclude.obj         \
                $(SOURCE_DIR)\EmsUtility\EmsUtilityMain.obj

RIVLOBJS     =  $(SOURCE_DIR)\EmsRivl\EmsRivlMain.obj                  \
                $(SOURCE_DIR)\EmsRivl\EmsRivlEndian.obj                \
                $(SOURCE_DIR)\EmsRivl\EmsRivlType.obj                  \
                $(SOURCE_DIR)\EmsRivl\EmsRivlInterType.obj             \
                $(SOURCE_DIR)\EmsRivl\EmsRivlExterType.obj             \
                $(SOURCE_DIR)\EmsRivl\EmsRivlVar.obj                   \
                $(SOURCE_DIR)\EmsRivl\EmsRivlNameScope.obj             \
                $(SOURCE_DIR)\EmsRivl\EmsRivlGetVar.obj                \
                $(SOURCE_DIR)\EmsRivl\EmsRivlTypedef.obj               \
                $(SOURCE_DIR)\EmsRivl\EmsRivlFunc.obj                  \
                $(SOURCE_DIR)\EmsRivl\EmsRivFuncDef.obj                \
                $(SOURCE_DIR)\EmsRivl\EmsRivlUtil.obj                  \
                $(SOURCE_DIR)\EmsRivl\EmsRivlDump.obj                  \
                $(SOURCE_DIR)\EmsRivl\EmsRivlRemoteDel.obj             \
                $(SOURCE_DIR)\EmsRivl\EmsRivlFuncDecl.obj              \
                $(SOURCE_DIR)\EmsRivl\EmsRivlTestExit.obj              \
                $(SOURCE_DIR)\EmsRivl\EmsRivlSizeof.obj                \
                $(SOURCE_DIR)\EmsRivl\EmsRivlTypeof.obj                \
                $(SOURCE_DIR)\EmsRivl\EmsRivlTclVar.obj                \
                $(SOURCE_DIR)\EmsRivl\EmsRivlSetVar.obj                \
                $(SOURCE_DIR)\EmsRivl\EmsRivlDeltclVar.obj             \
                $(SOURCE_DIR)\EmsRivl\EmsRivlGetAck.obj                \
                $(SOURCE_DIR)\EmsRivl\EmsRivlExec.obj

VTCPOBJ      =  $(SOURCE_DIR)\EmsVtcp\EmsVtcpMain.obj                  \
                $(SOURCE_DIR)\EmsVtcp\EmsVtcpTcb.obj                   \
                $(SOURCE_DIR)\EmsVtcp\EmsVtcpNamedList.obj

THREADOBJ    =  $(SOURCE_DIR)\EmsThread\EmsThread.obj

TIMEROBJ     =  $(SOURCE_DIR)\EmsTimer\EmsTimer.obj

TESTOBJ      =  $(SOURCE_DIR)\EmsTest\EmsTest.obj

OBJ          =  $(MAINOBJ) $(PROTOCOLOBJS) $(PACKETOBJS) \
                $(UTILITYOBJS) $(TCLOBJS) \
                $(INTERFACEOBJ)  $(RPCOBJS) $(EFTPOBJS) $(RIVLOBJS) \
                $(LOGOBJS) $(VTCPOBJ) $(THREADOBJ) $(TIMEROBJ) $(TESTOBJ)

all : $(TARGETNAME)

$(TARGETNAME): $(OBJ) 
    $(LINK) /OUT:"$(TARGETNAME)" $(OBJ) $(LFLAGS) $(EMS_LIBS)

#$(OBJ): $*.c
#{EMSBINPATH}.c{$(EMSBINPATH)}.obj::

.c.obj:
  $(CC) $(CFLAGS) -Fo$* -c $*.c



rebuild : clean  all
clean:
  del /F $(TARGETNAME)
  del /F $(MAINOBJ)
  del /F $(TCLOBJS)
  del /F $(EFTPOBJS)
  del /F $(LOGOBJS)
  del /F $(PACKETOBJS)
  del /F $(PROTOCOLOBJS)
  del /F $(INTERFACEOBJ)
  del /F $(RPCOBJS)
  del /F $(UTILITYOBJS)
  del /F $(RIVLOBJS)
  del /F $(VTCPOBJ)
  del /F $(THREADOBJ)
  del /F $(TIMEROBJ)
  del /F $(TESTOBJ)
  del /F $(EMSBINPATH)\Ems.ilk $(EMSBINPATH)\ems.pdb $(EMSBINPATH)\CaseTree.ini $(EMSBINPATH)\TempSeq.seq
  del /F $(SOURCE_DIR)\vc80.idb del /F $(SOURCE_DIR)\vc80.pdb
