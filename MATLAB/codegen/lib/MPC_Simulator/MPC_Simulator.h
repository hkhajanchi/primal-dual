/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * MPC_Simulator.h
 *
 * Code generation for function 'MPC_Simulator'
 *
 */

#ifndef MPC_SIMULATOR_H
#define MPC_SIMULATOR_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "MPC_Simulator_types.h"

/* Function Declarations */
extern void MPC_Simulator(const double ref_1[1000], const double ref_2[1000],
  const double noise[2000], double T, const double H[900], const double q_[60],
  const double E[600], const double F1[80], const double z_min[30], const double
  z_max[30], double n, double m, double N_h, const double A_d[16], const double
  B_d[8], const double C_d[8], const double Aob[36], const double Bob[12], const
  double Cob[12], const double Ld[12], emxArray_real_T *y_t, emxArray_real_T
  *u_t);

#endif

/* End of code generation (MPC_Simulator.h) */
