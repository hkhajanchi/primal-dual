%-----------------------------------------------------
% Clear Stuff
%-----------------------------------------------------
clear all; close all;

%------------------------------------------------
% Construct model
%------------------------------------------------
%Specify system here in state space form with A B C D
Ts = 1.0; %Sample interval
A=[0.9 0;0.9 0.9]; B=[0.1;0.2]; C=[1 1]; D=0;
%Specify system dimensions
n_in = size(B,2); %# inputs
n_out = size(C,1); %# outputs
n_states = size(A,1); %# states
%------------------------------------------------
% Specify horizons
%------------------------------------------------
M = 10; %Control Horizon
N = M; %Prediction Horizon
%------------------------------------------------------
% Initial Matrix Filling
%------------------------------------------------------
Lambda = zeros((N+1)*n_out,n_states);
Phi = zeros((N+1)*n_out);
AB = zeros((N+1)*n_out,n_in);
AB(1:n_out,:) = D;
for i = 2:N+1
    AB((i-1)*n_out+1:(i)*n_out,:) = C*A^(i-2)*B;
end
for i = 1:M+1
Phi(1+(i-1)*n_out:end,1+(i-1)*n_in:(i)*n_in) = AB(1:(N-i+2)*n_out,:);
end

Phi = sparse(Phi);
Lambda(1:n_out,:) = C;

for i = 2:N+1
Lambda(1+(i-1)*n_out:i*n_out,:) = C*A^(i-1);
end

%------------------------------------------------
% Quadratic cost weighting Q (error) and R (control) generation.
%------------------------------------------------
r = diag([1e4*ones(1,n_in)]); %Weights on input moves (i.e. ||u(t)-u(t-1)||)
q = diag([ones(1,n_out)]); %Weights on output deviation from setpoint
Q = sparse(kron(eye(N+1),q));
R = kron(diag([2*ones(1,N),1]),r);
R = R + kron(diag([-ones(1,N)],-1),r);
R = R + kron(diag([-ones(1,N)],1),r);
%-----------------------------------------------
% Generate the Hessian H
%-----------------------------------------------
H = full(Phi'*Q*Phi) + R;
%-----------------------------------------------
% Create an observer
%-----------------------------------------------
Aa = blkdiag(A,eye(n_out)); Ba = [B;zeros(n_out,n_in)];
Ca = [C eye(n_out)]; Da = D;
Ga = diag([ones(1,n_states),ones(1,n_out)]);
Qa = 1*eye(n_states+n_out);
Ra = 1*eye(n_out);
L = dlqe(Aa,Ga,Ca,Qa,Ra);
L = Aa*L;
%-----------------------------------------------
% Create plant constraints
%-----------------------------------------------
lb = -0.1*ones(n_in,1); ub = 0.1*ones(n_in,1);
11

Lb = kron(ones((M+1),1),lb); Ub = kron(ones((M+1),1),ub);
%------------------------------------------------
% Set initial conditions
%------------------------------------------------
sim_length = 1000; %Simulation length in sec
T = sim_length/Ts; %number of samples in simulation
t = 0:Ts:sim_length-Ts; %time steps
%-----------------------------------------------
% Set system initial conditions......
%-----------------------------------------------
x = zeros(n_states,T);
x(:,1) = -2*ones(n_states,1); %Plant state
xh = zeros(n_states+n_out,T); %Estimated state
u = zeros(n_in,T); %Input record
u_old = zeros(n_in,1);
y = zeros(n_out,T); %Output record
Aobs = Aa-L*Ca; %Generate observer state gain matrix
Bobs = Ba-L*Da; %Generate observer input gain matrix
fd = full([Phi'*Q*Lambda, Phi'*kron(ones(N+1,1),q)]);
opt=optimset('display','off');
%------------------------------------------------
% Generate reference signal
%------------------------------------------------
ref = ones(1,T); ref(201:600) = -ref(201:600);
%------------------------------------------------
% Generate noise signal
%------------------------------------------------
noise = 1e-2*cumsum(randn(T,n_out)')' + 1e-2*randn(T,n_out);
[bfilt,afilt] = butter(4,0.9);
noise = filter(bfilt,afilt,noise)';

%------------------------------------------------
% MPC Evolution
%------------------------------------------------
for i = 1:T
%SIMULATE REAL PLANT-------------------------------
x(:,i+1) = A*x(:,i) + B*u(:,i);
y(:,i) = C*x(:,i) + D*u(:,i) + noise(:,i);
%Add disturbance
if i>300, y(:,i)=y(:,i)+0.5*ones(n_out,1); end
%CONTROLLER STARTS HERE----------------------------
%Observe state
xh(:,i+1) = Aobs*xh(:,i) + Bobs*u(:,i) + L*y(:,i);
%Solve dynamic optimisation problem
f = fd*[xh(1:n_states,i+1);xh(n_states+1:end,i+1)-ref(:,i)];
f(1:n_in) = f(1:n_in)-r*u_old;
U = quadprog(H,f,[],[],[],[],Lb,Ub,[],opt);

u(:,i+1) = U(1:n_in); u_old = u(:,i);
end;

%------------------------------------------------
% Plots
%------------------------------------------------
subplot(2,1,1);
plot(ref','r--','Linewidth',2); hold on
plot(y','b-','Linewidth',2); hold off;
ylabel('Output and reference');
subplot(2,1,2);
plot([1 T],[ub ub],'r--','Linewidth',2); hold on;
plot([1 T],[lb lb],'r--','Linewidth',2);
plot(u(:,1:T)','b-','Linewidth',2); hold off;
xlabel('Time (sample number)');
ylabel('Input and constraints');
axis([1 T 2*lb 2*ub]);