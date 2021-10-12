import pandas as pd

df = pd.read_csv("./IrisDataset.csv")
print(df)
df['Species'] = df['Species'].map({'Iris-setosa': 1, 'Iris-versicolor': 2, 'Iris-virginica': 3})
print(df)

print(df['Species'].value_counts())
x_df = df.iloc[:, 0:4]
print(x_df)

y_df = df.iloc[:, 4:5]
print(y_df)

import seaborn as sns
import matplotlib.pyplot as plt
plt.subplots(figsize = (12, 5))
species_correlation = df.corr()
sns.heatmap(species_correlation, annot=True, cmap='RdPu')

from sklearn.model_selection import train_test_split
x_train, x_test, y_train, y_test = train_test_split(x_df, y_df, test_size=0.2, random_state=42)
print(x_train)
print(x_test)
print(y_train)
print(y_test)

from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import GridSearchCV

knn = KNeighborsClassifier()
k_range = []
for i in range(0, 50):
    if (i%2 != 0):
        k_range.append(i)
print(k_range)

param_grid = dict(n_neighbors=k_range) 
print(param_grid)

# Defining parameter range
grid = GridSearchCV(knn, param_grid, cv=10, scoring='accuracy', verbose=1)
print(grid)

# cv -> cross validation generator
# cv = 10 specifies 10 folds in k-fold cross validation
# scoring: Tells the strategy to evaluate the performance of the cross-validated model on the test set
# verbose = 1 will print some information about the progress during the execution
# Higher the value of verbose, more details it will print

# Fitting the model for grid search
grid_search = grid.fit(x_train, y_train.values.ravel())
print(grid_search)

print(grid_search.best_params_)

# best_score_ is the average of all cross validation folds for a single combination of the parameters specified in the param_grid
accuracy = grid_search.best_score_ *100
print(accuracy)

knn = KNeighborsClassifier(n_neighbors=11)
knn.fit(x_train, y_train.values.ravel())
y_pred = knn.predict(x_test) 
print(y_pred)

print(knn.score(x_test,y_test))

# Highly  Correlated so dropping and checking new results
df = df.drop(['PetalLength'], axis=1)
print(df)

x2 = df.iloc[:, 0:3]
print(x2)
y2 = df.iloc[:, 3:4]
print(y2)

x2_train, x2_test, y2_train, y2_test = train_test_split(x2, y2, test_size=0.2, random_state=42)
print(x_train)
print(x_test)
print(y_train)
print(y_test)

grid_search2 = grid.fit(x2_train, y2_train.values.ravel())
grid_search2
print(grid_search2.best_params_)

accuracy2 = grid_search2.best_score_ *100
print(accuracy2)

knn2 = KNeighborsClassifier(n_neighbors=7)
knn2.fit(x2_train, y2_train.values.ravel())
y2_pred = knn2.predict(x2_test) 
print(y2_pred)

print(knn2.score(x2_test,y2_test))
