from sklearn.datasets import load_iris
iris = load_iris()

x = iris.data
print(x)
y = iris.target
print(y)

from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test = train_test_split(x, y, test_size=0.2, random_state=42)
print(X_train)
print(X_test)
print(y_train)
print(y_test)

from sklearn.naive_bayes import GaussianNB
model = GaussianNB()
model = model.fit(X_train, y_train)
y_pred = model.predict(X_test)
print(y_pred)

from sklearn.metrics import confusion_matrix, accuracy_score, precision_score, recall_score, f1_score
print(confusion_matrix(y_test, y_pred))
print(f1_score(y_test, y_pred, average='macro'))

import numpy as np
TP = 0
TN = 0
FP = 0
FN = 0
y_test = np.array(y_test).reshape(-1, 1)
for i in range(len(y_pred)):
    if (y_test[i]==1 and y_pred[i]==1):
        TP = TP+1
    if (y_test[i]==1 and y_pred[i]==0):
        FN = FN+1
    if (y_test[i]==0 and y_pred[i]==1):
        FP = FP+1
    if (y_test[i]==0 and y_pred[i]==0):
        TN = TN+1

print("True Positive:", TP)
print("False Positive:", FP)
print("True Negative:", TN)
print("False Negative:", FN)

Accuracy = (TP+TN)/(TP+TN+FP+FN)
Recall = TP/(FN+TP)
Precision = TP/(FP+TP)
print("Accuracy Score:", Accuracy)
print("Recall Score:", Recall)
print("Precision Score:", Precision)
