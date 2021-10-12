import matplotlib.pyplot as plt
import numpy as np

def generate_X(x1,x2):
    x=[]
    temp=[]
    for i in range(len(x1)):
        temp.append(1)
        temp.append(x1[i])
        temp.append(x2[i])
        x.append(temp)
        temp=[]
    return x
    
def main():
    y = np.array([1464,1394,1357,1293,1256,1254,1234,1195,1159,1167,1130,1075,1047,965,943,958,971,949,884,866,876,822,704,719])
    x1 = np.array([2.75,2.5,2.5,2.5,2.5,2.5,2.5,2.25,2.25,2.25,2,2,2,1.75,1.75,1.75,1.75,1.75,1.75,1.75,1.75,1.75,1.75,1.75])
    x2 = np.array([5.3,5.3,5.3,5.3,5.4,5.6,5.5,5.5,5.5,5.6,5.7,5.9,6,5.9,5.8,6.1,6.2,6.1,6.1,6.1,5.9,6.2,6.2,6.1])
    
    X = np.array(generate_X(x1,x2))
    plt.plot(x1,y)
    plt.plot(x2,y)
    plt.plot(x1,x2,y)   
    plt.show()
    print(X.shape)
    print(y.shape)
    
    X_transpose = np.transpose(X)
    print(X_transpose.shape)
    b=np.dot(np.dot(np.linalg.inv(np.dot(X_transpose,X)),X_transpose),y)
    print(b.shape)
    print(b)
    #According to question 
    x_test1=1.5
    x_test2=5.8
    
    print("Stock Index price for given scenario is: ",b[0]+b[1]*x_test1+b[2]*x_test2)
    
if __name__ == "__main__":
    main()
