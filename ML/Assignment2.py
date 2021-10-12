import numpy as np

# Question 1
arr = np.ones(10)*5
print(arr)


# Question 2
arr= np.arange(10,50)
print(arr)


# Question 3
arr = np.arange(10,51,2)
print(arr)


# Question 4
arr = np.arange(0,9).reshape(3,3)
print(arr)


# Question 5
arr=np.random.normal(0,1,25)
print(arr)


# Question 6
arr = np.arange(0,1,0.01)
print(arr)


# Question 7
arr=np.linspace(0,1,20)
print(arr)


# Question 8
arr = np.arange(1,26).reshape(5,5)
print(arr[2:5,1:5])
print(arr[0:3,1].reshape(3,1))
print(np.sum(arr))
print(np.sum(arr,axis=0))
print(np.sum(arr,axis=1))