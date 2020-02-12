%%Generate H matrix from S(Q) R P and N
clear
clc

%N must be an integer
%R,S, and P must be square matrices
%The size of P must equal the size of S

%Horizon
N = 2
%Matrix associated with u_0 to u_N-1
R = 10; 
%Matrix associated with x_1 to x_N
S = eye(2); 
%Matrix associated with x_0
P = eye(2); 

[m,m] = size(R);
[n,n] = size(S);

rdim = m+n;

H = zeros((m+n)*N);
for samp = 1:N;
    d = samp-1;
    H(1+(d*rdim):m+(d*rdim),1+(d*rdim):m+(d*rdim)) = R;
    
    if samp ~= N;
        H((m+1)+(d*rdim):rdim+(d*rdim),(m+1)+(d*rdim):rdim+(d*rdim)) = S;
    else
        H((m+1)+(d*rdim):rdim+(d*rdim),(m+1)+(d*rdim):rdim+(d*rdim)) = P;
    end
end

H;

%% Generate E matrix from A B and N

%A must be square (nxn)
%B may be rectangular with the requirement that the dimention of its rows
%match the dimention of A (must be nxm)

%Matrix associated with x
A = [1 1;0 1];
%Matrix associated with u
B = [0;1]; 

[n2,n2] = size(A);
[n2,m2] = size(B);
I = eye(n2);

E = zeros(n2*N,(n2+m2)*N);
for samp = 1:N;
    d = samp-1;
    E(1+(d*n2):n2+(d*n2),1+(d*((n2)+m2)):m2+(d*((n2)+m2))) = -1*B;
    E(1+(d*n2):n2+(d*n2),(1+m2)+(d*(n2+m2)):(n2+m2)+(d*(n2+m2))) = I;
    if samp ~=1
        E(1+(d*n2):n2+(d*n2),(1+m2)+((d-1)*(n2+m2)):(n2+m2)+((d-1)*(n2+m2))) = -1*A;
    end
end

E;

num_T = nnz(inv(H)*E')
num_E = nnz(E)