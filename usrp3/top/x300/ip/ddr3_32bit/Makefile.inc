#
# Copyright 2014 Ettus Research
#

include $(TOOLS_DIR)/make/viv_ip_builder.mak

IP_DDR3_32BIT_SRCS = $(IP_BUILD_DIR)/ddr3_32bit/ddr3_32bit.xci

IP_DDR3_32BIT_OUTS = $(addprefix $(IP_BUILD_DIR)/ddr3_32bit/, \
ddr3_32bit/user_design/rtl/ddr3_32bit.v \
ddr3_32bit/user_design/rtl/ddr3_32bit_mig.v \
)

IP_DDR3_32BIT_SIM_OUTS = $(addprefix $(IP_BUILD_DIR)/ddr3_32bit/, \
ddr3_32bit/example_design/sim/ddr3_model.v \
ddr3_32bit/example_design/sim/ddr3_model_parameters.vh \
)


$(IP_DDR3_32BIT_SRCS) $(IP_DDR3_32BIT_OUTS) : $(IP_DIR)/ddr3_32bit/ddr3_32bit.xci $(IP_DIR)/ddr3_32bit/mig_*.prj
	mkdir -p $(IP_BUILD_DIR)/ddr3_32bit
	ln -fs mig_$(subst /,,$(PART_ID)).prj $(IP_BUILD_DIR)/ddr3_32bit/mig_a.prj
	$(call BUILD_VIVADO_IP,ddr3_32bit,$(PART_ID),$(IP_DIR),$(IP_BUILD_DIR),0)
	patch $(IP_BUILD_DIR)/ddr3_32bit/ddr3_32bit/user_design/rtl/clocking/mig_7series_v2_3_iodelay_ctrl.v $(IP_DIR)/ddr3_32bit/mig_7series_v2_3_iodelay_ctrl.v.patch
	patch $(IP_BUILD_DIR)/ddr3_32bit/ddr3_32bit/user_design/rtl/clocking/mig_7series_v2_3_infrastructure.v $(IP_DIR)/ddr3_32bit/mig_7series_v2_3_infrastructure.v.patch
	patch $(IP_BUILD_DIR)/ddr3_32bit/ddr3_32bit/user_design/rtl/ddr3_32bit_mig.v $(IP_DIR)/ddr3_32bit/ddr3_32bit_mig.v.patch
	patch $(IP_BUILD_DIR)/ddr3_32bit/ddr3_32bit/user_design/rtl/ddr3_32bit.v $(IP_DIR)/ddr3_32bit/ddr3_32bit.v.patch