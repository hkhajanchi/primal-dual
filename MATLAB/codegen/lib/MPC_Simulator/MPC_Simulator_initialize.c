/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * MPC_Simulator_initialize.c
 *
 * Code generation for function 'MPC_Simulator_initialize'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "MPC_Simulator.h"
#include "MPC_Simulator_initialize.h"

/* Function Definitions */
void MPC_Simulator_initialize(void)
{
  rt_InitInfAndNaN(8U);
}

/* End of code generation (MPC_Simulator_initialize.c) */
