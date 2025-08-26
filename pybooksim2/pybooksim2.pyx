# cython: language_level=3
import cython
from cpython.bytes cimport PyBytes_AsString
from cpython.pycapsule cimport PyCapsule_New, PyCapsule_GetPointer, PyCapsule_Destructor
from ._pybooksim2 cimport (
    pybooksim2_create_icnt,
    pybooksim2_destroy_icnt,

    pybooksim2_create_icnt_cmd_data_packet,
    pybooksim2_create_icnt_cmd_control_packet,
    pybooksim2_destroy_icnt_cmd,

    pybooksim2_check_icnt_cmd_executed,

    pybooksim2_icnt_dispatch_cmd,
    pybooksim2_icnt_cycle_step
)


cdef bytes ICNT_CAPSULE_NAME = b"pybooksim2.icnt"
cdef bytes CMD_CAPSULE_NAME  = b"pybooksim2.cmd"

cdef void icnt_capsule_destructor(capsule) except *:
    cdef void* p = PyCapsule_GetPointer(capsule, ICNT_CAPSULE_NAME)
    if p != NULL:
        pybooksim2_destroy_icnt(p)

cdef void cmd_capsule_destructor(capsule) except *:
    cdef void* p = PyCapsule_GetPointer(capsule, CMD_CAPSULE_NAME)
    if p != NULL:
        pybooksim2_destroy_icnt_cmd(p)


@cython.boundscheck(False)
@cython.wraparound(False)
def create_icnt(config_file, bint print_activity=0, bint print_trace=0, output_file=None):
    cdef char *config_file_p = PyBytes_AsString(config_file.encode("ascii"))
    cdef char *output_file_p
    if output_file is None:
        output_file_p = NULL
    else:
        output_file_p = PyBytes_AsString(output_file.encode("ascii"))
    cdef void *icnt_p = pybooksim2_create_icnt(config_file_p, print_activity, print_trace, output_file_p)

    cap = PyCapsule_New(icnt_p, ICNT_CAPSULE_NAME, <PyCapsule_Destructor> icnt_capsule_destructor)
    return cap


@cython.boundscheck(False)
@cython.wraparound(False)
def create_icnt_cmd_data_packet(int src_id, int dst_id, int subnet, int size, bint is_write):
    cdef void *cmd_p = pybooksim2_create_icnt_cmd_data_packet(src_id, dst_id, subnet, size, is_write)
    cap = PyCapsule_New(cmd_p, CMD_CAPSULE_NAME, <PyCapsule_Destructor> cmd_capsule_destructor)
    return cap

@cython.boundscheck(False)
@cython.wraparound(False)
def create_icnt_cmd_control_packet(int src_id, int dst_id, int subnet, int size):
    cdef void *cmd_p = pybooksim2_create_icnt_cmd_control_packet(src_id, dst_id, subnet, size)
    cap = PyCapsule_New(cmd_p, CMD_CAPSULE_NAME, <PyCapsule_Destructor> cmd_capsule_destructor)
    return cap


@cython.boundscheck(False)
@cython.wraparound(False)
def check_icnt_cmd_executed(cmd):
    cdef void *cmd_p = PyCapsule_GetPointer(cmd, CMD_CAPSULE_NAME)
    cdef bint flag = pybooksim2_check_icnt_cmd_executed(cmd_p)
    return flag


@cython.boundscheck(False)
@cython.wraparound(False)
def icnt_dispatch_cmd(icnt, cmd):
    cdef void *icnt_p = PyCapsule_GetPointer(icnt, ICNT_CAPSULE_NAME)
    cdef void *cmd_p = PyCapsule_GetPointer(cmd, CMD_CAPSULE_NAME)
    pybooksim2_icnt_dispatch_cmd(icnt_p, cmd_p)

@cython.boundscheck(False)
@cython.wraparound(False)
def icnt_cycle_step(icnt, int cycles):
    cdef void *icnt_p = PyCapsule_GetPointer(icnt, ICNT_CAPSULE_NAME)
    for _ in range(cycles):
        pybooksim2_icnt_cycle_step(icnt_p)