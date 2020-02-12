/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_MPC_Simulator_api.h
 *
 * Code generation for function '_coder_MPC_Simulator_api'
 *
 */

#ifndef _CODER_MPC_SIMULATOR_API_H
#define _CODER_MPC_SIMULATOR_API_H

/* Include files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_MPC_Simulator_api.h"

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real_T*/

#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T

typedef struct emxArray_real_T emxArray_real_T;

#endif                                 /*typedef_emxArray_real_T*/

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void MPC_Simulator(real_T ref_1[1000], real_T ref_2[1000], real_T noise
  [2000], real_T T, real_T H[900], real_T q_[60], real_T E[600], real_T F1[80],
  real_T z_min[30], real_T z_max[30], real_T n, real_T m, real_T N_h, real_T
  A_d[16], real_T B_d[8], real_T C_d[8], real_T Aob[36], real_T Bob[12], real_T
  Cob[12], real_T Ld[12], emxArray_real_T *y_t, emxArray_real_T *u_t);
extern void MPC_Simulator_api(const mxArray * const prhs[20], int32_T nlhs,
  const mxArray *plhs[2]);
extern void MPC_Simulator_atexit(void);
extern void MPC_Simulator_initialize(void);
extern void MPC_Simulator_terminate(void);
extern void MPC_Simulator_xil_shutdown(void);
extern void MPC_Simulator_xil_terminate(void);

#endif

/* End of code generation (_coder_MPC_Simulator_api.h) */
