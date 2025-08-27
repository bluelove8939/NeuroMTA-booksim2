from ctypes import c_void_p


__all__ = [
    "create_icnt",
    "create_icnt_cmd_data_packet",
    "create_icnt_cmd_control_packet",
    "check_icnt_cmd_executed",
    "icnt_dispatch_cmd",
    "icnt_cycle_step",
]


def create_icnt(config_file: str, print_activity: bool=False, print_trace: bool=False, output_file: str=None) -> c_void_p: ...

def create_icnt_cmd_data_packet(src_id: int, dst_id: int, subnet: int, size: int, is_write: bool) -> c_void_p: ...
def create_icnt_cmd_control_packet(src_id: int, dst_id: int, subnet: int, size: int) -> c_void_p: ...

def check_icnt_cmd_executed(cmd: c_void_p) -> bool: ...

def icnt_dispatch_cmd(icnt: c_void_p, cmd: c_void_p) -> None: ...
def icnt_cycle_step(icnt: c_void_p, cycles: int) -> None: ...