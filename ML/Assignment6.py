from sklearn.datasets import load_iris

iris = load_iris()
print(iris.data)
print(iris.target)

a = iris.target.copy()
for i in range(len(a)):
    if(a[i]!=0):
        a[i]=5
print(a)

b = iris.target.copy()
for i in range(len(b)):
    if(b[i]!=1):
        b[i]=5
print(b)

c = iris.target.copy()
for i in range(len(c)):
    if(c[i]!=2):
        c[i]=5
print(c)


from sklearn.linear_model import LogisticRegression 
model1 = LogisticRegression(solver='liblinear', random_state=0) 
model2 = LogisticRegression(solver='liblinear', random_state=0) 
model3 = LogisticRegression(solver='liblinear', random_state=0) 

from sklearn.model_selection import train_test_split 
X_train, X_test, y_train, y_test = train_test_split(iris.data, a, test_size=0.20, random_state=42)
model1.fit(X_train,y_train)

from sklearn.model_selection import train_test_split 
X_train, X_test, y_train, y_test = train_test_split(iris.data, b, test_size=0.20, random_state=42)
model2.fit(X_train,y_train)

from sklearn.model_selection import train_test_split 
X_train, X_test, y_train, y_test = train_test_split(iris.data, c, test_size=0.20, random_state=42)
model3.fit(X_train,y_train)

y_result1 = model1.predict(X_test)
y_result2 = model2.predict(X_test)
y_result3 = model3.predict(X_test)
y_result = []

for i in range(len(X_test)):
    if(y_result1[i]!=5):
        y_result.append(y_result1[i])
    elif(y_result2[i]!=5):
        y_result.append(y_result2[i])
    else:
        y_result.append(y_result3[i])    

X_train, X_test, y_train, y_test = train_test_split(iris.data, iris.target, test_size=0.20, random_state=42)

print(y_test)
print(y_result)

Total_Predictions = len(y_test)
True_Predictions = 0
for i in range(len(y_test)):
    if(y_test[i]== y_result[i]):
        True_Predictions +=1
print("Total Predictions:", Total_Predictions)
print("True Predictions:", True_Predictions)

import matplotlib.pyplot as plt
plt.scatter(X_test[:,0],y_test,color='r')
plt.scatter(X_test[:,0],y_result,color='g')
plt.show()
plt.scatter(X_test[:,1],y_test,color='r')
plt.scatter(X_test[:,1],y_result,color='g')
plt.show()
plt.scatter(X_test[:,2],y_test,color='r')
plt.scatter(X_test[:,2],y_result,color='g')
plt.show()
plt.scatter(X_test[:,3],y_test,color='r')
plt.scatter(X_test[:,3],y_result,color='g')
plt.show()

model = LogisticRegression(multi_class='multinomial', solver='lbfgs', max_iter=1000)
model.fit(X_train,y_train)

y_res = model.predict(X_test)
print(y_res)
print(y_test)

True_Predictions1 = 0
for i in range(len(y_test)):
    if(y_test[i]== y_res[i]):
        True_Predictions1 +=1

print("Total Predictions:", Total_Predictions)
print("True Predictions:", True_Predictions1)

import matplotlib.pyplot as plt
plt.scatter(X_test[:,0],y_test,color='r')
plt.scatter(X_test[:,0],y_res,color='g')
plt.show()
plt.scatter(X_test[:,1],y_test,color='r')
plt.scatter(X_test[:,1],y_res,color='g')
plt.show()
plt.scatter(X_test[:,2],y_test,color='r')
plt.scatter(X_test[:,2],y_res,color='g')
plt.show()
plt.scatter(X_test[:,3],y_test,color='r')
plt.scatter(X_test[:,3],y_res,color='g')
plt.show()

import numpy as np
from sklearn.model_selection import KFold
from sklearn.model_selection import cross_val_score
cv = KFold(n_splits=4, random_state=1, shuffle=True)
scores = cross_val_score(model, X_test, y_test, scoring='accuracy', cv=cv, n_jobs=-1)
print('Accuracy: %.3f (%.3f)' % (np.mean(scores), np.std(scores)))
