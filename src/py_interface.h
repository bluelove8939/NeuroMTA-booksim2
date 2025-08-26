#ifndef __PYDRAMSIM3_INTERFACE_H
#define __PYDRAMSIM3_INTERFACE_H

#include <sstream>
#include <fstream>
#include <memory>
#include "globals.hpp"

#pragma once
#ifdef __cplusplus
extern "C" {
#endif


void *pybooksim2_create_icnt(char *config_file, char print_activity, char print_trace, char *output_file);
void  pybooksim2_destroy_icnt(void *icnt_p);

void *pybooksim2_create_icnt_cmd_data_packet(int src_id, int dst_id, int subnet, int size, char is_write);
void *pybooksim2_create_icnt_cmd_control_packet(int src_id, int dst_id, int subnet, int size);
void  pybooksim2_destroy_icnt_cmd(void *cmd_p);

char  pybooksim2_check_icnt_cmd_executed(void *cmd_p);

void  pybooksim2_icnt_dispatch_cmd(void *icnt_p, void *cmd_p);
void  pybooksim2_icnt_cycle_step(void *icnt_p);


#ifdef __cplusplus
}
#endif

#endif