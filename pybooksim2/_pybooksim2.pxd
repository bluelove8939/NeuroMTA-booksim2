cdef extern from "py_interface.h":
    void *pybooksim2_create_icnt(char *config_file, bint print_activity, bint print_trace, char *output_file) nogil
    void  pybooksim2_destroy_icnt(void *icnt_p) nogil

    void *pybooksim2_create_icnt_cmd_data_packet(int src_id, int dst_id, int subnet, int size, bint is_write) nogil
    void *pybooksim2_create_icnt_cmd_control_packet(int src_id, int dst_id, int subnet, int size) nogil
    void  pybooksim2_destroy_icnt_cmd(void *cmd_p) nogil

    char  pybooksim2_check_icnt_cmd_executed(void *cmd_p) nogil

    void  pybooksim2_icnt_dispatch_cmd(void *icnt_p, void *cmd_p) nogil
    void  pybooksim2_icnt_cycle_step(void *icnt_p) nogil
