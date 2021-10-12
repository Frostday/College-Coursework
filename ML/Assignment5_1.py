import matplotlib.pyplot as plt
import numpy as np

def calculate_slope(x,y):
    #mean_y = sum(y)/len(y)
    mean_y = np.mean(y)
    mean_x = np.mean(x)
    var_0 = (y-mean_y)
    var_1 = (x-mean_x)
    num = 0
    for i in range(len(var_0)):
        num += (var_0[i] * var_1[i])
        
    denom = 0
    for i in range(len(var_0)):
        denom += (var_1[i] * var_1[i])
    
    m = num/denom
    return(m)


def calculate_intercept(x,y,m):
    c = np.mean(y) - (m*(np.mean(x)))
    return c

def main():
    x = np.array([1400,1600,1700,1875,1100,1550,2350,2450,1425,1700])
    y = np.array([245,312,279,308,199,219,405,324,319,255])
    #plt.scatter(x,y,marker = 'o')
    #plt.show()
    m = calculate_slope(x,y)
    print(m)
    c = calculate_intercept(x,y,m)
    print(c)

    y_test=[]
    x_test = [3000,2000,1500]
    for i in range(len(x_test)):
        y_test.append(m*x_test[i] + c)
    
    print(y_test)
    x2 = np.arange(100,3500)
    plt.plot(x2,x2*m+c,color='r')
    plt.scatter(x,y)
    plt.scatter(x_test,y_test,color = "g")
    plt.show()


if __name__ == "__main__":
    main()
