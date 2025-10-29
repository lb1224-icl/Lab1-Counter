# Task 3

## Overview

In Task 3, our aims were to experiment with Vbuddy functionality such as one-shot flags and the rotary encoder values

## Process

### Loadable Counter

We modified ```counter.sv``` heavily to create a version which loads a variable ```v``` into the counter when ```ld``` goes high.

```verilog
module counter #(
  parameter WIDTH = 8
)(
  // interface signals
  input  logic             clk,      // clock
  input  logic             rst,      // reset
  input  logic             ld,       // load counter from data
  input  logic [WIDTH-1:0] v,        // value to preload
  output logic [WIDTH-1:0] count     // count output
);

always_ff @ (posedge clk)
  if (rst) count <= {WIDTH{1'b0}};
  else     count <= ld ? v : count + {{WIDTH-1{1'b0}},1'b1};
endmodule
```

To make the testbench useful, we require a flag which doesn't toggle but instead goes high for one clock cycle. We can do this by changing the flag mode with `vbdSetMode(1)`

We edit `counter_tb.cpp` as well to change the `v` variable to the value of the encoder using `top->v = vbdValue()`

### One step counter

Very self explanatory, we use the same one-shot feature of the flag now to only add when the flag is active. 


