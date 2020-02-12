/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * MPC_Simulator_emxutil.h
 *
 * Code generation for function 'MPC_Simulator_emxutil'
 *
 */

#ifndef MPC_SIMULATOR_EMXUTIL_H
#define MPC_SIMULATOR_EMXUTIL_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "MPC_Simulator_types.h"

/* Function Declarations */
extern void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int oldNumel);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#endif

/* End of code generation (MPC_Simulator_emxutil.h) */
