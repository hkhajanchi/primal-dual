/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * main.c
 *
 * Code generation for function 'main'
 *
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/
/* Include files */
#include "rt_nonfinite.h"
#include "MPC_Simulator.h"
#include "main.h"
#include "MPC_Simulator_terminate.h"
#include "MPC_Simulator_emxAPI.h"
#include "MPC_Simulator_initialize.h"

/* Function Declarations */
static void argInit_1x1000_real_T(double result[1000]);
static void argInit_20x30_real_T(double result[600]);
static void argInit_20x4_real_T(double result[80]);
static void argInit_2x1000_real_T(double result[2000]);
static void argInit_2x4_real_T(double result[8]);
static void argInit_2x6_real_T(double result[12]);
static void argInit_30x1_real_T(double result[30]);
static void argInit_30x2_real_T(double result[60]);
static void argInit_30x30_real_T(double result[900]);
static void argInit_4x2_real_T(double result[8]);
static void argInit_4x4_real_T(double result[16]);
static void argInit_6x2_real_T(double result[12]);
static void argInit_6x6_real_T(double result[36]);
static double argInit_real_T(void);
static void main_MPC_Simulator(void);

/* Function Definitions */
static void argInit_1x1000_real_T(double result[1000])
{
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx1 = 0; idx1 < 1000; idx1++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx1] = argInit_real_T();
  }
}

static void argInit_20x30_real_T(double result[600])
{
  int idx0;
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 20; idx0++) {
    for (idx1 = 0; idx1 < 30; idx1++) {
      /* Set the value of the array element.
         Change this value to the value that the application requires. */
      result[idx0 + 20 * idx1] = argInit_real_T();
    }
  }
}

static void argInit_20x4_real_T(double result[80])
{
  int idx0;
  double result_tmp;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 20; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result_tmp = argInit_real_T();
    result[idx0] = result_tmp;

    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0 + 20] = result_tmp;

    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0 + 40] = argInit_real_T();

    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0 + 60] = argInit_real_T();
  }
}

static void argInit_2x1000_real_T(double result[2000])
{
  int idx0;
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 2; idx0++) {
    for (idx1 = 0; idx1 < 1000; idx1++) {
      /* Set the value of the array element.
         Change this value to the value that the application requires. */
      result[idx0 + (idx1 << 1)] = argInit_real_T();
    }
  }
}

static void argInit_2x4_real_T(double result[8])
{
  int idx0;
  double result_tmp;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 2; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result_tmp = argInit_real_T();
    result[idx0] = result_tmp;

    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0 + 2] = result_tmp;

    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0 + 4] = argInit_real_T();

    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0 + 6] = argInit_real_T();
  }
}

static void argInit_2x6_real_T(double result[12])
{
  int idx0;
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 2; idx0++) {
    for (idx1 = 0; idx1 < 6; idx1++) {
      /* Set the value of the array element.
         Change this value to the value that the application requires. */
      result[idx0 + (idx1 << 1)] = argInit_real_T();
    }
  }
}

static void argInit_30x1_real_T(double result[30])
{
  int idx0;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 30; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0] = argInit_real_T();
  }
}

static void argInit_30x2_real_T(double result[60])
{
  int idx0;
  double result_tmp;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 30; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result_tmp = argInit_real_T();
    result[idx0] = result_tmp;

    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0 + 30] = result_tmp;
  }
}

static void argInit_30x30_real_T(double result[900])
{
  int idx0;
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 30; idx0++) {
    for (idx1 = 0; idx1 < 30; idx1++) {
      /* Set the value of the array element.
         Change this value to the value that the application requires. */
      result[idx0 + 30 * idx1] = argInit_real_T();
    }
  }
}

static void argInit_4x2_real_T(double result[8])
{
  int idx0;
  double result_tmp;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 4; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result_tmp = argInit_real_T();
    result[idx0] = result_tmp;

    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0 + 4] = result_tmp;
  }
}

static void argInit_4x4_real_T(double result[16])
{
  int idx0;
  double result_tmp;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 4; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result_tmp = argInit_real_T();
    result[idx0] = result_tmp;

    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0 + 4] = result_tmp;

    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0 + 8] = argInit_real_T();

    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0 + 12] = argInit_real_T();
  }
}

static void argInit_6x2_real_T(double result[12])
{
  int idx0;
  double result_tmp;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 6; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result_tmp = argInit_real_T();
    result[idx0] = result_tmp;

    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0 + 6] = result_tmp;
  }
}

static void argInit_6x6_real_T(double result[36])
{
  int idx0;
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 6; idx0++) {
    for (idx1 = 0; idx1 < 6; idx1++) {
      /* Set the value of the array element.
         Change this value to the value that the application requires. */
      result[idx0 + 6 * idx1] = argInit_real_T();
    }
  }
}

static double argInit_real_T(void)
{
  return 0.0;
}

static void main_MPC_Simulator(void)
{
  emxArray_real_T *y_t;
  emxArray_real_T *u_t;
  double ref_1_tmp[1000];
  double noise[2000];
  double T;
  double H[900];
  double q_[60];
  double E[600];
  double F1[80];
  double z_min_tmp[30];
  double dv0[16];
  double dv1[8];
  double dv2[8];
  double dv3[36];
  double dv4[12];
  double dv5[12];
  double dv6[12];
  emxInitArray_real_T(&y_t, 2);
  emxInitArray_real_T(&u_t, 2);

  /* Initialize function 'MPC_Simulator' input arguments. */
  /* Initialize function input argument 'ref_1'. */
  argInit_1x1000_real_T(ref_1_tmp);

  /* Initialize function input argument 'ref_2'. */
  /* Initialize function input argument 'noise'. */
  argInit_2x1000_real_T(noise);
  T = argInit_real_T();

  /* Initialize function input argument 'H'. */
  argInit_30x30_real_T(H);

  /* Initialize function input argument 'q_'. */
  argInit_30x2_real_T(q_);

  /* Initialize function input argument 'E'. */
  argInit_20x30_real_T(E);

  /* Initialize function input argument 'F1'. */
  argInit_20x4_real_T(F1);

  /* Initialize function input argument 'z_min'. */
  argInit_30x1_real_T(z_min_tmp);

  /* Initialize function input argument 'z_max'. */
  /* Initialize function input argument 'A_d'. */
  /* Initialize function input argument 'B_d'. */
  /* Initialize function input argument 'C_d'. */
  /* Initialize function input argument 'Aob'. */
  /* Initialize function input argument 'Bob'. */
  /* Initialize function input argument 'Cob'. */
  /* Initialize function input argument 'Ld'. */
  /* Call the entry-point 'MPC_Simulator'. */
  argInit_4x4_real_T(dv0);
  argInit_4x2_real_T(dv1);
  argInit_2x4_real_T(dv2);
  argInit_6x6_real_T(dv3);
  argInit_6x2_real_T(dv4);
  argInit_2x6_real_T(dv5);
  argInit_6x2_real_T(dv6);
  MPC_Simulator(ref_1_tmp, ref_1_tmp, noise, T, H, q_, E, F1, z_min_tmp,
                z_min_tmp, argInit_real_T(), argInit_real_T(), argInit_real_T(),
                dv0, dv1, dv2, dv3, dv4, dv5, dv6, y_t, u_t);
  emxDestroyArray_real_T(u_t);
  emxDestroyArray_real_T(y_t);
}

int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  /* Initialize the application.
     You do not need to do this more than one time. */
  MPC_Simulator_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_MPC_Simulator();

  /* Terminate the application.
     You do not need to do this more than one time. */
  MPC_Simulator_terminate();
  return 0;
}

/* End of code generation (main.c) */
