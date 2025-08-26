#include "py_interface.h"
#include "mta_icnt_wrapper.h"


/****************************************************** 
 * Global declarations 
 ******************************************************/

TrafficManager *gTrafficManager = NULL;

int GetSimTime() {
    return gTrafficManager->getTime();
}

class Stats;
Stats * GetStats(const std::string & name) {
  Stats* test =  gTrafficManager->getStats(name);
  if(test == 0){
    cout<<"warning statistics "<<name<<" not found"<<endl;
  }
  return test;
}

int gK;
int gN;
int gC;

int gNodes;

bool gPrintActivity;
bool gTrace;

std::ostream * gWatchOut;
std::unique_ptr<std::ofstream> gWatchOutFileStream;


/****************************************************** 
 * Interfaces 
 ******************************************************/

void *pybooksim2_create_icnt(char *config_file, char print_activity, char print_trace, char *output_file) {
    InterconnectWrapper *icnt = new InterconnectWrapper(config_file);
    gTrafficManager = icnt->get_traffic_manager();

    gPrintActivity = print_activity;
    gTrace = print_trace;

    if (print_activity) {
        if (output_file == NULL) {
            gWatchOut = &cout;
        } else {
            gWatchOutFileStream = std::make_unique<std::ofstream>(output_file);
            if (!gWatchOutFileStream->is_open()) {
                cerr << "Error opening output file: " << output_file << ". Activity and traces are not being recorded. (Check whether the output file path is valid or not)" << endl;
                gPrintActivity = false;
                gTrace = false;
                gWatchOut = NULL;
            } else {
                gWatchOut = gWatchOutFileStream.get();
            }
        }
    } else {
        gWatchOut = NULL;
    }

    return icnt;
}

void  pybooksim2_destroy_icnt(void *icnt_p) {
    // if (gWatchOutFileStream->is_open()) {
    //     gWatchOutFileStream.get()->close();
    // }
    delete static_cast<InterconnectWrapper *>(icnt_p);
}


void *pybooksim2_create_icnt_cmd_data_packet(int src_id, int dst_id, int subnet, int size, char is_write) {
    InterconnectCommand *cmd = new InterconnectCommand;
    cmd->src_id = src_id;
    cmd->dst_id = dst_id;
    cmd->subnet = subnet;
    cmd->size = size;
    cmd->is_data = true;
    cmd->is_write = is_write;
    cmd->is_executed = false;
    return cmd;
}

void *pybooksim2_create_icnt_cmd_control_packet(int src_id, int dst_id, int subnet, int size) {
    InterconnectCommand *cmd = new InterconnectCommand;
    cmd->src_id = src_id;
    cmd->dst_id = dst_id;
    cmd->subnet = subnet;
    cmd->size = size;
    cmd->is_data = false;
    cmd->is_write = false;
    cmd->is_executed = false;
    return cmd;
}

void  pybooksim2_destroy_icnt_cmd(void *cmd_p) {
    delete static_cast<InterconnectCommand *>(cmd_p);
}

char  pybooksim2_check_icnt_cmd_executed(void *cmd_p) {
    InterconnectCommand *cmd = static_cast<InterconnectCommand *>(cmd_p);
    return cmd->is_executed;
}

void  pybooksim2_icnt_dispatch_cmd(void *icnt_p, void *cmd_p) {
    InterconnectWrapper *icnt = static_cast<InterconnectWrapper *>(icnt_p);
    InterconnectCommand *cmd = static_cast<InterconnectCommand *>(cmd_p);
    icnt->dispatch_command(cmd);
}

void  pybooksim2_icnt_cycle_step(void *icnt_p) {
    InterconnectWrapper *icnt = static_cast<InterconnectWrapper *>(icnt_p);
    icnt->cycle_step();
}