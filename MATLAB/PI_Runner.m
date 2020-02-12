% Script that Generates PI Simulations for IFAC 2020 Submission
clc
clear

%% --------- Time Frame Generation and Plant Setup ----------

%Script that generates MPC simulations for IFAC 2020 Submission


%Signal Parameters + Generation
%sim_length = 1000; %Simulation length in sec
Ts = 1.0; 

sim_length = 1400; 
Ts = 1.0; 

T = sim_length/Ts; %number of samples in simulation



% ref_0 = ones(1,T) * 2.0625; %2.12V needed to control tank at 15cm
% ref_1 = ones(1,T) * 1.3; %Tank 2 setpoint
% 
% 
% 
% ref_0(361:740) = 0.25; % Drop the step halfway through the simulation

ref_0 = load('PI_SETPOINT_1.mat');
ref_1 = load('PI_SETPOINT_2.mat');

ref_0 = ref_0.b;
ref_1 = ref_1.c;

%ref_1(201:600) = ref_1(201:600) - 0.2*ref_1(201:600); 

%-------------Create Disturbance-------------------


%noise = 1e-2*cumsum(randn(T,2)')' + 1e-2*randn(T,2);
%[bfilt,afilt] = butter(4,0.9);
%noise = filter(bfilt,afilt,noise)';

%------------Generate MPC Parameters-------------
% Generate A,B,C Matrices based on Quad-Tank system

[A_ct,B_ct,C_ct,D_ct] = quadruple_tank_setup(); %Generates A,B,C,D matrixes of CT system

% Discretize with Ts = 5s using Zero-Order Hold

[A_d,B_d,C_d,D_d] = discretizer(A_ct,B_ct,C_ct,D_ct,5);


%PI and Vector Initialization
acc_1 = 0; 
acc_2 = 0;
n = 4; 
m = 2; 

x_plant = zeros(n,T); 
u_t = zeros(m,T);
y_t = zeros(m,T); 

error = zeros(m,T); 
curr_acc = zeros(m,T); 

%% --------------- Closed Loop Simulation -------------------
 for i = 1:T-1

        %Simulate Plant 
        x_plant(:,i+1) = A_d*x_plant(:,i) + B_d*u_t(:,i); 
        y_t(:,i) = C_d * x_plant(:,i);
        
        curr_y_1 = y_t(1,i) /  7.15; %Cm to Voltage
        curr_y_2 = y_t(2,i) /  7.15;

        %PI Response
        [curr_u_out_0, curr_acc_0,error_0] = PI(ref_0(1,i), curr_y_1, acc_1); 
        [curr_u_out_1, curr_acc_1,error_1] = PI(ref_1(1,i), curr_y_2, acc_2); 
        
        
        u_t(1,i+1) = curr_u_out_0 ;
        u_t(2,i+1) = curr_u_out_1;
        
        acc_1 = curr_acc_0; 
        acc_2 = curr_acc_1; 

        error(1,i) = error_0; 
        error(2,i) = error_1; 
        curr_acc(1,i) = acc_1; 
        curr_acc(2,i) = acc_2; 
 end

%% ----------- Output Plots ---------------
subplot(2,1,1);
plot(ref_0 ,'r--','Linewidth',4); 
hold on;
plot(ref_1 , 'b--', 'Linewidth',4); 


plot(y_t(1,:)/7.15','y','Linewidth',2); 
plot(y_t(2,:)/7.15','c','Linewidth',2); 

hold off;
ylabel('Output and reference');

subplot(2,1,2);
plot(u_t(1,1:T)','y','Linewidth',2);
hold on; 
plot(u_t(2,1:T)','c','Linewidth',2);
hold off; 
xlabel('Time (sample number)');






