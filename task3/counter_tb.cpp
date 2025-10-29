#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main(int argc, char **argv, char **env) {
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);

    Vcounter* top = new Vcounter;

    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("counter.vcd");

    if(vbdOpen()!=1) return(-1);
    vbdHeader("Lab 1: Counter");

    top->clk = 1;
    top->rst = 0;

    vbdSetMode(1);

    for (i = 0; i < 900; i++) {

        for (clk = 0; clk < 2; clk++) {
            tfp->dump (2*i + clk);
            top->clk = !top->clk;
            top->eval ();
        }

        top->v = vbdValue();

        vbdHex(4, (int(top->count) >> 16) & 0xF);
        vbdHex(3, (int(top->count) >> 8) & 0xF);
        vbdHex(2, (int(top->count) >> 4) & 0xF);
        vbdHex(1, int(top->count)  & 0xF);

        vbdCycle(i+1);

        top->ld = vbdFlag();
        if (Verilated::gotFinish()) exit(0);
    }

    vbdClose();
    tfp->close();
    exit(0);
}