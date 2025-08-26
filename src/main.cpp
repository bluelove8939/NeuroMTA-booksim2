#include "py_interface.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        cerr << "Usage: " << argv[0] << " <config file> <output file>" << endl;
        return 0;
    }

    void *icnt = pybooksim2_create_icnt(argv[1], false, false, argv[2]);
    void *cmd = pybooksim2_create_icnt_cmd_control_packet(0, 1, 0, 10);

    pybooksim2_icnt_dispatch_cmd(icnt, cmd);

    for (int i = 0; i < 1000; i++)
    {
        pybooksim2_icnt_cycle_step(icnt);
        if (pybooksim2_check_icnt_cmd_executed(cmd))
        {
            printf("Command executed successfully at timestamp '%d'\n", i);
            break;
        }
    }

    pybooksim2_destroy_icnt_cmd(cmd);
    pybooksim2_destroy_icnt(icnt);

    return 0;
}
