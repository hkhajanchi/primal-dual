% Script to plot Experiment outputs

cd 'C:\Users\hkhaj\Desktop\MPC\Results\IFAC Graphs\111219-Run2\PI'


u_table = readtable('u_in.csv'); 
tank_resp_table = readtable('tank_resp.csv'); 
setpoints_table = readtable('setpoints.csv'); 

u_table.Var4 = [];
tank_resp_table.Var4 = [];
setpoints_table.Var4 = [];

u = table2array(u_table); 
tank_resp = table2array(tank_resp_table); 
setpoints = table2array(setpoints_table); 

%advance setpoints by 87 timesteps 
 v = 100; 
 s1 = delayseq(setpoints(:,2),v); 
 s2 = delayseq(setpoints(:,3),v); 

%  For PI 
  s1(1:25) = setpoints(340:364,2); 
   s2(1:25) = setpoints(340:364,3); 
% %  
   s1(26:100) = setpoints(26:100,2); 
   s2(26:100) = setpoints(26:100,3); 

%% -----------Plotting ------------
subplot(2,1,1)
%plot(setpoints(:,1), [setpoints(:,2) setpoints(:,3)]);
hold on 
plot((setpoints(:,1)./10), [s1 s2]);

plot((tank_resp(:,1)./10), [tank_resp(:,2) tank_resp(:,3)]);
hold off; 

subplot(2,1,2); 
plot((u(:,1)./10), [u(:,2)/1.21 u(:,3)/1.21]);

