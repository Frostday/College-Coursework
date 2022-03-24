clear
clc %% Basic Configuration done

%% Problem Setup :-
M = 1;
C = [0 0 0 0 -M 0];
Cf = [3 2 0 0 -M 0];
A = [1 1 1 0 0 2;1 3 0 1 0 3; 1 -1 0 0 1 1];
BV = [3 4 5];
AV = [5];
variables = {'x1','x2','s1','s2','a1','sol'};

ZjCj= C(BV) * A - C;
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
        A(i,:)=A(i,:) - A(i,pivot_col).*A(pivot_row,:);
        end
    end
    ZjCj = ZjCj - ZjCj(pivot_col).*A(pivot_row,:);
    ZCj=[ZjCj;A];
    simp_table = array2table(ZCj);
    simp_table.Properties.VariableNames(1:size(simp_table,2))=variables;
    disp(simp_table);
    end
else
    flag=0;
    for i=1:size(AV,2)
        for j=1:size(BV,2)
        if(BV(j)==AV(i))
             fprintf("Infeasible Solution\n");
             flag=1;
             break;
        end
        end
        if(flag)
            break;
        end
    end
    if(flag)
        run=0;
    else
    fprintf('Solution Exists\n');
    run=0;
    end
end
end

%% Phase-2 Begins
if(flag~=1)
  ZjCj= Cf(BV) * A - Cf;
  ZCj = [ZjCj;A];
  new_table = array2table(ZCj);
  new_table.Properties.VariableNames(1:size(new_table,2))=variables;
  disp(new_table);
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
            A(i,:)=A(i,:) - A(i,pivot_col).*A(pivot_row,:);
            end
        end
        ZjCj = ZjCj - ZjCj(pivot_col).*A(pivot_row,:);
        ZCj=[ZjCj;A];
        simp_table = array2table(ZCj);
        simp_table.Properties.VariableNames(1:size(simp_table,2))=variables;
        disp(simp_table);
        end
    else
    fprintf('Optimal Solution\n');
    BFS=zeros(1,size(ZCj,2));
    BFS(BV)=A(:,end);
    BFS(end)=sum(Cf*BFS');
    Optimal_table=array2table(BFS);
    Optimal_table.Properties.VariableNames(1:size(Optimal_table,2))=variables;
    disp(Optimal_table);
    run=0;
    end
  end
end
