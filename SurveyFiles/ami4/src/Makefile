#
# OMNeT++/OMNEST Makefile for ami
#
# This file was generated with the command:
#  opp_makemake -f --deep -IF:/Documents/Research/workspace/inet/src/networklayer/ipv4 -IF:/Documents/Research/workspace/MiXiM/src/base/modules -IF:/Documents/Research/workspace/inet/src/networklayer/common -IF:/Documents/Research/workspace/inet/src/base -IF:/Documents/Research/workspace/MiXiM/src -IF:/Documents/Research/workspace/inet/src/mobility/models -IF:/Documents/Research/workspace/inet/src/networklayer/contract -IF:/Documents/Research/workspace/MiXiM/src/base/utils -IF:/Documents/Research/workspace/inet/src/mobility -IF:/Documents/Research/workspace/MiXiM/src/base -IF:/Documents/Research/workspace/inet/src/util -IF:/Documents/Research/workspace/MiXiM/src/base/phyLayer -IF:/Documents/Research/workspace/inet/src/applications/pingapp -IF:/Documents/Research/workspace/inet/src/linklayer/contract -IF:/Documents/Research/workspace/inet/src/networklayer/arp -IF:/Documents/Research/workspace/MiXiM/src/base/connectionManager -IF:/Documents/Research/workspace/MiXiM/src/base/messages -IF:/Documents/Research/workspace/MiXiM/src/modules/utility -IF:/Documents/Research/workspace/MiXiM/src/modules/phy -IF:/Documents/Research/workspace/MiXiM/src/modules/analogueModel -IF:/Documents/Research/workspace/MiXiM/src/modules/messages -IF:/Documents/Research/workspace/MiXiM/src/modules -LF:/Documents/Research/workspace/MiXiM/out/$(CONFIGNAME)/src -LF:/Documents/Research/workspace/inet/out/$(CONFIGNAME)/src -lmixim -linet -DMIXIM_INET=1 -DINET_IMPORT -KMIXIM_PROJ=F:/Documents/Research/workspace/MiXiM -KINET_PROJ=F:/Documents/Research/workspace/inet
#

# Name of target to be created (-o option)
TARGET = ami$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I$(INET_PROJ)/src/networklayer/ipv4 \
    -I$(MIXIM_PROJ)/src/base/modules \
    -I$(INET_PROJ)/src/networklayer/common \
    -I$(INET_PROJ)/src/base \
    -I$(MIXIM_PROJ)/src \
    -I$(INET_PROJ)/src/mobility/models \
    -I$(INET_PROJ)/src/networklayer/contract \
    -I$(MIXIM_PROJ)/src/base/utils \
    -I$(INET_PROJ)/src/mobility \
    -I$(MIXIM_PROJ)/src/base \
    -I$(INET_PROJ)/src/util \
    -I$(MIXIM_PROJ)/src/base/phyLayer \
    -I$(INET_PROJ)/src/applications/pingapp \
    -I$(INET_PROJ)/src/linklayer/contract \
    -I$(INET_PROJ)/src/networklayer/arp \
    -I$(MIXIM_PROJ)/src/base/connectionManager \
    -I$(MIXIM_PROJ)/src/base/messages \
    -I$(MIXIM_PROJ)/src/modules/utility \
    -I$(MIXIM_PROJ)/src/modules/phy \
    -I$(MIXIM_PROJ)/src/modules/analogueModel \
    -I$(MIXIM_PROJ)/src/modules/messages \
    -I$(MIXIM_PROJ)/src/modules \
    -I. \
    -Inet \
    -InodeColector \
    -InodeMeshUnder \
    -InodeRouteOver \
    -Iphylayerplc

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L$(MIXIM_PROJ)/out/$(CONFIGNAME)/src -L$(INET_PROJ)/out/$(CONFIGNAME)/src  -lmixim -linet
LIBS += -Wl,-rpath,`abspath $(MIXIM_PROJ)/out/$(CONFIGNAME)/src` -Wl,-rpath,`abspath $(INET_PROJ)/out/$(CONFIGNAME)/src`

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/net/Adaptation.o \
    $O/net/MeshUnder.o \
    $O/net/NetLayer.o \
    $O/net/NetLayerCollector.o \
    $O/net/NetworkToMacControlInfo.o \
    $O/net/RouteOver.o \
    $O/net/RoutingTablesConf.o \
    $O/phylayerplc/PERModelPLC.o \
    $O/phylayerplc/PhyLayerPLC.o \
    $O/Fragment_m.o \
    $O/Packet_m.o

# Message files
MSGFILES = \
    Fragment.msg \
    Packet.msg

# Other makefile variables (-K)
MIXIM_PROJ=F:/Documents/Research/workspace/MiXiM
INET_PROJ=F:/Documents/Research/workspace/inet

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS) -DMIXIM_INET=1 -DINET_IMPORT $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f ami ami.exe libami.so libami.a libami.dll libami.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f net/*_m.cc net/*_m.h
	$(Q)-rm -f nodeColector/*_m.cc nodeColector/*_m.h
	$(Q)-rm -f nodeMeshUnder/*_m.cc nodeMeshUnder/*_m.h
	$(Q)-rm -f nodeRouteOver/*_m.cc nodeRouteOver/*_m.h
	$(Q)-rm -f phylayerplc/*_m.cc phylayerplc/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc net/*.cc nodeColector/*.cc nodeMeshUnder/*.cc nodeRouteOver/*.cc phylayerplc/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/Fragment_m.o: Fragment_m.cc \
	Fragment_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h
$O/Packet_m.o: Packet_m.cc \
	Packet_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h
$O/net/Adaptation.o: net/Adaptation.cc \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/NetwToMacControlInfo.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	Fragment_m.h \
	Packet_m.h \
	net/Adaptation.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h
$O/net/MeshUnder.o: net/MeshUnder.cc \
	$(MIXIM_PROJ)/src/base/modules/ArpInterface.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/NetwToMacControlInfo.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	Fragment_m.h \
	Packet_m.h \
	net/MeshUnder.h \
	net/NetworkToMacControlInfo.h \
	net/RoutingTablesConf.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/networklayer/arp/ARP.h \
	$(INET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTableAccess.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/util/FWMath.h
$O/net/NetLayer.o: net/NetLayer.cc \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	Packet_m.h \
	net/NetLayer.h \
	net/RoutingTablesConf.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/mobility/IMobility.h \
	$(INET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTableAccess.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/util/FWMath.h
$O/net/NetLayerCollector.o: net/NetLayerCollector.cc \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	Packet_m.h \
	net/NetLayerCollector.h \
	net/RoutingTablesConf.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/mobility/IMobility.h \
	$(INET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTableAccess.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/util/FWMath.h
$O/net/NetworkToMacControlInfo.o: net/NetworkToMacControlInfo.cc \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	net/NetworkToMacControlInfo.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h
$O/net/RouteOver.o: net/RouteOver.cc \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/NetwToMacControlInfo.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	Fragment_m.h \
	Packet_m.h \
	net/NetworkToMacControlInfo.h \
	net/RouteOver.h \
	net/RoutingTablesConf.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/linklayer/contract/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTableAccess.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/util/FWMath.h
$O/net/RoutingTablesConf.o: net/RoutingTablesConf.cc \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	net/NetLayer.h \
	net/RoutingTablesConf.h \
	$(INET_PROJ)/src/base/BasicModule.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/mobility/IMobility.h \
	$(INET_PROJ)/src/mobility/models/MobilityAccess.h \
	$(INET_PROJ)/src/mobility/models/MobilityBase.h \
	$(INET_PROJ)/src/mobility/models/StationaryMobility.h \
	$(INET_PROJ)/src/networklayer/common/IInterfaceTable.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceEntry.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceTableAccess.h \
	$(INET_PROJ)/src/networklayer/common/InterfaceToken.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/networklayer/ipv4/IPv4InterfaceData.h \
	$(INET_PROJ)/src/util/FWMath.h
$O/phylayerplc/PERModelPLC.o: phylayerplc/PERModelPLC.cc \
	$(MIXIM_PROJ)/src/base/messages/MiXiMAirFrame.h \
	$(MIXIM_PROJ)/src/base/messages/MiximAirFrame_m.h \
	$(MIXIM_PROJ)/src/base/phyLayer/AnalogueModel.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Interpolation.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Mapping.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingBase.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Signal_.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	phylayerplc/PERModelPLC.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/util/FWMath.h
$O/phylayerplc/PhyLayerPLC.o: phylayerplc/PhyLayerPLC.cc \
	$(MIXIM_PROJ)/src/base/connectionManager/ConnectionManagerAccess.h \
	$(MIXIM_PROJ)/src/base/messages/MiXiMAirFrame.h \
	$(MIXIM_PROJ)/src/base/messages/MiximAirFrame_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/phyLayer/AnalogueModel.h \
	$(MIXIM_PROJ)/src/base/phyLayer/BasePhyLayer.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelInfo.h \
	$(MIXIM_PROJ)/src/base/phyLayer/ChannelState.h \
	$(MIXIM_PROJ)/src/base/phyLayer/DeciderToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Interpolation.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MacToPhyInterface.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Mapping.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingBase.h \
	$(MIXIM_PROJ)/src/base/phyLayer/MappingUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/PhyUtils.h \
	$(MIXIM_PROJ)/src/base/phyLayer/Signal_.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayer.h \
	$(MIXIM_PROJ)/src/modules/phy/PhyLayerBattery.h \
	phylayerplc/PERModelPLC.h \
	phylayerplc/PhyLayerPLC.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/mobility/IMobility.h \
	$(INET_PROJ)/src/mobility/models/MobilityAccess.h \
	$(INET_PROJ)/src/util/FWMath.h

