clc


%Pre Script Definitions 
fimath_obj = fimath();
fimath_obj.ProductMode = 'SpecifyPrecision'; 
fimath_obj.ProductWordLength = 16; 
fimath_obj.ProductFractionLength = 8; 



%This script demonstrates the functionality of fixed-point design 
%for implementation of a simple QP problem

%The Dataflow is like this 

% ADC (12-bit, unsigned integer between 0-4096) ---> ZeroPadder (16 bit
% signed number) --> Fixed Point Scaler (16 bit Q8.8 Number) ---> QP Solver
% (16bit Q8.8 number) --> Unscaler (16bit signed number) --> Saturator (12
% bit unsigned number) ---> DAC


%To start with, the ADC takes in am analog voltage in between 0-3.3V and
%returns a 12-bit binary integer between 0-4096
%The ADC can be considered as a gain of 1241, so 1 V input would be 1241 in
%binary 

x = 1241; 

%Assuming the number has been zero padded, we need to see what the effects
%of putting a Q8.8 interpretation on it

adc_interpretation = fi([],1,16,8,fimath_obj);

adc_interpretation.int = 1241; 

disp('Q8.8 Raw Interpretation of ADC Sample: ')
disp(adc_interpretation.Data); 


%In the case of the ADC output being 1241, the Q8.8 will give us a real
%interpretation of approximately 4.8. We need our fixed point
%representation to represent the original input analog voltage of 1 V, so
%we need to scale our fixed point number down to get an interpretation of
%1. We can do this by multiplying by a derived constant

const = 0.2066; 
const_fp = fi([],1,16,8,fimath_obj); 
const_fp.data = const;

scaled_adc_sample = const_fp * adc_interpretation; 


%We can see the resulting Q8.8 Interpretation of the sample after scaling
disp('Scaled ADC Q8.8 Interpretation: ')
disp(scaled_adc_sample.data)

%Omitting Fixed-Point QP implementation for now.. 

%The output of the QP needs to be de-scaled prior to being fed to the DAC.
%We can use the inverse of the scaling const we used earlier. We should get
%around 4.85 

descaler = 1/0.2066;
descaler_fi = fi([],1,16,8,fimath_obj); 
descaler_fi.data = descaler; 


descaled_output = descaler_fi * scaled_adc_sample; 

disp('De-scaled ADC Sample: ')
disp(descaled_output.data)

disp('De-scaled ADC Binary Integer: ')
disp(descaled_output.int);






