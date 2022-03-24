clear
clc
format short %% Basic Configuration done

%% Problem Setup
C=[1 2];
A=[-1 1;1 1];
B=[1;2];
m=size(B,1);
n=size(A,2);

%% Number of solutions
fprintf("No. of basic solutions %d\n",nchoosek(n,m));
v = nchoosek(1:n,m);
disp(v);

%% Feasible Solutions
if(n>=m)
solutions=[];
degen=[];
for i=1:size(v,1)
    a=A(:,v(i,:));
    y=zeros(n,1);
    x=a\B;
    if all(x>=0 & x~=inf & x~=-inf)
    y(v(i,:))=x;
    if any(x==0)
        degen=[degen y];
    end
    %disp(y(v(i,:)));
    solutions=[solutions y];
    end
end
else
    fprintf("Error, Number of constraints > No. of variables");
end
fprintf("Feasible Solutions\n");
disp(solutions');
Z = solutions' * C';
Table = [solutions' Z];
fprintf("Solutions and Values\n");
disp(Table)
fprintf("Degenerate Solutions\n");
disp(degen');
fprintf("\n");
[max_opt_value,index1] = max(Z);
[min_opt_value,index2] = min(Z);
%disp(index);
max_opt_soln =  solutions(:,index1);
min_opt_soln =  solutions(:,index2);
fprintf("Max Optimal Value is %d\n",max_opt_value);
fprintf("Max Optimal Solution is \n");
disp(max_opt_soln');
fprintf("Min Optimal Value is %d\n",min_opt_value);
fprintf("Min Optimal Solution \n");
disp(min_opt_soln');
