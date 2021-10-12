import pandas as pd

df = pd.read_csv('AWCustomers.csv')
print(df.head())

print(df.info())

columns_to_keep = ['AddressLine1','AddressLine2','City','StateProvinceName','CountryRegionName',
                  'PostalCode', 'BirthDate','Education','Occupation','Gender','MaritalStatus','HomeOwnerFlag',
                  'NumberCarsOwned','NumberChildrenAtHome','TotalChildren','YearlyIncome']

new_df = df[columns_to_keep]
print(new_df.info())

# Checking Uniqueness
print(new_df.nunique())

# These columns rejected redundant to area which can be determined using Country 
new_df = new_df.drop(columns=['AddressLine1','AddressLine2','City','PostalCode', 'StateProvinceName'], axis=1)
print(new_df.info())

# Data Type of remaining selected columns finally:
    # Discrete: All except YearlyIncome
    # Nominal: CountryRegionName, Gender, MaritalStatus
    # Ordinal: Education, BirthDate, Occuptaion
    # Ratio: YearlyIncome, HomeOwnerFlag, NumberCarsOwned, NumberChildrenAtHome, TotalChildren
    # Interval: None

# Part 2 of Assignment
new_df['BirthDate']= pd.to_datetime(new_df['BirthDate'])
import datetime
present_day = datetime.datetime(2021, 8, 24)
def calculate_age(dob, current=present_day):
    ans=current-dob
    return ans.days//365


new_df['Age']=new_df['BirthDate'].apply(lambda a: calculate_age(a))
new_df.drop(['BirthDate'],axis=1,inplace=True)
print(new_df.head())


countries = pd.get_dummies(new_df['CountryRegionName'], drop_first=True)
new_df.drop(columns=['CountryRegionName'], axis=1, inplace=True)
new_df = pd.concat([countries,new_df], axis=1)
print(new_df.head())


print(new_df['Education'].value_counts())
print(new_df['Occupation'].value_counts())

new_df['Education']=new_df['Education'].map({'Bachelors':1,'Partial College':2,'High School':3,'Graduate Degree':4,'Partial High School':5})
new_df['Occupation']=new_df['Occupation'].map({'Skilled Manual':1,'Clerical':2,'Manual':3,'Management':4,'Professional':5})
print(new_df.head())


new_df['Male']=new_df['Gender'].map({'M':1,'F':0})
new_df.drop(['Gender'],axis=1,inplace=True)
new_df['MaritalStatus']=new_df['MaritalStatus'].map({'S':0,'M':1})
print(new_df.head())


from sklearn.preprocessing import MinMaxScaler

scaling_func = MinMaxScaler()
after_scaling = scaling_func.fit_transform(new_df[['YearlyIncome','Age']])
new_df['YearlyIncomeChanged']=after_scaling[:,0]
new_df['AgeChanged']=after_scaling[:,1]
new_df = new_df.drop(['YearlyIncome','Age'], axis=1)
print(new_df.head())


# Part 3 of Assignment

fin = new_df.corr()
print(fin)
