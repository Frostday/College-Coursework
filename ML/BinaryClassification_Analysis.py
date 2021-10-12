import matplotlib.pyplot as plt

from sklearn.datasets import load_iris
iris = load_iris()
print(iris.data)

import numpy as np
x = np.arange(-100,100)

import math
y=[]

for i in range(len(x)):
    y.append(1/(1+ math.exp(-x[i])))

plt.scatter(x,y,color="yellow")
plt.show()
plt.plot(x,y,color="green")
plt.show()

import pandas as pd

data = pd.read_csv("https://raw.githubusercontent.com/johnmyleswhite/ML_for_Hackers/master/02-Exploration/data/01_heights_weights_genders.csv")
print(data)

from scipy.stats import pearsonr
print(pearsonr(data.Height,data.Weight))
# As both are 92% related We can be applying PCA to reduce it.

# Converting the Strings of Male and Female into 0 and 1 as Covariance of numbers can only be found.
data['Male']=data.Gender.map({'Male':1,'Female':0}) 
data.drop(['Gender'],axis=1,inplace=True) 
print(data)

from sklearn.linear_model import LogisticRegression 
model = LogisticRegression(solver='liblinear', random_state=0) 
from sklearn.model_selection import train_test_split 
x = data.iloc[:,0:2]
y = data.iloc[:,2:3]

print(x)
print(y)
X_train, X_test, y_train, y_test = train_test_split(x, y, test_size=0.20, random_state=42)

model.fit(X_train,y_train.values.ravel())
y_result = model.predict(X_test)
print(y_result)
print(y_test)

print('Model with Both Features', model.score(X_test,y_test))
print(model.coef_)
print(model.intercept_)
plt.scatter(data.Height,data.Male)
plt.show()
plt.scatter(data.Weight,data.Male)
plt.show()

# As both features are 92% correlated, Trying only with Height First and then only Weight
x = data.iloc[:,0:1]
y = data.iloc[:,2:3]
X_train, X_test, y_train, y_test = train_test_split(x, y, test_size=0.20, random_state=42)
model.fit(X_train,y_train.values.ravel())
y_result = model.predict(X_test)
print(y_result)
print(y_test)
print('Model with Height Features', model.score(X_test,y_test))

# Only weight
x = data.iloc[:,1:2]
y = data.iloc[:,2:3]
print(x.shape)
print(y.shape)
X_train, X_test, y_train, y_test = train_test_split(x, y, test_size=0.20, random_state=42)
model.fit(X_train,y_train.values.ravel())
y_result = model.predict(X_test)
print(y_result)
print(y_test)
print('Model with Weight Feature', model.score(X_test,y_test))

# Now Reducing the features as they are correlated by 92%

covariance_matrix = np.cov(np.transpose(data.iloc[:,0:2])) 
eigen_values, eigen_vectors = np.linalg.eigh(covariance_matrix) 
sorted_index = np.argsort(eigen_values)[::-1] 
sorted_eigenvalue = eigen_values[sorted_index] 
sorted_eigenvectors = eigen_vectors[:,sorted_index] 
subset_eigen_vector = sorted_eigenvectors[:,0] 
X = np.dot(data.iloc[:,0:2],subset_eigen_vector)
X = np.array(np.reshape(X,(-1,1)))
y = data.iloc[:,2:3]

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.20, random_state=42)
model.fit(X_train,y_train.values.ravel())
y_result = model.predict(X_test)
print(y_result)
print(y_test)
print('Model with Reduced Features', model.score(X_test,y_test))
plt.scatter(X,y)
plt.show()

# So in totality it accounts that:
# Using only Height feature gives 83.75% accuracy, 
# Using only Weight feature gives 90.9% accuracy,
# Using both individual features gives 92.45% accuracy,
# Using Reduced features gives 90.85% accuracy

# As individual feature might lead to underfitting, and both features will lead to more processing. 
# Therefore when correlation exists it is best to use reduced features for more accuracy and less processing.
