import numpy as np
from sklearn.linear_model import LinearRegression
import matplotlib.pyplot as plt
from scipy.stats import pearsonr
from sklearn.model_selection import train_test_split
import random


def correlation(X,y):
    for i in range(len(X)):
        print(pearsonr(X[i],y))
        
def using_model_with_random(x1,x2,x3,y):
    X=[]
    X.append(x1)
    X.append(x2)
    X.append(x3)
    #print(np.array(X).shape)
    #print(y.shape)
    plt.scatter(X[0],y,color='r')
    plt.show()
    plt.scatter(X[1],y,color='y')
    plt.show()
    plt.scatter(X[2],y,color='g')
    plt.show()
    
    #correlation(X, y)
    X= np.transpose(np.array(X))
    
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.20, random_state=42)
    model = LinearRegression()
    model.fit(X_train,y_train)
    y_result = model.predict(X_test)
    
    #print(y_test)
    #print(y_result)
    e=[]
    for i in range(len(y_test)):
        e.append((y_test[i]-y_result[i])**2)
    print("Error with random",sum(e)/len(e))
    
    print(model.intercept_)
    print(model.coef_)
    
    x_test1=1.5
    x_test2=5.8
    x_test3=4
    print("Output using Model with random approach",model.intercept_+model.coef_[0]*x_test1+model.coef_[1]*x_test2+model.coef_[2]*x_test3)
    
def using_model_without_random(x1,x2,y):
    X=[]
    X.append(x1)
    X.append(x2)
   
    #print(np.array(X).shape)
    #print(y.shape)
    
    plt.scatter(X[0],y,color='r')
    plt.show()
    plt.scatter(X[1],y,color='y')
    plt.show()
    
    #correlation(X, y)
    X= np.transpose(np.array(X))
    
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.20, random_state=42)
    model = LinearRegression()
    model.fit(X_train,y_train)
    y_result = model.predict(X_test)
    
    #print(y_test)
    #print(y_result)
    e=[]
    for i in range(len(y_test)):
        e.append((y_test[i]-y_result[i])**2)
    print("Error without random",sum(e)/len(e))
   
    print(model.intercept_)
    print(model.coef_)
    
    x_test1=1.5
    x_test2=5.8
    print("Output using Model without random approach",model.intercept_+model.coef_[0]*x_test1+model.coef_[1]*x_test2)

def step_by_step(X,y):
    X_transpose = np.transpose(X)
    #print(X_transpose.shape)
    b=np.dot(np.dot(np.linalg.inv(np.dot(X_transpose,X)),X_transpose),y)
    #print(b.shape)
    print(b)
    x_test1=1.5
    x_test2=5.8
    print("Output using step by step approach",b[0]+b[1]*x_test1+b[2]*x_test2)


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
    random.seed(10)
    x3=[]
    for i in range(24):
        x3.append(random.randint(0,10))
    #print(x2.shape)
    #print(x3.shape)
    #print(x3)
    X = np.array(generate_X(x1,x2))
    # print(X.shape)
    # print(y.shape)
    
    step_by_step(X,y)
    using_model_with_random(x1,x2,x3,y)
    using_model_without_random(x1,x2,y)
     
if __name__ == "__main__":
    main()
