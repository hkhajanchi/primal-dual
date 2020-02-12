/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * MPC_Simulator.c
 *
 * Code generation for function 'MPC_Simulator'
 *
 */

/* Include files */
#include <string.h>
#include "rt_nonfinite.h"
#include "MPC_Simulator.h"
#include "MPC_Simulator_emxutil.h"

/* Function Definitions */
void MPC_Simulator(const double ref_1[1000], const double ref_2[1000], const
                   double noise[2000], double T, const double H[900], const
                   double q_[60], const double E[600], const double F1[80],
                   const double z_min[30], const double z_max[30], double n,
                   double m, double N_h, const double A_d[16], const double B_d
                   [8], const double C_d[8], const double Aob[36], const double
                   Bob[12], const double Cob[12], const double Ld[12],
                   emxArray_real_T *y_t, emxArray_real_T *u_t)
{
  emxArray_real_T *x_d_obs;
  int i0;
  double temp1;
  int i1;
  int i2;
  int loop_ub;
  emxArray_real_T *x_plant;
  int aoffset;
  emxArray_real_T *z;
  int i;
  emxArray_real_T *b_x_plant;
  int b_i;
  double y[4];
  double b_y[4];
  double c_y[2];
  double d_y[6];
  double e_y[6];
  double f_y[6];
  int i3;
  double e[20];
  double L[20];
  double Q[30];
  double Z[30];
  double maxval[30];
  boolean_T exitg1;
  double D;
  double temp2;
  emxInit_real_T(&x_d_obs, 2);

  /* Signal Based MPC Function for Fixed-Point Analysis */
  /*  -------- System Initial Conditions --------- */
  i0 = x_d_obs->size[0] * x_d_obs->size[1];
  temp1 = n + m;
  i1 = (int)temp1;
  x_d_obs->size[0] = i1;
  i2 = (int)T;
  x_d_obs->size[1] = i2;
  emxEnsureCapacity_real_T(x_d_obs, i0);
  loop_ub = i1 * i2;
  for (i0 = 0; i0 < loop_ub; i0++) {
    x_d_obs->data[i0] = 0.0;
  }

  emxInit_real_T(&x_plant, 2);
  i0 = x_plant->size[0] * x_plant->size[1];
  i1 = (int)n;
  x_plant->size[0] = i1;
  x_plant->size[1] = i2;
  emxEnsureCapacity_real_T(x_plant, i0);
  loop_ub = i1 * i2;
  for (i0 = 0; i0 < loop_ub; i0++) {
    x_plant->data[i0] = 0.0;
  }

  i0 = u_t->size[0] * u_t->size[1];
  i1 = (int)m;
  u_t->size[0] = i1;
  u_t->size[1] = i2;
  emxEnsureCapacity_real_T(u_t, i0);
  aoffset = i1 * i2;
  for (i0 = 0; i0 < aoffset; i0++) {
    u_t->data[i0] = 0.0;
  }

  emxInit_real_T(&z, 2);
  i0 = z->size[0] * z->size[1];
  i = (int)(temp1 * N_h);
  z->size[0] = i;
  z->size[1] = i2;
  emxEnsureCapacity_real_T(z, i0);
  loop_ub = i * i2;
  for (i0 = 0; i0 < loop_ub; i0++) {
    z->data[i0] = 0.0;
  }

  i0 = y_t->size[0] * y_t->size[1];
  y_t->size[0] = i1;
  y_t->size[1] = i2;
  emxEnsureCapacity_real_T(y_t, i0);
  for (i0 = 0; i0 < aoffset; i0++) {
    y_t->data[i0] = 0.0;
  }

  i0 = (int)(T - 1.0);
  emxInit_real_T(&b_x_plant, 1);
  for (b_i = 0; b_i < i0; b_i++) {
    /* Simulate Plant  */
    i1 = x_plant->size[0];
    if (i1 == 1) {
      loop_ub = x_plant->size[0];
      i1 = b_x_plant->size[0];
      b_x_plant->size[0] = loop_ub;
      emxEnsureCapacity_real_T(b_x_plant, i1);
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_x_plant->data[i1] = x_plant->data[i1 + x_plant->size[0] * b_i];
      }

      for (i1 = 0; i1 < 4; i1++) {
        temp1 = A_d[i1] * b_x_plant->data[0];
        temp1 += A_d[i1 + 4] * b_x_plant->data[1];
        temp1 += A_d[i1 + 8] * b_x_plant->data[2];
        temp1 += A_d[i1 + 12] * b_x_plant->data[3];
        y[i1] = temp1;
      }
    } else {
      y[0] = 0.0;
      y[1] = 0.0;
      y[2] = 0.0;
      y[3] = 0.0;
      for (loop_ub = 0; loop_ub < 4; loop_ub++) {
        aoffset = loop_ub << 2;
        y[0] += x_plant->data[loop_ub + x_plant->size[0] * b_i] * A_d[aoffset];
        y[1] += x_plant->data[loop_ub + x_plant->size[0] * b_i] * A_d[aoffset +
          1];
        y[2] += x_plant->data[loop_ub + x_plant->size[0] * b_i] * A_d[aoffset +
          2];
        y[3] += x_plant->data[loop_ub + x_plant->size[0] * b_i] * A_d[aoffset +
          3];
      }
    }

    i1 = u_t->size[0];
    if (i1 == 1) {
      loop_ub = u_t->size[0];
      i1 = b_x_plant->size[0];
      b_x_plant->size[0] = loop_ub;
      emxEnsureCapacity_real_T(b_x_plant, i1);
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_x_plant->data[i1] = u_t->data[i1 + u_t->size[0] * b_i];
      }

      for (i1 = 0; i1 < 4; i1++) {
        temp1 = B_d[i1] * b_x_plant->data[0];
        temp1 += B_d[i1 + 4] * b_x_plant->data[1];
        b_y[i1] = temp1;
      }
    } else {
      b_y[0] = 0.0;
      b_y[1] = 0.0;
      b_y[2] = 0.0;
      b_y[3] = 0.0;
      for (loop_ub = 0; loop_ub < 2; loop_ub++) {
        aoffset = loop_ub << 2;
        b_y[0] += u_t->data[loop_ub + u_t->size[0] * b_i] * B_d[aoffset];
        b_y[1] += u_t->data[loop_ub + u_t->size[0] * b_i] * B_d[aoffset + 1];
        b_y[2] += u_t->data[loop_ub + u_t->size[0] * b_i] * B_d[aoffset + 2];
        b_y[3] += u_t->data[loop_ub + u_t->size[0] * b_i] * B_d[aoffset + 3];
      }
    }

    loop_ub = x_plant->size[0];
    y[0] += b_y[0];
    y[1] += b_y[1];
    y[2] += b_y[2];
    y[3] += b_y[3];
    for (i1 = 0; i1 < loop_ub; i1++) {
      x_plant->data[i1 + x_plant->size[0] * (b_i + 1)] = y[i1];
    }

    i1 = x_plant->size[0];
    if (i1 == 1) {
      loop_ub = x_plant->size[0];
      i1 = b_x_plant->size[0];
      b_x_plant->size[0] = loop_ub;
      emxEnsureCapacity_real_T(b_x_plant, i1);
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_x_plant->data[i1] = x_plant->data[i1 + x_plant->size[0] * b_i];
      }

      for (i1 = 0; i1 < 2; i1++) {
        temp1 = C_d[i1] * b_x_plant->data[0];
        temp1 += C_d[i1 + 2] * b_x_plant->data[1];
        temp1 += C_d[i1 + 4] * b_x_plant->data[2];
        temp1 += C_d[i1 + 6] * b_x_plant->data[3];
        c_y[i1] = temp1;
      }
    } else {
      c_y[0] = 0.0;
      c_y[1] = 0.0;
      for (loop_ub = 0; loop_ub < 4; loop_ub++) {
        aoffset = loop_ub << 1;
        c_y[0] += x_plant->data[loop_ub + x_plant->size[0] * b_i] * C_d[aoffset];
        c_y[1] += x_plant->data[loop_ub + x_plant->size[0] * b_i] * C_d[aoffset
          + 1];
      }
    }

    loop_ub = y_t->size[0];
    aoffset = b_i << 1;
    c_y[0] += 0.01 * noise[aoffset];
    c_y[1] += 0.01 * noise[1 + aoffset];
    for (i1 = 0; i1 < loop_ub; i1++) {
      y_t->data[i1 + y_t->size[0] * b_i] = c_y[i1];
    }

    /* Observer  */
    i1 = x_d_obs->size[0];
    if (i1 == 1) {
      loop_ub = x_d_obs->size[0];
      i1 = b_x_plant->size[0];
      b_x_plant->size[0] = loop_ub;
      emxEnsureCapacity_real_T(b_x_plant, i1);
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_x_plant->data[i1] = x_d_obs->data[i1 + x_d_obs->size[0] * b_i];
      }

      for (i1 = 0; i1 < 6; i1++) {
        temp1 = 0.0;
        for (i2 = 0; i2 < 6; i2++) {
          temp1 += Aob[i1 + 6 * i2] * b_x_plant->data[i2];
        }

        d_y[i1] = temp1;
      }
    } else {
      for (i = 0; i < 6; i++) {
        d_y[i] = 0.0;
      }

      for (loop_ub = 0; loop_ub < 6; loop_ub++) {
        aoffset = loop_ub * 6;
        for (i = 0; i < 6; i++) {
          d_y[i] += x_d_obs->data[loop_ub + x_d_obs->size[0] * b_i] *
            Aob[aoffset + i];
        }
      }
    }

    i1 = u_t->size[0];
    if (i1 == 1) {
      loop_ub = u_t->size[0];
      i1 = b_x_plant->size[0];
      b_x_plant->size[0] = loop_ub;
      emxEnsureCapacity_real_T(b_x_plant, i1);
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_x_plant->data[i1] = u_t->data[i1 + u_t->size[0] * b_i];
      }

      for (i1 = 0; i1 < 6; i1++) {
        temp1 = Bob[i1] * b_x_plant->data[0];
        temp1 += Bob[i1 + 6] * b_x_plant->data[1];
        e_y[i1] = temp1;
      }
    } else {
      for (i = 0; i < 6; i++) {
        e_y[i] = 0.0;
      }

      for (loop_ub = 0; loop_ub < 2; loop_ub++) {
        aoffset = loop_ub * 6;
        for (i = 0; i < 6; i++) {
          e_y[i] += u_t->data[loop_ub + u_t->size[0] * b_i] * Bob[aoffset + i];
        }
      }
    }

    i1 = x_d_obs->size[0];
    if (i1 == 1) {
      loop_ub = x_d_obs->size[0];
      i1 = b_x_plant->size[0];
      b_x_plant->size[0] = loop_ub;
      emxEnsureCapacity_real_T(b_x_plant, i1);
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_x_plant->data[i1] = x_d_obs->data[i1 + x_d_obs->size[0] * b_i];
      }

      for (i1 = 0; i1 < 2; i1++) {
        temp1 = 0.0;
        for (i2 = 0; i2 < 6; i2++) {
          temp1 += Cob[i1 + (i2 << 1)] * b_x_plant->data[i2];
        }

        c_y[i1] = temp1;
      }
    } else {
      c_y[0] = 0.0;
      c_y[1] = 0.0;
      for (loop_ub = 0; loop_ub < 6; loop_ub++) {
        aoffset = loop_ub << 1;
        c_y[0] += x_d_obs->data[loop_ub + x_d_obs->size[0] * b_i] * Cob[aoffset];
        c_y[1] += x_d_obs->data[loop_ub + x_d_obs->size[0] * b_i] * Cob[aoffset
          + 1];
      }
    }

    loop_ub = x_d_obs->size[0];
    aoffset = y_t->size[0];
    i1 = b_x_plant->size[0];
    b_x_plant->size[0] = aoffset;
    emxEnsureCapacity_real_T(b_x_plant, i1);
    for (i1 = 0; i1 < aoffset; i1++) {
      b_x_plant->data[i1] = y_t->data[i1 + y_t->size[0] * b_i];
    }

    c_y[0] -= b_x_plant->data[0];
    c_y[1] -= b_x_plant->data[1];
    for (i1 = 0; i1 < 6; i1++) {
      f_y[i1] = (d_y[i1] + e_y[i1]) - (Ld[i1] * c_y[0] + Ld[i1 + 6] * c_y[1]);
    }

    for (i1 = 0; i1 < loop_ub; i1++) {
      x_d_obs->data[i1 + x_d_obs->size[0] * (b_i + 1)] = f_y[i1];
    }

    /* Scale Reference Voltage to height  */
    /* V to Cm scaling factor */
    /* Compute f and e Matrix  */
    if (n + 1.0 > x_d_obs->size[0]) {
      i1 = 1;
      i2 = 0;
    } else {
      i1 = (int)(n + 1.0);
      i2 = x_d_obs->size[0];
    }

    if (1.0 > n) {
      i3 = 0;
    } else {
      i3 = (int)n;
    }

    if (i3 == 1) {
      i = b_x_plant->size[0];
      b_x_plant->size[0] = 1;
      emxEnsureCapacity_real_T(b_x_plant, i);
      for (i = 0; i < 1; i++) {
        b_x_plant->data[0] = x_d_obs->data[x_d_obs->size[0] * b_i];
      }

      for (i = 0; i < 20; i++) {
        temp1 = F1[i] * b_x_plant->data[0];
        temp1 += F1[i + 20] * b_x_plant->data[1];
        temp1 += F1[i + 40] * b_x_plant->data[2];
        temp1 += F1[i + 60] * b_x_plant->data[3];
        e[i] = temp1;
      }
    } else {
      memset(&e[0], 0, 20U * sizeof(double));
      for (loop_ub = 0; loop_ub < 4; loop_ub++) {
        aoffset = loop_ub * 20;
        for (i = 0; i < 20; i++) {
          e[i] += x_d_obs->data[loop_ub + x_d_obs->size[0] * b_i] * F1[aoffset +
            i];
        }
      }
    }

    i = b_x_plant->size[0];
    loop_ub = i2 - i1;
    b_x_plant->size[0] = loop_ub + 1;
    emxEnsureCapacity_real_T(b_x_plant, i);
    for (i2 = 0; i2 <= loop_ub; i2++) {
      b_x_plant->data[i2] = x_d_obs->data[((i1 + i2) + x_d_obs->size[0] * b_i) -
        1];
    }

    c_y[0] = ref_1[b_i] * 7.15 - b_x_plant->data[0];
    c_y[1] = ref_2[b_i] * 7.15 - b_x_plant->data[1];

    /*  Define Loop Parameters */
    /*  Instantiate z and lambda vectors  */
    for (i = 0; i < 30; i++) {
      Q[i] = -(q_[i] * c_y[0] + q_[i + 30] * c_y[1]);
      Z[i] = 0.0;
    }

    memset(&L[0], 0, 20U * sizeof(double));

    /*  Convergence Parameters  */
    for (aoffset = 0; aoffset < 30; aoffset++) {
      maxval[aoffset] = H[30 * aoffset];
      for (i = 0; i < 29; i++) {
        temp1 = H[(i + 30 * aoffset) + 1];
        if ((!rtIsNaN(temp1)) && (rtIsNaN(maxval[aoffset]) || (maxval[aoffset] <
              temp1))) {
          maxval[aoffset] = temp1;
        }
      }
    }

    if (!rtIsNaN(maxval[0])) {
      aoffset = 1;
    } else {
      aoffset = 0;
      loop_ub = 2;
      exitg1 = false;
      while ((!exitg1) && (loop_ub < 31)) {
        if (!rtIsNaN(maxval[loop_ub - 1])) {
          aoffset = loop_ub;
          exitg1 = true;
        } else {
          loop_ub++;
        }
      }
    }

    if (aoffset == 0) {
      D = maxval[0];
    } else {
      D = maxval[aoffset - 1];
      i1 = aoffset + 1;
      for (loop_ub = i1; loop_ub < 31; loop_ub++) {
        temp1 = maxval[loop_ub - 1];
        if (D < temp1) {
          D = temp1;
        }
      }
    }

    /* Arbitrary Positive Number */
    for (loop_ub = 0; loop_ub < 200; loop_ub++) {
      /* Compute Z_k+1 */
      for (i = 0; i < 30; i++) {
        temp1 = 0.0;
        temp2 = 0.0;
        for (aoffset = 0; aoffset < 30; aoffset++) {
          temp1 += H[i + 30 * aoffset] * Z[aoffset];
        }

        for (aoffset = 0; aoffset < 20; aoffset++) {
          temp2 += E[aoffset + 20 * i] * L[aoffset];
        }

        temp1 = ((temp1 - temp2) + Q[i]) / D;

        /* Projection  */
        if (Z[i] - temp1 < z_min[i]) {
          Z[i] = z_min[i];
        } else if (Z[i] - temp1 > z_max[i]) {
          Z[i] = z_max[i];
        } else {
          Z[i] -= temp1;
        }
      }

      /* Compute Lambda_k+1 */
      for (i = 0; i < 20; i++) {
        temp1 = 0.0;
        for (aoffset = 0; aoffset < 30; aoffset++) {
          temp1 += E[i + 20 * aoffset] * Z[aoffset];
        }

        temp1 = (temp1 - e[i]) / 4.33;
        L[i] -= temp1;
      }
    }

    loop_ub = z->size[0];
    for (i1 = 0; i1 < loop_ub; i1++) {
      z->data[i1 + z->size[0] * b_i] = Z[i1];
    }

    /* Implement DAC Based Saturation */
    if (z->data[z->size[0] * b_i] < 0.0) {
      u_t->data[u_t->size[0] * (b_i + 1)] = 0.0;
    } else if (z->data[z->size[0] * b_i] > 3.3) {
      u_t->data[u_t->size[0] * (b_i + 1)] = 3.3;
    } else {
      u_t->data[u_t->size[0] * (b_i + 1)] = z->data[z->size[0] * b_i];
    }

    if (z->data[1 + z->size[0] * b_i] < 0.0) {
      u_t->data[1 + u_t->size[0] * (b_i + 1)] = 0.0;
    } else if (z->data[1 + z->size[0] * b_i] > 3.3) {
      u_t->data[1 + u_t->size[0] * (b_i + 1)] = 3.3;
    } else {
      u_t->data[1 + u_t->size[0] * (b_i + 1)] = z->data[1 + z->size[0] * b_i];
    }

    if (1.0 > m) {
      loop_ub = 0;
    } else {
      loop_ub = (int)m;
    }

    for (i1 = 0; i1 < loop_ub; i1++) {
      u_t->data[i1 + u_t->size[0] * (b_i + 1)] = z->data[i1 + z->size[0] * b_i];
    }
  }

  emxFree_real_T(&b_x_plant);
  emxFree_real_T(&z);
  emxFree_real_T(&x_plant);
  emxFree_real_T(&x_d_obs);

  /*  ------- Generate Plots ----------------- */
  /* subplot(2,1,1); */
  /* plot(ref_1 * 7.15,'r--','Linewidth',4);  */
  /* plot(ref_2 * 7.15, 'r--', 'Linewidth',4);  */
  /* plot(y_t','b-','Linewidth',2); hold off; */
  /* ylabel('Output and reference'); */
  /* subplot(2,1,2); */
  /* plot(u_t(:,1:T)','b-','Linewidth',2); */
  /* xlabel('Time (sample number)'); */
}

/* End of code generation (MPC_Simulator.c) */
