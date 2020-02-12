/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_MPC_Simulator_mex.c
 *
 * Code generation for function '_coder_MPC_Simulator_mex'
 *
 */

/* Include files */
#include "_coder_MPC_Simulator_api.h"
#include "_coder_MPC_Simulator_mex.h"

/* Function Declarations */
static void MPC_Simulator_mexFunction(int32_T nlhs, mxArray *plhs[2], int32_T
  nrhs, const mxArray *prhs[20]);

/* Function Definitions */
static void MPC_Simulator_mexFunction(int32_T nlhs, mxArray *plhs[2], int32_T
  nrhs, const mxArray *prhs[20])
{
  const mxArray *outputs[2];
  int32_T b_nlhs;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 20) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 20, 4,
                        13, "MPC_Simulator");
  }

  if (nlhs > 2) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 13,
                        "MPC_Simulator");
  }

  /* Call the function. */
  MPC_Simulator_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }

  emlrtReturnArrays(b_nlhs, plhs, outputs);
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(MPC_Simulator_atexit);

  /* Module initialization. */
  MPC_Simulator_initialize();

  /* Dispatch the entry-point. */
  MPC_Simulator_mexFunction(nlhs, plhs, nrhs, prhs);

  /* Module termination. */
  MPC_Simulator_terminate();
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_MPC_Simulator_mex.c) */
