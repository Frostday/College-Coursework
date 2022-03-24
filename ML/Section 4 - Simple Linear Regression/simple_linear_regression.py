# Data Preprocessing Template

# Importing the libraries
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

# Importing the dataset
#dataset = pd.read_csv('Salary_Data.csv')
X = [1400,1600,1700,1875,1100,1550,2350,2450,1425,1700]
y = [245,312,279,308,199,219,405,324,319,255]
# Splitting the dataset into the Training set and Test set
#from sklearn.model_selection import train_test_split
#X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = 0.2, random_state = 0)

# Feature Scaling
"""from sklearn.preprocessing import StandardScaler
sc_X = StandardScaler()
X_train = sc_X.fit_transform(X_train)
X_test = sc_X.transform(X_test)
sc_y = StandardScaler()
y_train = sc_y.fit_transform(y_train.reshape(-1,1))"""


#Fitting simple linear regression to training set
from sklearn.linear_model import LinearRegression

regressor = LinearRegression()
regressor.fit(X,y)

y_pred = regressor.predict([[3000]])

#Plotting Regression with train values
plt.scatter(X,y,color = 'red')
plt.plot(X,regressor.predict(X),color='blue')
plt.title("Price vs Square Feet")
plt.xlabel("Square Feet")
plt.ylabel("House Price")
plt.show()

#Plotting Regression with test values


