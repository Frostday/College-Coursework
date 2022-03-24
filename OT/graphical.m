clear;
clc;
format rat

c1 = @(x1, x2) 2*x1+4*x2-8;
c2 = @(x1, x2) 3*x1+5*x2-15;
z = @(x1, x2) 3*x1+2*x2;

a = [2 4; 3 5; 1 0; 0 1];
b = [8; 15; 0; 0];

% plotting
n = size(a, 1);
x1 = 0:max(b);
colors = ['b', 'g', 'm', 'k', 'y', 'c'];
for i = 1:n
    x22 = (b(i) - a(i, 1).*x1)./a(i, 2);
    x2 = max(0, x22);
    plot(x1, x2, colors(i), 'linewidth', 2);
    hold on;
end

% all intersection points between any two constraints
points = [];
for i=1:n
    for j=i+1:n
        aa = [a(i, :); a(j, :)];
        bb = [b(i, :); b(j, :)];
        x = aa\bb;
        %x = inv(aa)*bb;
        if (x>=0)
            points = [points x]
        end
    end
end

% finding feasible points
fp = [];
costs = [];
for i=1:length(points)
    ptx1 = points(1, i);
    ptx2 = points(2, i);
    %ptx1, ptx2
    %c1(ptx1, ptx2)
    %c2(ptx1, ptx2)
    if (c1(ptx1, ptx2)<=0 && c2(ptx1, ptx2)<=0)
        points(:, i)
        fp = [fp points(:, i)];
        plot(ptx1, ptx2, '*r', 'markerSize', 8);
        hold on;
        cost = z(ptx1, ptx2);
        costs = [costs cost];
    end
end
fp
costs
final_ans = [fp(:, find(costs==max(costs)))' max(costs)]
