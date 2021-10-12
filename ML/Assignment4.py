from sklearn.datasets import load_digits
import pandas as pd
import numpy as np

digits = load_digits()
print(digits.data.shape)
print(digits.data)


df=pd.DataFrame(data=digits.data)
print(df.shape)

covariance_matrix=np.cov(df.T)
covariance_matrix.shape
print(covariance_matrix)
eigen_values , eigen_vectors = np.linalg.eigh(covariance_matrix)
print(eigen_values)

sorted_index = np.argsort(eigen_values)[::-1]
sorted_eigenvalue = eigen_values[sorted_index]
sorted_eigenvectors = eigen_vectors[:,sorted_index]
print(sorted_eigenvalue)

esum = sorted_eigenvalue.sum()
print(esum)
new_evalues = sorted_eigenvalue/esum * 100
print(new_evalues)

components = 0
sum=0
for i in range(len(new_evalues)):
    if(sum<=90):
        sum=sum+new_evalues[i]
        components+=1

print(components)

subset_eigen_vector = sorted_eigenvectors[:,0:components]
print(subset_eigen_vector.shape)

Reduced_digits = np.dot(digits.data,subset_eigen_vector)
print(Reduced_digits.shape)
print(Reduced_digits)
