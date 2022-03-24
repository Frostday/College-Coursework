clear
clc %% Basic Configuration done

%% Problem Setup :-
C = [0 0 5 3 0];
A = [1 0 3 5 15; 0 1 5 2 10];
BV = [1 2];
variables = {'s1','s2','x1','x2','sol'};

ZjCj = C(BV) * A - C;
ZCj = [ZjCj;A];
simp_table = array2table(ZCj);
simp_table.Properties.VariableNames(1:size(simp_table,2))=variables;
disp(simp_table);
run=1;
while(run)
ZC=ZjCj(1:end-1);
if any(ZC<0)
    fprintf('Not an Optimal Solution\n');
    [Entering,pivot_col]=min(ZC);
    fprintf("The entering variable is %d\n",pivot_col);
    Ratio=[];
    if all(A(:,pivot_col)<=0)
        fprintf("Unbounded Solution\n");
        run=0;
    else
    for i=1:size(A,1)
        if(A(i,pivot_col)>0)
            Ratio(i)=A(i,end)/A(i,pivot_col);
        else
            Ratio(i)=inf;
        end
    end
    [Leaving, pivot_row]=min(Ratio);
    fprintf("The leaving variable is %d\n",pivot_row);
    BV(pivot_row)=pivot_col;
    disp('The New Basic Variables are');
    disp(BV);
    pvt_key=A(pivot_row,pivot_col);
    A(pivot_row,:)=A(pivot_row,:)./pvt_key;
    for i=1:size(A,1)
        if i~=pivot_row
        A(i,:) = A(i,:) - A(i,pivot_col).*A(pivot_row,:);
        end
    end
    %ZjCj = ZjCj - ZjCj(pivot_col).*A(pivot_row,:);
    ZjCj = C(BV)*A - C;
    ZCj=[ZjCj;A];
    simp_table = array2table(ZCj);
    simp_table.Properties.VariableNames(1:size(simp_table,2))=variables;
    disp(simp_table);
    end
else
    fprintf('Optimal Solution\n');
    BFS=zeros(1,size(ZCj,2));
    BFS(BV)=A(:,end);
    BFS(end)=sum(C*BFS');
    Optimal_table=array2table(BFS);
    Optimal_table.Properties.VariableNames(1:size(Optimal_table,2))=variables;
    disp(Optimal_table);
    run=0;
end
end
