# Question 1
s = "Hi there Class!"
s = s.split(" ")
print(s)


# Question 2
planet = "Earth"
diameter = 12742
print("The diameter of {} is {} kilometers.".format(planet, diameter))


# Question 3
lst = [1,2,[3,4],[5,[100,200,['hello']],23,11],1,7]
print(lst[3][1][2][0])


# Question 4
d = {'k1':[1,2,3,{'tricky':['oh','man','inception',{'target':[1,2,3,'hello']}]}]}
print(d['k1'][3]['tricky'][3]['target'][3])


# Question 5
def grab(x):
    print(x.split('@')[1])
    
x = "smittal1_be19@thapar.edu"
grab(x)


# Question 6
def check(s):
    for x in s.split():
        if x=='dog':
            return True
    return False

s= "Hey! Look there is a dog"
print(check(s))


# Question 7
def count(s):
    return s.count('dog')

s= "I had a dog dog dog dog"
print(count(s))


# Question 8
seq = ['soup','dog','salad','cat','great']
result = list(filter(lambda word: word[0] != 's', seq))
print(result)

    
# Question 9
def caught_speeding(speed,birthday):
    if (speed<=60 or (birthday and speed<=65)):
        return "No Challan"
    elif ((speed>=61 and speed<=80) or (birthday and speed>=61 and  speed<=85)):
        return "Small Challan"
    else:
        return "Heavy Challan"

print(caught_speeding(81,True))
print(caught_speeding(81, False))


# Question 10 (Referred from GeeksforGeeks)
list1 = ["M", "na", "i", "She"]
list2 = ["y", "me", "s", "lly"]
res = [i + j for i,j in zip(list1,list2)]
print (res)


# Question 11
list1 = ["Hello ", "take "]
list2 = ["Dear", "Sir"]
res=[]
for i in list1:
    for j in list2:
        res.append(i + j)
print(res)


# Question 12
list1 = [10, 20, [300, 400, [5000, 6000], 500], 30, 40]
list1[2][2].append(7000)
print(list1)


# Question 13 
list1 = [5, 20, 15, 20, 25, 50, 20]
for i in list1:
    if i==20:
        list1.remove(i)
print(list1)


# Question 14
d1 = {'a': 100, 'b': 200, 'c': 300}
x=0
for i in d1.values():
    if i == 200:
        x=1
        print("200 Exists")
if x==0:
    print("Not Found")


# Question 15
def sum(n):
    res=0
    for i in range(1,n+1):
        string=''
        for x in range(i):
            string = string + '2'
        res = res + int(string)
    return res
print(sum(int(input("Enter the value of n to find sum: "))))
