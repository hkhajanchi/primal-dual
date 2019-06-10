#include "iostream"
using namespace std; 

/*
Hussain Khajanchi
Quadratic Programming Solver - C++ Prototype
Laboratory of Embedded Control and Optimziation
Research Professor: Dr. Ambrose Adegbege

This C++ code serves as a pre-HLS template for a Quadratic Programming Problem solver, later to be embedded in the 
context of a Model Predictive Controller (MPC). 

Notes 
- This serves as a pre-HLS benchmark for C++ functional correctness. 
- This code will be optimized in future versions for HLS Synthesis

*/

int main()
{

	//Define all System Matrix Parameters

	float H[2][2] = { {4,2}, {2,4} };
	float Q[2] = {-2,-3};

	//Define Constraint Conditions
	float Z_MIN = -5; 
	float Z_MAX = 5; 

	float E[2] = {3, -1};
	float e = 2; 

	//Initialize Z and Lambda Vectors
	float Z[2] = { 0,0 };
	float LAMBDA = 0; 

	//Loop Parameters 
	float M = 2; 
	float N = 1; 

	//Define Convergence Parameters
	float W = 1; 
	float A = 1; 
	float D = 4; 
	float U = 4.33; 

	//Define Iteration Count
	float k = 0; 
	float maxIterations = 200; 

	//Define Intermediary Loop Variables 
	float delta_z = 0; 
	float delta_l = 0; 

	float x = 0; 
	float y = 0; 


	while (k < maxIterations)
	{

		//Compute Z_K+1

		for (int i = 0; i < M; i++)
		{
			delta_z = 0; 
			x = 0; 
			y = 0; 

			for (int j = 0; j < M; j++)
			{
				x = x + H[i][j] * Z[j];
			}

			for (int j = 0; j < N; j++)
			{
				y = y + (E[i] * LAMBDA);
			}

			delta_z = A * (((x - y) + Q[i]) / D); 

			//Projection Block

			if (Z[i] - delta_z < Z_MIN)
				Z[i] = Z_MIN;
			else if (Z[i] - delta_z > Z_MAX)
				Z[i] = Z_MAX;
			else
				Z[i] = Z[i] - delta_z;
		}
		
		//Compute Lambda_K+1

		for (int i = 0; i < N; i++)
		{
			delta_l = 0; 

			for (int j = 0; j < M; j++)
			{
				delta_l = delta_l + E[j] * Z[j];
			}

			delta_l = W * (delta_l - e) / U; 

			LAMBDA = LAMBDA - delta_l;
		}

		k = k + 1; 

	}

	std::cout << "Optimized Z Values: " << "\n"; 
	
	for (int i = 0; i < M; i++)
		std::cout << Z[i] << "\n";

	std::cout << "Final Lambda: " << "\n" << LAMBDA << "\n";

	return 0; 

}


